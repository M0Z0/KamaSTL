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
		destroyAndDeallocateAll();
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
	void vector<T, Alloc>::push_back(const value_type& value) {
		if (_finish != _end_of_storage) {
			construct(_finish, value);
			++_finish;
		}
		else
			insert_aux(end(), x);
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(iterator first, iterator last) { //返回值需要指定为类型
		iterator i = std::copy(last, _finish, first);
		dataAllocator::destroy(i, _finish);
		_finish = _finish - (last - first);
		return first;
	}

	template <class T, class Alloc>
	typename vector<T, Alloc>::iterator vector<T, Alloc>::erase(pointer position) { //返回值需要指定为类型
		if (position + 1 != end())
			std::copy(position+1, _finish, position);
		--_finish;
		dataAllocator::destroy(_finish);
		return position;
	}

	template<class T, class Alloc>
	void vector<T, Alloc>::pop_back(){
		--_finish;
		dataAllocator::destroy(_finish);
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::insert_aux(pointer position, const T& value) {
		if (_finish != _end_of_storage) {
			construct(_finish, *(_finish - 1));
			++_finish;
			T value_copy = value;
			std::copy_backward(position, _finish - 1, _finish - 2);
			*position = value_copy;
		}
		else{//无备用空间
			const size_type oldSize = size();
			const size_type len = oldSize != 0 ? 2 * oldSize : 1;

			pointer newStart = dataAllocator::allocate(len);
			pointer newFinish = nullptr;
			try {
				newFinish = uninitialized_copy(_start, position, newStart);
				construct(newFinish, value);
				++newFinish;
				newFinish = uninitialized_copy(position, _finish, newFinish);
			}catch (...) {
				destroy(newStart, newFinish);
				dataAllocator::deallocate(newStart, len);
				throw;
			}
			
			destroyAndDeallocateAll();

			_start = newStart;
			_finish = newFinish;
			_end_of_storage = newStart + len;
		}
		
	}

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