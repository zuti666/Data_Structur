#include<iostream>
using namespace std;
#define DefaultSize  10
class UFSets {//���鼯 �����е��Ӽ��ϻ����ཻ
public:
	UFSets(int sz = DefaultSize);//���캯��
	~UFSets() { delete[] parent; }//��������
	UFSets& operator =(UFSets& R);//���غ��������ϸ�ֵ
	void Union(int Root1, int Root2);//�����Ӽ��Ϻϲ�
	int Find(int x);//Ѱ�Ҽ���x�ĸ����ǵݹ飩
	void WeightedUnion(int Root1, int Root2);//��Ȩ�ĺϲ��㷨
	int CollapsingFind(int i);//�����۵�����ѹ��·�����㷨
private:
	int* parent;//
	int size;//
};
