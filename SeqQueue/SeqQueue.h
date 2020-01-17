#include<iostream>
#include<assert.h>
using namespace std;

template<class T>
class SeqQueue {			//ѭ�����е��ඨ��
public:
	SeqQueue(int sz = 10);	//���캯��
	~SeqQueue() { delete[]elements; }//��������
	bool EnQueue(const T& x);
		//�����в�������x���ӣ�������������
	bool  DeQueue(T& x);
		//�����в��գ����˳���ͷԪ��x���ɺ�������true������ӿգ�����false
	bool getFront(T& x);
		//�����в�Ϊ�գ���������true����ͷԪ�ص�ֵ�����򷵻�false
	void makeEmpty() { front = rear = 0; }
		//�ÿղ�������ͷָ��Ͷ�βָ����0
	bool IsEmpty()const { return(front == rear) ? true : false; }
		//�ж϶����Ƿ�Ϊ�գ��������пգ���������true;���򷵻�false
	bool IsFull()const { return ((rear + 1) % maxSize == front) ? true : false; }
		//�ж϶����Ƿ�Ϊ����������������������true;���򷵻�false	
	int	getSize()const { return (rear - front + maxSize) % maxSize; }
		//�����Ԫ�ظ���
	friend ostream& operator <<(ostream& os, SeqQueue<T>& Q) {
		//���ջ��Ԫ�ص����ز���<<
		os << "front=" << Q.front << ",rear=" << Q.rear << endl;
		for (int i = Q.front; i != Q.rear; i = (i + 1) % Q.maxSize)
			os << i << ":" << Q.elements[i] << endl;
		return os;
}
		//�������Ԫ�ص����ز���<<
private:
	int rear,front;		//��β���ͷָ��
	T *elements;			//��Ŷ���Ԫ�ص�����
	int maxSize;			//������������Ԫ�ظ���
}; 

template<class T>
inline SeqQueue<T>::SeqQueue(int sz):front(0),rear(0),maxSize(sz)
{//����һ������maxSize��Ԫ�صĿն���
	elements = new T[maxSize];		//�������пռ�
	assert(elements != NULL);		//���ԣ���̬�洢����ɹ����
};

template<class T>
inline bool SeqQueue<T>::EnQueue(const T& x)
{//�����в�������Ԫ��x���뵽�ö��еĶ�β�����������
	if (IsFull() == true)return false;//�����������ʧ�ܣ�����false
	elements[rear] = x;				  //���Ŷ�βָ��ָʾλ�ò���
	rear = (rear + 1) % maxSize;	  //��βָ���1
	return true;					  //����ɹ�������
};

template<class T>
inline bool SeqQueue<T>::DeQueue(T& x)
{//�����в��������˵�һ����ͷԪ�ز�����true,����������false
	
	if(IsEmpty() == true) return false;//������Ϊ����ɾ��ʧ�ܣ�����false
	x = elements[front];
	front = (front + 1) % maxSize;	  //��ͷָ���1
	return true;					  //ɾ���ɹ�������true
};

template<class T>
inline bool SeqQueue<T>::getFront(T& x)
{//�����в�Ϊ���������ظö��ж�ͷԪ�ص�ֵ
	if (IsEmpty() == true)return false;	//���ӿ���������false
	x = elements[front];				//���ض�ͷԪ�ص�ֵ
	return true;
};


