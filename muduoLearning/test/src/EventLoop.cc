#include "EventLoop.h"
#include <stdio.h> // printf()
#include <iostream>
#include "Channel.h"
#include "EPoller.h"

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
	: looping_(false),
	  threadId_(CurrentThread::tid()) {
	activeChannels_.resize(16);
	poller_.reset(new EPoller(this));
	if (t_loopInThisThread) {
		// some log theWorld
	} else {
		t_loopInThisThread = this;
	}

}

EventLoop::~EventLoop() {
	assert(!looping_);
	t_loopInThisThread = NULL;
	poller_.reset();
}

EventLoop* EventLoop::getEventLoopOfCurrentThread() {
	return	t_loopInThisThread;
}

void EventLoop::loop() {
	assert(!looping_);
	assertInLoopThread();
	looping_ = true;
	// beginBook
	quit_ = false;
	while (!quit_) {
		activeChannels_.clear();
		poller_->poll(10000/* kPollTimeMs */, &activeChannels_);
		for (ChannelList::iterator it = activeChannels_.begin(); it != activeChannels_.end(); it++) {
			(*it)->handleEvent();
		}
		std::cout << "EventLoop threadId_ = " << threadId_ << " stop looping\n";
	}
	// endBook
	looping_ = false;
}

void EventLoop::abortNotInLoopThread() {
	printf("ERROR in :EventLoop::abortNotInLoopThread()\n");
	assert(false);
}

void EventLoop::updateChannel(Channel* channel) {
	printf("--- start update in EventLoop\n");
	assert(channel->getOwnerEventLoop() == this);
	assertInLoopThread();
	poller_->updateChannel(channel);
	printf("--- start update in EventLoop\n");
}

void EventLoop::assertInLoopThread() {
	printf("----- start assertInLoopThread\n");
	if (!isInLoopThread()) {
		printf("----- here\n");
		abortNotInLoopThread();
		printf("----- pass here\n");
	}
	printf("----- end   assertInLoopThread\n");
}
