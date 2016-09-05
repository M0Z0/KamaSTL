#ifndef __H_ALLOC__
#define __H_ALLOC__

#include <cstdlib>

namespace HandySTL{

	class alloc{
	private:
		enum {__ALIGN = 8}; //小型区块的上调边界
		enum {__MAX_BYTES = 128}; //小型区块的上限
		enum { __NFREELISTS = __MAX_BYTES / __ALIGN }; //free-lists个数
		enum { __NOBJS = 20 };//每次增加的节点数

	private:
		static size_t ROUND_UP(size_t bytes) {
			return (((bytes)+__ALIGN - 1) &~(__ALIGN - 1));
		}
		//free-lists的节点构造
		union obj {
			union obj *next;
			char client_data[1];
		};
		//16个free-list
		static obj * free_list[__NFREELISTS];
		//以下函数根据区块大小，决定使用第n号free-list,n从0起算
		static size_t FREELIST_INDEX(size_t bytes) {
			return (((bytes)+__ALIGN - 1) / __ALIGN - 1);
		}
	private:
		static char *start_free;//内存池起始位置
		static char *end_free;//内存池结束位置
		static size_t heap_size;
		//返回一个大小为n的对象，并可能加入大小为n的其他区块到free-list
		static void *refill(size_t n);
		//配置一大块空间，可容纳nobjs个大小为size的区块
		//如果配置nobjs个区块有所不便，nobjs可能会降低
		static char *chunk_alloc(size_t size, size_t& nobjs);

	public:
		static void *allocate(size_t bytes);
		static void deallocate(void *ptr, size_t bytes);
		static void *reallocate(void *ptr, size_t old_sz, size_t new_sz);
	};
}

#endif