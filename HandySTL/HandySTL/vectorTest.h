#ifndef _VECTOR_TEST_H_
#define _VECTOR_TEST_H_

#include "Vector.h"
#include "TestUtil.h"

#include <vector>

#include <array>
#include <cassert>
#include<iostream>
#include <iterator>
#include <string>
namespace HandySTL{

	template<class T>
	using stdVec = std::vector < T >;

	template<class T>
	using tsVec = HandySTL::vector < T >;

	void testCase1();

}
#endif