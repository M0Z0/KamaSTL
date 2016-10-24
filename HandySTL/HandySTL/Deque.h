#ifndef _DEQUE_H_
#define _DEQUE_H_

#include "Allocator.h"
#include "Iterator.h"

#define max(a, b)    (((a) > (b)) ? (a) : (b))
#define min(a,b)    (((a) < (b)) ? (a) : (b))
const size_t MAPSIZE = 8;

namespace HandySTL{

	inline size_t _deque_buf_size(size_t n, size_t sz) {
		return n != 0 ? n : (sz < 512 ? size_t(512 / sz) : size_t(1));
	}

	template<class T, class Ref, class Ptr, size_t BufSize>
	struct _deque_iterator {

		typedef _deque_iterator<T, T&, T*, BufSize> iterator;
		typedef _deque_iterator<T, const T&, const T*, BufSize> const_iterator;
		static size_t buffer_size() { return _deque_buf_size(BufSize, sizeof(T)); }

		typedef random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef Ptr pointer;
		typedef Ref reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		typedef T** map_pointer;

		typedef _deque_iterator self;

		T* cur;
		T* first;
		T* last;
		map_pointer node;

		//构造、拷贝构造...
		
		_deque_iterator(T* x, map_pointer y) :cur(x), first(*y), last(*y + buffer_size()), node(y) {}
		_deque_iterator() : cur(nullptr), first(nullptr), last(nullptr), node(nullptr) {}
		inline _deque_iterator(const iterator& x) : cur(x.cur), first(x.first), last(x.last), node(x.node) {}

		void set_node(map_pointer newNode) {
			node = newNode;
			first = *newNode;
			last = first+difference_type(buffer_size());
		}

		reference operator*() const { return *cur; }
		pointer operator->() const { return &(operator*()); }

		self& operator++() {
			++cur;
			if (cur == last) {
				set_node(node + 1);
				cur = first;
			}
			return *this;
		}

		self operator++(int) {
			self tmp = *this;
			++*this;
			return tmp;
		}

		self& operator--() {
			--cur;
			if (cur == first) {
				set_node(node - 1);
				cur = first;
			}
			return *this;
		}

		self operator--(int) {
			self tmp = *this;
			--*this;
			return tmp;
		}

		difference_type operator-(const self& x) const {
			return difference_type(buffer_size())*(node - x.node - 1) +
				(cur - first) + (x.last - x.cur);
		}

		self& operator+=(difference_type n) {
			difference_type leftSpase = last - cur;
			if (n > 0 && n < leftSpase) {
				cur += n;
			}else{
				difference_type offSet_node  = n / buffer_size();
				set_node(node + offSet_node);
				cur = first + (n%buffer_size());
			}
			return *this;
		}

		self operator+(difference_type n) const {
			self tmp = *this;
			return tmp += n;
		}

		//迭代器随机存取
		reference operator[](difference_type n) const {
			return *(*this + n);
		}

		bool operator==(const self& x) const { return cur == x.cur; }
		bool operator!=(const self& x) const { return !(*this == x); }
		bool operator<(const self& x) const {
			return (node == x.node) ? (cur < x.cur) : (node < x.node);
		}

	};//end of iterator
	
	template<class T, size_t BuffSize=0>
	class deque {

	public:
		typedef T value_type;
		typedef value_type* pointer;
		typedef const value_type* const_pointer;
		typedef value_type& reference;
		typedef const value_type& const_reference;
		typedef size_t size_type;
		typedef ptrdiff_t difference_type;
		
	private:
		typedef T* pointer;
		typedef pointer* map_pointer;

	public:
		typedef _deque_iterator<T, T&, T*, BuffSize> iterator;

	protected:
		iterator start;
		iterator finish;

		map_pointer map;

		size_type map_size;

		typedef allocator<T> dataAllocator;
		typedef allocator<T*> mapAllocator;

		//enum class EBucksSize{ BUFSIZE = 64 };

		static size_type buffer_size() {
			return _deque_buf_size(BuffSize, sizeof(value_type));
		}

		static size_type initial_map_size() { return MAPSIZE; }
		pointer allocate_node() { return dataAllocator::allocate(buffer_size()); }
		void deallocate_node(pointer n) {
			dataAllocator::deallocate(n, buffer_size());
		}

		void create_map_and_nodes(size_type num_elements);
		void destroy_map_and_nodes();
		map_pointer create_buffer(const size_t size);
		void reallocate_map(size_type nodes_to_add, bool add_at_front);
		void reserve_map_at_back(size_type node_added = 1);
		void reserve_map_at_front(size_type node_added = 1);
		void fill_initialize(size_type n, const value_type& val);
		void push_back_aux(const value_type& val);
		void push_front_aux(const value_type& val);
		void pop_back_aux();
		void pop_front_aux();
		iterator insert_aux(iterator pos, const value_type& val);
		template <class InputIterator>
		void range_initialize(InputIterator first, InputIterator last,
			input_iterator_tag);

		template <class ForwardIterator>
		void range_initialize(ForwardIterator first, ForwardIterator last,
			forward_iterator_tag);


	public:
		inline iterator begin() { return start; }
		inline iterator end() { return finish; }
		reference operator[](size_type n) {
			return start[difference_type(n)];
		}

		reference front() { return *start; }
		reference back() { return*(finish - 1); }

		size_type size() const { return finish - start; }
		bool empty() { return begin() == end(); }

		void push_back(const value_type& val);
		void push_front(const value_type& val);
		void pop_back();
		void pop_front();

		void clear();
		iterator erase(iterator pos);
		iterator erase(iterator first, iterator last);
		iterator insert(iterator position, const value_type& val);

	public:
		inline deque() 
			:start(), finish(), map(nullptr), map_size(0) { create_map_and_nodes(0); }
		deque(size_type n, const value_type& value)
			: start(), finish(), map(0), map_size(0) { fill_initialize(n, value); }
		deque(int n, const value_type& value)
			: start(), finish(), map(0), map_size(0){ fill_initialize(n, value); }
		deque(long n, const value_type& value)
			: start(), finish(), map(0), map_size(0) { fill_initialize(n, value); }
		explicit deque(size_type n)
			: start(), finish(), map(0), map_size(0) { fill_initialize(n, value_type()); }
		template <class InputIterator>
		explicit deque(InputIterator first, InputIterator last);
		deque(const deque& x)
			: start(), finish(), map(0), map_size(0)
		{
			create_map_and_nodes(x.size());
			uninitialized_copy(x.begin(), x.end(), start);
		}
		~deque() { destroy(start, finish); destroy_map_and_nodes(); }
	};
}// end of HandySTL namespace

#include "Deque.impl.h"
#endif