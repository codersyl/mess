#ifndef _TIMER_H_
#define _TIMER_H_

#include "HttpData.h"
#include "noncopyable.h"
#include <memory>
#include <unistd.h>

class HttpData;

class Time : noncopyable {
public:
	Timer(std::shared_ptr<HttpData> dataSP, int timeout);
	~Timer();
	void update(int when);
	bool isValid();
	void clearData();
	void setDeleted() { deleted_ = true; }
	bool isDeleted() const { return deleted_; }
	size_t getExpTime() const { return expiredTime_; }
	
private:
	bool deleted_;
	size_t expiredTime_;	// ms
	std::shared_ptr<HttpData> dataSP_;
};

#endif