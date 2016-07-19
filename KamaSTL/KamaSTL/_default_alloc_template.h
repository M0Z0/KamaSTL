#include<stdio.h>
#include<stdlib.h>


static const size_t __ALIGN = 8;
static const size_t __MAX_BYTES = 128;
static const size_t __NFREELISTS = __MAX_BYTES / __ALIGN;



class __default_alloc_template
{
private:
	//��bytes�ϵ���8�ı���
	static size_t ROUND_UP(size_t bytes)
	{
		//��Ч�ʰ汾��û���õ��˷���,����8��1ʱ����Ӧ�üӱ�9+7=16,��2ʱ9+8=17,Ȼ����1000000���16,Ϊ8��������
		return (((bytes)+__ALIGN - 1)&~(__ALIGN - 1));
	}

	//free_list�ڵ㹹��
public:
	union obj
	{
		union obj* free_list_link;
		char client_data[1];
	};

private:
	static obj *volatile free_list[__NFREELISTS];

	//���ݿ��С��ѡ��ʹ�õ�n�ŵ�free_list,n��0��ʼ
	static size_t FREELIST_INDEX(size_t bytes)
	{
		return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
	}

public:
	static void *refill(size_t n);

	static char *chunk_alloc(size_t size, int &nobjs);

public:
	//�ڴ����״̬
	static char *start_free;
	static char *end_free;
	static size_t heap_size;
	static size_t nmalloc;

public:
	static void *allocate(size_t n)
	{
		obj *volatile *my_free_list;
		obj *result;

		//����128���õ�һ��������,������Դ��ڴ�Ĵ���

		//��16�����������ҵ����ʵ�free_list
		my_free_list = free_list + FREELIST_INDEX(n);
		result = *my_free_list;
		if (result == 0)
		{
			void *r = refill(ROUND_UP(n));
			return r;
		}
		//����free_list,���ط���Ŀռ䣬��������ָ�����µĿռ��׵�ַ..���õ��ֽڶ��룿
		*my_free_list = result->free_list_link;
		printf("��%d�ֽڵĿռ������ʹ��\n", n);
		return result;
	}

	static void *deallocate(void *p, size_t n)
	{
		obj *q = (obj*)p;
		obj *volatile *my_free_list;

		//����һ���������Ĵ���
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