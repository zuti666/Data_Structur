#include<iostream>
#include<cstdlib>
using namespace std;

template<class T>
struct DblNode						//链表结点类定义
{
	T data;							//链表结点数据
	DblNode<T>* lLink, * rLink;		//链表前驱（坐链），后继（右链）
	DblNode(DblNode<T> *left=NULL,DblNode<T>*right=NULL)
		:lLink(left),rLink(right){} //构造函数
	DblNode(T value, DblNode<T>* left = NULL, DblNode<T>* right = NULL)
		:data(value),lLink(left), rLink(right) {}//构造函数
};

template<class T>
class DblList {						//链表类定义
public:
	DblList(T uniqueVal);			//构造函数：建立附加头结点
	~DblList();						//析构函数：释放所用存储
	int Length()const;				//计算双链表的长度
	bool IsEmpty() { return first->rlink == first; }//判断表是否为空
	DblNode<T>* getHead()const { return first; }	//取附加头结点位置
	void setHead(DblNode<T>* ptr) { first = ptr; }	//设置附加头结点地址
	DblNode<T>* Search(const T& x);//在链表沿后继方向寻找等于给定值x的结点
	DblNode<T>* Locate(int i, int d);//在链表定位序号为i的结点。d=0按前驱方向
	bool Insert(int i, const T& x, int d);//在i个结点后插入一个包含有值x的新结点。d=0按前驱方向
	bool Remove(int i, T& x, int d);//删除第i个结点，x返回其值。d=0按前驱方向
	int Swap(T x);	//查找第一个元素为x的结点，并与其前驱结点交换
private:
	DblNode<T>* first;
};

template<class T>
inline DblList<T>::DblList(T uniqueVal)
{//构造函数，建立双向循环链表的附加头结点，它包含了一个用于某些特定情况的值
	first = new DblNode<T>(uniqueVal);
	if (first == NULL) { cerr << "存储分配出错！" << endl; exit(1); }
	first->rLink = first->lLink = first;
}
template<class T>
inline DblList<T>::~DblList()
{
	T x;
	int changdu = Length();
	for (int i = 1; i < changdu; i++)
		Remove(i, x, 1);
}
;

template<class T>
inline int DblList<T>::Length() const
{//计算带附加头结点的双向循环链表的长度，通过函数返回
	DblNode<T>* current = first->rLink; int count = 0;
	while (current != first) { current = current->rLink; count++; }
	return count;
}

template<class T>
inline DblNode<T>* DblList<T>::Search(const T& x)
{//在附加头结点的双向循环链表中寻找其值等于x的结点
//若找到，则函数返回该结点地址，否则函数返回NULL
	DblNode<T>* current = first->rLink;
	while (current != first && current->data != x)
		current = current->rLink;
	if (current != first)return current;		//搜索成功
	else return NULL;							//搜索失败
}

template<class T>
inline DblNode<T>* DblList<T>::Locate(int i, int d)
{//在带附加头结点的双向循环链表中按d所指方向寻找第i个结点的位置
 //若d=0，在前驱方向寻找第i个结点，若d！=0,在后继方向寻找第i个结点
	if (first->rLink == first || i == 0)return first;
	DblNode<T>* current;
	if (d == 0)current = first->lLink;			//搜索方向
	else current = first->rLink;
	for (int j = 1; j < i; j++)					//逐个结点检测
		if (current == first) break;			//链太短退出搜索
		else if (d == 0)current = current->lLink;
		else current = current->rLink;

	if (current != first)return current;		//搜索成功
	else return NULL;							//搜索失败
}

template<class T>
inline bool DblList<T>::Insert(int i, const T& x, int d)
{//建立一个包含有值x的新结点，并将其按d指定方向插入到第i个结点后面
	DblNode<T>* current = Locate(i, d);		//查找第i个结点
	if (current == NULL) { cout <<i<< "不合理"; return false; }
				//i不合理，插入式失败
	DblNode<T>* newNode = new DblNode<T>(x);
		if (newNode == NULL) { cerr << "存储分配失败！" << endl; exit(1); }
	if (d == 0) {							//前驱方向插入
		newNode->lLink = current->lLink;
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else {									//后驱方向插入
		newNode->rLink = current->rLink;
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;							//插入成功
};

template<class T>
inline bool DblList<T>::Remove(int i, T& x, int d)
{//在带附加头结点的双向循环链表中按着d所指方向删除第i个结点。
	DblNode<T>* current = Locate(i, d);		//查找第i个结点
	if (current == NULL)return false;		//i不合理，删除失败
	else {
		current->rLink->lLink = current->lLink; //从lLink链中摘下
		current->lLink->rLink = current->rLink; //从rlink链中摘下
		x = current->data; delete current;		//删除
		return true;
	}						//删除成功
}

template<class T>
inline int DblList<T>::Swap(T x)
{
	DblNode<T>* current;
	T data;
	current = Search(x);			//查找元素值为x的结点
	if (current == NULL)	return 0;//若没有查找到元素值为x的结点
	else {							//交换与其前继结点的值
		data = current->data;
		current->data = current->lLink->data;
		current->lLink->data = data;
		return 1;
	}
}
