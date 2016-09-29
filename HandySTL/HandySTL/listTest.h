#ifndef _LIST_TEST_H_
#define _LIST_TEST_H_

#include "TestUtil.h"

#include "List.h"
//#include "Mlist.h"
#include <list>

#include <cassert>
#include <functional>
#include <string>
#include <random>

namespace HandySTL{

	namespace TestList {

		template<class T>
		using stdL = std::list < T >;
		template<class T>
		using tsL = HandySTL::list < T >;
		//using tsL = HandySTL::list < T >;

		void testCase1();

		void testAllCases();
	}
}

#endif