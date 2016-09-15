#include "vectorTest.h"
#include <iostream>
#include <vector>
namespace HandySTL{

	void testCase1()
	{
		int a = 2;
		HandySTL::vector<int> v1(1);
		v1.push_back(a);
		HandySTL::vector<int>::iterator it = v1.begin();
		for (; it != v1.end(); it++)
		{
			std::cout << *it << std::endl;
		}

		std::vector<int> v2(1);
		v2.push_back(a);
		std::vector<int>::iterator it1 = v2.begin();
		for (; it1 != v2.end(); it1++)
		{
			std::cout << *it1 << std::endl;
		}
		getchar();

	}


}
