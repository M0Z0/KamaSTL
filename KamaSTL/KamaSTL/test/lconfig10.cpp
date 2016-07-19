//测试template参数可否根据前一个template参数而设定默认值
#include <iostream>
#include <cstddef>  // for size_t
using namespace std;

class alloc{};

template<class T, class Alloc = alloc, size_t bufSiz = 0>
class deque{
public:
	deque() { cout << "deque" << endl; }
};

//根据前一个参数值T， 设定下一个参数Sequence的默认值为deque<T>
template<class T, class Sequence = deque<T> >
class stack{
public:
	stack() { cout << "stack" << endl; }
private:
	Sequence c;
};

//int main()
//{
//	stack<char> s;
//	getchar();
//}