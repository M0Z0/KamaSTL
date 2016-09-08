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

		typedef Alloc dataAllocator;
	public:
		//构造、拷贝构造、析构
		vector() :start(nullptr), finish(nullptr), end_of_storage(nullptr) {}
		explicit vector(const size_type n);
		explicit vector(const size_type n, value_type& value);
		vector(const vector&);
		vector(vector&&);
		vector& operator=(const vector&);
		vector& operator=(vector&&);

		difference_type capacity() const { return end_of_storage - start; }

	private:
		void destroyAndDeallocateAll();
		void allocate_and_fill(const size_type n, const value_type& value);
		template<class InputIterator>
		void allocate_and_copy(InputIterator first, InputIterator last);
	};//end of class

}

#include "impl/vector.impl.h"

#endif