#ifndef __H_VECTOR_IMPL__
#define __H_VECTOR_IMPL__

#include "vector.h"
#include "uninitialized.h"

namespace HandySTL{

	template <class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n) {
		allocate_and_fill(n, value_type());
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(const size_type n, value_type& value) {
		allocate_and_fill(n, value);
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(const vector &v) {
		allocate_and_copy(v.start, v.finish);
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(vector &&v) {
		this->start = v.start;
		this->finish = v.finish;
		this->end_of_storage = v.end_of_storage;
		v.start = v.finish = v.end_of_storage = nullptr;
	}

	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector &v) {
		if (this != &v)
			allocate_and_copy(v.start, v.finish);
		return *this;
	}

	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector &&v) {
		if (this != &v) {
			destroyAndDeallocateAll();
			this->start = v.start;
			this->finish = v.finish;
			this->end_of_storage = v.end_of_storage;
			v.start = v.finish = v.end_of_storage = nullptr;
		}
		return *this;
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::allocate_and_fill(const size_type n, const value_type& value) {
		start = dataAllocator::allocate(n);
		HandySTL::uninitialized_fill_n(start, n, value);
		finish = end_of_storage = start + n;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last) {
		start = dataAllocator::allocate(n);
		finish = HandySTL::uninitialized_copy(first, last, start);
		end_of_storage = finish;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::destroyAndDeallocateAll(){
		if (capacity() != 0){
			dataAllocator::destroy(start, finish);
			dataAllocator::deallocate(start, capacity());
		}
	}

}

#endif