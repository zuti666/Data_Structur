#include<iostream>
#include"BinaryTree.h"
using namespace std;

int main()
{
	BinaryTree<int> S(-999);
	cout << "�����������ݣ������������ݹ齨��������-999��Ϊ�������ı�־��" << endl;
	cin >> S;
	cout << S;
	cout << "���Ľ�����Ϊ�� " << S.Size() << endl;
	cout << "���ĸ߶�Ϊ�� " << S.Height() << endl;
	//��һ��
	cout << "���Ķ�Ϊ2�Ľ�����Ϊ�� " << S.count2() << endl;
	//�ڶ���
	cout << "����Ҷ������Ϊ�� " << S.leafnum() << endl;

	return 0;
}