#include "UFSets.h"

UFSets::UFSets(int sz)
{//���캯����s�Ǽ���Ԫ�ظ�����
 //	��ָ������ķ�ΧΪparent[0]~parent[size-1]

	size=sz;//����Ԫ�ظ���
	parent=new int[size];//������ָ������
	for (int i = 0; i < size; i++)//ÿ���Գɵ�Ԫ�ؼ���
		parent[i] = -1;
}

UFSets& UFSets::operator=(UFSets& R)
{//���ز���
	for (int i = 0; i < size; i++)
		parent[i] = R.parent[i];
	return *this;
}

void UFSets::Union(int Root1, int Root2)
{//�������������ཻ�ļ��ϵĲ���
//Ҫ��root1��Root2�ǲ�ͬ�ģ��Ұ������Ӽ��ϵ����֡�
//��Ϊunion��C++�Ĺؼ��֣�Ϊ���»��ң���ʹ��Set_Union������
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;//����Root2���ӵ���һ��Root1֮��
}

int UFSets::Find(int x)
{//��������������Ԫ��x�����ĸ�
	while (parent[x] >= 0)x = parent[x];//ѭ��Ѱ��x�ĸ�
	return x; //����parent[]С��0
}

void UFSets::WeightedUnion(int Root1, int Root2)
{//ʹ�ý�����̽�鷽��������UFSets�ͼ��ϵĲ�
	int r1 = Find(Root1), r2 = Find(Root2), temp;
	if (r1 != r2) {
		temp = parent[r1] + parent[r2];//��r2Ϊ����������
		if (parent[r2] < parent[r1]) {//��r1����r2����
			parent[r1] = r2;
			parent[r2] = temp;
		}
		else { //��r1��Ϊ�µĸ�
			parent[r2] = r1;
			parent[r1] = temp;
		}
	}
}

int UFSets::CollapsingFind(int i)
{//�ڰ���Ԫ��i��������������������j������·���ϵ����н�㶼��ɸ�����Ů
	int j;
	for ( j = i; parent[j] >= 0; j = parent[j]);//������j
	while (i != j) { //�������ѹ��
		int temp = parent[i];
		parent[i] = j;
		i = temp;
	}
	return j;  //���ظ�
}
