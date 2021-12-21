#ifndef	_EVENTLOOP_H_
#define	_EVENTLOOP_H_

#include "Thread.h"
#include "CurrentThread.h"
#include "noncopyable.h"
#include <memory>
#include <assert.h>
#include <vector>

class Channel;
class EPoller;

class EventLoop : noncopyable
{
public:
	EventLoop();
	~EventLoop();
	
	void loop();

	void assertInLoopThread() {
		if(!isInLoopThread()) {
			abortNotInLoopThread();
		}
	}
	bool isInLoopThread() const { return threadId_ == CurrentThread::tid();}
	static EventLoop* getEventLoopOfCurrentThread();

	// beginBook
	void quit() {
		quit_ = true;
	}

	void updateChannel(Channel* channel);
	// endBook
private:
	void abortNotInLoopThread();
	bool looping_;
	const pid_t threadId_;

	// 分两向，book
	typedef std::vector<Channel*> ChannelList;
	bool quit_;
	std::unique_ptr<EPoller> poller_;
	ChannelList activeChannels_;
	// EventLoop::loop()有了工作内容：
	// 调用Epoller::poll()获得当前活动事件的Channel列表，然后调用每个Channel的handleEvent函数
};

#endif
