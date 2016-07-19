#include <iostream>
template<typename T>
struct MyIter
{
	typedef T type_value;
	MyIter(T *p = 0) :ptr(p) {}
	T& operator*()
	{
		return *ptr;
	}

private:
	T *ptr;
};

template<typename I>
struct iterator_traits
{
	typedef typename I::type_value type_value;
};

template<typename I>
struct iterator_traits<I*>
{
	typedef I type_value;
};

template<typename I>
struct iterator_traits<const I*>
{
	typedef I type_value;
};

template<typename T>
typename iterator_traits<T>::type_value func(T ite){
	return *ite;
}

//int main()
//{
//	MyIter<int> it(new int(8));
//	std::cout << func(it);
//}