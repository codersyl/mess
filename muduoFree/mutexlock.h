// mine
#ifndef _MUTEXLOCK_H_
#define _MUTEXLOCK_H_


#include <pthread.h>
#include "base/noncopyable.h"

/* 使用方法
 * 写一个{}块，然后块第一行调用
 * MutexLockGuard(mutex);
 * 之后就访问资源就行了
 * 也不用解锁
 */

// 无holder_版本
class MutexLock : noncopyable {
public:
    // 构造函数：搞一个mutex线程锁
    MutexLock() {pthread_mutex_init(&mutex_, NULL); }
    ~MutexLock() {
        pthread_mutex_lock(&mutex_);
        pthread_mutex_destroy(&mutex_);
    }
    void lock() { pthread_mutex_lock(&mutex_); }
    void unlock() { pthread_mutex_unlock(&mutex_); }
    pthread_mutex_t *get() { return &mutex_; }

 private:

    pthread_mutex_t mutex_;

    // 友元类不受访问权限影响，妹理解
 private:
    friend class Condition;
};

class MutexLockGuard : noncopyable {
public:
    explicit MutexLockGuard(MutexLock &mutex) : mutex_(mutex) { mutex_.lock(); }
    ~MutexLockGuard() { mutex_.unlock(); }

private:
    MutexLock &mutex_;
};


#endif  // MUTEXLOCK_H_