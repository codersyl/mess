预期的流程：
一个Acceptor负责监听端口（一般是80 or 443），如果有连接来了就按round robin分配给其他的IO线程的pending functors，其他线程把连接加到EPoller中，挂上关闭连接的定时器，同时EPoller监听消息，来了消息后分析HTTP报文（是否长连接、请求的资源的位置），然后把请求的资源发送回去，根据HTTP报文选择是立即关闭连接还是挂一个关闭连接的定时器，然后到期的计时器所对应连接的fd关掉，同时如果是长连接，则每次有新报文则要更新定时器在队列中的信息，疑问：更新定时器的信息则可能会导致定时器队列失效？
loop 的循环 EPoller->poll()（可以收到其他线程的消息，以防卡在轮询而长时间不能接受新的连接），过期的定时器关掉，pending functor接受其他的线程给这个线程挂上的回调函数（在此模型中，主要是Acceptor给IO线程挂上的新连接）


---
* Socket.h
使用RAII封装fd

* InetAddress.h
用来封装ipv4地址的
可能不需要写，因为我要写的http服务器功能比较具体，不像muduo库一样提供比较完善的网络库功能，理一理逻辑关系后再决定写不写

* Acceptor.h
mainloop不使用Channel，而是使用Acceptor来监听端口，然后把新的连接分给其他Channel

* TcpConnection.h
一个对象管理一个连接的具体事务，里面的函数提供的功能应该主要是数据的传输与收取

解析HTTP报文的东西
---
分析一下过程

一个主线程，开
EventLoop + Acceptor

其余线程开
EventLoop + Channel + 
---
# 已经测过了的类的说明
## EventLoop
每个线程一个EventLoop，loop()是线程的主要内容，每次loop都会调去当前的活动事件，然后依次执行每个事件
---
# 类的功能

## TimerQueue
高效的组织没到期的Timer，具体体现在
* 快速根据当前时间找到已经过期的Timer
* 高效添加和删除Timer

可选用线性表、二叉树或者堆

把Channel EPoller Timestamp 对应的源文件加到了 include 与 src 中