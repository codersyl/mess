#include <queue>

// 默认大的在顶端
priority_queue<int>	q;
// 上面这个声明等价于：
priority_queue<int, vector<int>, less<int> > q;

// 若需要小的在顶部，可这样声明
priority_queue<int, vector<int>, greater<int> > q;


// 自定义排序方法
// 1. lambda 函数与 decltype
auto cmp = [](int a, int b) {return a > b;};
priority_queue<int, vector<int>, decltype(cmp)> q(cmp);

// 2. 重载operator<
// 此方法会破坏类型原有的大小判断方法，故最好重载后的<要符合逻辑
// 若不符合逻辑，最好专门造一个结构体来重载，且确保该结构体不用于其他地方


// 3. 重写仿函数
struct cmp {
	bool operator() (int a, int b) {
		return	 a > b;
	}
};
priority_queue<int, vector<int>, cmp > q;