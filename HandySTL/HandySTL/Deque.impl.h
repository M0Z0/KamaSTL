#ifndef __H_DEQUE_IMPL__
#define __H_DEQUE_IMPL__
#include "uninitialized.h"
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
	void deque<T, BufSize>::reallocate_map(size_type nodes_to_add, bool add_at_front){
		size_type old_nodes_num = finish.node - start.node + 1;
		size_type new_nodes_num = old_nodes_num + nodes_to_add;

		size_type new_map_size = map_size + max(map_size, nodes_to_add) + 2;
		map_pointer new_map = mapAllocator::allocate(new_map_size);
		map_pointer new_nStart = new_map + (new_map_size - new_nodes_num) / 2
			+ (add_at_front ? nodes_to_add : 0);
		std::copy(start.node, finish.node + 1, new_nStart);
		mapAllocator::deallocate(map, map_size);
		map = new_map;
		map_size = new_map_size;
		//重新设定迭代器
		start.set_node(new_nStart);
		finish.set_node(new_nStart + old_nodes_num - 1);
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::reserve_map_at_back(size_type node_added = 1) {
		if (node_added + 1>map_size - (finish.node - map)){
			reallocate_map(node_added, false);
		}
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::reserve_map_at_front(size_type node_added = 1) {
		if (start.node-map<node_added){
			reallocate_map(node_added, true);
		}
	}

	template<class T, size_t BufSize>
	void deque<T, BufSize>::fill_initialize(size_type n, const value_type& val) {
		create_map_and_nodes(n);
		map_pointer cur;
		try {
			for (cur = start.node; cur < finish.node; ++cur)
				HandySTL::uninitialized_fill(*cur, *cur + buffer_size(), val);
			HandySTL::uninitialized_fill(finish.first, finish.cur, val);
		}
		catch (...) {
			for (map_pointer m = start.node; m < cur; m++)
				HandySTL::destroy(*m, *m + buffer_size());
			destroy_map_and_nodes();
		}
		
	}

	template<class	T, size_t BufSize>
	deque<T, BufSize>::deque(size_type n, const value_type& val) {
		fill_initialize(n, val);
	}

	//template<class	T, size_t BufSize>
	//template <class InputIterator>
	//deque<T, BufSize>::deque(InputIterator first, InputIterator last) {

	//}

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
		finish.cur = finish.first + num_elements % buffer_size();
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::push_back(const value_type& val) {
		if (finish.cur != finish.last-1){
			construct(finish.cur, val);
			++finish.cur;
		}
		else{
			// TODO:push_back_aux();
		}
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::destroy_map_and_nodes() {
		for (map_pointer cur = start.node; cur <= finish.node; ++cur)
			deallocate_node(*cur);
		mapAllocator::deallocate(map, map_size);

	}
}//end of namespace
#endif