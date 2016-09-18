#ifndef __H_LIST_IMPL__
#define __H_LIST_IMPL__

namespace HandySTL{

	template <class T>
	list_iterator<T>& list_iterator<T>::operator ++() {
		node = node->next;
		return *this;
	}

	template <class T>
	list_iterator<T>& list_iterator<T>::operator ++(int) {
		auto res = *this;
		++*this;
		return res;
	}

	template <class T>
	list_iterator<T>& list_iterator<T>::operator --() {
		node = node->prev;
		return *this;
	}

	template <class T>
	list_iterator<T>& list_iterator<T>::operator ++(int) {
		auto res = *this;
		--*this;
		return res;
	}

	template<class T>
	bool operator ==(const listIterator<T>& lhs, const listIterator<T>& rhs){
		return lhs.node == rhs.node;
	}
	template<class T>
	bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs){
		return !(lhs.node == rhs.node);
	}

	template<class T>
	typename list<T>::size_type
		list<T>::size() const {
			size_type result = 0;
			distance(begin(), end(), result);
			return p;
	}

	template<class T>
	typename list<T>::link_type
		list<T>::createNode(const T& val /* = T() */) {
			link_type p = nodeAllocator::allocate();
			nodeAllocator::construct(p, val);
			return p;
	}

	template<class T>
	void list<T>::destroyNode(link_type p) {
		node->prev = node->next = nullptr;
		nodeAllocator::destroy(p);
		nodeAllocator::deallocate(p);
	}

	template<class T>
	void list<T>::emptyInit() {
		node = get_node();
		node->next = node;
		node->prev = node;
	}
	template <class T>
	list<T>::list() {
		emptyInit();
	}

	template<class T>
	void list<T>::push_back(const value_type& val) {
		auto newNode = createNode(val);
	}
}
#endif