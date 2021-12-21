已经差不多与书对齐的类：
* Channel

先跳过的类：
* Epoller

# 类的功能
## TimerQueue
高效的组织没到期的Timer，具体体现在
* 快速根据当前时间找到已经过期的Timer
* 高效添加和删除Timer

可选用线性表、二叉树或者堆

## EPoller
基于epoll 的poller