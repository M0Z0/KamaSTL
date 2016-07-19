#include "myIter.h"

int main()
{
	MyIter<int> it(new int(8));
	std::cout << func(it);
	getchar();
}