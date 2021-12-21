接下来需要写

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
# 类的功能
## TimerQueue
高效的组织没到期的Timer，具体体现在
* 快速根据当前时间找到已经过期的Timer
* 高效添加和删除Timer

可选用线性表、二叉树或者堆

把Channel EPoller Timestamp 对应的源文件加到了 include 与 src 中