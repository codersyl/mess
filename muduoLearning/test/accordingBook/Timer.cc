// #include "Timer.h"
// #include <sys/time.h>

// Timer::Timer(std::shared_ptr<HttpData> dataSP, int timeout)
// 	: deleted_(false),
// 	  dataSP_(dataSP),
// 	  id_(idx++) {
// 	expiredTime_ = Timestamp::now();
// 	expiredTime_.addMS(timeout);
// }

// void Timer::update(int timeout) {
// 	expiredTime_.becomeNow();
// 	expiredTime_.addMS(timeout);
// }

// bool Timer::isValid() {
// 	if (Timestamp::now() < expiredTime_)
// 		return true;
// 	else {
// 		this->setDeleted();
// 		return false;
// 	}
// }

// void Timer::clearData() {
// 	dataSP_.reset();
// 	this->setDeleted();
// }