#include<iostream>
#include"StaticList.h"
using namespace std;
int main()
{
	StaticList<int> A;
	A.InitList();
	cout << "长度" << A.Length()<< endl;
	int geshu, x;
	cout << "请输入元素个数" << endl;
	cin >> geshu;
	for (int i = 1; i < geshu; i++)
	{
		cout << "请输入元素"<<i<<":" << endl;
		cin >> x;
		A.Insert(x, i);
	}
	cout << "长度" << A.Length() << endl;
	return 0;
};