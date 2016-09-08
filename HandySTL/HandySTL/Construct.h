#ifndef __H_CONSTRUCT__
#define __H_CONSTRUCT__

#include <new.h>
#include "Type_traits.h"

namespace HandySTL{

	template <class T1, class T2>
	inline void construct(T1 *p, const T2 &value) {
		new (p) T1(value); //placement new;½ö¹¹Ôì
	}

	template <class T>
	inline void destroy(T *p) {
		p->~T();
	}

	template<class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _true_type) {}

	template<class ForwardIterator>
	inline void _destroy(ForwardIterator first, ForwardIterator last, _false_type) {
		for (; first != last; ++first) {
			destroy(&*first);
		}
	}

	template<class ForwardIterator>
	inline void destroy(ForwardIterator first, ForwardIterator last){
		typedef typename _type_traits<ForwardIterator>::is_POD_type is_POD_type;
		_destroy(first, last, is_POD_type());
	}
}

#endif