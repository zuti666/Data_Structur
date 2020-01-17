#include<iostream>
#include"List.h"

template <class T>
class LinkQueue {		//链式队列类定义
public:
	LinkQueue():rear(NULL),front(NULL){}	//构造函数，建立空队列
	~LinkQueue() { makeEmpty(); }				//析构函数
	bool EnQueue(const T& x);				//将x加入到队列中
	bool DeQueue(T& x);						//删除队头元素，x返回其值
	bool getFront(T& x)const;				//查看队头元素的值
	void makeEmpty();						//置空队列
	bool IsEmpty()const { return (front == NULL) ? true : false; }
			//判断队列是否为空
	int getSize()const;						//求队列元素个数
	friend ostream& operator <<(ostream& os, LinkQueue<T>& Q) {
	//输出队列元素的重载操作<<


	}


private:
	LinkNode<T>* front, * rear;





};


template<class T>
inline bool LinkQueue<T>::EnQueue(const T& x)
{//将新元素x插入到队列的队尾（链式队列的链尾）
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
{//置空队列，释放链表中所有结点
	LinkNode<T>* p;
	while (front != NULL) {			//从头指针开始逐个删除队列中的结点
		p = front; front = front->link; delete p;
	}
}

template<class T>
inline int LinkQueue<T>::getSize() const
{
	return 0;
}
