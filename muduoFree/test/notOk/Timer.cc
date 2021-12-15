#include "Timer.h"
#include <sys/time.h>

Timer::Timer(std::shared_ptr<HttpData> dataSP, int timeout)
	: deleted_(false),
	  dataSP_(dataSP) {
	struct timeval now;
	gettimeofday(&now, NULL);
	// 截头以防爆int
	expiredTime_ = (((now.tv_sec % 1000000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

void Timer::update(int timeout) {
	struct timeval now;
	gettimeofday(&now, NULL);
	expiredTime_ = (((now.tv_sec % 1000000) * 1000) + (now.tv_usec / 1000)) + timeout;
}

bool Timer::isValid() {
	struct timeval now;
	gettimeofday(&now, NULL);
	size_t temp = (((now.tv_sec % 1000000) * 1000) + (now.tv_usec / 1000));
	if (temp < expiredTime_)
		return true;
	else {
		this->setDeleted();
		return false;
	}
}

void Timer::clearData() {
	dataSP_.reset();
	this->setDeleted();
}