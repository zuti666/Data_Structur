#include<iostream>
#include"List.h"

template <class T>
class LinkQueue {		//��ʽ�����ඨ��
public:
	LinkQueue():rear(NULL),front(NULL){}	//���캯���������ն���
	~LinkQueue() { makeEmpty(); }				//��������
	bool EnQueue(const T& x);				//��x���뵽������
	bool DeQueue(T& x);						//ɾ����ͷԪ�أ�x������ֵ
	bool getFront(T& x)const;				//�鿴��ͷԪ�ص�ֵ
	void makeEmpty();						//�ÿն���
	bool IsEmpty()const { return (front == NULL) ? true : false; }
			//�ж϶����Ƿ�Ϊ��
	int getSize()const;						//�����Ԫ�ظ���
	friend ostream& operator <<(ostream& os, LinkQueue<T>& Q) {
	//�������Ԫ�ص����ز���<<


	}


private:
	LinkNode<T>* front, * rear;





};


template<class T>
inline bool LinkQueue<T>::EnQueue(const T& x)
{//����Ԫ��x���뵽���еĶ�β����ʽ���е���β��
	return false;
}

template<class T>
inline bool LinkQueue<T>::DeQueue(T& x)
{
	return false;
}

template<class T>
inline bool LinkQueue<T>::getFront(T& x) const
{
	return false;
}

template<class T>
inline void LinkQueue<T>::makeEmpty()
{//�ÿն��У��ͷ����������н��
	LinkNode<T>* p;
	while (front != NULL) {			//��ͷָ�뿪ʼ���ɾ�������еĽ��
		p = front; front = front->link; delete p;
	}
}

template<class T>
inline int LinkQueue<T>::getSize() const
{
	return 0;
}
