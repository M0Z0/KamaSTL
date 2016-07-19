#include <new>
#include <cstddef>
#include <cstdlib>
#include <climits>
#include <iostream>
using namespace std;

template<int inst>
class __malloc_alloc_template{
private:
	// oom: out of memory
	static void *oom_malloc(size_t);
	static void *oom_realloc(void *, size_t);
	static void (*__malloc_alloc_oom_handler) ();

public:
	static void *allocate(size_t n)
	{
		void *result = malloc(n);
		if (0 == result) result = oom_malloc(n);
		return result;
	}

	static void deallocate(void *p, size_t)
	{
		free(p);
	}

	static void *reallocate(void *p, size_t, size_t new_sz)
	{
		void *result = realloc(p, new_sz);
		if (0 == result) result = oom_realloc(p, new_sz);
		return result;
	}

	static void(*set_malloc_handler(void(*f)()))()
	{
		 void(*old)() = __malloc_alloc_oom_handler;
		__malloc_alloc_oom_handler = f;
		return (old);
	}
};

template<int inst>
void(*__malloc_alloc_template<inst>::__malloc_alloc_oom_handler)() = 0;

template <int inst>
void *__malloc_alloc_template<inst>::oom_malloc(size_t n)
{
	void(*my_malloc_handler)();
	void *result;

	for (;;){
		my_malloc_handler = __malloc_alloc_oom_handler;
		if (0 == my_malloc_handler){
			_THROW_BAD_ALLOC;
		}
		(*my_malloc_handler)();
		result = realloc(p, n);
	}
}
