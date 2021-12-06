#include <memory>

// --------------------------------------------------------------------
// shared_ptr
// 声明
shared_ptr<int>	p(q); // 用共享指针管理原生指针 q 所指向的对象
shared_ptr<int>	p(q, d);	// 同上，但销毁对象时会调用d 
shared_ptr<int>	p(p2, d);	// 同上，区别是 p2 是一个智能指针
shared_ptr<int>	p(u); // 用共享指针接管unique_ptr u 所管理的资源

// .reset()
p.reset();	// 若 p 是唯一一个指向该对象的指针，则会销毁，然后将 p 置空
p.reset(q);	// 同上，但是会管理 q 所指资源
p.reset(q, d);	// 同上，但是之后会调用 d 来销毁新接管的资源


// --------------------------------------------------------------------
// unique_ptr
// 声明
unique_ptr<int> u_ptr = make_unique<int>();	// make_unique 需要C++14支持
unique_ptr<string>	su_ptr(new string("stone free!"));
// 错误的声明，因为 unique_ptr 不支持拷贝
unique_ptr<string>	wrong_way(su_ptr); // X
unique_ptr<string>	wrong_way;
wrong_way = su_ptr;		// 错误，因为 unique_ptr 不支持赋值

// 释放
su_ptr = nullptr;
su_ptr.reset();

// .release() 返回当前指针，然后置空，但是不会回收内存，一般用于将资源交给另一个 unique_ptr
wrong_way.reset( su_ptr.release() );
// 陷阱：若某一行只有 aUnPtr.release()，则会切段智能指针与资源对象的联系，且不会释放资源
willBeLeaked.release(); // wrong

// 禁止拷贝与赋值，但有例外：
// 作为返回值返回的时候，由于函数结束，即将离开作用域，应被销毁
// 但可以其成功传递出去并且可被复制
// 例：
unique_ptr<int>	get(int a) {
	return	unique_ptr<int>(new int(a));
}
unique_ptr<int> uPtr;
uPtr = get(10);	// ok


// --------------------------------------------------------------------
// weak_ptr
// 声明
weak_ptr<int> wp;
weak_ptr<int> wp(sp);	// 用 shared_ptr 进行初始化
w = p;	// p可以是 shared_ptr 或者 weak_ptr

// .reset
wp.reset()	// 将 wp 置空

// .use_count()
wp.use_count()	// 返回 wp 所指对象的引用计数（即有多少个shared_ptr指向它)

// .expired()
wp.expired()	// 若 wp 指的对象已经没了，则 true，否则返回 false

// .lock()
wp.lock()		// 若对象已经销毁，则返回一个空智能指针，否则返回指向对象的shared_ptr