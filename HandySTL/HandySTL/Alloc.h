#ifndef __H_ALLOC__
#define __H_ALLOC__

#include <new.h>

namespace HandySTL{

	template <class T1, class T2>
	inline void construct(T1 *p, const T2 &value) {
		new (p)T1(value); //placement new;½ö¹¹Ôì
	}
}

#endif