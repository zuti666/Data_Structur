#include<iostream>
#include "SeqStack.h"
using namespace std;

template<class T>
ostream& operator<<(ostream& os, SeqStack<T>& s)
{//输出栈中元素的重载操作<<
	os << "top=" << s.top << endl;
	for (int i = 0; i <= s.top; i++)
		os << i << ":  " << s.elements[i] << endl;
	return os;
};
