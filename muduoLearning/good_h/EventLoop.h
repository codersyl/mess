#ifndef	_EVENTLOOP_H_
#define	_EVENTLOOP_H_

#include "Thread.h"
#include "CurrentThread.h"
#include "noncopyable.h"

class EventLoop : noncopyable
{
public:
	EventLoop();
	~EventLoop();
	
	void loop();

	void assertInLoopThread() {
		if(!isInLoopThread()) {
			abortNotInLoopThread();
		}
	}
	bool isInLoopThread() const { return threadId_ == CurrentThread::tid();}
	static EventLoop* getEventLoopOfCurrentThread();
private:
	void abortNotInLoopThread();
	bool looping_;
	const pid_t threadId_;
};


#endif
