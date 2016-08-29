#ifndef __H_ITERATOR__
#define  __H_ITERATOR__
#include <cstddef>


struct input_iterator_tag { };
struct output_iterator_tag { };
struct forward_iterator_tag : public input_iterator_tag { };
struct bidirectional_iterator_tag : public forward_iterator_tag{ };
template <class T>
struct iterator_traits
{
	typedef typename T::iterator_category iterator_category;
	typedef typename T::value_type value_type;
	typedef typename T::difference_type difference_type;
	typedef typename T::pointer pointer;
	typedef typename T::reference reference;
};

//偏特化版本，内置指针类型
template <class T>
struct iterator_traits<T*>
{
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer pointer;
	typedef T& reference reference;
};

template <class T>
struct iterator_traits<const T*>
{
	typedef T value_type;
	typedef ptrdiff_t difference_type;
	typedef T* pointer pointer;
	typedef T& reference reference;
};
#endif