
## 交互式命令
通过命令 `sqlite3 <file_name.db>` 连接到数据库（文件）
直接使用 `sqlite3` 将连接到暂时的内存数据库

然后可以使用如下的命令：

- `.open <file_name.db>`：连接到其他数据库，或创建新的数据库
- `.databases`：查看当前处于哪个数据库
- `.tables` ：当前数据库有哪些表
- `.schema <table_name>`：查看表的详细信息

也可以直接使用 SQL 语句


## 数据库
一个文件就是一个数据库，可以使用命令 `.open <file_name.db>` 创建


## 存储类型

- `NULL`
- `INTEGER`：有符号整数，存在1，2，3，4，6，8字节
- `REAL`：浮点，8位IEEE浮点
- `TEXT`：字符串
- `BLOB`

以上是 sqlite3 的实际存储类型，在使用 SQL 语句时，可以用 `INT`，`CHAR(50)` 等，实际存储都会进行转换


## 表的操作

CREATE
```sqlite
create table test_table(
    id INT PRIMARY KEY NOT NULL,
    name TEXT NOT NULL,
    ADDRESS CHAR(50)
);
```

ALTER
DROP：
```sqlite
DROP TABLE [db.]<table>
```


## 记录的操作
INSERT：
```sqlite
INSERT INTO <table> [(col1, col2, ...)] VALUES (val1, val2, ...);
```

UPDATE
DELETE
SELECT
```sqlite
SELECT * FROM <table>;
SELECT <col1, col2, ...> FROM <table>;
```
