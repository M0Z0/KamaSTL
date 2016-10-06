#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Allocator.h"
#include "Iterator.h"


namespace HandySTL{

	inline size_t _deque_buf_size(size_t n, size_t sz) {
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
	}

	template<class T, class Ref, class Ptr, size_t BufSize>
	struct _deque_iterator {

		typedef _deque_iterator<T, T&, T*, BufSize> iterator;
		typedef _deque_iterator<T, const T&, const T*, BufSize> const_iterator;
		static size_t buffer_size() { return _deque_buf_size(BufSize, sizeof(T)); }

		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T** map_pointer;

		typedef _deque_iterator self;

		T* cur;
		T* first;
		T* last;
		map_pointer node;

		void set_node(map_pointer newNode) {
			node = newNode;
			first = *newNode;
			last = difference_type(buffer_size());
		}

		reference operator*() const { return *cur; }
		pointer operator->() const { return &(operator*()); }

		self& operator++() {
			++cur;
			if (cur == last) {
				set_node(node + 1);
				cur = first;
			}
		}

		self operator++(int) {
			self tmp = *this;
			++*this;
			return tmp;
		}
	};
	
}// end of HandySTL namespace

#endif