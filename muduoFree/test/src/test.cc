#include "EventLoop.h"


void threadFunc() {
	printf("threadFunc() : pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
	EventLoop loop;
	loop.loop();
}

int main() {
	printf("main() : pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
	EventLoop loopMain;
	Thread thread(threadFunc);
	thread.start();
	loopMain.loop();
	thread.join();
	return	0;
}