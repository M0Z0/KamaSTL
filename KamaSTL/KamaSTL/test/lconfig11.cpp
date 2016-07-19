//测试class template可否拥有non-type template参数
#include <iostream>
#include <cstddef> 
using namespace std;

class alloc{};

inline size_t __deque_buf_size(size_t n, size_t sz)
{
	return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
}

template<class T, class Ref, class Ptr, size_t bufSiz>
struct __deque_iterator 
{
	typedef __deque_iterator<T, T&, T*, bufSiz> iterator;
	typedef __deque_iterator<T, const T&, const T*, bufSiz> const_iterator;
	static size_t buffer_size() { return __deque_buf_size(bufSiz, sizeof(T)); }
};

template<class T, class Alloc = alloc, size_t bufSiz = 0>
class deque{
public:
	typedef __deque_iterator<T, T&, T*, bufSiz> iterator;
};

//int main()
//{
//	cout << deque<int>::iterator::buffer_size() << endl;
//	cout << deque<int, alloc, 64>::iterator::buffer_size() << endl;
//	getchar();
//}