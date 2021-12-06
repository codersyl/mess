#include <pthread.h> 
// reference:
// https://blog.csdn.net/networkhunter/article/details/100218945

// 线程的创建
int pthread_create(pthread_t *thread, const pthread_attr_t *attr, void *(*start_routine)(void*), void *arg); 
// 线程句柄会传给 thread
// 线程属性 attr 用于设置线程的属性。当不需要修改线程的默认属性时，传递 NULL 就行
// 入口函数 start_routine() ：线程的入口函数。如果线程创建成功，这个接口会返回0


// 线程的合并
int pthread_join(pthread_t thread, void ** retval);
// 进行这个调用的线程会一直阻塞，直到线程 thread 执行完毕
// thread 表示我们需要接收的线程
// retval 用来接收此线程的返回值

// 返回值有以下几种可能，
// EDEADLK：检测到线程发生了死锁。关于线程发生死锁，我们会在《Linux如何避免线程发生死锁？》一节中做详细讲解。
// EINVAL：分为两种情况，要么目标线程本身不允许其它线程获取它的返回值，要么事先就已经有线程调用 pthread_join() 函数获取到了目标线程的返回值。
// ESRCH：找不到指定的 thread 线程。
// 这些宏都存储在
#include <errno.h>


// 线程的分离
pthread_detach(pthread_t thread);
// 与线程合并类似，都是用于回收某个线程的资源
// 区别是调用此函数后，当前线程不会被搁置


// 线程的属性
// 一般地，Linux下的线程有：绑定属性、分离属性、调度属性、堆栈大小属性和满占警戒区大小属性。
// 线程属性对象由pthread_attr_init()接口初始化
int pthread_attr_init(pthread_attr_t *attr);  
// 线程属性由pthread_attr_destory()来销毁
int pthread_attr_destory(pthread_attr_t *attr);  
// 设置绑定属性：
int pthread_attr_setscope(pthread_attr_t *attr, int scope);
// 参数1是线程属性对象的指针
// 参数2是绑定类型，拥有两个取值：PTHREAD_SCOPE_SYSTEM（绑定的）和PTHREAD_SCOPE_PROCESS（非绑定的）


// 互斥锁
// 锁的初始化
int pthread_mutex_init(pthread_mutex_t *restrict mutex, const pthread_mutexattr_t *restrict attr);  
// 锁的销毁
int pthread_mutex_destory(pthread_mutex_t *mutex);  
// 加锁
int pthread_mutex_lock(pthread_mutex_t *mutex);
// 尝试加锁
// 用它加锁不成功不会被搁置，而是会返回 EBUSY
int pthread_mutex_trylock(pthread_mutex_t *mutex);
// 解锁
int pthread_mutex_unlock(pthread_mutex_t *mutex);  


// 条件变量
// 条件变量初始化
int pthread_cond_init(pthread_cond_t *cond, const pthread_condattr_t *attr);
// 条件变量的销毁
int pthread_cond_destory(pthread_cond_t *cond);
// 等待事件发生
int pthread_cond_wait(pthread_cond_t *cond, pthread_mutex_t *mutex);
int pthread_cond_timedwait(pthread_cond_t *cond, pthread_mutex_t *mutex, const timespec *abstime);	// 等一段时间，没发生就干别的
// 控制事件发生
int pthread_cond_signal(pthread_cond_t *cond);
int pthread_cond_broadcast(pthread_cond_t *cond);	// 广播事件的发生