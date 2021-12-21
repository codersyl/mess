// mine
#ifndef _EPOLL_H_
#define _EPOLL_H_

#include <sys/epoll.h>
#include <memory>
#include "Channel.h"
// linyas
#include <unordered_map>
#include <vector>
#include "HttpData.h"
#include "Timer.h"


// Epoll 是 EventLoop 的间接成员，只能其owner EventLoop在 IO 线程调用
// 声明周期与 EventLoop相等
class Epoll
{
public:
	Epoll();
	~Epoll();
	void epoll_add(SP_Channel request, int timeout);
	void epoll_mod(SP_Channel request, int timeout);
	void epoll_del(SP_Channel request);
	std::vector<std::shared_ptr<Channel>> poll();
	std::vector<std::shared_ptr<Channel>> getEventsRequest(int events_num);
	void add_timer(std::shared_ptr<Channel> request_data, int timeout);
	int getEpollFd() { return epollFd_; }
	void handleExpired();

private:
	static const int MAXFDS = 100000;
	int epollFd_;
	std::vector<epoll_event> events_;
	SP_Channel fd2chan_[MAXFDS];
	std::shared_ptr<HttpData> fd2http_[MAXFDS];
	TimerQueue TQ_;
};
#endif