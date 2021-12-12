#include "EventLoop.h"

void threadFunc() {
	printf("threadFunc() : pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
	EventLoop loop;
	loop.loop();
}

void printTestPropose() {
	printf("---------------------------\n\
本测试会先打印main函数的 pid 与 tid\n\
然后实例化一个EventLoop\n\
然后用函数threadFunc()初始化一个Thread\n\
然后Thread_start() EventLoop_loop() Thread_join()\n\
最终结束函数\n\
---------------------------\n");
}

int main() {
	printTestPropose();
	printf("main() : pid = %d, tid = %d\n", getpid(), CurrentThread::tid());
	EventLoop loopMain;
	Thread thread(threadFunc);
	thread.start();
	loopMain.loop();
	thread.join();
	return	0;
}
