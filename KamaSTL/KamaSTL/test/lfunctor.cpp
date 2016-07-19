#include <iostream>
using namespace std;

template<class T>
struct plusK{
	T operator() (const T& x, const T& y) const
	{
		return x + y;
	}
};

template<class T>
struct minusK{
	T operator() (const T& x, const T& y) const
	{
		return x - y;
	}
};

//int main()
//{
//	plus<int> p;
//	cout << p(3, 5) << endl;
//	//以下直接产生仿函数的临时对象
//	cout << minus<int>()(2, 4) << endl;
//	getchar();
//
//}