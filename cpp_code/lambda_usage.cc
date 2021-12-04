// lambda 表达式表示一个可调用的代码单元。
// 一个 lambda 表达式具有一个返回类型、一个参数列表和一个函数体
// [capture-list] (parameter list) -> return type(optional) { function body } 

// 例子：
auto cmp = [](int a, int b) {return a < b;};
// 调用方法
bool xIsSmaller = cmp(x, y);	// 若cmp无参数列表，也需要加括号，例如：cmp()

// 用法：
// 1. priority_queue 声明的第三个参数 decltype(lambda) > = q(lambda)
// 2. 