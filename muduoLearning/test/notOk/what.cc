#include "Timestamp.h"
#include <iostream>
#include <unistd.h>
using namespace std;
int main() {
	Timestamp a = Timestamp::now();
	sleep(5);
	Timestamp b = Timestamp::now();
	cout<<a.toString()<<endl;
	cout<<b.toString()<<endl;
	return 0;
}
