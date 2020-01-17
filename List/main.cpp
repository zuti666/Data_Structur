#include<iostream>
#include<stdlib.h>
#include"List.h"
using namespace std;

void union1(List<int>& LA, List<int>& LB) {
	//�ϲ�����LA��LB���������LA���ظ�Ԫ��ֻ��һ����
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

//��������������ϲ�(ѭ��ʵ��)
void Combian(LinkNode<int>* head1, LinkNode<int>* head2)
{
	
	//��������ָ��ֱ�ָ��������������ݿ�ʼ����
	LinkNode<int>* p1 = head1->link;
	LinkNode<int>* p2 = head2->link;
	//����һ��ָ����ָ������������һ�����,��ʼʱָ��head
	LinkNode<int>* last = head1;
	while (p1 != NULL && p2 != NULL)
	{
		//p1��������С����lastָ��p1��㣬last��p1�ֱ����
		if (p1->data < p2->data)
		{
			last->link = p1;
			p1 = p1->link;
			last = last->link;
		}
		//p2�������С����lastָ��p2��㣬last��p2�ֱ����
		else
		{
			last->link = p2;
			p2 = p2->link;
			last = last->link;
		}
	}
	//����һ���������ʱ�򣬽�lastָ��δ����������
	if (p1 == NULL)
		last->link = p2;
	else if (p2 == NULL)
		last->link = p1;
};



//��List��������������صĸ��ƺ���=
//��List�����и��ƹ��캯��
//��List������ɾ������Remove
int main()
{
	List<int>  LA,  LB; 
	
	LA.input(); cout << "����" << LA.Length() << endl; LA.Sort(); LA.output();
	LB.input(); LB.Sort(); LB.output();
//һ���ϲ���������
	//����һ���Ⱥϲ���������Ϊ�Ѿ����˺ϲ�����������ֱ�ӵ�����
//	cout << "�ϲ��������" << endl; cout << "����" << LA.Length() << endl;
//	union1(LA, LB);  LA.output();	
//	cout << "����������" << endl;
//	LA.Sort(); LA.output();
	//��������
	Combian(LA.getHead(), LB.getHead());
	cout << "�ϲ���" << endl;
	LA.output();

//�������������㷨
//	cout << "��������صĸ��ƺ���" << endl;;
//	LB = LA; LB.output();//������������صĸ��ƺ���=���и���
//	cout << "���ƹ��캯���ĸ��ƺ���" << endl;;
//	List<int>  LC(LA); LC.output();//���ø��ƹ��캯�����и���
//����ɾ�������㷨
//	int x;
//	LA.Remove(2,x);					//����ɾ������
//	cout << "��ɾ��Ԫ��"<<x << endl;
//	cout << "ɾ�������������" << endl;
//	LA.output();


	return 0;
	
};