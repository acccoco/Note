TODO`LISTs` 还不知道怎么用
头文件位于： `sys/queue.h` 
该库函数全是宏定义，只需要头文件就能工作。该库不是 `posix` 标准的，源于 `BSD`  

可以通过 `man queue` 查看详细的说明和用法指引


#### `list` 的定义
支持的操作：

- 插入：在头部插入；在任意一个元素的后面插入
- 删除：删除任意一个元素
- 遍历：顺序遍历

链表结构的示意图：

- 当前链表的结构是单向链表， `le_prev` 的存在方便删除节点 

![[不活跃主题/Unix编程/数据结构/_attachments/1601197381226-fa90e775-2524-4d54-b02e-2e677dd121ae.png | 593]]

创建相关的操作：
```c
// 创建一个头节点
#define	LIST_HEAD(name, type)			\
struct name {							\
	struct type *lh_first;				\
}

// 初始化链表（头）
#define	LIST_INIT(head) do {			\
	(head)->lh_first = NULL;			\
} while (/*CONSTCOND*/0)

// 创建一个链表元素
#define	LIST_ENTRY(type)				\
struct {								\
	struct type *le_next;				\
	struct type **le_prev;				\
}

```


#### `list` 的使用
```c
// 链表节点的类型
struct entry {
        ...
        LIST_ENTRY(entry) entries;      /* List. */
        ...
}

// 创建一个头节点
LIST_HEAD(listhead, entry) head;

// 注：可以通过这种方式来引用头节点
struct listhead *headp;         /* List head. */

// 创建链表节点
 struct entry *n1, *n2, *np;

// 初始化链表（头）
LIST_INIT(&head);                       /* Initialize the list. */

// 在头部插入节点
n1 = malloc(sizeof(struct entry));      /* Insert at the head. */
LIST_INSERT_HEAD(&head, n1, entries);

// 在任意位置插入节点
n2 = malloc(sizeof(struct entry));      /* Insert after. */
LIST_INSERT_AFTER(n1, n2, entries);

// 遍历
for (np = head.lh_first; np != NULL; np = np->entries.le_next)
        np-> ...

// 删除元素
while (head.lh_first != NULL)           /* Delete. */
        LIST_REMOVE(head.lh_first, entries);
```

