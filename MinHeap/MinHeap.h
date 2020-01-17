#include<iostream>
#include<stdlib.h>
using namespace std;
#define  DefaultSize 10

template<class E>
class MinHeap {
public:
	MinHeap(int sz);	//构造函数：建立空堆
	MinHeap(E arr[], int n);//构造函数：通过一个数组建堆
	~MinHeap() { delete[]heap; }//析构函数
	bool Insert(const E& x);//将x插入到最小堆中
	bool RemoveMin(E& x);//删除堆顶上的最小元素
	bool IsEmpty()const//判断堆是否为空，空返回true，否则返回false
	{
		return (currentSize == 0) ? true : false;
	}
	bool IsFull()const//判断堆是否为满，满返回true,否则返回false
	{
		return (currentSize == maxHeapSize) ? true : false;
	}
	void MakeEmpty() { currentSize = 0; }//置空堆
	E* getfirst();//返回头结点
	int Find(E x);


protected:
	E* heap;		//存放最小堆中元素的数组
	int currentSize;//最小堆当前元素个数
	int maxHeapSize;//最小堆最多允许元素个数
	void siftDown(int start, int m);//从stsrt到m下滑调整成为最小堆
	void siftUp(int start);//从start到0上滑调整成为最小堆
	friend ostream& operator << (ostream& out, MinHeap<E>& Heap) {
		//输出堆中元素的重载操作<<
		for (int i = 0; i < Heap.maxHeapSize; i++)
			out << "  " << Heap.heap[i];
		out << endl;
		return out;
	};


};

template<class E>
inline MinHeap<E>::MinHeap(int sz)
{
	if ( DefaultSize < sz )
		maxHeapSize = sz;
	else
		maxHeapSize=DefaultSize;

	heap = new E[maxHeapSize];//创建堆存储空间
	if (heap == NULL) { cerr << "堆存储分配失败！" << endl; exit(1); }
	currentSize = 0;//建立当前大小
}

template<class E>
inline MinHeap<E>::MinHeap(E arr[], int n)
{
	maxHeapSize = (DefaultSize < n) ? n : DefaultSize;
	heap = new E[maxHeapSize];
	if (heap == NULL) { cerr << "堆存储失败！" << endl; exit(1); }
	for (int i = 0; i < n; i++)heap[i] = arr[i];
	currentSize = n;		//复制堆数组，建立当前大小
	int currentPos = (currentSize - 2) / 2;//找最初调整位置：最后分支结点
	while (currentPos >= 0) {//自底向上逐步扩大成堆
		siftDown(currentPos, currentSize - 1);//局部自上向下下滑调整
		currentPos--;		//再向前换一个分支结点
	}
}

template<class E>
inline bool MinHeap<E>::Insert(const E& x)
{//公共函数：将x插入到最小堆中
	if(currentSize==maxHeapSize)//堆满
	{
		cerr << "堆满" << endl; return false;
	}
	heap[currentSize] = x;//插入
	siftUp(currentSize);//向上调整
	currentSize++;//堆计数加一
	return true;
}

template<class E>
inline bool MinHeap<E>::RemoveMin(E& x)
{//最小堆的删除算法
	if (!currentSize) {//堆空返回false
		cout << "堆空" << endl;
		return false;
	}
	x = heap[0]; heap[0] = heap[currentSize - 1];//最后元素填补到根结点
	currentSize--;
	siftDown(0, currentSize - 1);//自上向下调整堆
	return true;//返回true
}

template<class E>
inline E* MinHeap<E>::getfirst()
{
	return heap;
}


template<class E>
inline void MinHeap<E>::siftDown(int start, int m)
{//私有函数：从结点start开始到m为止，自上向下比较，
//如果子女的值小于父结点的值，则关键码小的上浮
//继续向下层比较，这样将一个集合局部调整为最小堆
	int i = start, j = 2 * i + 1;	//j是i的右子女位置
	E temp = heap[i];
	while (j <= m) {//检查是否到最后位置
		if (j<m && heap[j]>heap[j + 1])j++;//让j指向两子女中较小的
		if (temp <= heap[j])break; //小则不必调整
		else { heap[i] = heap[j]; i = j; j = 2 * j + 1; }//否则小者上移，i,j下降
	}
	heap[i] = temp;//回放temp中暂存的元素
}

template<class E>
inline void MinHeap<E>::siftUp(int start)
{//私有函数：从结点staart开始到结点0为止，自下向上比较
//如果子女的值小于父结点的值，则交换，这样将集合重新调整为最小堆
	int j = start, i = (j - 1) / 2; E temp = heap[j];
	while (j > 0) {		//沿父结点路径向上直达根
		if (heap[i] <= temp)break;//父结点小，不调整
		else { heap[j] = heap[i]; j = i; i = (i - 1) / 2; }
			//父结点大调整
	}
	heap[j] = temp;	//回送
}

template<class E>
inline int MinHeap<E>::Find(E x)
{
	for (int i = 0; i < maxHeapSize; i++)
		if (heap[i] == x)return i;
	return 0;
	
}
