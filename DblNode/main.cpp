#include<iostream>
#include"DblList.h"
using namespace std;
int main()
{
	int geshu, x;	
	cout << "请输入要建立的双向链表元素个数" << endl;	//建立链表
	cin >> geshu;
	DblList<int> A(geshu);
	for (int i = 0; i < geshu; i++)
	{
		cout << "请输入第" << i+1<< "个元素：" << endl;
		cin >> x;
		if (A.Insert(i, x, 1) == true)cout << "插入成功" << endl;
	}

	for (int i = 1; i <= geshu; i++)			//将链表进行输出
	{
		cout << "第" << i << "个元素：" << "   ";
		if(A.Locate(i,1) != NULL)
			cout << A.Locate(i, 1)->data << endl;
	}

	cout << "请输入要交换的元素" << endl;	   //对元素进行交换
	cin >> x;
	A.Swap(x);
	for (int i = 1; i <= geshu; i++)		   //将链表输出
	{
		cout << "第" << i << "个元素：" << "   ";
		if (A.Locate(i, 1) != NULL)
			cout << A.Locate(i, 1)->data << endl;
	}
		

	return 0;
}