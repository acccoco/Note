### 打开文件
相关的函数为：`fstream.open(path, mod)`

其中`mod`表示文件的打开方式，可以使用或运算进行组合：

| `ios::in` | 读 |
| --- | --- |
| `ios::out` | 写 |
| `ios::ate` | 文件打开后定位到文件末尾。 |
| `ios::app` | 写入都追加到文件末尾。 |
| `ios::trunc` | 忽略已存在的文件内容 |
| `ios::binary` | 二进制方式打开 |


### 判断文件是否存在
```cpp
fstream file;
file.open(path, mod, prot);
if (!file) {
	cout << "文件不存在" << endl;
}
```

- 或者使用`is_open()`函数判断

### 创建文件
```cpp
fstream file;
file.open(path, std::ios::out);
fs.close();
```

### 从文件中读取行
```cpp
int main() {
    std::fstream fs;
    fs.open("../test.txt", std::ios::in);
    std::string str;
    while (std::getline(fs, str)) {
        std::cout << str << std::endl;
    }
    fs.close();
}
```
