#include<iostream>
#include<stdlib.h>
#include"seqList.h"
using namespace std;
void union1(SeqList<int>& LA, SeqList<int>& LB) {
	//�ϲ�˳���LA��LB���������LA���ظ�Ԫ��ֻ��һ����
	int n = LA.Length(), m = LB.Length(), i, k, x;
	for (i = 1; i <= m; i++) {
		LB.getData(i, x);
		k = LA.Search(x);
		if (k == 0)
		{
			LA.Insert(n, x);
			n++;
		}
	}
};
void combine(int* a, int* b, int len1, int len2)
{//���ôӺ���ǰ�ϲ������ȼ�����ܳ��ȣ�����һ��ָ���a���������ǰ�ƶ���
 //����������ֱ���һ���±꣬��󳤶������鳤�ȼ�һ����λѭ���Ƚ��������飬
 //��СԪ�صķ��������飬�±��һ��ע�⣬�ϴ�Ԫ�ض�Ӧ���±겻��һ��,ֱ��ĳһ���±곬�����鳤��ʱ�˳�ѭ����
 //��ʱ�϶������Ѿ�ȫ�����������飬�ϳ����黹�в���ʣ�࣬
 //���ʣ�µĲ���Ԫ�ط��������飬�󹦸��
	if (a == NULL || b == NULL )
		return ;

	int new_point;
	int a_point = len1 - 1;
	int b_point = len2 - 1;

	new_point = len1 + len2 - 1;	//�ܵĳ���

	while (a_point >= 0 && b_point >= 0)
	{
		if (a[a_point] > b[b_point])
		{
			a[new_point--] = a[a_point--];
		}
		else
		{
			a[new_point--] = b[b_point--];
		}
	}

	while (a_point >= 0)
	{
		a[new_point--] = a[a_point--];
	}

	while (b_point >= 0)
	{
		a[new_point--] = b[b_point--];
	}

}

int main()
{
	SeqList <int> LA(10); SeqList <int> LB(10);
	LA.input(); LA.Sort(); 
	cout << "�����LA��" << endl;
	LA.output();

	LB.input(); LB.Sort(); 
	cout << "�����LA��" << endl;
	LB.output();
//����һ���Ⱥϲ���������Ϊ�Ѿ����˺ϲ�����������ֱ�ӵ�����
//	cout << "�ϲ��������" << endl;
//	union1(LA, LB); LA.output();	cout << "����������" << endl;
//	LA.Sort(); LA.output();
//

//��������
	combine(LA.getHead(), LB.getHead(), LA.Length(), LB.Length());

	return 0;
}