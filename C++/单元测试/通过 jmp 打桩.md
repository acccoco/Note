#### 测试打桩的方法
测试打桩常用有两种方法：

1. 通过宏定义来实现
2. 通过 `jmp` 指令来实现

#### 通过 `jmp`  实现打桩
实现代码如下：
```c
#define JMP_LEN 5
#define JMP_INS 0xe9     // 该jmp指令的操作数是相对地址
typedef char backup_t[JMP_LEN];

/**
 * 在运行期间打桩
 * @param [in]old_func 旧的函数
 * @param [in]new_func 新的函数
 * @param [out]backup 用于备份旧的函数的入口指令
 */
void install_stub(void *old_func, void *new_func, backup_t *backup)
{
    char jmp_cmd[JMP_LEN] = {0};
    unsigned offset = 0;      // 新旧函数相对地址
    void *page_addr;
    int ret = 0;
    
    /* 将函数入口所在页设为可读可写可执行 */
    page_addr = (void*)((uint64_t)old_func & ~(getpagesize() - 1));
    ret = mprotect(page_addr, getpagesize(), PROT_WRITE | PROT_READ | PROT_EXEC);
    if (ret) {
        fprintf(stderr, "mprotect failed.\n");
    }

    /* 替换入口指令 */
    jmp_cmd[0] = JMP_INS;
    offset = (unsigned long)new_func - (unsigned long)old_func - JMP_LEN;
    memcpy(&jmp_cmd[1], &offset, sizeof(offset));
    memcpy(*backup, old_func, JMP_LEN);
    memcpy(old_func, jmp_cmd, JMP_LEN);
}
```


#### 运行时打桩是否破坏调用关系
结论是：不会
原因：**「主调函数」只有在 **`**call**`**语句中会出现「被调函数」的地址；「被调函数」谁都能调用，完全和「主调函数」无关**；

首先看下简单的调用关系。对于如下代码：
```c
int foo(int a) {
	...
}
int main() {
	int res = foo(7);
}
```

汇编代码如下：( `gcc -S -O0 -m32` )
```
foo:
    pushl 	%ebp
    movl  	%esp, %ebp
    subl    $16,  %esp		# 申请栈空间
    ...
    leave                   # 释放栈空间，等价于：movl  %ebp, %esp;  pop  %ebp
    ret                     # 等价于：pop  %eip
main:
	pushl  	    $7	        # 传参
    call		foo			# 等价于：pushl  %eip, %esp; movl $foo, %eip
```

从上面的汇编代码可以得知：
函数调用者将**返回地址写到栈里面**；函数被调者在返回时只需要**将返回地址从栈中拿出**即可

因此，通过 `jmp` 进行打桩，不会对函数的调用关系产生影响

