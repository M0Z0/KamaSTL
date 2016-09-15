#ifndef __H_VECTOR_IMPL__
#define __H_VECTOR_IMPL__
#pragma warning(disable : 4996)

#include "../vector.h"
#include "../uninitialized.h"
#include <algorithm>

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
			insert_aux(end(), value);
	}

	template <class T, class Alloc>
	void vector<T, Alloc>::resize(size_type n, value_type val = value_type()) {
		if (n < size()) {
			dataAllocator::destroy(_start + n, _finish);
			_finish = _start + n;
		}
		else if (n > size() && n < capacity()) {
			auto lengthOfInsert = n - size();
			_finish = uninitialized_fill_n(_finish, lengthOfInsert, val);
		}
		else if (n > capacity()){
			auto lengthOfInsert = n - size();
			T *newStart = dataAllocator::allocate(getNewCapacity(lengthOfInsert));
			T *newFinish = HandySTL::uninitialized_copy(begin(), end(), newStart);
			newFinish = HandySTL::uninitialized_fill_n(newFinish, lengthOfInsert, val);

			destroyAndDeallocateAll();
			_start = newStart;
			_finish = newFinish;
			_end_of_storage = _start + n;
		}
		
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
				newFinish = HandySTL::uninitialized_copy(_start, position, newStart);
				construct(newFinish, value);
				++newFinish;
				newFinish = HandySTL::uninitialized_copy(position, _finish, newFinish);
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
	typename vector<T, Alloc>::iterator 
		vector<T, Alloc>::insert(iterator position, const value_type& val) {

	}

	template <class T, class Alloc>
	void vector<T, Alloc>::insert(iterator position, const size_type& n, const value_type& val) {
			//if (_finish+n <= _end_of_storage && position < _finish) {
			//	iterator positionOrigin = position;
			//	iterator positionDes = position+n;
			//	std::copy_backward(position, positionDes, positionDes);
			//	for (; position != positionDes; ++positionOrigin)
			//		construct(position, val);			
			//} 
			//else if (_finish + n <= _end_of_storage && position >= _finish) {
			//	iterator positionOrigin = position;
			//	iterator positionDes = position + n;
			//	for (; position != positionDes; ++positionOrigin)
			//		construct(position, val);
			//}
			//else{
			//	const size_type oldSize = _end_of_storage + n;
			//	const size_type newSize = oldSize != 0 ? 2 * oldSize : 1;
			//	pointer newStart = dataAllocator::allocate(newSize);
			//	pointer newFinish = nullptr;
			//	newFinish = HandySTL::uninitialized_copy(_start, _finish, newStart);
			//	//TODO

			//	
			//}
		if (n != 0) {
			if (size_type(_end_of_storage-_finish) >= n) {//剩余空间大于需要空间
				T valTmp = val;
				//插入点后现有元素个数
				const size_type elemsAfter = _finish - position;
				iterator oldFinish = _finish;
				if (elemsAfter > n) {
					HandySTL::uninitialized_copy(_finish - n, _finish, _finish);
					_finish += n;
					std::copy_backward()
				}
				
			}
			
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

	template<class T, class Alloc>
	typename vector<T, Alloc>::size_type vector<T, Alloc>::getNewCapacity(size_type len) const {
		size_type oldCapacity = _end_of_storage - _start;
		auto res = oldCapacity > len ? oldCapacity : len;
		size_type newCapacity = (oldCapacity != 0 ? (oldCapacity + res) : len);
		return newCapacity;
	}

}

#endif