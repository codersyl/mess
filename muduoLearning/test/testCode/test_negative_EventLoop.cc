#include "EventLoop.h"

EventLoop* g_loop;

void threadFunc() {
	g_loop->loop();
}

void printTestPropose() {
	printf("---------------------------\n\
本测试将会做：\n\
main函数中实例化一个EventLoop，并将全局指针指向这个EventLoop\n\
然后用函数threadFunc()初始化一个Thread\n\
然后Thread_start() Thread_join()\n\
其中threadFunc() 会调用全局指针的loop()，应该发生错误\n\
最终结束函数\n\
---------------------------\n");
}

int main() {
	printTestPropose();
	EventLoop loopInMain;
	g_loop = &loopInMain;
	Thread thread(threadFunc);
	thread.start();
	thread.join();
	return	0;
}

/* 运行后的输出：
---------------------------
本测试将会做：
main函数中实例化一个EventLoop，并将全局指针指向这个EventLoop
然后用函数threadFunc()初始化一个Thread
然后Thread_start() Thread_join()
其中threadFunc() 会调用全局指针的loop()，应该发生错误
最终结束函数
---------------------------
test: /root/stoneFree/muduoFree/test/src/EventLoop.cc:38: void EventLoop::abortNotInLoopThread(): Assertion `false' failed.
ERROR in :EventLoop::abortNotInLoopThread()/n已放弃
*/