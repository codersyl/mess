#ifndef _SOCKET_H_
#define _SOCKET_H_
#include "noncopyable.h"

// class InetAddress; 如果有的话代表ip地址的封装

class Socket : noncopyable
{
public:
    explicit Socket(int socketfd): socketfd_(socketfd) {}

    // Socket(Socket&&) // move constructor in C++11
    ~Socket();

    int getFd() const { return socketfd_; }

    // 如果地址已经被使用则abort
    void bindAddress(const InetAddress& localaddr);
    
    // 如果地址已经被使用则abort
    void listen();

    // 接收成功：
        // 返回一个代表新连接的非负整数fd
        // 并且已经设置了非阻塞non-blocking and close-on-exec
        // *peeraddr 会被赋值
    // 接受失败：
        // 返回 -1
        // *peeraddr 不变
    int accept(InetAddress* peeraddr);

    void shutdownWrite();

    // 打开/关闭TCP_NODELAY
    // 用来控制是否开启Nagle算法，true不使用算法，false使用
    // 该算法要求一个TCP连接上最多只能有一个未被确认的小分组，在该小分组的确认到来之前，不能发送其他小分组。
    void setTcpNoDelay(bool on);

    // 打开/关闭SO_REUSEADDR
    // 大意是允许服务器bind一个地址，即使这个地址当前已经存在已建立的连接
    void setReuseAddr(bool on);

    // 打开/关闭SO_REUSEPORT
    // SO_REUSEPORT支持多个进程或者线程绑定到同一端口，提高服务器程序的性能
    void setReusePort(bool on);

    // 打开/关闭心跳包
    void setKeepAlive(bool on);

private:
    const int socketfd_;
};


#endif  // _SOCKET_H_