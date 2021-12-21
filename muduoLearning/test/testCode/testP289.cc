// p289 s01/test3.cc
#include <sys/timerfd.h>
#include <stdio.h>	// printf
#include "EventLoop.h"
#include "Channel.h"
#include <string.h> // bzero
#include <fstream> // close() ?

EventLoop* g_loop;

void timeout() {
	printf("timeout!\n");
	g_loop->quit();
}

int main() {
	printf("start!\n");
	EventLoop loop;
	printf("EventLoop in main() constructed!\n");
	g_loop = &loop;
	printf("g_loop = &loop;!\n");
	int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
	printf("timerfd got!\n");
	Channel channel(&loop, timerfd);
	printf("channel constructed!\n");
	channel.setReadCallback(timeout);
	printf("ReadCallback set!\n");
	channel.enableReading();
	printf("enableReading()!\n");
	struct itimerspec howlong;
	printf("howlong constructed!\n");
	bzero(&howlong, sizeof(howlong));
	printf("howlong bzero!\n");
	howlong.it_value.tv_sec = 5;
	printf("howlong set 5 seconds!\n");
	::timerfd_settime(timerfd, 0, &howlong, NULL);
	printf("::timerfd_settime()\n");
	loop.loop();
	printf("loop end!\n");
	::close(timerfd);
	return 0;
}