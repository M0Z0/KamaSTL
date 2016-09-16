#include "vectorTest.h"
#include <iostream>
#include <vector>
#include "TestUtil.h"


namespace HandySTL{

	void testCase1()
	{
		//int a = 2;
		//HandySTL::vector<int> v1(1);
		//v1.push_back(a);
		//HandySTL::vector<int>::iterator it = v1.begin();
		//for (; it != v1.end(); it++)
		//{
		//	std::cout << *it << std::endl;
		//}

		//std::vector<int> v2(1);
		//v2.push_back(a);
		//std::vector<int>::iterator it1 = v2.begin();
		//for (; it1 != v2.end(); it1++)
		//{
		//	std::cout << *it1 << std::endl;
		//}
		//getchar();
		stdVec<std::string> v1(10, "mk");
		tsVec<std::string> v2(10, "mk");
		assert(HandySTL::Test::container_equal(v1, v2));

		stdVec<std::string> v3(10);
		tsVec<std::string> v4(10);
		assert(HandySTL::Test::container_equal(v3, v4));

		//std::array<std::string, 3> arr = { "abc", "def", "ghi" };
		//stdVec<std::string> v5(std::begin(arr), std::end(arr));
		//tsVec<std::string> v6(std::begin(arr), std::end(arr));
		//assert(HandySTL::Test::container_equal(v5, v6));

	}


}
