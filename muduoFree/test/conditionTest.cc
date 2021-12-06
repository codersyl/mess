#include <unistd.h>
#include <thread>         // std::thread
#include <pthread.h>
#include <iostream>
#include "../MutexLock.h"
#include "../Condition.h"
#include <vector>

MutexLock mtx;
std::vector<int>	v;
Condition buffEvent(mtx);

void consumer()
{
	// 消耗 1500个吧
	std::cout<<"consumer start ---"<<std::endl;
	// MutexLockGuard a(mtx);
	// for(int i = 0; i < 1500; i++) {
	// 	while(v.empty())
	// 		buffEvent.wait();
	// 	assert(!v.empty());
	// 	std::cout<<"consume NO."<<v.size()<<" : "<<v.back()<<std::endl;
	// 	v.pop_back();
	// }
}

void producer()
{
	// 生产 2000 个
	std::cout<<"PRODUCER start ---"<<std::endl;
	// MutexLockGuard b(mtx);
	// for(int i = 0; i < 2000; i++) {
	// 	v.push_back(i);
	// 	std::cout<<"PRODUCE NO."<<v.size()<<" : "<<v.back()<<std::endl;
	// 	buffEvent.notify();
	// }
}

int main() {
	std::thread first(consumer);
	std::thread second(producer);
	return 0;
}