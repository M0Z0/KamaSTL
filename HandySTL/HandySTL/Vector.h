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

		//容量相关
		difference_type size() const { return _finish - _start; }
		difference_type capacity() const { return _end_of_storage - _start; }
		bool empty() { return (_start == _finish); }

		//迭代器相关
		iterator begin() { return (_start); }
		iterator begin() const { return (_start); }
		iterator end() { return (_finish); }
		iterator end() const { return (_finish); }

		void push_back(const value_type& value);

	private:
		void destroyAndDeallocateAll();
		void allocate_and_fill(const size_type n, const value_type& value);
		template<class InputIterator>
		void allocate_and_copy(InputIterator first, InputIterator last);
		void insert_aux(iterator position, const T& x);
	};//end of class

}

#include "impl/vector.impl.h"

#endif