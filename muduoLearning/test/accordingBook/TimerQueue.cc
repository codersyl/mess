// #include "TimerQueue.h" 

// TimerQueue::TimerQueue() {}
// TimerQueue::~TimerQueue() {}

// void TimerQueue::addTimer(std::shared_ptr<HttpData> dataSP, int timeout) {
//     SP_Timer timerSP(new Timer(dataSP, timeout));
//     timerQueue_.push(timerSP);
//     dataSP->linkTimer(timerSP);
// }

// // 对于被置为deleted_的时间节点，会延迟到它
// // 超时 or 它前面的节点都被删除时，它才会被删除。
// // 一个点被置为deleted_,它最早会在过期时间到了后才被删除，这样做有两个好处：
// // (1) 不需要遍历优先队列，省时。
// // (2) 如果监听的请求在超时后的下一次请求中又一次出现了，就不用再重新申请HttpData
// void TimerQueue::handleExpiredEvent() {
//     while (!timerQueue_.empty()) {
//         SP_Timer timerAtTopSP = timerQueue_.top();
//         if (timerAtTopSP->isDeleted())
//             timerQueue_.pop();
//         else if (timerAtTopSP->isValid() == false)
//             timerQueue_.pop();
//         else break;
//     }
// }