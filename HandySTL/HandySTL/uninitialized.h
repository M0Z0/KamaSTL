#ifndef __H_UNINITIALIZED__
#define __H_UNINITIALIZED__

#include "Construct.h"
#include "Iterator.h"
#include "Type_traits.h"
#include <utility>

namespace HandySTL{

	//********* [fill] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class ForwardIterator, class T>
	void fill(ForwardIterator first, ForwardIterator last, const T& value)
	{
		for (; first != last; ++first)
			*first = value;
	}
	inline void fill(char *first, char *last, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), last - first);
	}
	inline void fill(wchar_t *first, wchar_t *last, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), (last - first) * sizeof(wchar_t));
	}

	//********* [fill_n] ********************
	//********* [Algorithm Complexity: O(N)] ****************
	template<class OutputIterator, class Size, class T>
	OutputIterator fill_n(OutputIterator first, Size n, const T& value)
	{
		for (; n > 0; --n, ++first)
			*first = value;
		return first;
	}
	template<class Size>
	char *fill_n(char *first, Size n, const char& value)
	{
		memset(first, static_cast<unsigned char>(value), n);
		return first + n;
	}
	template<class Size>
	wchar_t *fill_n(wchar_t *first, Size n, const wchar_t& value)
	{
		memset(first, static_cast<unsigned char>(value), n * sizeof(wchar_t));
		return first + n;
	}

	//declare
	template <class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type);
	template <class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type);
	//
	template <class InputIterator, class ForwardIterator>
	ForwardIterator uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result) {
		typedef typename _type_traits<iterator_traits<InputIterator>::value_type>::is_POD_type isPODtype;
		return _uninitialized_copy_aux(first, last, result, isPODtype());
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _true_type){
		memcpy(result, first, (last - first) * sizeof(*first));
		return result + (last - first);
	}

	template<class InputIterator, class ForwardIterator>
	ForwardIterator _uninitialized_copy_aux(InputIterator first, InputIterator last, ForwardIterator result, _false_type){
		int i = 0;
		for (; first != last; ++first, ++i)
			construct((result + i), *first);
		return (result + i);
	}

	//////////////////////////////////////////////////////////////////////////
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type);
	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type);

	template<class ForwardIterator, class T>
	void uninitialized_fill(ForwardIterator first, ForwardIterator last, const T& value) {
		typedef typename _type_traits<T>::is_POD_type isPODtype;
		_uninitialized_fill_aux(first, last, value, isPODtype());
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _true_type) {
		fill(first, last, value);
	}

	template<class ForwardIterator, class T>
	void _uninitialized_fill_aux(ForwardIterator first, ForwardIterator last, const T& value, _false_type) {
		for (; first != last; ++first)
			construct(first, value);
	}

	//////////////////////////////////////////////////////////////////////////
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _true_type);
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _false_type);

	template<class ForwardIterator, class Size, class T>
	inline ForwardIterator uninitialized_fill_n(ForwardIterator first, Size n, const T& x) {
		typedef typename _type_traits<T>::is_POD_type isPODtype;
		return _uninitialized_fill_n_aux(first, n, x, isPODtype());
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _true_type) {
		return fill_n(first, n, x);
	}
	template<class ForwardIterator, class Size, class T>
	ForwardIterator _uninitialized_fill_n_aux(ForwardIterator first, Size n, const T& x, _false_type) {
		int i = 0;
		for (; i != n; ++i){
			construct((T*)(first + i), x);
		}
		return (first + i);
	}

}
#endif