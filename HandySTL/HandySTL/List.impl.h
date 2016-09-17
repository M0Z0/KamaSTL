#ifndef __H_LIST_IMPL__
#define __H_LIST_IMPL__

namespace HandySTL{

	template <class T>
	list_iterator<T>& list_iterator<T>::operator ++() {
		p = p->next;
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
		p = p->prev;
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
		return lhs.p == rhs.p;
	}
	template<class T>
	bool operator !=(const listIterator<T>& lhs, const listIterator<T>& rhs){
		return !(lhs == rhs);
	}

	template<class T>
	typename list<T>::nodePtr
		list<T>::createNode(const T& val /* = T() */) {
			nodePtr p = nodeAllocator::allocate();
			nodeAllocator::construct(p, val);
			return p;
	}

	template<class T>
	void list<T>::destroyNode(nodePtr p) {
		p->prev = p->next = nullptr;
		nodeAllocator::destroy(p);
		nodeAllocator::deallocate(p);
	}

	template<class T>
	void list<T>::emptyInit() {

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