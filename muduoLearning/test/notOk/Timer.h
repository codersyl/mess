#ifndef _TIMER_H_
#define _TIMER_H_

#include "HttpData.h"
#include "noncopyable.h"
#include <memory>
#include <unistd.h>
#include <inttypes.h>
// 构造
	// 绑数据指针
	// 卡一个多少ms后过时的计时器
	// 带一个id对相同过期时间的Timer进行比大小
	// 是否删除的标记 deleted_
// update(int)
	// 给Timer中的过期时间设为现在 + 一定时间
class HttpData;

class Timer : noncopyable {
public:
	Timer(std::shared_ptr<HttpData> dataSP, int timeout);
	~Timer();
	void update(int timeout);
	bool isValid();
	void clearData();
	void setDeleted() { deleted_ = true; }
	bool isDeleted() const { return deleted_; }
	int64_t getExpTime() const { return expiredTime_.get(); }
	unsigned long long getId() const { return id_; }
	
private:
	bool deleted_;
	Timestamp expiredTime_;	// miu s
	unsigned long long id_;
	static atomic<unsigned long long> idx;
	std::shared_ptr<HttpData> dataSP_;
};

#endif