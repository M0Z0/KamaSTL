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
		allocate_and_copy(v._start, v._finish);
	}

	template <class T, class Alloc>
	vector<T, Alloc>::~vector() {
		destroyAndDeallocateAll;
	}

	template <class T, class Alloc>
	vector<T, Alloc>::vector(vector &&v) {
		this->_start = v._start;
		this->_finish = v._finish;
		this->_end_of_storage = v._end_of_storage;
		v._start = v._finish = v._end_of_storage = nullptr;
	}

	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(const vector &v) {
		if (this != &v)
			allocate_and_copy(v._start, v._finish);
		return *this;
	}

	template <class T, class Alloc>
	vector<T, Alloc>& vector<T, Alloc>::operator=(vector &&v) {
		if (this != &v) {
			destroyAndDeallocateAll();
			this->_start = v._start;
			this->_finish = v._finish;
			this->_end_of_storage = v._end_of_storage;
			v._start = v._finish = v._end_of_storage = nullptr;
		}
		return *this;
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::push_back(const value_type& value);

	template <class T, class Alloc>
	void vector<T, Alloc>::allocate_and_fill(const size_type n, const value_type& value) {
		_start = dataAllocator::allocate(n);
		HandySTL::uninitialized_fill_n(_start, n, value);
		_finish = _end_of_storage = _start + n;
	}

	template <class T, class Alloc>
	template <class InputIterator>
	void vector<T, Alloc>::allocate_and_copy(InputIterator first, InputIterator last) {
		_start = dataAllocator::allocate(n);
		_finish = HandySTL::uninitialized_copy(first, last, _start);
		_end_of_storage = _finish;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::destroyAndDeallocateAll(){
		if (capacity() != 0){
			dataAllocator::destroy(_start, _finish);
			dataAllocator::deallocate(_start, capacity());
		}
	}

}

#endif