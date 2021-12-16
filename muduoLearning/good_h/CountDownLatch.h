#ifndef _CountDownLatch_H_
#define _CountDownLatch_H_
#include "Condition.h"
#include "MutexLock.h"

// 基础的同步工具，用于等待其他 count_ 个线程
class CountDownLatch : noncopyable {
public:
    explicit CountDownLatch(int count)
        : mutex_(), condition_(mutex_), count_(count) {}

    // wait 供主线程调用
    // 等其他几个线程的准备工作完成后，可继续运行
    void wait() {
        MutexLockGuard lock(mutex_);
        while (count_ > 0)
            condition_.wait();
    }

    // 支线程调用，表示准备工作完成
    void countDown() {
        MutexLockGuard lock(mutex_);
        --count_;
        if (count_ == 0)
            condition_.notifyAll();
    }

private:
    mutable MutexLock mutex_;
    Condition condition_;
    int count_;
};

#endif  // _CountDownLatch_H_