#include "vectorTest.h"
#include "listTest.h"
#include "dequeTest.h"

int main()
{
	HandySTL::testCase1();
	HandySTL::TestList::testAllCases();
	HandySTL::TestDeque::testAllCases();
}