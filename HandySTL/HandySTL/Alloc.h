#ifndef __H_ALLOC__
#define __H_ALLOC__

#include <cstdlib>

namespace HandySTL{

	class alloc{
	private:
		enum {__ALIGN = 8}; //С��������ϵ��߽�
		enum {__MAX_BYTES = 128}; //С�����������
		enum { __NFREELISTS = __MAX_BYTES / __ALIGN }; //free-lists����
		enum { __NOBJS = 20 };//ÿ�����ӵĽڵ���

	private:
		static size_t ROUND_UP(size_t bytes) {
			return (((bytes)+__ALIGN - 1) &~(__ALIGN - 1));
		}
		//free-lists�Ľڵ㹹��
		union obj {
			union obj *next;
			char client_data[1];
		};
		//16��free-list
		static obj * free_list[__NFREELISTS];
		//���º������������С������ʹ�õ�n��free-list,n��0����
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
		}
	private:
		static char *start_free;//�ڴ����ʼλ��
		static char *end_free;//�ڴ�ؽ���λ��
		static size_t heap_size;
		//����һ����СΪn�Ķ��󣬲����ܼ����СΪn���������鵽free-list
		static void *refill(size_t n);
		//����һ���ռ䣬������nobjs����СΪsize������
		//�������nobjs�������������㣬nobjs���ܻή��
		static char *chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
	};
}

#endif