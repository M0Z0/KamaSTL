#ifndef __H_VECTOR__
#define __H_VECTOR__

#include "Allocator.h"

namespace HandySTL{

	template <class T, class Alloc = allocator<T>>
	class vector{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	private:
		pointer start;
		pointer finish;
		pointer end_of_storage;

	public:
		//构造、拷贝构造、析构
		vector() :start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
		explicit vector(const size_type n);
		explicit vector(const size_type n, value_type& value);

	private:
		void allocate_and_fill(const size_type n, const value_type& value);
	};//end of class

}

#include "impl/vector.impl.h"

#endif