// mine
include "Channel.h" 
include "EventLoop.h"

#include <sys/epoll.h>

Channel::Channel(EventLoop* loop, int fd) :
    loop_(loop),
    fd_(fd),
    events_(0),
    revents_(0),
    index_(-1) {
}

Channel::~Channel() {
}

void Channel::update() {
    loop_->updateChannel(this);
}

void Channel::handleEvent() {
    events_ = 0;
    if ((revents_ & EPOLLHUP) && !(revents_ & EPOLLIN)) {
        events_ = 0;
        return;
    }
    if (revents_ & EPOLLERR) {
        if (ErrorCallback_) ErrorCallback_();
        events_ = 0;
        return;
    }
    if (revents_ & (EPOLLIN | EPOLLPRI | EPOLLRDHUP)) {
        if(ReadCallback_) ReadCallback_();
    }
    if (revents_ & EPOLLOUT) {
        if(WriteCallback_) WriteCallback_();
    }
}