#ifndef _CONDITION_H_
#define _CONDITION_H_

#include "MutexLock.h"
#include <pthread.h>
#include <errno.h>
#include <time.h>

class Condition : noncopyable
{
public:
	explicit Condition(MutexLock& mtx) : mutex_(mtx){ pthread_cond_init(&cond_, NULL); }
	~Condition(){ pthread_cond_destroy(&cond_);}
	void wait() { pthread_cond_wait(&cond_, mutex_.get()); }
	void notify() { pthread_cond_signal(&cond_); }
	void notifyAll() { pthread_cond_broadcast(&cond_); }
	bool waitForSeconds(int seconds) {
        struct timespec abstime;
        clock_gettime(CLOCK_REALTIME, &abstime);
        abstime.tv_sec += static_cast<time_t>(seconds);
        return ETIMEDOUT == pthread_cond_timedwait(&cond, mutex.get(), &abstime);
    }
    
private:
	MutexLock& mutex_;
	pthread_cond_t cond_;
};


#endif	// _CONDITION_H_