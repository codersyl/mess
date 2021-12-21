// #ifndef _TIMERQUEUE_H_ 
// #define _TIMERQUEUE_H_
// #include "Timer.h"
// #include <queue>
// #include <vector>

// struct TimerCmp {
// 	bool operator()(std::shared_ptr<Timer> &a,
// 	                std::shared_ptr<Timer> &b) const {
// 		if(a->getExpTime() == b->getExpTime())
// 			return a->getId() > b->getId();
// 		return a->getExpTime() > b->getExpTime();
// 	}
// };

// class TimerQueue {
// public:
// 	TimerQueue();
// 	~TimerQueue();
// 	void addTimer(std::shared_ptr<HttpData> dataSP, int timeout);
// 	// 处理队伍中过期的结点
// 	void handleExpiredEvent();

// private:
// 	typedef std::shared_ptr<Timer> SP_Timer;
// 	std::priority_queue<SP_Timer, std::deque<SP_Timer>, TimerCmp> timerQueue_;
// };

// #endif