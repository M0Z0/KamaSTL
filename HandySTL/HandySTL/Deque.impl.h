#ifndef __H_DEQUE_IMPL__
#define __H_DEQUE_IMPL__

#include <stdlib.h>
namespace HandySTL{

	template<class	T, size_t BufSize>
	typename deque<T, BufSize>::map_pointer 
		deque<T, BufSize>::create_buffer(const size_t size) {
		map_pointer map = new T*[size];
		for (size_t i = 0; i < size; ++i)
			map[i] = allocate_node();
		return map;	
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::create_map_and_nodes(size_type num_elements) {
		//节点数=元素个数/每个缓冲区可容纳节点数+1
		size_type node_num = num_elements / buffer_size() + 1;

		map_size = max(initial_map_size(), node_num + 2);
		map = mapAllocator::allocate(map_size);

		map_pointer nStart = map + (map_size - node_num) / 2;
		map_pointer nEnd = nStart + node_num - 1;

		map_pointer cur;

		try {
			for (cur = nStart; cur <= nEnd; ++cur)
				*cur = allocate_node();	
		}
		catch (...) {
			for (map_pointer n = nStart; n < cur; ++n)
				deallocate_node(*n);
			mapAllocator::deallocate(map, map_size);
			throw;
		}	
		start.set_node(nStart);
		finish.set_node(nEnd);
		start.cur = start.first;
		finish.cur = finish.first + num_elements / buffer_size();
	}
}//end of namespace
#endif