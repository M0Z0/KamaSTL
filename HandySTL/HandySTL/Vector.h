#ifndef __H_VECTOR__
#define __H_VECTOR__

#include "Allocator.h"

namespace HandySTL{

	template <class T, class Alloc = allocator<T>>
	class vector{
	public:
		typedef T value_type;
		typedef T* pointer;
		typedef T* iterator;
		typedef const T* const_pointer;
		typedef T& reference;
		typedef const T& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

	private:
		pointer _start;
		pointer _finish;
		pointer _end_of_storage;

		typedef Alloc dataAllocator;
	public:
		//构造、拷贝构造、析构
		vector() :_start(nullptr), _finish(nullptr), _end_of_storage(nullptr) {}
		explicit vector(const size_type n);
		explicit vector(const size_type n, value_type& value);
		vector(const vector&);
		vector(vector&&); //move construct
		~vector();
		vector& operator=(const vector&);
		vector& operator=(vector&&);
		reference operator[](const difference_type i){ return *(begin() + i); }

		//容量相关
		difference_type size() const { return _finish - _start; }
		difference_type capacity() const { return _end_of_storage - _start; }
		bool empty() { return (_start == _finish); }
		void resize(size_type n, value_type val = value_type());

		//迭代器相关
		pointer begin() { return (_start); }
		pointer begin() const { return (_start); }
		pointer end() { return (_finish); }
		pointer end() const { return (_finish); }

		void push_back(const value_type& value);
		void pop_back();
		iterator insert(iterator position, const value_type& val);
		void insert(iterator position, const size_type& n, const value_type& val);
		pointer erase(iterator first, iterator last);
		pointer erase(pointer position);

	private:
		void destroyAndDeallocateAll();
		void allocate_and_fill(const size_type n, const value_type& value);
		template<class InputIterator>
		void allocate_and_copy(InputIterator first, InputIterator last);
		void insert_aux(pointer position, const T& x);
		size_type getNewCapacity(size_type len) const;
	};//end of class

}

#include "impl/vector.impl.h"

#endif