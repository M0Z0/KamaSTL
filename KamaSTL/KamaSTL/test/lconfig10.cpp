//����template�����ɷ����ǰһ��template�������趨Ĭ��ֵ
#include <iostream>
#include <cstddef>  // for size_t
using namespace std;

class alloc{};

template<class T, class Alloc = alloc, size_t bufSiz = 0>
class deque{
public:
	deque() { cout << "deque" << endl; }
};

//����ǰһ������ֵT�� �趨��һ������Sequence��Ĭ��ֵΪdeque<T>
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