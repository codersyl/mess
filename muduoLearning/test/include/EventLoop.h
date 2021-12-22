#ifndef	_EVENTLOOP_H_
#define	_EVENTLOOP_H_

#include "Thread.h"
#include "CurrentThread.h"
#include "noncopyable.h"
#include <memory>
#include <assert.h>
#include <vector>
#include <stdio.h>	// printf

class Channel;
class EPoller;

class EventLoop : noncopyable
{
public:
	EventLoop();
	~EventLoop();
	
	void loop();

	void assertInLoopThread();
	// 判断是否在当前对应的线程
	bool isInLoopThread() const { return threadId_ == CurrentThread::tid(); }
	
	static EventLoop* getEventLoopOfCurrentThread();

	void quit() { quit_ = true; }

	void updateChannel(Channel* channel);
private:
	void abortNotInLoopThread();
	bool looping_;
	bool quit_;
	const pid_t threadId_;

	typedef std::vector<Channel*> ChannelList;
	std::unique_ptr<EPoller> poller_;
	ChannelList activeChannels_;
	// EventLoop::loop()有了工作内容：
	// 调用EPoller::poll()获得当前活动事件的Channel列表，然后调用每个Channel的handleEvent函数
};

#endif
