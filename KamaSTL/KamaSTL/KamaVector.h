/**
* @file vector.h
* @brief a simple vector class
* @author makai
* @date 2016.7.17
*/

#ifndef _KAMA_VECTOR_
#define _KAMA_VECTOR_

#include <iostream>  
#include <algorithm>  
#include <memory>  

namespace Km{

	template<typename T>
	class KamaVector{
	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const T* const_pointer;
		typedef value_type* iterator;
		typedef const T*const_iterator;
		typedef value_type& reference;
		typedef const T& const_reference;
		typedef size_t size_type;

	public:
		KamaVector();
		KamaVector(size_type n, T value = T());
		KamaVector(iterator begin, iterator end);
		~KamaVector();

		//copy control  
		KamaVector(const KamaVector&);
		KamaVector& operator=(const KamaVector&);

		bool empty() const { return begin() == end(); }
		size_type size() const { return (size_type)(finish - start); }
		size_type capacity() const { return (size_type)(end_of_storage - start); }

		iterator begin() { return start; }
		const_iterator begin() const{ return start; }
		iterator end()   { return finish; }
		const_iterator end() const{ return finish; }

		reference operator[](size_type i){ return *(start + i); }
		const_reference operator[](size_type i)const { return *(start + i); }

		void insert(iterator position, size_type n, const T& value);
		void push_back(const T& value);
		void pop_back();

		void erase(iterator first, iterator last);
		void clear();

		void reserve(size_type n);

	protected:
		iterator start;//目前使用的空间的头
		iterator finish;//目前使用的空间的尾
		iterator end_of_storage;//目前可用的空间的尾

	private:
		static std::allocator<T> alloc; // object to get raw memory 
	};

	// static class member needed to be defined outside of class  
	template<typename T>
	std::allocator<T> KamaVector<T>::alloc;

	// default constructor  
	template<typename T>
	KamaVector<T>::KamaVector()
		: start(NULL), finish(NULL), end_of_storage(NULL)
	{
	}

	template<typename T>
	KamaVector<T>::KamaVector(size_type n, T value)
	{
		start = alloc.allocate(n);
		end_of_storage = finish = start + n;

		for (iterator i = start; i != finish; ++i)
			alloc.construct(i, value);
	}
}

#endif