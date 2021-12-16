#include "Timestamp.h"
#include <iostream>
using namespace std;
int main() {
	Timestamp a = Timestamp::now();
	Timestamp b = Timestamp::now();
	cout<<a.toString()<<endl;
	cout<<b.toString()<<endl;
	if(a < b)
		cout<<"b 大"<<endl;
	else if(b > a)
		cout<<"a 大"<<endl;
	else
		cout<<"一样大"<<endl;
	return 0;
}
