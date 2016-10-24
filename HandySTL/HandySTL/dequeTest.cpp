#include "dequeTest.h"

namespace HandySTL{

	namespace TestDeque {

		void testCase1() {
			stdDe<int> d1;

			tsDe<int> td1;

			tsDe<int> dq2(10, 0);
			//int i = dq2.size();
			//assert(dq2.size() == 10);
		}

		void testAllCases() {
			testCase1();
		}
	}
}