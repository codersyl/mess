// mine
#include "EPoller.h"
#include <assert.h>


EPoller::EPoller(EventLoop* loop) :
	epollFd_(epoll_create1(EPOLL_CLOEXEC)),
	events_(16),	// 初试长度设为16
	ownerLoop_(loop) {
	assert(epollFd_ > 0);
}
EPoller::~EPoller() {}


Timestamp EPoller::poll(int timeousMs, ChannelList* activeChannels) {
	int numEvents = epoll_wait(epollFd_,
	                           events_.data(),
	                           static_cast<int>(events_.size()),
	                           timeousMs);
	Timestamp now(0);
	now.becomeNow();
	if (numEvents > 0) {
		std::cout << numEvents << " events happended\n" << endl;
		fillActiveChannels(numEvents, activeChannels);
		if(implicit_cast<size_t>(numEvents) == events_.size()) {
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
	assert(implicit_cast<size_t>(numEvents) <= events_.size());
	for (int i = 0; i < numEvents; ++i)
	{
		Channel* channel = static_cast<Channel*>(events_[i].data.ptr);
		channel->set_revents(events_[i].events);
		activeChannels->push_back(channel);
	}
}