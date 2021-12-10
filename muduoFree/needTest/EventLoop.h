
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
	void isInLoopThread() const { return threadId_ == CurrentThread::tid();}
private:
	void abortNotInLoopThread();
	bool looping_;
	const pid_t threadId_;
};


#endif