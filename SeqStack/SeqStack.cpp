#include<iostream>
#include "SeqStack.h"
using namespace std;

template<class T>
ostream& operator<<(ostream& os, SeqStack<T>& s)
{//���ջ��Ԫ�ص����ز���<<
	os << "top=" << s.top << endl;
	for (int i = 0; i <= s.top; i++)
		os << i << ":  " << s.elements[i] << endl;
	return os;
};
