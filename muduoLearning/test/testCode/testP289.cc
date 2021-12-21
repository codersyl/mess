// p289 s01/test3.cc
#include <sys/timerfd.h>
#include <stdio.h>	// printf

EventLoop* g_loop;

void timeout() {
	printf("timeout!\n");
	g_loop->quit();
}

int main() {
	EventLoop loop;
	g_loop = &loop;
	int timerfd = ::timerfd_create(CLOCK_MONOTONIC, TFD_NONBLOCK | TFD_CLOEXEC);
	Channel channel(&loop, timerfd);
	channel.setReadCallback(timeout);
	channel.enableReading();

	struct itimerspec howlong;
	memset(&howlong, 0, sizeof(howlong));
	howlong.it_value.tv_sec = 5;
	::timerfd_settime(timerfd, 0, &howlong, NULL);

	loop.loop();
	::close(timerfd);

	return 0;
}