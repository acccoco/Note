
#### server
首先编辑配置文件：`/etc/exports`，直接使用最不安全的配置即可，`-ro`表示只读
```
/dir/share -ro
```

然后是开启服务进程：
```shell
sudo nfsd start
```


#### client
挂载就可以用了：
```shell
mount -t nfs <ip>:/dir/server /dir/mount
```


#### 注意
最好在同一个网段，也就是 `255.255.255.0`
