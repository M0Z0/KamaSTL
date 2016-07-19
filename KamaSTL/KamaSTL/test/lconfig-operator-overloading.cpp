#include <iostream>
//#include <cstddef> 
using namespace std;

class INT{
	friend ostream& operator<<(ostream& os, const INT& i);

public:
	INT(int i) :m_i(i) {};

	INT& operator++()
	{
		++(this->m_i);
		return *this;
	}

	const INT operator++(int)
	{
		INT temp = *this;
		++(*this);
		return temp;
	}

	int& operator*() const
	{
		return (int&)m_i;
	}
private:
	int m_i;

};

ostream& operator<<(ostream& os, const INT& i)
{
	os << '[' << i.m_i << ']';
	return os;
}
//int main()
//{
//	INT I(3);
//	cout << I++;
//	cout << ++I;
//	cout << *I;
//	getchar();
//}