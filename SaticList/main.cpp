#include<iostream>
#include"StaticList.h"
using namespace std;
int main()
{
	StaticList<int> A;
	A.InitList();
	cout << "����" << A.Length()<< endl;
	int geshu, x;
	cout << "������Ԫ�ظ���" << endl;
	cin >> geshu;
	for (int i = 1; i < geshu; i++)
	{
		cout << "������Ԫ��"<<i<<":" << endl;
		cin >> x;
		A.Insert(x, i);
	}
	cout << "����" << A.Length() << endl;
	return 0;
};