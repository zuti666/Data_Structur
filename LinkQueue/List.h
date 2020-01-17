#include<iostream>
#include<stdlib.h>
using namespace std;
template<class T>
struct LinkNode {							//链表结点类的定义
	T data;									//数据域
	LinkNode<T>* link;						//链指针域
	LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }
										    //仅初始化指针成员的构造函数
	LinkNode(const T& item,LinkNode<T> *ptr=NULL)
	{									    //初始化数据域指针成员的构造函数
		data = item;
		link = ptr;
	}


};

template  <class T>
class List  {			//单链表类定义
public:
	List() { first = new LinkNode<T>; }		//构造函数
	List(const T& x) { first = new LinkNode<T>(x); }//构造函数
	List(List<T>& L);						//复制构造函数
	~List() { makeEmpty(); }				//析构函数
	void makeEmpty();						//将链表置空
	int Length()const;						//计算链表的长度
	LinkNode<T>* getHead()const { return first; }//返回附加头结点地址
	LinkNode<T>* Search(T x);				//搜索含数据x的元素
	LinkNode<T>* Locate(int i);				//搜索第i个元素的地址
	bool getData(int i, T& x);			//取出第i个元素的值
	void setData(int i, T& x);				//用x修改第i个元素的值
	bool Insert(int i, T& x);				//在第i个元素后插入x
	bool Remove(int i, T& x);				//删除第i个元素，x返回该元素的值
	bool IsEmpty()const						//判断表是否为空，空返回true
	{
		return first->link == NULL ? true : false;
	};
	bool IsFull()const { return false; };	//判断表是否为满，不满返回false
	void Sort();							//排序
	void input();							//输入
	void inputFront(T endTag);				//前插法建立单链表
	void inputRear(T endTag);				//后插法建立链表
	void output();							//输出
	List<T>& operator=(List<T>& L);			//重载函数：复制
protected:
	LinkNode<T>* first;						//链表的头指针
};

template<class T>
inline List<T>::List(List<T>& L)
{//复制构造函数
	T value;
	LinkNode<T>* srcptr = L.getHead();		//被复制表的被附加头结点地址
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {		//逐个结点复制
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;

	}
};
template<class T>
inline void List<T>::makeEmpty()
{//将链表置为空表
	LinkNode<T>* q;
	while (first->link != NULL) {	//当链表不空时，删去表中所有结点
		q = first->link;
		first->link = q->link;		//保存被删结点，从链上摘下该结点
		delete q;					//删除（仅保留一个表头结点）
	}
};
template<class T>
inline int List<T>::Length() const
{//计算带附加头结点的单链表的长度
	LinkNode<T>* p = first; int count = 0;
	while (p != NULL)				//循环扫描链表，寻找链尾
	{
		p = p->link;
		count++;
	}
	return count;
};
template<class T>
inline LinkNode<T>* List<T>::Search(T x)
{//在表中搜索含数据x的结点，
//搜索成功时返回该结点地址；否则返回NULL值
	LinkNode<T>* current = first->link;
	while (current != NULL)				//循环在链表中寻找x结点
		if (current->data == x)break;
		else current = current->link;
	return current;
};
template<class T>
inline LinkNode<T>*  List<T>::Locate(int i)
{//定位函数，返回表中第i个元素的地址。若i<0或者i超出表中结点个数，返回NULL
	if (i < 0)return NULL;				//i不合理
	LinkNode<T>* current = first; int k = 0;
	while (current != NULL && k < i)	//循环在链表中寻找第i个结点
	{
		current = current->link; k++;
	}
	return current;						//返回第i个结点地址，若返回NULL，表示I值太大
};
template<class T>
inline bool List<T>::getData(int i, T& x) 
{//取出链表中第i个元素的值
	if (i <= 0) return false;			//i值太小
	LinkNode<T> * current = Locate(i);
	if (current == NULL)return false;	//i值太大
	else {
		x = current->data;
		return true;
	}

};
template<class T>
inline void List<T>::setData(int i, T& x)
{//给链表中第i个元素赋值x
	if (i <= 0)return;					//i值太小
	LinkNode<T> * current = Locate(i);
	if (current == NULL)return;
	else current->data = x;				//i值太大
};
template<class T>
inline bool List<T>::Insert(int i, T& x)
{//将新元素x插在链表中第i个结点之后
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return false;	//插入不成功
	LinkNode<T>* newNode = new LinkNode<T>(x);
	if (newNode == NULL) { cerr << "存储分配失误！" << endl; exit(1); }
	newNode->link = current->link;		//链接在current之后
	current->link = newNode;
	return true;						//插入成功
}
template<class T>
inline bool List<T>::Remove(int i, T& x)
{//将链表中的第i个元素删去，通过引用型参数x返回该元素的值。
	LinkNode<T>* current = Locate(i - 1);
	if (current == NULL || current->link == NULL)return false;
	//删除不成功
	LinkNode<T> * del = current->link;	//重新拉链，将被删点从链中摘下
	current->link = del->link;
	x = del->data; delete del;			//取出被删点中的数据值
	return true;
};
template<class T>
inline void List<T>::Sort()
{//对链表进行排序：冒泡排序,从小到大顺序
	LinkNode<T>* p=NULL,*q;
	T temp;
	bool isChange = true;
	if (first == NULL || first->link == NULL)return;
	while (p!=first->link&&isChange)
	{
		q = first;
		isChange = false;//标志这一轮没有元素发生交换，表示已经有序
		for (; q->link!= p && q->link!=NULL; q = q->link)
		{
			
			if (q->data > q->link->data)    /*相邻节点比较，数据交换*/
			{
				temp = q->data;
				q->data = q->link->data;
				q->link->data = temp;
				cout << "交换" <<q->data<<"和"<<q->link->data<<endl;
			}
			p = q;
		}
	
	}
};
template<class T>
inline void List<T>::input()
{//单链表的输入函数：将链表中的所有数据按着逻辑顺序输出在屏幕上
	int geshu;
	cout << "开始建立单链表，请输入表中结点个数：" << endl;
	cin >> geshu;
	int i = 0; T x;
	LinkNode<T>* current = first = new LinkNode<T>;
	while (i<geshu) {
		i++;
		cout << "请输入第" << i << "个元素：";
		cin >> x;
		current->link = new LinkNode<T>(x);
		current = current->link;
	}
};
template <class T>
inline void List<T>::inputFront(T endTag) {
//endTag是约定的输入序列结束的标志。
//如果输入序列是正整数，endTag可以是0或负数
//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"
	LinkNode<T>* newNode;  T val;
	makeEmpty();
	cin >> val;
	while (val != endTag) {
		newNode = new LinkNode<T>(val);		//创建新结点
		if (newNode == NULL) { cerr << "存储分配错误！" << endl; exit(1); }
		newNode->link = first->link;
		first->link= newNode;
		cin >> val;							//插入到表前段
	}
};
template <class T>
inline void List<T>::inputRear(T endTag) {
	//endTag是约定的输入序列结束的标志。
	//如果输入序列是正整数，endTag可以是0或负数
	//如果输入序列是字符，endTag可以是字符集中不会出现的字符，如"\0"
	LinkNode<T>* newNode,*last;  T val;
	makeEmpty();
	cin >> val; last = first;				//尾指针last总是指向新链表的最后一个结点
	while (val != endTag) {
		newNode = new LinkNode<T>(val);		//创建新结点
		if (newNode == NULL) { cerr << "存储分配错误！" << endl; exit(1); }
		last->link = newNode;
		last = newNode;
		cin >> val;							//插入到表前段
	}
	last->link = NULL;						//表收尾，此句可以省略
};



template<class T>
inline void List<T>::output()
{//单链表的输出函数：将链表中的所有数据按着逻辑顺序输出在屏幕上
	LinkNode<T>* current = first->link;
	while (current != NULL) {
		cout << current->data << endl;
		current = current->link;
	}
};

template<class T>
inline List<T>& List<T>::operator=(List<T>& L)
{//重载函数：赋值操作，形如A=B，其中A是调用此操作的List对象
 //B是与参数表中的引用型参数L结合的实参
	T value;
	LinkNode<T>* srcptr = L.getHead();		//被复制表中的附加头结点地址
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {			//逐个结点复制
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
	return* this;							//返回操作对象地址
		
};
