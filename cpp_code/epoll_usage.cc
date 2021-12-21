// epoll 

// Reference：
// https://blog.csdn.net/zhaobryant/article/details/80557262

#include <sys/epoll.h>

int epoll_create(int size);

int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);

int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);


// 分别详解
// epoll_create
int epoll_create(int size);
/* 当创建好epoll句柄后，它就会占用一个fd值。
 * 在使用完epoll后，必须调用close函数进行关闭，否则可能导致fd被耗尽.
 */


// epoll_ctl
int epoll_ctl(int epfd, int op, int fd, struct epoll_event *event);
// epoll的事件注册函数，通过epoll_ctl注册要监听的事件类型。
// 参数1：epoll_create函数的返回值
// 参数2：表示动作类型。有三个宏来表示： 
// 	* EPOLL_CTL_ADD：注册新的fd到epfd中； 
// 	* EPOLL_CTL_MOD：修改已经注册的fd的监听事件； 
// 	* EPOLL_CTL_DEL：从epfd中删除一个fd。
// 参数3：第三个参数fd：需要监听的fd
// 参数4：告诉内核需要监听什么事件


// epoll_event的数据结构，保存触发事件的某个文件描述符相关的数据
typedef union epoll_data {
    void *ptr;
    int fd;
    __uint32_t u32;
    __uint64_t u64;
} epoll_data_t;

// 感兴趣的事件和被触发的事件
struct epoll_event {
    __uint32_t events; // Epoll events
    epoll_data_t data; // User data variable
};


// Epoll Events可以是下面几个宏的集合：
// * EPOLLIN：表示对应的文件描述符可读（包括对端Socket）；
// * EPOLLOUT：表示对应的文件描述符可写；
// * EPOLLPRI：表示对应的文件描述符有紧急数据可读（带外数据）；
// * EPOLLERR：表示对应的文件描述符发生错误；
// * EPOLLHUP：表示对应的文件描述符被挂断；
// * EPOLLET：将EPOLL设为边缘触发（Edge Triggered），这是相对于水平触发（Level Triggered）而言的。
// * EPOLLONESHOT：只监听一次事件，当监听完这次事件之后，如果还需要继续监听这个socket，需要再次


// 注册epoll时 epoll_event 的使用方法：
struct epoll_event event;
event.events = EPOLLIN|EPOLLET;
event.data.fd = someFd;
if(epoll_ctl(epfd, EPOLL_CTL_ADD, someFd, &event) < 0) {
	perror("epoll add error");
}

// epoll_wait
int epoll_wait(int epfd, struct epoll_event *events, int maxevents, int timeout);
// 收集在epoll监控的事件中已经发生的事件。
// 参数events是分配好的epoll_event结构体数组，epoll将会把发生的事件赋值到events数组中
// events不可以是空指针，内核只负责把数据赋值到这个event数组中，不会去帮助我们在用户态分配内存
// maxevents告诉内核这个events数组有多大，这个maxevents的值不能大于创建epoll_create时的size
// 参数timeout是超时时间（毫秒）。如果函数调用成功，则返回对应IO上已准备好的文件描述符数目，如果返回0则表示已经超时。