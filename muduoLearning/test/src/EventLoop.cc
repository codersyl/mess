#include "EventLoop.h"
#include <stdio.h> // printf()
#include <iostream>

__thread EventLoop* t_loopInThisThread = 0;

EventLoop::EventLoop()
	: looping_(false),
	  threadId_(CurrentThread::tid()) {
	if (t_loopInThisThread) {
		// some log theWorld
	} else {
		t_loopInThisThread = this;
	}

}

EventLoop::~EventLoop() {
	assert(!looping_);
	t_loopInThisThread = NULL;
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
	while(!quit_) {
		activeChannels_.clear();
		poller_->poll(kPollTimeMs, &activeChannels_);
		for(ChannelList::iterator it = activeChannels_.begin(); it != activeChannels_.end(); it++) {
			(*it)->handleEvent();
		}
		std::cout<<"EventLoop threadId_ = "<<threadId_<<" stop looping\n";
	}
	// endBook
}

void EventLoop::abortNotInLoopThread() {
	printf("ERROR in :EventLoop::abortNotInLoopThread()\n");
	assert(false);
}
