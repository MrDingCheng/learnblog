# 高级IO

### 五种IO模型

> * 阻塞IO：在内核将数据准备好之前，系统调用会一直等待，所有的套接字，默认都是阻塞方式
> * 非阻塞IO：如果内核还未将数据准备好，系统调用仍然会直接返回，并且返回EWOULDBLOCK错误码（需要轮询）
> * 信号驱动IO：内核将数据准备好的时候，使用SIGIO信号通知应用程序进行IO操作
> * IO多路转接：虽然从流程上看起来和阻塞IO类似，但IO多路转接能够同时等待多个文件描述符的就绪状态
> * 异步IO：由内核在数据拷贝完成时，通知应用程序（而信号驱动是告诉应用程序何时可以开始拷贝数据）

### 同步通信：

发出一个调用时，在没有得到结果之前，该调用就不返回。但是一旦调用返回，就得到返回值了，即调用者主动等待这个调用的结果

### 异步通信

当一个异步过程调用发出后，调用者不会立刻得到结果，而是在调用发出后，被调用者通过状态、通知来通知调用者，或通过回调函数处理这个调用

### 阻塞

阻塞调用指调用结果返回之前，当前线程会被挂起。调用线程只有在得到结果之后才会返回

### 非阻塞

非阻塞调用指在不能立刻得到结果之前，该调用不会阻塞当前线程

### 非阻塞IO

#### fcntl

int fcntl(int fd, int cmd, .../*arg */)

传入的cmd的值不同，后面追加的参数也不相同

fcntl函数由五种功能：

> * 复制一个现有的描述符（cmd=f_DUPFD）
> * 获得/设置文件描述符标记（cmd=F_GETFD或F_SETFD）
> * 获得/设置文件状态标记（cmd=F_GETFL或F_SETFL)
> * 获得/设置异步I/O所有权（cmd=F_GETOWN或F_SETOWN）
> * 获得/设置记录锁（cmd=F_GETLK,G_SETLK或F_SETLKW)

#### 实现函数SetNoBlock

```
void SetNoBlock(int fd){
    int fl = fcntl(fd,F_GETFL);
    if (fl<0){
        perror("fcntl");
        return;
    }
    fcntl(fd,F_SETFL,fl|O_NONBLOCK);
}
int main(){
    SetNoBlock(0);
    while(1){
        char buf[1024] = {0};
        ssize_t read_size = read(0,buf,sizeof(buf)-1);
        if(read_size < 0){
            perror("read");
            sleep(1);
            continue;
        }
        printf("input:%s\n",buf);
    }
    return 0;
}

```

### I/O多路转接之select

* select系统调用是用来让我们的程序监视多个文件描述符的状态变化的
* 程序会停在select这里等待，直到被监视的文件描述符有一个或多个发生了状态改变

#### select函数原型

int select(int nfds, fd_set *readfds,fd_set *writefds, fd_set* exceptfds, struct timeval* timeout)

**参数解释：**

> * 参数nfds是需要监视的最大的文件描述符+1
> * rdset,wrset,exset分别对应于需要检测的可读文件描述符的集合，可写文件描述符的集合及异常文件描述符的集合
> * 参数timeout为结构timeval，用来设置select()的**等待时间**

**参数timeout取值**：

> * NULL：则表示select（）没有timeout，select将一直被阻塞，直到某个文件描述符上发生了事件
> * 0：仅检测描述符集合的状态，然后立即返回，并不等待外部事件的发生
> * 特定的时间值：如果在指定的时间段里没有事件发生，select将超时返回

#### select特点

* 可监控的文件描述符个数取决与sizeof(fd_set)的值
* 将fd加入select监控集的同时，还要再使用一个数据结构array保存到select监控集中的fd
  * 一是用于在select返回后，array作为源数据和fd_set进行FD_ISSET判断。
  * 二是select返回后会把以前加入的但并无事件发生的fd清空，则每次开始select前都要重新从array取得fd逐一加入（FD_ZERO最先），扫描array的同时取得fd最大值maxfd，用于select的第一个参数

#### select的缺点

> * 每次调用select，都需要手动设置fd集合，从接口使用角度来说非常不便
> * 每次调用select，都需要把fd集合从用户态拷贝到内核态，这个开销在fd很多时会很大
> * 同时每次调用select都需要在内核遍历传递进来的所有fd，这个开销在fd很多时也很大
> * select支持的文件描述符数量太小

### I/O多路转接之epoll

#### epoll_create

```
int epollc_create(int size)
```

创建一个epoll的句柄

> * 自从Linux2.6.8之后，size参数是被忽略的
> * 用完之后，必须用close()关闭

#### epoll_ctl

```
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event)
```

epoll的事件注册函数

> * 它不同于select()是在监听事件时告诉内核要监听什么类型的事件，而是在这里先注册要监听的事件类型
> * 第一个参数是epoll_create()的返回值（epoll的句柄）；
> * 第二个参数表示动作，用三个宏来表示
>   * EPOLL_CTL_ADD:注册新的fd到epfd中
>   * EPOLL_CTL_MOD:修改已经注册的fd的监听事件
>   * EPOLL_CTL_DEL：从epfd中删除一个fd
> * 第三个参数是需要监听的fd
> * 第四个参数是告诉内核需要监听什么事，可以是以下几个宏的集合
>   * EPOLLON：表示对应的文件描述符可读
>   * EPOLLOUT：表示对应的文件描述符可以写
>   * EPOLLPRI：表示对应的文件描述符有紧急的数据可读（这里应该表示有带外数据到来）
>   * EPOLLERR：表示对应的文件描述符发生错误
>   * EPOLLHUP：表示对应的文件描述符被挂断
>   * EPOLLET：将EPOLL设为边缘触发模式
>   * EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket的话，需要再次把这个socket加入到EPOLL队列里

#### epoll_wait

```
int epoll_wait(int epfd, struct epoll_event* events, int maxevents, int timeout)
```

收集在epoll监控的事件中已经发送的事件

> * 参数events是分配好的epoll_event结构体数组
> * epoll将会把发生的事件赋值到events数组中（events不可以是空指针，内核只负责把数据复制到这个events数组中，不会去帮助我们在用户态中分配内存）
> * maxevents告之内核这个events有多大，这个maxevents的值不能大于创建epoll_create()时的size
> * 参数timeout是超时事件（毫秒，0会立即返回，-1是永久阻塞）
> * 如果函数调用成功，返回对应I/O上已准备好的文件描述符数目，如返回0表示已超时，返回小于0表示函数失败

#### epoll的优点（对比select）

> * 接口使用方便
> * 数据拷贝轻量
> * 事件回调机制
> * 没有数量限制