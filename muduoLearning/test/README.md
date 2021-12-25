预期的流程：
一个Acceptor负责监听端口（一般是80 or 443），如果有连接来了就按round robin分配Socket然后创建TcpConnection给其他的IO线程的pending functors，其他线程把fd加到EPoller中监听，挂上SP_TcpConnection的定时器，同时EPoller监听消息，来了消息后分析HTTP报文（是否长连接、请求的资源的位置），然后把请求的资源发送回去，根据HTTP报文再挂一个定时器，然后到期的计时器直接pop出来，如果是TimerQueue中最后留存的一个SP的话，TcpConnection会自动析构，这样就不用考虑TimerQueue中的数据改变可能造成的暂时失效的问题了。

loop 的循环 EPoller->poll()（可以收到其他线程的消息，以防卡在轮询而长时间不能接受新的连接），过期的定时器pop，pending functor接受其他的线程给这个线程挂上的回调函数（在此模型中，主要是Acceptor给IO线程挂上的新连接）。
-----
还没写的

* Socket.h 
使用RAII封装fd，持有fd，析构的时候关闭fd

* TcpConnection.h 
一个对象管理一个连接的具体事务，里面的函数提供的功能应该主要是数据的传输与收取

* InetAddress.h 
用来封装ipv4地址的
可能不需要写，因为我要写的http服务器功能比较具体，不像muduo库一样提供比较完善的网络库功能，理一理逻辑关系后再决定写不写

* Acceptor.h
mainloop不使用Channel，而是使用Acceptor来监听端口，然后把新的连接分给其他Channel

* Util.h 
不写类，而是写一些函数

* HTTP.h
计划用于解析HTTP的报文，有三种方案：
1. 写成无状态的函数，这样一个函数（也可能是每个函数）会很长，
2. 写成一个类，然后里面的静态数据成员用于存储每次解析的一些状态量，另外要考虑不同线程之间的争用问题，因为静态数据成员存储状态量，那么每次解析的过程中，不能有其他线程调用此类，否则会造成错误
3. 写成一个类，每次解析时构造一个对象来完成解析任务
4. 写成一个类，每个线程配备一个对象，因为一个线程一次只能同时解析一份报文，避免了争用问题
5. 与TcpConnection耦合在一起，这样这些状态量会以TcpConnection的数据段存储在里面
目前倾向于4或者5的实现方法
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