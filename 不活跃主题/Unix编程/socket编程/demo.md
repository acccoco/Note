
#### IO复用的学习和练习
[[不活跃主题/Unix编程/socket编程/_attachments/echo_client_select.c]]
```c
/**
 * 说明：echo 程序的客户端
 * 命令行参数：[127.0.0.1]。如果没有参数，默认使用本地回环地址
 * 在输入EOF之后会半关闭：发送FIN
 * 使用select 来等待stdin的输入和sockfd的相应，可以处理批量输入
 */


#include "../unp.h"
void str_cli(FILE *fp, int sockfd);

int main(int argc, char** argv) {

    int sock_fd;        // 用于和服务器建立连接的套接字
    struct sockaddr_in servaddr;    // 服务器的地址结构
    char ipAddrStr[16] = "127.0.0.1";
    char* ipAddrStrPtr;

    /* 命令行读取服务器IP地址 */
    if (argc == 1)
        ipAddrStrPtr = ipAddrStr;
    else
        ipAddrStrPtr = argv[1];

    /* 准备连接套接字 */
    sock_fd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_port = htons(SERV_PORT);
    Inet_pton(AF_INET, ipAddrStrPtr, &servaddr.sin_addr);


    Connect(sock_fd, (struct sockaddr*) &servaddr, sizeof(servaddr));
    str_cli(stdin, sock_fd);

    exit(0);
}

/**
 * echo客户端的功能实现
 * 参数：fp表示一个文件指针，从该文件指针中读取数据发送到服务器
 * 参数：sockfd表示与服务器连接的套接字描述符
 */
void str_cli(FILE *fp, int sockfd)
{
    int maxfdp1;            // 最大文件描述符+1
    int stdineof;           // stdin是否已经到达了EOF
    fd_set rset;            // 需要select的文件描述符的集合
    char buf[MAXLINE];      // read 和 write 使用的缓冲
    int n;                  // 缓冲 buf 的有效长度

    stdineof = 0;
    FD_ZERO(&rset);
    for (;;) {

        /* 进行select */
        if (stdineof == 0)
            FD_SET(fileno(fp), &rset);
        FD_SET(sockfd, &rset);
        maxfdp1 = max(fileno(fp), sockfd) + 1;
        Select(maxfdp1, &rset, NULL, NULL, NULL);   // 时间设置为NULL，表示阻塞

        /* sockfd已经可以读了 */
        if (FD_ISSET(sockfd, &rset)) {
            if((n = Read(sockfd, buf, MAXLINE)) == 0) {
                if (stdineof == 1)
                    return;
                else
                    err_quit("str_cli: server terminated permaturely");
            }
            Write(fileno(stdout), buf, n);
        }
        
        /* fp的数据已经准备好了 */
        if (FD_ISSET(fileno(fp), &rset)) {
            if ((n = Read(fileno(fp), buf, MAXLINE)) == 0) {
                stdineof = 1; 
                Shutdown(sockfd, SHUT_WR);  // 半关闭，不再写了，向服务器发送FIN
                FD_CLR(fileno(fp), &rset);
                continue;
            }
            Writen(sockfd, buf, n);
        }
    }
}
```

[[不活跃主题/Unix编程/socket编程/_attachments/echo_server_poll.c]]
```c
#include "../unp.h"
# define OPEN_MAX 256       // <limits.h>中并没有OPEN_MAX的定义

/**
 * echo服务器
 * 单线程使用 poll 来处理多个连接
 * 使用 client 数组表示关心的xx
 */

int main(int argc, char**argv) {

    struct pollfd client[OPEN_MAX];
    int sockfd;                     // client 数组中的元素
    int i;                          // client 数组的临时下标
    int clientMaxValid_i;           // client 数组中有效连接的最大下标
    int nready;                     // select 返回后，准备好的描述符的数量
    
    char buffer[MAXLINE];           // 存放临时数据的数组
    ssize_t bufferSize;             // 临时数据的大小

    int connfd;                     // listen 到的新连接
    int listenfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    /* 服务器Listen */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    /* 初始化 client 集合 */
    client[0].fd = listenfd;
    client[0].events = POLLRDNORM;      // 关心 listenfd 是否可读
    for (i = 1; i < OPEN_MAX; i++)
        client[i].fd = -1;      // -1 表示poll不关心的描述符/无效的描述符
    clientMaxValid_i = 0;

    for (;;) {
        nready = Poll(client, clientMaxValid_i + 1, INFTIM);    // INFTIM表示无限阻塞
        /* 每次只会监听最多一个连接请求，和若干个客户端数据发送 */

        /* 监听到了客户端的连接请求 */
        if (client[0].revents & POLLRDNORM) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);

            /* 将客户端的sockfd 加入到 client集合中 */
            for (i = 0; i < OPEN_MAX; i++) {
                if (client[i].fd < 0) {
                    client[i].fd = connfd;
                    break;
                }
            }
            if (i == OPEN_MAX)
                err_quit("too many clients");

            /* 让 poll 关心这个sockfd */
            client[i].events = POLLRDNORM;
            if (i > clientMaxValid_i)
                clientMaxValid_i = i;

            if (--nready <= 0)
                continue;
        }

        /* 客户端发来了数据 */
        for (i = 0; i <= clientMaxValid_i; i++) {     // 遍历整个client集合，才能找到是哪一个客户端发来了数据
            sockfd = client[i].fd;
            if (sockfd < 0)
                continue;
            if (client[i].revents & (POLLRDNORM | POLLERR)) {
                bufferSize = Read(sockfd, buffer, MAXLINE);

                /* 客户端连接出现了错误 */
                if (bufferSize < 0) {
                    if (errno == ECONNRESET) {
                        Close(sockfd);
                        client[i].fd = -1;
                    }
                }

                /* 客户端连接 EOF */
                else if (bufferSize == 0) {
                    Close(sockfd);
                    client[i].fd = -1;
                }
                else
                    Writen(sockfd, buffer, bufferSize);

                if (--nready <= 0)
                    break;
            }
        }
    }
}
```


[[不活跃主题/Unix编程/socket编程/_attachments/echo_server_select.c]]
```c
#include "../unp.h"

/**
 * echo服务器
 * 单线程使用select来处理多个连接
 * 使用client数组，存放已经建立连接的sockfd
 * 使用allset/rset，存放需要select - read的集合：包括一众客户端sockfd，以及服务器的listen sockfd
 */

int main(int argc, char**argv) {

    int client[FD_SETSIZE];         // 已经建立连接的客户端的 sockfd 的集合；-1表示没有使用
    int sockfd;                     // client 数组中的元素
    int i;                          // client 数组的临时下标
    int clientMaxIndex;             // client 数组中有效连接的最大下标

    fd_set rset;                    // 需要select 的一系列描述符。包括listen sockfd，以及客户端连接的 sockfd
    fd_set allset;                  // allset 是 rset 第一个副本。因为rset可能会被select函数改变
    int maxfd;                      // rset/allset 集合中最大的描述符编号
    int nready;                     // select 返回后，准备好的描述符的数量
    
    char buffer[MAXLINE];           // 存放临时数据的数组
    ssize_t bufferSize;             // 临时数据的大小

    int connfd;                     // listen 到的新连接
    int listenfd;
    socklen_t clilen;
    struct sockaddr_in cliaddr, servaddr;

    /* 服务器Listen */
    listenfd = Socket(AF_INET, SOCK_STREAM, 0);
    bzero(&servaddr, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
    servaddr.sin_port = htons(SERV_PORT);
    Bind(listenfd, (SA*)&servaddr, sizeof(servaddr));
    Listen(listenfd, LISTENQ);

    /* 初始化各个集合 */
    maxfd = listenfd;
    clientMaxIndex = -1;
    for (i = 0; i < FD_SETSIZE; i++) 
        client[i] = -1;
    FD_ZERO(&allset);
    FD_SET(listenfd, &allset);


    for (;;) {
        rset = allset;
        nready = Select(maxfd + 1, &rset, NULL, NULL, NULL);
        /* 每次只会监听最多一个连接请求，和若干个客户端数据发送 */

        /* 监听到了客户端的连接请求 */
        if (FD_ISSET(listenfd, &rset)) {
            clilen = sizeof(cliaddr);
            connfd = Accept(listenfd, (SA*)&cliaddr, &clilen);

            /* 将客户端的sockfd 加入到 client集合中 */
            for (i = 0; i < FD_SETSIZE; i++) {
                if (client[i] < 0) {
                    client[i] = connfd;
                    break;
                }
            }
            if (i == FD_SETSIZE)
                err_quit("too many clients");

            /* 将客户端的 sockfd 加入 allset集合中。同时更新maxfd，maxi */
            FD_SET(connfd, &allset);
            if (connfd > maxfd)
                maxfd = connfd;
            if (i > clientMaxIndex)
                clientMaxIndex = i;

            if (--nready <= 0)
                continue;
        }

        /* 客户端发来了数据 */
        for (i = 0; i <= clientMaxIndex; i++) {     // 遍历整个client集合，才能找到是哪一个客户端发来了数据
            sockfd = client[i];
            if (sockfd < 0)
                continue;
            if (FD_ISSET(sockfd, &rset)) {
                bufferSize = Read(sockfd, buffer, MAXLINE);
                if (bufferSize == 0) {
                    Close(sockfd);
                    FD_CLR(sockfd, &allset);
                    client[i] = -1;
                }
                else
                    Writen(sockfd, buffer, bufferSize);

                if (--nready <= 0)
                    break;
            }
        }
    }
}
```


#### 简单的echo服务器和客户端

- 服务器将收到的内容反射回客户端

- 服务器使用子进程来处理多个连接


[[不活跃主题/Unix编程/socket编程/_attachments/echo_client.c]]
[[不活跃主题/Unix编程/socket编程/_attachments/echo_server.c]]
