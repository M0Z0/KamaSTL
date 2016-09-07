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
	void vector<T, Alloc>::allocate_and_fill(const size_type n, const value_type& value) {
		start = alloc::allocate(n);
		HandySTL::uninitialized_fill_n(start, n, value);
		finish = end_of_storage = start + n;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last) {
		start = alloc::allocate(n);
		finish = HandySTL::uninitialized_copy(first, last, start);
		finish = end_of_storage = start + n;
	}
}

#endif