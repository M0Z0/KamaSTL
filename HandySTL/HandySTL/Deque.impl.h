#ifndef __H_DEQUE_IMPL__
#define __H_DEQUE_IMPL__
#include "Iterator.h"
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
	template <class InputIterator>
	deque<T, BufSize>::deque(InputIterator first, InputIterator last) 
		: start(), finish(), map(0), map_size(0) {
		range_initialize(first, last, iterator_category(last));
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
		finish.cur = finish.first + num_elements % buffer_size();
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::push_back(const value_type& val) {
		if (finish.cur != finish.last-1){
			construct(finish.cur, val);
			++finish.cur;
		}
		else{
			push_back_aux(val);
		}
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::push_front(const value_type& val) {
		if (start.first != start.cur) {
			construct(start.cur-1, val);
			--start.cur;
		}
		else{
			push_front_aux(val);
		}
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::pop_back() {
		if (finish.cur != finish.first){
			destroy(finish.cur, val);
			--finish.cur;
		}
		else{
			pop_back_aux(val);
		}
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::pop_front() {
		if (start.cur != start.last-1){
			destroy(finish.cur, val);
			++start.cur;
		}
		else{
			pop_front_aux(val);
		}
	}

	template<class T, size_t BufSize>
	void deque<T, BufSize>::push_back_aux(const value_type& val) {
		value_type val_copy = val;
		reserve_map_at_back();
		*(finish.node + 1) = allocate_node();
		try {
			construct(finish.cur, val_copy);
			finish.set_node(finish.node + 1);
			finish.cur = finish.first;
		}
		catch (...) {
			deallocate_node(*(finish.node + 1));
		}		
	}

	template<class T, size_t BufSize>
	void deque<T, BufSize>::push_front_aux(const value_type& val) {
		value_type val_copy = val;
		reserve_map_at_back();
		*(start.node - 1) = allocate_node();
		try {
			start.set_node(start.node - 1);
			start.cur = start.last - 1;
			construct(start.cur, val_copy);
		}
		catch (...) {
			start.set_node(start.node + 1);
			start.cur = start.first;
			deallocate_node(*(start.node - 1));
		}
	}

	template<class T, size_t BufSize>
	void deque<T, BufSize>::pop_back_aux() {
		deallocate_node(finish.first);
		finish.set_node(finish.first - 1);
		finish.cur = finish.last - 1;
		destroy(finish.cur);
	}

	template<class T, size_t BufSize>
	void deque<T, BufSize>::pop_front_aux() {
		destroy(start.cur);
		deallocate_node(start.first);
		start.set_node(start.node + 1);
		start.cur = start.first;
	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::destroy_map_and_nodes() {
		for (map_pointer cur = start.node; cur <= finish.node; ++cur)
			deallocate_node(*cur);
		mapAllocator::deallocate(map, map_size);

	}

	template<class	T, size_t BufSize>
	void deque<T, BufSize>::clear() {
		for (map_pointer node = start.node + 1, p < finish.node; ++p) {
			destroy(*node, *node+buffer_size());
			mapAllocator::deallocate(*node, buffer_size());
		}
		if (start.node != last.node) {
			destroy(start.cur, start.last);
			destroy(finish.cur, finish.last);
			mapAllocator::deallocate(finish.first, buffer_size());
		}
		else{
			destroy(start.cur, finish.cur);
			finish = start;
		}
	}

	template<class	T, size_t BufSize>
	typename deque<T, BufSize>::iterator 
		deque<T, BufSize>::erase(iterator pos) {
		iterator next = pos;
		++next;
		difference_type index = pos - start;
		if (index<(size()>>1)) {
			std::copy_backward(start, pos, next);
			pop_front();
		}
		else{
			copy(next, finish, pos);
			pop_back();
		}
		return start + index;
	}

	template<class	T, size_t BufSize>
	typename deque<T, BufSize>::iterator
		deque<T, BufSize>::erase(iterator first, iterator last) {
			if (first == start && last == finish) {
				clear();
				return finish;
			}
			else{
				difference_type dst = last - first;
				difference_type ele_before = first - start;
				if (ele_before < (size() - dst) / 2) {
					std::copy_backward(start, first, last);
					iterator new_start = start + dst;
					destroy(start, new_start);
					for (map_pointer p = start.node; p < new_start.node; ++p)
						dataAllocator::deallocate(*p, buffer_size());
					start = new_start;
				}
				else{
					std::copy(last, finish, first);
					iterator new_finish = finish - dst;
					destroy(new_finish, finish);
					for (map_pointer p = new_finish.node+1; p <= finish.node; ++p)
						dataAllocator::deallocate(*p, buffer_size());
					finish = new_finish;
				}
				return start + ele_before;
			}
		}
	template<class	T, size_t BufSize>
	typename deque<T, BufSize>::iterator
		deque<T, BufSize>::insert(iterator pos, const value_type& val) {
			if (pos.cur == start.cur) {
				push_front(val);
				return start;
			}
			else if (pos.cur == finish.cur) {
				push_back(val);
				iterator tmp = finish;
				--tmp;
				return tmp;
			}
			else{
				insert_aux(pos, val);
			}
		}

	template<class	T, size_t BufSize>
	typename deque<T, BufSize>::iterator
		deque<T, BufSize>::insert_aux(iterator pos, const value_type& val) {
			difference_type index = pos - start;
			value_type val_copy = val;
			if (index<(size()/2)) {
				push_front(front()); 
				iterator front1 = start;
				++front1;
				iterator front2 = front1;
				++front2;
				pos = start + index;
				iterator pos1 = pos;
				++pos1;
				std::copy(front2, pos1, front1);
			}
			else{
				push_back(back()); 
				iterator back1 = finish;
				--back1;
				iterator back2 = back1;
				--back2;
				pos = start + index;
				std::copy_backward(pos, back2, back1);
			}
			*pos = val; //在插入点设定新值
			return pos;
		}

	template<class	T, size_t BufSize>
	template <class InputIterator>
	void deque<T, BufSize>::range_initialize(InputIterator first, InputIterator last,
		input_iterator_tag) {
		create_map_and_nodes(0);
		for (; first != last; ++first) 
			push_back(*first);
	}

	template<class	T, size_t BufSize>
	template <class ForwardIterator>
	void deque<T, BufSize>::range_initialize(ForwardIterator first, ForwardIterator last,
		forward_iterator_tag) {
		size_type n = 0;
		distance(first, last, n);
		create_map_and_nodes(n);
		uninitialized_copy(first, last, start);

	}
}//end of namespace
#endif