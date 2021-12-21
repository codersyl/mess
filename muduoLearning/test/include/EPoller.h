// mine
#ifndef _EPOLLER_H_
#define _EPOLLER_H_

#include <memory>
#include <map>
#include <sys/epoll.h>
#include "Timestamp.h"	// 这个可以加，不会循环编译
#include "noncopyable.h"
#include "EventLoop.h"
#include <vector>

// EPoller 是 EventLoop 的间接成员，只能其owner EventLoop在 IO 线程调用
// 声明周期与 EventLoop相等

class Channel;

class EPoller : noncopyable
{
public:
	typedef std::vector<Channel*> ChannelList;

	EPoller(EventLoop* loop);
	~EPoller();

	// 核心
	Timestamp poll(int timeousMs, ChannelList* activeChannels);
	void updateChannel(Channel* channel);

	void assertInLoopThread();
private:
	static const int kInitEventListSize = 4000;

	void fillActiveChannels(int numEvents, ChannelList* activeChannels) const;

	typedef std::vector<struct epoll_event> EventList;
	typedef std::map<int, Channel*> ChannelMap;

	int epollFd_;

	EventLoop* ownerLoop_;
	EventList events_;
	ChannelMap channels_;
};
#endif
