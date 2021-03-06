#ifndef _Thread_H_
#define _Thread_H_

#include <pthread.h>
#include <functional>   // std::function
#include <memory>       // ζΊθ½ζι
#include "noncopyable.h"
#include "CountDownLatch.h"
#include <sys/syscall.h>
#include <unistd.h>
#include <string>

class Thread : noncopyable {
public:
    typedef std::function<void()> ThreadFunc;
    explicit Thread(const ThreadFunc&, const std::string& name = std::string());
    ~Thread();
    void start();
    int join();

    bool started() const { return started_; }
    pid_t tid() const { return tid_; }
    const std::string& name() const { return name_; }
private:
    void setDefaultName();
    bool started_;
    bool joined_;
    pthread_t pthreadId_;
    pid_t tid_;
    ThreadFunc func_;
    std::string name_;
    CountDownLatch latch_;
};
#endif
