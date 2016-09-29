//
//
//#include "Allocator.h"
//#include "Iterator.h"
//#include <list>
//#include "Type_traits.h"
//
//namespace Mlist{
//
//	template <class T>
//	class list;
//
//
//	template <class T>
//	struct __list_node {
//		typedef void* void_pointer;
//		void_pointer next;
//		void_pointer prev;
//		T data;
//	};
//
//	template<class T, class Ref, class Ptr>
//	struct __list_iterator {
//		typedef __list_iterator<T, T&, T*>             iterator;
//		typedef __list_iterator<T, const T&, const T*> const_iterator;
//		typedef __list_iterator<T, Ref, Ptr>           self;
//		template <class T>
//		friend class list;
//
//		typedef T value_type;
//		typedef Ptr pointer;
//		typedef Ref reference;
//		typedef __list_node<T>* link_type;
//		typedef size_t size_type;
//		typedef ptrdiff_t difference_type;
//
//		link_type node;
//
//		__list_iterator(link_type x) : node(x) {}
//		__list_iterator() {}
//		__list_iterator(const iterator& x) : node(x.node) {}
//
//		bool operator==(const self& x) const { return node == x.node; }
//		bool operator!=(const self& x) const { return node != x.node; }
//		reference operator*() const { return (*node).data; }
//
//		pointer operator->() const { return &(operator*()); }
//
//		self& operator++() {
//			node = (link_type)((*node).next);
//			return *this;
//		}
//		self operator++(int) {
//			self tmp = *this;
//			++*this;
//			return tmp;
//		}
//		self& operator--() {
//			node = (link_type)((*node).prev);
//			return *this;
//		}
//		self operator--(int) {
//			self tmp = *this;
//			--*this;
//			return tmp;
//		}
//	};
//
//	template <class T>
//	class list {
//
//	public:
//		typedef void* void_pointer;
//		typedef __list_node<T> list_node;
//		typedef HandySTL::allocator<__list_node<T> > list_node_allocator;
//	public:
//		typedef T value_type;
//		typedef value_type* pointer;
//		typedef const value_type* const_pointer;
//		typedef value_type& reference;
//		typedef const value_type& const_reference;
//		typedef list_node* link_type;
//		typedef size_t size_type;
//		typedef ptrdiff_t difference_type;
//
//	public:
//		typedef __list_iterator<T, T&, T*>             iterator;
//		typedef __list_iterator<T, const T&, const T*> const_iterator;
//	private:
//		link_type node;
//
//	protected:
//		link_type get_node() { return list_node_allocator::allocate(); }
//		void put_node(link_type p) { list_node_allocator::deallocate(p); }
//
//		link_type create_node(const T& x) {
//			link_type p = get_node();
//			{
//				construct(&p->data, x);
//			}
//			return p;
//		}
//		void destroy_node(link_type p) {
//			destroy(&p->data);
//			put_node(p);
//		}
//	public:
//		list() {  }
//		~list(){};
//	protected:
//		void empty_initialize() {
//			node = get_node();
//			node->next = node;
//			node->prev = node;
//		}
//
//
//
//	};
//}
