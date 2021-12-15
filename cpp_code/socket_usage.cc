// socket usage
// reference
// https://www.jianshu.com/p/3b233facd6bb

// 头文件
#include <sys/socket>

// socket函数
int socket(int domain, int type, int protocol);
// socket()创建一个socket描述符（socket descriptor），唯一标识一个socket。
// 这个socket描述字跟文件描述符一样。
// 参数一：domain，指定协议域，或称协议族（family），决定了socket的地址类型。
//	* PF_UNIX,PF_LOCAL		本地通信
//	* AF_INET,PF_INET		IPv4 Internet协议
//	* PF_INET6				IPv6 Internet协议
//	* PF_IPX				IPX-Novell协议
//	* PF_NETLINK			内核用户界面设备
//	* PF_X25				ITU-T X25 / ISO-8208协议
//	* PF_AX25				Amateur radio AX.25
//	* PF_ATMPVC				原始ATM PVC访问
//	* PF_APPLETALK			Appletalk
//	* PF_PACKET				底层包访问
// 参数二：type，指定socket类型。
//	* SOCK_STREAM			Tcp连接，提供序列化的、可靠的、双向连接的字节流。
//	* SOCK_DGRAM			支持UDP连接（无连接状态的消息）
//	* SOCK_SEQPACKET		序列化包，提供一个序列化的、可靠的、双向的基本连接的数据传输通道，数据长度定常。每次调用读系统调用时数据需要将全部数据读出
//	* SOCK_RAW				RAW类型，提供原始网络协议访问
//	* SOCK_RDM				提供可靠的数据报文，不过可能数据会有乱序
//	* SOCK_PACKET			这是一个专用类型，不能呢过在通用程序中使用
// 参数三：protocol，指定协议。
// 常用的协议有，IPPROTO_TCP、IPPTOTO_UDP、IPPROTO_SCTP、IPPROTO_TIPC等。
// 它们分别对应TCP传输协议、UDP传输协议、STCP传输协议、TIPC传输协议。
// 当protocol为0时，会自动选择type类型对应的默认协议。
// 我用 IPv4 的 TCP连接，应该是
int socketfd = socket(AF_INET, SOCK_STREAM, 0);


// bind函数
int bind(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// 参数一：sockfd，即要操作的socket描述字，socket()函数的返回值。
// 参数二：addr，一个const struct sockaddr *指针，指向要绑定给sockfd的协议地址。
// 		  这个地址结构根据地址创建socket时的地址协议族的不同而不同。
// 参数三：addrlen，对应地址的长度。
//  	  通常服务器在启动的时候都会绑定一个众所周知的地址（如ip地址+端口号）
//		  用于提供服务，客户可以通过它来接连服务器。

// 关于sockaddress
// ipv4
struct sockaddr_in {
    sa_family_t    sin_family; /* address family: AF_INET */
    in_port_t      sin_port;   /* port in network byte order */
    struct in_addr sin_addr;   /* internet address */
};
/* Internet address. */
struct in_addr {
    uint32_t       s_addr;     /* address in network byte order */
};
// ipv6
struct sockaddr_in6 { 
    sa_family_t     sin6_family;   /* AF_INET6 */ 
    in_port_t       sin6_port;     /* port number */ 
    uint32_t        sin6_flowinfo; /* IPv6 flow information */ 
    struct in6_addr sin6_addr;     /* IPv6 address */ 
    uint32_t        sin6_scope_id; /* Scope ID (new in 2.4) */ 
};
struct in6_addr { 
    unsigned char   s6_addr[16];   /* IPv6 address */ 
};
// Unix
#define UNIX_PATH_MAX    108
struct sockaddr_un { 
    sa_family_t sun_family;               /* AF_UNIX */ 
    char        sun_path[UNIX_PATH_MAX];  /* pathname */ 
};


// listen函数
// 服务端使用，用于监听是否有连接进来
int listen(int sockfd, int backlog);
// 参数一：sockfd即为要监听的socket描述字
// 参数二：blacklog为相应socket可以排队的最大连接个数


// connect函数
// 客户端使用，创建socket后就调用connect()向服务端发出连接请求
int connect(int sockfd, const struct sockaddr *addr, socklen_t addrlen);
// 参数一：sockfd即为客户端的socket描述字
// 参数二：addr为要连接的服务器的socket地址
// 参数三：addrlen为服务器socket地址的长度


// accept函数
int accept(int sockfd, struct sockaddr *addr, socklen_t *addrlen);
// 参数一：sockfd为服务器的socket描述字
// 参数二：addr为指向struct sockaddr *的指针，用于返回客户端的协议地址
// 参数三：addrlen为协议地址的长度
// 如果accpet成功，返回值是由内核自动生成的一个全新的描述字，代表与返回客户的TCP连接


// close函数
#include <unistd.h>
int close(int fd);
// close操作会使相应socket描述字的引用计数减一
// 当引用计数为0的时候，才会触发TCP客户端向服务器发送终止连接请求



// 网络I/O的函数，待完善 besoin
read() / write()
recv() / send()
readv() / writev()
recvmsg() / sendmsg()
recvfrom() / sendto()



