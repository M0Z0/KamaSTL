#ifndef __H_VECTOR__
#define __H_VECTOR__

#include "Allocator.h"

namespace HandySTL{

	template <class T, class Alloc = allocator<T>>
	class Vector{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	private:
		iterator start;
		iterator finish;
		iterator end_of_storage;

	public:
		//构造、拷贝构造、析构
		Vector() :start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
		explicit Vector(const size_type n);
		explicit Vector(const size_type n, value_type& value);

	private:
		
	};//end of class

}

#include "impl/Vector.impl.h"

#endif