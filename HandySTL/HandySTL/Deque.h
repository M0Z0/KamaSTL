#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Allocator.h"
#include "Iterator.h"
#include "ReverseIterator.h"


namespace TinySTL{
	template<class T, class Alloc = allocator<T>>
	class deque;
	namespace Detail{
		//class of deque iterator
		template<class T>
		class dq_iter :public iterator<bidirectional_iterator_tag, T>{
		private:
			template<class T, class Alloc>
			friend class ::TinySTL::deque;
		private:
			//typedef TinySTL::deque<T>* cntrPtr;
			typedef const ::TinySTL::deque<T>* cntrPtr;
			size_t mapIndex_;
			T *cur_;
			cntrPtr container_;
		public:
			dq_iter() :mapIndex_(-1), cur_(0), container_(0){}
			dq_iter(size_t index, T *ptr, cntrPtr container)
				:mapIndex_(index), cur_(ptr), container_(container){}
			dq_iter(const dq_iter& it)
				:mapIndex_(it.mapIndex_), cur_(it.cur_), container_(it.container_){}
			dq_iter& operator = (const dq_iter& it);
			void swap(dq_iter& it);
			reference operator *(){ return *cur_; }
			const reference operator *()const{ return *cur_; }
			pointer operator ->(){ return &(operator*()); }
			const pointer operator ->()const{ return &(operator*()); }
			dq_iter& operator ++();
			dq_iter operator ++(int);
			dq_iter& operator --();
			dq_iter operator --(int);
			bool operator ==(const dq_iter& it)const;
			bool operator !=(const dq_iter& it)const;
		private:
			T *getBuckTail(size_t mapIndex)const;
			T *getBuckHead(size_t mapIndex)const;
			size_t getBuckSize()const;
		public:
			template<class T>
			friend dq_iter<T> operator + (const dq_iter<T>& it, typename dq_iter<T>::difference_type n);
			template<class T>
			friend dq_iter<T> operator + (typename dq_iter<T>::difference_type n, const dq_iter<T>& it);
			template<class T>
			friend dq_iter<T> operator - (const dq_iter<T>& it, typename dq_iter<T>::difference_type n);
			template<class T>
			friend dq_iter<T> operator - (typename dq_iter<T>::difference_type n, const dq_iter<T>& it);
			template<class T>
			friend typename dq_iter<T>::difference_type operator - (const dq_iter<T>& it1, const dq_iter<T>& it2);
			template<class T>
			friend void swap(dq_iter<T>& lhs, dq_iter<T>& rhs);
		};
	}// end of Detail namespace

#endif