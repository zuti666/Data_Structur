#include<iostream>
#include<assert.h>
using namespace std;
const int stackIncreament = 20;				//栈溢出时扩展空间的增量
template<class T>
class SeqStack {							//顺序类的定义
public:
	SeqStack(int sz = 50);					//建立一个空栈
	~SeqStack() { delete[]elements; }		//析构函数
	void Push(const T& x);	//如果IsFull()，则溢出处理；否则把x插入到栈的栈顶
	bool Pop(T& x);		//如果IsEmpty()，则不执行退栈，返回false;否则退掉位于栈顶的元素，返回true
						//退出的元素通过引用型参数x返回
	bool getTop(T& x);  //如果IsEmpty()，则返回false;否则返回true
						//通过引用型参数x得到栈顶元素的值
	bool IsEmpty()const { return (top == -1) ? true : false; }
	//如果栈中元素个数为0则返回true;否则返回false
	bool IsFull()const { return (top == maxSize - 1) ? true : false; }
	//如果栈中元素个数为maxSize则返回true;否则返回false
	int getSize()const { return top + 1; }	//函数返回栈中元素个数		
	void MakeEmpty() { top = -1; }			//清空栈的内容
	void convert(int num, int n);			//将整数进制num转化为n进制数
	friend ostream& operator <<(ostream & os, SeqStack<T> & s);
	//输出栈中元素的重载操作<<
private:
	T* elements;							//存放栈中元素的数组
	int top;								//栈顶指针
	int maxSize;							//栈最大可容纳元素个数
	void overflowProcess();					//栈的溢出操作
};

template<class T>
inline SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz)
{//建立一个最大尺寸为sz的空栈，若分配不成功则错误处理
	elements = new T[maxSize];			//创建栈的数组空间
	assert(elements != NULL);			//断言，动态存储分配成功与否
};

template<class T>
inline void SeqStack<T>::Push(const T & x)
{//公共函数：若栈不满，则将元素x插入到该栈的栈顶，否则溢出处理
	if (IsFull() == true)overflowProcess();	//栈满则溢出处理
	elements[++top] = x;					//栈顶指针先加1，再进栈
};

template<class T>
inline bool SeqStack<T>::Pop(T & x)
{//公共函数：若栈不空则函数返回该栈栈顶元素的值，然后栈顶指针退1
	if (IsEmpty() == true)return false;		//判断栈空否，栈空函数返回false
	x = elements[top--];					//栈顶指针退1
	return true;							//退栈成功
};

template<class T>
inline bool SeqStack<T>::getTop(T & x)
{//公共函数：若栈不空则函数返回该栈栈顶元素的地址
	if (IsEmpty() == true)return false;
	x = elements[top];
	return true;
};

template<class T>
inline void SeqStack<T>::convert(int num, int n)
{
	int yushu;
	while (num != 0)
	{
		yushu = num % n;
		num = num / n;
		Push(yushu);
	}
	int x;
	while (Pop(x)) {

		cout << "  " << x << "  ";
	}
	cout << endl;


}

template<class T>
inline void SeqStack<T>::overflowProcess()
{//私有函数：扩充栈的存储空间
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == NULL) { cerr << "存储分配失败！" << endl; exit(1); }
	for (int i = 0; i <= top; i++)newArray[i] = elements[i];
	maxSize = maxSize + stackIncreament;
	delete[]elements;
};

