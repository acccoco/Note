sqlite

命令行 quick start：
https://www.sqlite.org/cli.html

.mode json 设置显示模式为 json
支持很多有用的格式。
例如 html 可以直接插入到网页；insert 输出的就是 sql 语句

.schema 命令可以输出 table 的模式，比如创建语句
创建了哪些索引等

.read 可以读取外部文件，例如读取一个 sql 脚本文件

.cd 可以改变工作文件夹

readfile('path') 可以读取文件为 blob，例如：
update table_name set img=readfile("123.png") where id=123;

writefile 可以将 blob 写入到目标文件中，例如：
select writefile("456.png", img) from table_name where id=123;

之后会输出一共写入了多少 bytes。

上面两个函数是 sqlite 特有的

----------------

sqlite 的特性

类型非常灵活：随便插入，不会报错
可以将 "1234" 插入到 integer 中，自动转换
将 "abcd" 插入 integer，则以 string 形式存储

创建表的时候甚至可以不用指定数据类型。

id：设置 integer primary key 即可，不要手动填充，sqlite 会自动分配一个独一无二的值。
手动插入的话，可以插入 null，sqlite 会自动选择一个数

---------------

索引
primary key 和 unique 都会自动创建索引
索引可以加快查询速度，降低修改速度

自用的话，应该还不需要索引吧。。。


------

trigger

例如：在一个表的某个字段发生更新时，自动更新另一个表的某些字段

-----------

多个进程

多个进程可以同时大概一个 sqlite 文件，可以多读，但是只有一个可以写成功。

-----------------

支持的数据格式

可以向 VARCHAR (10) 中插入任意多个字符串，且不会被截断。（动态类型）

注：字符串应该使用单引号

类型只有：NULL, INTEGER, REAL, TEXT, BLOB

https://www.sqlite.org/datatype3.html

------------------------

transaction

默认情况下，每个 insert 语句都是一个 transaction，意味着需要等待写入磁盘后 insert 才算完成。

性能水平：每秒 transaction 的级别在机械磁盘上大概是 100。

可以将多个 insert 语句包装为一个 transaction，这样每秒可以执行上万个 insert



----------------



