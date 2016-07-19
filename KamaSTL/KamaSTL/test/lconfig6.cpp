#include <iostream>
using namespace std;

class alloc{};

template<class T, class Alloc = alloc>
class vector{
public:
	void swap(vector<T, Alloc>&) { cout << "swap()" << endl; }
};

#ifdef __STL_FUNCTION_TEMP_PATIAL_ORDER
template<class T, class Alloc>
class vector{
public:
	inline void swap(vector<T, Alloc>& x, vector<T, Alloc>& y) { x.swap(y); }
};
#endif

//int main()
//{
//	vector<int> x, y;
//	swap(x, y);
//	x.swap(y);
//	getchar();
//}