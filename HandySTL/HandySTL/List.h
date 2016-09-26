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
		void *prev;
		void *next;
		//list_node(const T &d) :data(d), prev(nullptr), next(nullptr) {}
	};

	//list iterator
	template <class T>
	struct list_iterator : public iterator<bidirectional_iterator_tag, T>{
		typedef list_iterator<T> iterator;
		template <class T>
		friend class list;

		typedef list_node<T>* link_type;
		link_type node;

		explicit list_iterator(link_type ptr = nullptr) :node(ptr) {}
		list_iterator() {}
		list_iterator(const iterator &x) :node(x.node) {}

		list_iterator& operator++();
		list_iterator operator++(int);
		list_iterator& operator--();
		list_iterator operator--(int);
		T& operator *() { return node->data; }
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
		typedef list_node<T> *list_type;
		//nodeָ�����һ���ڵ����һ���ڵ�
		typedef list_node<T> *node;
	public:
		typedef T value_type;
		typedef list_iterator<T> iterator;
		typedef list_iterator<const T> const_iterator;
		typedef T& reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;

		typedef list_iterator<T> iterator;
	public:
		list() { emptyInit(); }
		list(size_type n, const T& value) { fill_initialize(n, value); }
		list(int n, const T& value) { fill_initialize(n, value); }
		explicit list(size_type n)
		explicit list(size_type n, const value_type& val = value_type());
		template<class Input>

		iterator begin() { return (list_type)((*node).next); }
		const iterator begin() const { return (list_type)((*node).next); }
		iterator end() { return node; }
		const_iterator end() const { return node; }

		bool empty() const { return node->next == node; }
		size_type size() const;
		reference front() { return *begin(); }
		const_reference front() const { return *begin(); }
		reference back() { return *(--end()); }
		const_reference back() const { return *(--end()); }
		void swap(list<T> &x) { std::swap(node, x.node); }

		iterator insert(iterator position, const T& x);
		inline iterator insert(iterator position) { return insert(position, T()); }
		template<class InputIterator>
		void insert(iterator position, InputIterator first, InputIterator last);
		void insert(iterator position, const T* first, const T* last);
		inline void insert(iterator pos, int n, const T& x) { insert(pos, (size_type)n, x); }
		inline void insert(iterator pos, long n, const T& x) { insert(pos, (size_type)n, x); }
		inline void push_back(const T& val) { insert(end(), val); }
		inline void push_front(const T& val) { insert(begin(), val); }
		iterator erase(iterator position);
		void remove(const T& value);
		void unique();
		void splice(iterator position, list& li);
		void splice(iterator it, list& li, iterator first);//����li������[first,end)��Ԫ�ز������ָ��itǰ
		void splice(iterator it, list& li��iterator first, iterator last);//li������[first,last)��Ԫ�ز��������ָ��itǰ

	private:
		// ����һ�����c�K����
		link_type get_node() { return nodeAllocator::allocate(); }
		// ጷ�һ�����c
		void put_node(link_type p) { nodeAllocator::deallocate(p); }

		void emptyInit();
		node createNode(const T& val = T());
		void destroyNode(node);
		void clear();
		void push_back(const value_type& val);
		void fill_initialize(size_type n, const T& value); 
		void range_initialize(const T* first, const T* last);
		template<class InputIterator>
		void range_initialize(InputIterator first, InputIterator last);
		void transfer(iterator position, iterator first, iterator last);
	};
}
#endif