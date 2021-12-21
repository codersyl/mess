#ifndef _TIMESTAMP_H_
#define _TIMESTAMP_H_

#include <sys/time.h>
#include <stdio.h>
#include <string>
#include <inttypes.h>	// PRID64

// 构造
	// 主要用 Timestamp::now()，可得到一个当前时间的 Timestamp
// 关于内置时间
	// 将现有的Timestamp置为当前时间
	// 给Timestamp延后 x ms
	// 返回Timestamp代表的时间 in microsecond
// 输出
// toString()返回内置时间的字符串（带.的六位小数）
// toFormattedString(true/false) 返回时间，可选是否带微秒
	// 20211216 13:35:15 不带微秒
	// 20211216 13:35:15.202477 带微秒

class Timestamp {
private:
	int64_t MiuSSinceEpoch_;
	static const int M = 1000 * 1000;

public:
	explicit Timestamp(int64_t tt) : MiuSSinceEpoch_(tt) {}
	Timestamp(Timestamp &ts) : MiuSSinceEpoch_(ts.MiuSSinceEpoch_) {}
	~Timestamp() {}
	static Timestamp now() {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		int64_t seconds = tv.tv_sec;
		return Timestamp(seconds * M + tv.tv_usec);
	}

	void addMS(int64_t ms) {
		MiuSSinceEpoch_ += ms * 1000;
	}

	void becomeNow() {
		struct timeval tv;
		gettimeofday(&tv, NULL);
		int64_t seconds = tv.tv_sec;
		this->MiuSSinceEpoch_ = seconds * M + tv.tv_usec;
	}

	int64_t get() {
		return MiuSSinceEpoch_;
	}

	inline bool operator<(Timestamp a) {
		return this->get() < a.get();
	}

	inline bool operator==(Timestamp a) {
		return this->get() == a.get();
	}

	inline bool operator>(Timestamp a) {
		return this->get() > a.get();
	}

// 输出字符用
	std::string toString() const
	{
		char buf[32] = {0};
		int64_t seconds = MiuSSinceEpoch_ / M;
		int64_t microseconds = MiuSSinceEpoch_ % M;
		snprintf(buf, sizeof(buf), "%" PRId64 ".%06" PRId64 "", seconds, microseconds);
		return buf;
	}

	std::string toFormattedString(bool showMicroseconds) const
	{
		char buf[64] = {0};
		time_t seconds = static_cast<time_t>(MiuSSinceEpoch_ / M);
		struct tm tm_time;
		gmtime_r(&seconds, &tm_time);

		if (showMicroseconds)
		{
			int microseconds = static_cast<int>(MiuSSinceEpoch_ % M);
			snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d.%06d",
			         tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			         tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec,
			         microseconds);
		}
		else
		{
			snprintf(buf, sizeof(buf), "%4d%02d%02d %02d:%02d:%02d",
			         tm_time.tm_year + 1900, tm_time.tm_mon + 1, tm_time.tm_mday,
			         tm_time.tm_hour, tm_time.tm_min, tm_time.tm_sec);
		}
		return buf;
	}
};

#endif