// mine
#include "EPoller.h"
#include "Channel.h"
#include "EventLoop.h"
#include <assert.h>

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
		if(numEvents == events_.size()) {
			events_.resize(events_.size() * 2);
		}
	} else if (numEvents == 0) {
		std::cout << "nothing happended\n";
	} else {
		std::cout << "numEvents 出现负数\n";
	}
	return now;
}


void EPoller::fillActiveChannels(int numEvents,
                                ChannelList* activeChannels) const {
	assert(numEvents <= events_.size());
	for (int i = 0; i < numEvents; ++i)
	{
		Channel* channel = (Channel*) (events_[i].data.ptr);
		channel->setRevents(events_[i].events);
		activeChannels->push_back(channel);
	}
}