#include<iostream>
using namespace std;
const int maxSize = 100;	//��̬�����С

template <class T>
struct SLinkNode
{
	T data;					//�������
	int link;				//�������ָ��
};

template<class T>
class StaticList {
	SLinkNode< T> elem[maxSize];
	int avil;				//��ǰ�ɷ���ռ��׵�ַ
public:
	void InitList();
	int Length();			//���㾲̬������
	int Search(T x);		//�ھ�̬�����в��Ҿ��ж�ֵ�ý��
	int Locate(int i);		//�ھ�̬�����в��ҵ�i�����
	bool Append(T x);		//�ھ�̬����ı�β׷��һ���½��
	bool Insert(int i, T x);//�ھ�̬�����i����������½��
	bool Remove(int i);		//�ھ�̬�������ͷŵ�i�����
	bool IsEmpty();			//�ж������Ƿ�Ϊ��
};

template<class T>
inline void StaticList<T>::InitList()
{//�������ʼ��
	elem[0].link = -1;
	avil = 1;
	//��ǰ�ɷ���ռ��1��ʼ������ͷ���Ŀ�����
	for (int i = 1; i < maxSize - 1; i++)
		elem[i].link = i + 1;				//���ɿ�������
	elem[maxSize - 1].link = -1;			//������β
};

template<class T>
inline int StaticList<T>::Length()
{//���㾲̬������
	int p = elem[0].link; int i = 0;
	while (p != -1) {
		p = elem[p].link;
		i++;
	}
	return i;
};

template<class T>
inline int StaticList<T>::Search(T x)
{//�ھ�̬�����в��Ҿ��ж�ֵ�Ľ��
	int p = elem[0].link;				//ָ��pָ������ĵ�һ�����
	while (p != -1)						//����������Ҿ��и���ֵ�Ľ��
		if (elem[p].data == x)break;
		else p = elem[p].link;
	return p;
};

template<class T>
inline int StaticList<T>::Locate(int i)
{//�ھ�̬�����в��ҵ�i�����
	if (i < 0) return -1;				//����������
	if (i == 0)return 0;
	int j = 1, p = elem[0].link;
	while (p != -1 && j < i)
	{
		p = elem[p].link;				//ѭ�����ҵ�i�Ž��
		j++;
	}
	return p;
};

template<class T>
inline bool StaticList<T>::Append(T x)
{//�ھ�̬�����еı�β׷��һ���µĽ��
	if (avil == -1)return false;		//׷��ʧ��
	int q = avil;						//������
	avil = elem[avil].link;
	elem[q].data = x; elem[q].link = -1;
	int p = 0;							//���ұ�β
	while (elem[p].link != -1)
		p = elem[p].link;
	elem[p].link = q;					//׷��
	return true;
};

template<class T>
inline bool StaticList<T>::Insert(int i, T x)
{//�ھ�̬�����е�i������������½��
	int p = Locate(i);
	if (p == -1)return false;			//�Ҳ������
	int q = avil;						//������
	avil = elem[avil].link;
	elem[q].data = x;
	elem[q].link = elem[p].link;		//����
	elem[p].link = q;
	return true;
};

template<class T>
inline bool StaticList<T>::Remove(int i)
{//�ھ�̬�������ͷŵ�i�����
	int p = Locate(i - 1);
	if(p == -1) return false;			//�Ҳ������
	int q = elem[p].link;				//��i�Ž��
	elem[p].link = elem[q].link;
	elem[q].link = avil;
	avil = q;						    //�ͷ�
	return true;
};

template<class T>
inline bool StaticList<T>::IsEmpty()
{//�ж������Ƿ�Ϊ��
	if (elem[0].link == -1)return true;
	else return false;
};
