

## target

cmake 的核心是 target

例如，有以下语句：

```cmake
target_include_directories(<target_name> PUBLIC <include_dir>)
```

那么其他 target，只要 link 了这个 target，就可以直接使用这个 target 的头文件

```cmake
target_link_libraries(main <lib-name>)
```


PRIVATE 和 PUBLIC

这两个选项一般是出现在和 target 相关的命令中的，表示当前 target 是否向外暴露某些内容

```cmake
# 其他的 target，如果 link 了 lib1，可以使用 lib1 的 include
add_library(lib1 <src_files>)
target_include_directories(lib1 PUBLIC <public_include>)

# 其他的 target，如果 link 了 lib2，无法使用 lib1 的 include
add_library(lib2 src/main.cpp)
target_link_libraries(lib2 PRIVATE lib1)
```


## 项目

项目的好处是，能够通过项目来控制依赖和包含的层级

```cmake
project(<name>)
```

考虑层级项目的情况，有这些内建变量

```cmake
# top project 相关的
CMAKE_PROJECT_NAME
CMAKE_SOURCE_DIR / CMAKE_BINARY_DIR

# 当前 project 相关的
PROJECT_NAME
CMAKE_CURRENT_SOURCE_DIR / CMAKE_CURRENT_BINARY_DIR
PROJECT_SOURCE_DIR / PROJECT_BINARY_DIR

# 一般用于 top project 引用 sub project
<name>_SOURCE_DIR / <name>_BINARY_DIR
```

可以通过以下命令来执行子 project 的构建：

```cmake
add_subdirectory(<dir-name>)
```


## 创建变量

```cmake
# set
set(<var-name> main.cpp)

# list：可以很方便地追加
list(APPEND <var-name> 1.cpp 2.cpp)

# file：专用于文件。该语句相比于 set 的好处就是，支持通配符搜索
file(GLOB SOUR_FILES "src/*.cpp")
```


## 变量注入

```cmake
configure_file(xxx.h.in ${PROJECT_BINARY_DIR}/xxx.h)
```

在文件中，可以以这种形式

```cpp
// xx.h.in
const char *var_1 = "${CMAKE_SOURCE_DIR}";
const char *var_2 = "@CMAKE_SOURCE_DIR@";
```

还可以注入宏定义

```cmake
add_definitions(-DSOURCE_PATH="${PROJECT_SOURCE_PATH}")
```


## 编译选项

通过 `target_compile_definitions` 可以为每个 target 指定宏定义：

```cmake
# 为 target foo 添加 # define FOO 1 的宏定义
target_compile_definitions(foo PUBLIC FOO=1)
```

通过 `CMAKE_CXX_FLAGS` 可以为所有变量设置宏定义

```cmake
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -DEX2")
```

**指定编译器**

可以通过 `CMAKE_C_COMPILER` 和 `CMAKE_CXX_COMPILER` 指定编译器


**指定链接器**

通过 `CMAKE_LINKER` 指定链接器

**指定 C++ 标准**

```cmake
# 方法1
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --std=c++17")
# 方法2
set (CMAKE_CXX_STANDARD 17)
```

**指定编译的类型**

cmake 内置了一些 build type，设置了之后，在编译时自动添加 flag

```cmake
Release             # -O3 -DNDEBUG
Debug               # -g
MinSizeRel          # -Os -DNDEBUG
RelWIthDebInfo      # -O2 -g -DNDEBUG
```

涉及到的变量是：`CMAKE_BUILD_TYPE`


## 头文件

如果需要引用的头文件不在环境变量，也不在当前项目中，可以通过以下指令来设置

**设置全局的头文件目录**

```cmake
include_directories(<路径>)
```

**分别为每个 target 设置头文件路径，还可以控制可见性**

```cmake
target_include_directories(<target> [PRIVATE | INTERFACE | PUBLIC]
    <include-dir>
)
```


## 纯头文件的库

有一些库只有头文件，没法生成静态库文件或动态库文件，如何来生成 target 呢？

可以通过 INTERFACE 来生成 target

```cmake
add_library(<header-lib> INTERFACE)
```

把头文件包含进去

```cmake
target_include_directories(<header-lib> INTERFACE
    ${PROJECT_SOURCE_DIR}/include
)
```

这样的库，make 之后并不会生成动态链接或静态链接文件

其他 target 要使用，就像使用动态库或静态库一样

```cmake
target_link_libraries(main <header-lib>)
```


## 生成静态库

```cmake
add_library(<lib-name> STATIC lib.cpp)
target_include_directories(<lib-name> PUBLIC
    <static-lib>/include
)
```

其中，PUBLIC 的 `target_include_directories` 可以将该 target 的头文件暴露给 link 到该 target 的其他 target


## 为库指定别名

可以为 library 指定别名

```cmake
add_library(hello_library SHARED 
    src/Hello.cpp
)
add_library(hello::library ALIAS hello_library)
```


## 使用第三方库

`find_package` 会首先搜索 `CMAKE_MODULE_PATH` 路径，找到名为 `FindXXX.cmake` 的文件

cmake 会自带一些有名的库的 `FindXXX.cmake` 文件

```cmake
find_package(<pkg-name> 1.46.1 REQUIRED
    COMPONENTS <component-1> <component-2>
)
```

- REQUIRED 表示：如果找不到对应的包，就报错
- COMPONENTS 选项后面会跟随需要的一些组件。组件好像是库的别名

对于第三方库，会通过 Config 模式搜索，找到名为 `XXXConfig.cmake` 的文件

包会导出一些变量，比如：

```cmake
xxx_FOUND
xxx_INCLUDE_DIRS
xxx_LIBRARIES
```

很多包都会为头文件，库等设置别名，例如：(这些变量都是**只读**的)

```cmake
# 使用别名
target_link_ligraries(hello_world PRIVATE
    Boost::filesystem            
)

# 不使用别名
target_link_ligraries(hello_world PRIVATE        
    ${Boost_SYSTEM_LIBRARY}     
)
```


## 链接

指定链接文件的搜索目录

```cmake
link_directories(<dir>)
```

也可以为特定 target 指定

```cmake
target_link_directories(<target> PRIVATE
    <dir>
)
```

将库连接到目标

```cmake
target_link_libraries(<target> <lib>)
```


## 指定最终生成的文件位置

默认情况下，target 会在 `PROJECT_BINARY_DIR` 目录下，也就是执行 cmake 命令的目录，一般是 `build/` 目录

可以通过修改两个内建变量来指定其他目录

```cmake
set(EXECUTABLE_OUTPUT_PATH <可执行二进制文件的位置>)
set(LIBRARY_OUTPUT_PATH <动态库和静态库文件的位置>)
```


## install

make 编译完成后，可以根据 cmake 的配置来执行 `make install` 将相关文件安装到特定目录下

执行 `make install` 后，会生成 `install_manifest.txt` 文件，里面包含了安装的细节

通过指定 `CMAKE_INSTALL_PREFIX` 变量来指定安装的目录

可以在 cmake 命令时指定该变量：

```shell
cmake -DCMAKE_INSTALL_PREFIX=/tmp/usr ..
```

例子：

```cmake
# 将文件夹安装到 ${CMAKE_INSTALL_PREFIX}/include 目录下
install (DIRECTORY ${PROJECT_SOURCE_DIR}/include/
    DESTINATION include)

install (FILES README.md
    DESTINATION share/doc/cmake/hello)
install (PROGRAMS runhello.sh
    DESTINATION bin)

# 将名为 hello 的 target 安装到 ${CMAKE_INSTALL_PREFIX}/bin 目录下
install (TARGETS hello
    DESTINATION bin)
```

uninstall 需要手动去做，一个简单的方法就是：

```shell
sudo xargs rm < install_manifest.txt
```


## 单元测试

cmake 支持单元测试，可以将某个 target 指定为测试 target

按照如下方式编写，就可以通过 `make test` 执行单元测试

```cmake
enable_testing()
add_excutable(<ut-target> ...)
add_test(<ut-name> <ut-target>)
```


## 打包

cmake 支持以特定形式发布 pkg，以 deb 环境下 为例

```cmake
set(CPACK_GENERATOR "DEB")
include(CPack)
set(CPACK_DEBIAN_PACKAGE_MAINTAINER "charvl")
set(CPACK_PACKAGE_VERSION "0.0.1")
```

在打包之前，需要在 cmake 中做好 install 相关的配置

之后，只需要执行 `make package` 即可打包

