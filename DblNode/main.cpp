#include<iostream>
#include"DblList.h"
using namespace std;
int main()
{
	int geshu, x;	
	cout << "������Ҫ������˫������Ԫ�ظ���" << endl;	//��������
	cin >> geshu;
	DblList<int> A(geshu);
	for (int i = 0; i < geshu; i++)
	{
		cout << "�������" << i+1<< "��Ԫ�أ�" << endl;
		cin >> x;
		if (A.Insert(i, x, 1) == true)cout << "����ɹ�" << endl;
	}

	for (int i = 1; i <= geshu; i++)			//������������
	{
		cout << "��" << i << "��Ԫ�أ�" << "   ";
		if(A.Locate(i,1) != NULL)
			cout << A.Locate(i, 1)->data << endl;
	}

	cout << "������Ҫ������Ԫ��" << endl;	   //��Ԫ�ؽ��н���
	cin >> x;
	A.Swap(x);
	for (int i = 1; i <= geshu; i++)		   //���������
	{
		cout << "��" << i << "��Ԫ�أ�" << "   ";
		if (A.Locate(i, 1) != NULL)
			cout << A.Locate(i, 1)->data << endl;
	}
		

	return 0;
}