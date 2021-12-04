// 一个可以运行的仿函数示例
#include <iostream>
#include <string>
using namespace std;

class FunctorThatPrintSomething
{
public:
	void operator() (const string str) const
	{
		cout << str << endl;
	}
};

int main()
{
	FunctorThatPrintSomething functorOne;
	functorOne("Hello world!");
	return 0;
}