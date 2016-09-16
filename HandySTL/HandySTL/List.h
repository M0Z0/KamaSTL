#ifndef __H_LIST__
#define __H_LIST__

#include "Allocator.h"
#include "Iterator.h"

#include "Type_traits.h"

namespace HandySTL{

	template <class T>
	class list;

	template <class T>
	struct list_node{
		T data;
		list_node *prev;
		list_node *next;

	};

	//list iterator
	template <class T>
	struct list_iterator : public iterator<bidirectional_iterator_tag, T>{
		template <class T>
		friend class list;

		typedef list_node<T>* nodePtr;
		nodePtr p;

		explicit list_iterator(nodePtr ptr = nullptr) :p(ptr) {}

		list_iterator& operator++();
		list_iterator operator++(int);
		list_iterator& operator--();
		list_iterator operator--(int);
		T& operator *() { return p->data; }
		T* operator->() { return &(this->operator*()); }

		template<class T>
		friend bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs);
		template<class T>
		friend bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs);
	};
}
#endif