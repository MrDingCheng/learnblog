# 基础IO

### 文件接口

fread/fwrite/fopen/fclose库函数（使用FILE * 做参数）

read/write/open/close 系统调用（linux提供的比较底层的文件操作）（使用文件描述符作为参数）

find -name test.c 1> ~/out 2> ~/err把标准输出重定向到out，标准错误重定向到err

stdin&stdout&stderr

> * C默认打开三个输入输出流，分别是stdin、stdout、stderr
> * 这三个流的类型都是FILE*，fopen范围值类型，文件指针

fseek

> 根据文件指针的位置和偏移量来定位文件指针

```
int fseek(FILE * stream, long int offset, int origin);
```

> 返回文件指着相对于起始位置的偏移量

```
long int ftell(FILE * stream);
```

rewind

> 让文件指针的位置回到文件的起始位置

```
void rewind(FILE * stream)
```

可以认为，f#系列的函数，都是对系统调用的封装，方便二次开发

### 文件描述符fd

> open函数的返回值，文件描述符就是一个小整数

### 0&1&2

> * Linux进程默认情况下会有三个缺省打开的文件描述符，分别是标准输入0，标准输出1，标准错误2
> * 0，1，2对应的物理设备一般是：键盘，显示器，显示器 

##### 管理策略

> 每次打开一个文件的时候，会从文件描述符表的开始位置依次往后找，找到第一个空闲的下标位置，作为新的文件描述符

### 重定向

```
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h> 
#include <stdlib.h>
 
int main()
{
	//重定向，依赖操作系统的底层行为
	close(1);
	int fd = open("myfile", O_WRONLY|O_CREAT, 00644);
    if(fd < 0){
    	perror("open");
        return 1;
 	}
    printf("fd: %d\n", fd);
    fflush(stdout);
    close(fd);
    exit(0);
}

```

### 使用dup2系统调用

函数原型如下：

```
#include <unistd.h>
//将下标为oldfd的内容拷贝至下标为newfd
int dup2(int oldfd, int newfd);
```

### 动态库和静态库

##### 动态链接库

> 把一些.c/.cpp文件编译生成了一种特殊的二进制程序，自身不能直接执行，但是可以被其他的可执行程序调用
>
> 应用场景：客户端更新的时候不必更新整个程序，而是更新其中的一部分模块，其中的模块就是以动态库的方式组织的
>
> ldd查看依赖的动态库
>
> LD_LIBRARY_PATH 设定这个环境变量提醒系统去哪些目录中查找动态库

##### 静态链接库

> 把一些.o文件打包到一起生成了一种特殊的二进制程序，自身不能直接执行，但是可以和其他的.c/.cpp文件编译生成一个新的可执行程序，这个新的可执行程序就可以单独发布了
>
> 应用场景：发布小程序的时候，可以使用静态库的方式编译生成一个到哪都的可执行程序并且不依赖其他库。发布比较方便

##### Linux静态链接库命名规则：

lib前缀

.a后缀

```
//Makefile静态库
test:test.c libadd.a
	gcc $^ -o $@
libadd.a:add.c
	gcc -c add.c -o add.o
	ar -rc libadd.a add.o
```

```
//Makefile动态库
libadd.so:add.c
	gcc add.c -shared -fPIC -o libadd.so
```

