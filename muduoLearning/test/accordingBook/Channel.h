// mine
#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "noncopyable.h"
#include <sys/epoll.h>

class EventLoop;	// 前向声明

// Channel 负责注册和响应 IO事件
// 不拥有fd
// 是Acceptor、Connector、EventLoop、TimerQueue、TcpConnection的成员
// 生命期由上面一排控制

class Channel : noncopyable
{
public:
	typedef std::function<void()> Callback;
	Channel(EventLoop* loop, int fd);
	~Channel();

	void handleEvent();
	void setReadCallback(Callback && cb) { ReadCallback_ = cb; }
	void setWriteCallback(Callback && cb) { WriteCallback_ = cb; }
	void setErrorCallback(Callback && cb) { ErrorCallback_ = cb; }

	int getfd() const { return fd_;}
	int getEvents() const { return events_;}
	void setRevents(int revt) { revents_ = revt; }
	void setEvents(int evt) { events_ = }

	// for Poller
	int getIndex() { return index_; }
	void setIndex(int idx) { index_ = idx; }

	EventLoop* getOwnerEventLoop() { return loop_; }
private:
	void update();
	EventLoop* loop_;
	int fd_;		// 构造时初始化
	int events_;	// 构造时初始化,关心的事件，由用户设置
	int revents_;	// 目前活动的事件，由 EventLoop / Poller 设置
	int index_;	// used by Poller

	Callback ReadCallback_;
	Callback WriteCallback_;
	Callback ErrorCallback_;
};

typedef std::shared_ptr<Channel> SP_Channel;
#endif	// _CHANNEL_H_