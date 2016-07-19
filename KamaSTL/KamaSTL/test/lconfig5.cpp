#include <iostream>
#include <vector>

using namespace std;

template < class I, class O>
struct testClass
{
	testClass() { cout << "I, O" << endl; }
};

template<class T>
struct testClass<T*, T*> 
{
	testClass() { cout << "T*, T*" << endl; }
};

//int main()
//{
//	testClass<int, char>obj1;
//	testClass<char*, char*>obj2;
//	getchar();
//}