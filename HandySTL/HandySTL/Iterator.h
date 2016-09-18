#ifndef __H_ITERATOR__
#define  __H_ITERATOR__
//#include <cstddef>

namespace HandySTL{

	struct input_iterator_tag { };
	struct output_iterator_tag { };
	struct forward_iterator_tag : public input_iterator_tag { };
	struct bidirectional_iterator_tag : public forward_iterator_tag { };
	struct random_access_iterator_tag : public bidirectional_iterator_tag { };

	template <class T, class Distance>
	struct input_iterator
	{
		typedef input_iterator_tag iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef T* pointer;
		typedef T& reference;
	};
    
	struct output_iterator
	{
		typedef output_iterator_tag iterator_category;
		typedef void value_type;
		typedef void difference_type;
		typedef void pointer;
		typedef void reference;
	};

	template <class T, class Distance> 
	struct forward_iterator
	{
		typedef forward_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance difference_type;
		typedef T*	 pointer;
		typedef T& reference;
	};
	template <class T, class Distance>
	struct bidirectional_iterator
	{
		typedef bidirectional_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance difference_type;
		typedef T* pointer;
		typedef T& reference;
	};
	template <class T, class Distance>
	struct random_access_iterator
	{
		typedef random_access_iterator_tag	iterator_category;
		typedef T	value_type;
		typedef Distance difference_type;
		typedef T*	 pointer;
		typedef T& reference;
	};

	template <class Category, class T, class Distance = ptrdiff_t, class Pointer = T*, class Reference = T&>
	struct iterator
	{
		typedef Category iterator_category;
		typedef T value_type;
		typedef Distance difference_type;
		typedef Pointer pointer;
		typedef Reference reference;
	};

	template <class T>
	struct iterator_traits
	{
		typedef typename T::iterator_category iterator_category;
		typedef typename T::value_type value_type;
		typedef typename T::difference_type difference_type;
		typedef typename T::pointer pointer;
		typedef typename T::reference reference;
	};

	//偏特化版本，针对内置指针类型
	template <class T>
	struct iterator_traits<T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template <class T>
	struct iterator_traits<const T*>
	{
		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};

	template<class Iterator>
	inline typename iterator_traits<Iterator>::iterator_category
		iterator_category(const Iterator& It){
			typedef typename iterator_traits<Iterator>::iterator_category category;
			return category();
		}
	template<class Iterator>
	inline typename iterator_traits<Iterator>::value_type*
		value_type(const Iterator& It){
			return static_cast<typename iterator_traits<Iterator>::value_type*>(0);
		}
	template<class Iterator>
	inline typename iterator_traits<Iterator>::difference_type*
		difference_type(const Iterator& It){
			return static_cast<typename iterator_traits<Iterator>::difference_type*>(0);
		}

	template <class T, class Distance>
	inline Distance* distance_type(const input_iterator<T, Distance>&) {
		return (Distance*)(0);
	}

	template <class T, class Distance>
	inline Distance* distance_type(const forward_iterator<T, Distance>&) {
		return (Distance*)(0);
	}

	template <class T, class Distance>
	inline Distance*
		distance_type(const bidirectional_iterator<T, Distance>&) {
			return (Distance*)(0);
		}

	template <class T, class Distance>
	inline Distance*
		distance_type(const random_access_iterator<T, Distance>&) {
			return (Distance*)(0);
		}

	template <class T>
	inline ptrdiff_t* distance_type(const T*) { return (ptrdiff_t*)(0); }

	// 以下是整組 distance 函式
	template <class InputIterator, class Distance>
	inline void __distance(InputIterator first, InputIterator last, Distance& n,
		input_iterator_tag) {
		while (first != last) { ++first; ++n; }
	}

	template <class RandomAccessIterator, class Distance>
	inline void __distance(RandomAccessIterator first, RandomAccessIterator last,
		Distance& n, random_access_iterator_tag) {
		n += last - first;
	}

	template <class InputIterator, class Distance>
	inline void distance(InputIterator first, InputIterator last, Distance& n) {
		__distance(first, last, n, iterator_category(first));
	}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		__distance(InputIterator first, InputIterator last, input_iterator_tag) {
			iterator_traits<InputIterator>::difference_type n = 0;
			while (first != last) {
				++first; ++n;
			}
			return n;
		}

	template <class RandomAccessIterator>
	inline typename iterator_traits<RandomAccessIterator>::difference_type
		__distance(RandomAccessIterator first, RandomAccessIterator last,
		random_access_iterator_tag) {
			return last - first;
		}

	template <class InputIterator>
	inline typename iterator_traits<InputIterator>::difference_type
		distance(InputIterator first, InputIterator last) {
			typedef typename iterator_traits<InputIterator>::iterator_category category;
			return __distance(first, last, category());
		}

}

#endif