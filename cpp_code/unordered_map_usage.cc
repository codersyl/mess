// unordered_map
#include <unordered_map>

// 构造方法
std::unordered_map<int,int> first;	// O(1), empty
std::unordered_map<int,int> second(first.begin(), first.end());	// O(n), maybe O(n^2), range
std::unordered_map<int,int> third(first);	// O(1), copy
std::unordered_map<int,int> fourth(merge(first, second));	// O(n), maybe O(n^2), move，把 first 和 second 装进 fourth
std::unordered_map<int,int> third( { {1,1} , {2,2} } );	// initialzation



// at
// 只改值，不差值
first.at( k ) = v;
// 该语句相当于 first[k] = v
// 不同的是，k 需要本身就在 first 里，不然Exception
// O(1), worst O(n)


// begin
// end
first.begin();	// 第一个元素的 iterator
first.begin(int pos)	//	返回 bucket pos 的第一个元素的 iterator
first.begin(int pos)	//	返回 bucket pos 的最后一个元素的后面一个 iterator
// O(1)


// bucket_count
first.bucket_count();
// 返回现有的 bucket 的数量
// O(1)


// bucket_size()
first.bucket_size(int n);	// n shall be smaller than first.bucket_count()
// 返回 index 为 n 的 bucket 中的元素的数量
// O(m)，m 为返回值的大小


// clear
first.clear();
// 清空 map，不解释
// O(n)，n 为 first 中所有元素的个数


// count
first.count(k);
// 返回 first 中等于 k 的 key 值的个数
// 由于在 map 中 key 具有唯一性，所以返回值只能为 0 或者 1
// O(数过的元素数量)，最差情况，与 first 尺寸成比例


// emplace
// 只插值，不改值
first.emplace( k , v );
// 让 first[k] = v
// 但是不支持改值
// 返回 一个 pair，左边是一个iterator，指向 key 为 k 的键值对，右边是是否插入成功
// O(1)，最糟情况，O(n)，可能会触发 rehash


// emplace_hint
// need to be filled


// empty
first.empty();
// 判断 map 是否为空，不解释
// O(1)




// equal_range
first.equal_range(k);
// need to be filled，不是很明白
// O(1)，最差 O(n)


// erase
first.erase(iterator position_in_iterator_form);		// O(1)，有时会调整占用内存大小，平均下来还是常数耗时
first.erase(k);								// O(ln n)
first.erase(first.begin(), first.end());	// O(m)，m为要删除的范围的长度
// cpp98 无返回值
// cpp11 返回一个 iterator，指向被删元素的后一个键值对，如果删的是最后一个，那么会是 first.end()
// O(m)，m 为要删除的元素个数，最坏情况为 O(n)


// find
first.find(k);
// 如果 first 里有 k，则返回对应的 iterator
// 如果没有，怎返回 first.end()
// O(1)，最坏情况 O(n)

// pause


// get_allocator
// need to be filled


// insert
// 
first.insert( {k,v} );
first.insert( pair<int,int>(1, 1) );
first.insert(hit_iterator, {k,v});	// hint 是用来提示插入位置的，好的 hint 可以提高插入效率
first.insert(second.begin(), second.end());	// 把 second 里的 k-v 全插入到 first 里去
// 第三种合理利用可以提高效率
// O(ln n)，如果 hint 给的好，可以近似常数耗时


// key_comp
std::map<int, int> mycomp = first.key_comp
// 构造 map 时的第三个参数
// 用来决定 map 中存的 k-v 对如何排序


// lower_bound
auto it = first.lower_bound(k);
// k 不一定要在 first 里
// 返回一个 iterator
// 如果 first 里有 k， 则返回 k 的 iterator
// 如果没有 k，则返回大于 k 的最小的 key 对应的 iterator
// 如果 first 里所有 key 都小于 k，则返回 first.end()
// O(ln n)


// upper_bound
auto it = first.upper_bound(k);
// 返回第一个大于 k 的 iterator
// 好像还是没搞明白，上面一行不一定对
// need to be filled
// O(ln n)


// max_size
unsigned int = first.max_size();
// 可以容纳的最大元素数量
// O(1)


// size
unsigned int = first.size();
// 现在的元素数量
// O(1)


// operator=
// 分成两种：
// 		复制 = : 把一个好多元素的 map 给一个空的， O(n)，n 为新尺寸
//		移动 = : 让一个好多元素的 map 变成空的，O(n)，n 为老尺寸


// operator[]
first[k];
// 返回值为 k 对应的 k-v 的 v 的值
// 注意！若 first 中没有 k，哪怕没给 first[k] 赋值，也会使得 first 中增加以 k 为键的元素对
// O(ln n)


// size
first.size();
// 返回 first 中现有元素的数量
// O(1)


// swap
first.swap( second );
// 把两个 map 的内容物换一下
// O(1)


// value_comp
// need to be filled
// O(1)


// 比大小
// need to be filled


// swap 非成员函数版
swap(first, second);



/////////////////////////////////////////////////////////////////

// 只改值，不插值
first.at( k ) = v;



// 只插值，不改值
first.emplace( {k, v} );
first.insert( {k,v} );



// 可插可改
first[k] = v;

