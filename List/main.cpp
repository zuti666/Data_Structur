#include<iostream>
#include<stdlib.h>
#include"List.h"
using namespace std;

void union1(List<int>& LA, List<int>& LB) {
	//合并链表LA与LB，结果存于LA，重复元素只留一个。
int n=LA.Length(), m = LB.Length(), i, x;
for (i = 1; i <= m; i++) {
	LB.getData(i, x);
	if (LA.Search(x) == NULL)
	{
		LA.Insert(n-1, x);
		n++;
		LA.getData(n, x);	
	}
}

};

//将两个有序链表合并(循环实现)
void Combian(LinkNode<int>* head1, LinkNode<int>* head2)
{
	
	//声明两个指针分别指向两个链表的数据开始部分
	LinkNode<int>* p1 = head1->link;
	LinkNode<int>* p2 = head2->link;
	//声明一个指针来指向新链表的最后一个结点,开始时指向head
	LinkNode<int>* last = head1;
	while (p1 != NULL && p2 != NULL)
	{
		//p1结点的数据小：将last指向p1结点，last和p1分别后移
		if (p1->data < p2->data)
		{
			last->link = p1;
			p1 = p1->link;
			last = last->link;
		}
		//p2结点数据小：将last指向p2结点，last和p2分别后移
		else
		{
			last->link = p2;
			p2 = p2->link;
			last = last->link;
		}
	}
	//当有一个链表结束时候，将last指向还未结束的链表
	if (p1 == NULL)
		last->link = p2;
	else if (p2 == NULL)
		last->link = p1;
};



//在List类中有运算符重载的复制函数=
//在List类中有复制构造函数
//在List类中有删除函数Remove
int main()
{
	List<int>  LA,  LB; 
	
	LA.input(); cout << "长度" << LA.Length() << endl; LA.Sort(); LA.output();
	LB.input(); LB.Sort(); LB.output();
//一、合并有序链表
	//方法一，先合并再排序，因为已经有了合并和排序函数就直接调用了
//	cout << "合并后的链表" << endl; cout << "长度" << LA.Length() << endl;
//	union1(LA, LB);  LA.output();	
//	cout << "排序后的链表" << endl;
//	LA.Sort(); LA.output();
	//方法二，
	Combian(LA.getHead(), LB.getHead());
	cout << "合并后" << endl;
	LA.output();

//二、复制链表算法
//	cout << "运算符重载的复制函数" << endl;;
//	LB = LA; LB.output();//调用运算符重载的复制函数=进行复制
//	cout << "复制构造函数的复制函数" << endl;;
//	List<int>  LC(LA); LC.output();//调用复制构造函数进行复制
//三、删除链表算法
//	int x;
//	LA.Remove(2,x);					//调用删除函数
//	cout << "被删除元素"<<x << endl;
//	cout << "删除操作后的链表" << endl;
//	LA.output();


	return 0;
	
};