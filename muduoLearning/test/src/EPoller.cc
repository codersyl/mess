// mine
#include "EPoller.h"
#include "Channel.h"
#include "EventLoop.h"
#include <assert.h>
#include <string.h>
// cout
#include <iostream>


EPoller::EPoller(EventLoop* loop) :
	epollFd_(epoll_create1(EPOLL_CLOEXEC)),
	events_(16),	// 初试长度设为16
	ownerLoop_(loop) {
	assert(epollFd_ > 0);
}
EPoller::~EPoller() {}

void EPoller::assertInLoopThread() { ownerLoop_->assertInLoopThread(); }

Timestamp EPoller::poll(int timeousMs, ChannelList* activeChannels) {
	int numEvents = epoll_wait(epollFd_,
	                           events_.data(),
	                           static_cast<int>(events_.size()),
	                           timeousMs);
	Timestamp now(0);
	now.becomeNow();
	if (numEvents > 0) {
		std::cout << numEvents << " events happended\n";
		fillActiveChannels(numEvents, activeChannels);
		if ((size_t)numEvents == events_.size()) {
			events_.resize(events_.size() * 2);
		}
	} else if (numEvents == 0) {
		std::cout << "nothing happended\n";
	} else {
		std::cout << "numEvents 出现负数\n";
	}
	return now;
}

void updateChannel(Channel* channel) {
	EPoller::assertInLoopThread();
	const int index = channel->index();
	if (index == -1 || index == 2)	// 初始化为 -1，删除为 2
	{
		// a new one, add with EPOLL_CTL_ADD
		int fd = channel->fd();
		if (index == -1)
		{
			assert(channels_.find(fd) == channels_.end());
			channels_[fd] = channel;
		}
		else // 删了
		{
			assert(channels_.find(fd) != channels_.end());
			assert(channels_[fd] == channel);
		}

		channel->set_index(1);
		// 监听channel
		struct epoll_event event;
		bzero(event, sizeof(event));
		event.events = channel->events();
		event.data.ptr = channel;
		::epoll_ctl(epollfd_, EPOLL_CTL_ADD, fd, &event);
	}
	else
	{
		// update existing one with EPOLL_CTL_MOD/DEL
		int fd = channel->fd();
		(void)fd;
		assert(channels_.find(fd) != channels_.end());
		assert(channels_[fd] == channel);
		assert(index == 1);
		if (channel.events_ == 0)	// 没事件，删掉
		{
			struct epoll_event event;
			bzero(event, sizeof(event));
			event.events = channel->events();
			event.data.ptr = channel;
			int fd = channel->fd();
			::epoll_ctl(epollfd_, EPOLL_CTL_DEL, fd, &event)
			channel->set_index(2);
		}
		else // 有事件，改一改
		{
			struct epoll_event event;
			bzero(event, sizeof(event));
			event.events = channel->events();
			event.data.ptr = channel;
			int fd = channel->fd();
			::epoll_ctl(epollfd_, EPOLL_CTL_MOD, fd, &event)
		}
	}
}


void EPoller::fillActiveChannels(int numEvents,
                                 ChannelList* activeChannels) const {
	assert((size_t)numEvents <= events_.size());
	for (int i = 0; i < numEvents; ++i)
	{
		Channel* channel = (Channel*) (events_[i].data.ptr);
		channel->setRevents(events_[i].events);
		activeChannels->push_back(channel);
	}
}