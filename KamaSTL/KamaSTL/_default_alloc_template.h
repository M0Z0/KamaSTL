#include<stdio.h>
#include<stdlib.h>


static const size_t __ALIGN = 8;
static const size_t __MAX_BYTES = 128;
static const size_t __NFREELISTS = __MAX_BYTES / __ALIGN;



class __default_alloc_template
{
private:
	//将bytes上调至8的倍数
	static size_t ROUND_UP(size_t bytes)
	{
		//高效率版本，没有用到乘法器,当比8多1时，就应该加倍9+7=16,多2时9+8=17,然后与1000000变成16,为8的整倍数
		return (((bytes)+__ALIGN - 1)&~(__ALIGN - 1));
	}

	//free_list节点构造
public:
	union obj
	{
		union obj* free_list_link;
		char client_data[1];
	};

private:
	static obj *volatile free_list[__NFREELISTS];

	//根据块大小，选择使用第n号的free_list,n从0开始
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
	}

public:
	static void *refill(size_t n);

	static char *chunk_alloc(size_t size, int &nobjs);

public:
	//内存分配状态
	static char *start_free;
	static char *end_free;
	static size_t heap_size;
	static size_t nmalloc;

public:
	static void *allocate(size_t n)
	{
		obj *volatile *my_free_list;
		obj *result;

		//大于128调用第一级配置器,这里忽略大内存的处理

		//在16个链表里面找到合适的free_list
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (result == 0)
		{
			void *r = refill(ROUND_UP(n));
			return r;
		}
		//调整free_list,返回分配的空间，自由链表指向余下的空间首地址..会用到字节对齐？
		*my_free_list = result->free_list_link;
		printf("把%d字节的空间给容器使用\n", n);
		return result;
	}

	static void *deallocate(void *p, size_t n)
	{
		obj *q = (obj*)p;
		obj *volatile *my_free_list;

		//忽略一级配置器的处理
		my_free_list = free_list + FREELIST_INDEX(n);
		q->free_list_link = *my_free_list;
		*my_free_list = q;
	}

	static void *reallocate(void *p, size_t old_sz, size_t new_sz)
	{
	}
};

char *__default_alloc_template::start_free = 0;

char *__default_alloc_template::end_free = 0;

size_t __default_alloc_template::heap_size = 0;

size_t __default_alloc_template::nmalloc = 2;

__default_alloc_template::obj *volatile
__default_alloc_template::free_list[__NFREELISTS] =
{ 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0 };