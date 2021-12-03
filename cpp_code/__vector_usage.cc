// vector usage


// constructor
std::vector<int> first;                                // empty vector of ints
std::vector<int> second (4,100);                       // four ints with value 10
std::vector<int> oh(100);                              // get 100 zeros
std::vector<int> third (second.begin(),second.end());  // iterating through second
std::vector<int> fourth (third);
// the iterator constructor can also be used to construct from arrays:
int ints[] = {16,2,77,29};
std::vector<int> fifth (ints,ints + sizeof(ints) / sizeof(int) );


// assign
first.assign(7,100);             // 7 ints with a value of 100
second.assign(first.begin(), first.end()); // get a copy of vector first


// at
first.at(2);    // 相当于 first[2]，好处是比较安全


// front
first.front();  // 返回first的第一个元素的值


// back
first.back();   // 返回first的最后一个元素的值


// iterator
// begin
first.begin();
// end
first.end();
// cbegin
// 返回const_iterator，具体区别不详，待学习
first.cbegin();
// cend
// 返回const_iterator，具体区别不详，待学习
first.cend();
// rbegin
first.rbegin();
// rend
first.rend();
// crbegin
first.crbegin();
// crend
first.crend();


// capacity
// 得到目前first分到的内存能够支持的size大小，大于等于first.size()
// first不断扩张直至大于capacity的话，会申请另一块更大一点的内存
first.capacity();


// clear
// 把vector清空
first.clear();


// data
// 返回一个指针，指向第一个元素
first.data();


// emplace
first.emplace (first.begin()+1, 100);   // 在第二个位置插入100，且返回值为一个itetator，指向新加入的那个100


// emplace_back
// C++11 无返回值
// C++14 返回一个对这个值的引用
first.emplace_back(100);    // 在结尾加上100


// empty
first.empty()


// erase
first.erase(1);     // 删除index为1的元素，后面的前移
first.erase(1,3);   // 删除index为[1,3)的元素，后面的前移


// get_allocator
// 不太懂，待学习
first.get_allocator();  // 返回allocator的一个copy


// insert