#ifndef __H_LIST__
#define __H_LIST__

#include "Allocator.h"
#include "Iterator.h"
#include <list>
#include "Type_traits.h"

namespace HandySTL{

	template <class T>
	class list;

	template <class T>
	struct list_node{
		T data;
		list_node *prev;
		list_node *next;
		list_node(const T &d) :data(d), prev(nullptr), next(nullptr) {}
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

	//class of list
	template <class T>
	class list{
		template<class T>
		friend struct list_iterator;
	private:
		typedef allocator<list_node<T>> nodeAllocator;
		typedef list_node<T> *node;
	public:
		typedef T value_type;
		typedef list_iterator<T> iterator;
		typedef list_iterator<const T> const_iterator;
		typedef T& reference;
		typedef size_t size_type;
	public:
		list();
		explicit list(size_type n, const value_type& val = value_type());

		iterator begin() { return }
	private:
		void emptyInit();
		node createNode(const T& val = T());
		void destroyNode(node);
		void push_back(const value_type& val);
	};
}
#endif