#include<iostream>
#include"MaxHeap.h"
int main()
{
	int a[] = { 4,8,7,6,5,2,1,3,0,9 };
	MaxHeap<int> A(a, 10);
	cout << A;
	cout << A.Find(2) << endl;
	return 0;
}