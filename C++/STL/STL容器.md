### STL容器
| 容器 | 类型 | 特点 |
| --- | --- | --- |
| vector | 序列容器：动态数组 | 元素连续，容量会自动收缩和扩张 |
| deque | 序列容器：双端队列 | 分段数组实现 |
| list | 关联容器：双向链表 | 双向链表实现 |
| set | 关联容器：集合 | 红黑树实现；元素有序，不重复 |
| map | 关联容器：键值对 |  |
| multiset | 集合 | 允许重复元素 |
| multimap |  |  |
| unordered_set | 集合 | 散列实现 |
| unordered_map | 键值对 | 散列实现 |


#### `**deque<Key>**`
顺序的双端队列
实现方式是：多个顺序表
![[C++/STL/_attachments/双端队列deque.PNG.png|400]]

#### `**unordered_set<Key, Hasher, Equal>**`
这是一个通过散列实现的集合容器，元素不能重复。可以自己提供散列函数和比较函数。
通过仿函数提供散列方法和比较方法：`Hasher`和`Equal`
```cpp
struct Hasher {
	int operator()(const char c) {
    	return c - 'a';
    }
};
```

### 迭代器
##### **以**`**vector**`**为例**
![[C++/STL/_attachments/1600055251208-4c174392-4781-4665-b3bb-2237b9fb02c9.png|400]]

##### 在循环中删除迭代器指向的元素
```cpp
vector<int> a = { 0, 1, 2, 3, 4, 5 };
for (auto it = a.begin(); it != a.end();)
	if (*it == 3)
    	it = a.erease(it);
    else
    	++it;
```

- `erase`返回指向下一个元素的迭代器，应该使用这个返回值来覆盖原来的迭代器。

### 适配器
| 适配器 | 类型 | 特点 |
| --- | --- | --- |
| stack | 栈 | 将任何序列容器转化为栈；默认`deque` |
| queue | 队列 | 将任何序列容器转化为队列，默认`deque` |
| priority_queue | 优先队列 | 序列容器转化为优先队列 |

