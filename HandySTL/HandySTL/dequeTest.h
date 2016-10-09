#ifndef _DEQUE_TEST_H_
#define _DEQUE_TEST_H_

#include "Deque.h"
#include "TestUtil.h"

#include <deque>

#include <array>
#include <cassert>
#include<iostream>
#include <iterator>
#include <string>
namespace HandySTL{

	template<class T>
	using stdDe = std::deque < T >;

	template<class T>
	using tsDe = HandySTL::deque < T >;

	void testCase1();

	void testAllCases();

}
#endif