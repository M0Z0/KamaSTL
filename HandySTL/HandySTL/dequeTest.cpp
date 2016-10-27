#include "dequeTest.h"

namespace HandySTL{

	namespace TestDeque {

		void testCase1() {
			stdDe<int> dq1(10, 0);
			tsDe<int> dq2(10, 0);
			assert(HandySTL::Test::container_equal(dq1, dq2));

			int arr[] = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9 };
			stdDe<int> dq3(std::begin(arr), std::end(arr));
			tsDe<int> dq4(std::begin(arr), std::end(arr));
			//assert(HandySTL::Test::container_equal(dq3, dq4));

			//auto dq5(dq1);
			//auto dq6(dq2);
			//assert(HandySTL::Test::container_equal(dq5, dq6));

			//auto dq7 = dq3;
			//auto dq8 = dq4;
			//assert(HandySTL::Test::container_equal(dq7, dq8));

			//auto dq9 = std::move(dq7);
			//auto dq10 = std::move(dq8);
			//assert(HandySTL::Test::container_equal(dq9, dq10));
		}

		void testAllCases() {
			testCase1();
		}
	}
}