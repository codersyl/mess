#include "EventLoop.h"
#include <assert.h>
#include <stdio.h> // printf()

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
	// 循环要做的事 theWorld
	printf("我在循环\n"); // 先用输出点东西代表
	looping_ = false;
}

void EventLoop::abortNotInLoopThread() {
	printf("ERROR in :EventLoop::abortNotInLoopThread()/n");
	assert(false);
}
