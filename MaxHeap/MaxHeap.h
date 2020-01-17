#include<iostream>
#include<stdlib.h>
using namespace std;
#define  DefaultSize 10

template<class E>
class MaxHeap {
public:
	MaxHeap(int sz);	//���캯���������ն�
	MaxHeap(E arr[], int n);//���캯����ͨ��һ�����齨��
	~MaxHeap() { delete[]heap; }//��������
	bool Insert(const E& x);//��x���뵽��С����
	bool RemoveMax(E& x);//ɾ���Ѷ��ϵ���СԪ��
	bool IsEmpty()const//�ж϶��Ƿ�Ϊ�գ��շ���true�����򷵻�false
	{
		return (currentSize == 0) ? true : false;
	}
	bool IsFull()const//�ж϶��Ƿ�Ϊ����������true,���򷵻�false
	{
		return (currentSize == maxHeapSize) ? true : false;
	}
	void MakeEmpty() { currentSize = 0; }//�ÿն�
	E* getfirst();//����ͷ���
	int Find(E x);


protected:
	E* heap;		//�����С����Ԫ�ص�����
	int currentSize;//��С�ѵ�ǰԪ�ظ���
	int maxHeapSize;//��С���������Ԫ�ظ���
	void siftDown(int start, int m);//��stsrt��m�»�������Ϊ��С��
	void siftUp(int start);//��start��0�ϻ�������Ϊ��С��
	friend ostream& operator << (ostream& out, MaxHeap<E>& Heap) {
		//�������Ԫ�ص����ز���<<
		for (int i = 0; i < Heap.maxHeapSize; i++)
			out << "  " << Heap.heap[i];
		out << endl;
		return out;
	};


};

template<class E>
inline MaxHeap<E>::MaxHeap(int sz)
{
	if (DefaultSize < sz)
		maxHeapSize = sz;
	else
		maxHeapSize = DefaultSize;

	heap = new E[maxHeapSize];//�����Ѵ洢�ռ�
	if (heap == NULL) { cerr << "�Ѵ洢����ʧ�ܣ�" << endl; exit(1); }
	currentSize = 0;//������ǰ��С
}

template<class E>
inline MaxHeap<E>::MaxHeap(E arr[], int n)
{
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) { cerr << "�Ѵ洢ʧ�ܣ�" << endl; exit(1); }
	for (int i = 0; i < n; i++)heap[i] = arr[i];
	currentSize = n;		//���ƶ����飬������ǰ��С
	int currentPos = (currentSize - 2) / 2;//���������λ�ã�����֧���
	while (currentPos >= 0) {//�Ե�����������ɶ�
		siftDown(currentPos, currentSize - 1);//�ֲ����������»�����
		currentPos--;		//����ǰ��һ����֧���
	}
}

template<class E>
inline bool MaxHeap<E>::Insert(const E & x)
{//������������x���뵽��С����
	if (currentSize == maxHeapSize)//����
	{
		cerr << "����" << endl; return false;
	}
	heap[currentSize] = x;//����
	siftUp(currentSize);//���ϵ���
	currentSize++;//�Ѽ�����һ
	return true;
}

template<class E>
inline bool MaxHeap<E>::RemoveMax(E & x)
{//��С�ѵ�ɾ���㷨
	if (!currentSize) {//�ѿշ���false
		cout << "�ѿ�" << endl;
		return false;
	}
	x = heap[0]; heap[0] = heap[currentSize - 1];//���Ԫ����������
	currentSize--;
	siftDown(0, currentSize - 1);//�������µ�����
	return true;//����true
}

template<class E>
inline E* MaxHeap<E>::getfirst()
{
	return heap;
}


template<class E>
inline void MaxHeap<E>::siftDown(int start, int m)
{//˽�к������ӽ��start��ʼ��mΪֹ���������±Ƚϣ�
//�����Ů��ֵ���ڸ�����ֵ����ؼ������ϸ�
//�������²�Ƚϣ�������һ�����Ͼֲ�����Ϊ����
	int i = start, j = 2 * i + 1;	//j��i������Ůλ��
	E temp = heap[i];
	while (j <= m) {//����Ƿ����λ��
		if (j<m && heap[j]<heap[j + 1])j++;//��jָ������Ů�нϴ��
		if (temp >= heap[j])break; //���򲻱ص���
		else { heap[i] = heap[j]; i = j; j = 2 * j + 1; }//����������ƣ�i,j�½�
	}
	heap[i] = temp;//�ط�temp���ݴ��Ԫ��
}

template<class E>
inline void MaxHeap<E>::siftUp(int start)
{//˽�к������ӽ��staart��ʼ�����0Ϊֹ���������ϱȽ�
//�����Ů��ֵ���ڸ�����ֵ���򽻻����������������µ���Ϊ����
	int j = start, i = (j - 1) / 2; E temp = heap[j];
	while (j > 0) {		//�ظ����·������ֱ���
		if (heap[i] >= temp)break;//�����С��������
		else { heap[j] = heap[i]; j = i; i = (i - 1) / 2; }
		//�����С����
	}
	heap[j] = temp;	//����
}

template<class E>
inline int MaxHeap<E>::Find(E x)
{
	for (int i = 0; i < maxHeapSize; i++)
		if (heap[i] == x)return i;
	return 0;

}

