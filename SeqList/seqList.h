//利用数组作为顺序表的存储结构，被封装在类的私有域中
#include<iostream>
#include<stdlib.h>

using namespace std;
const int defaultSize = 100;
template <class T>
class SeqList  {
protected:
	T* data;								//存放数组
	int maxSize;							//最大可容纳表项的项数
	int last;								//当前已存放表项的最后位置（从0开始）
	void reSize(int newSize);				//改变data数组空间大小
public:
	SeqList(int sz = defaultSize);			//构造函数
	SeqList(SeqList<T>& L);					//复制构造函数
	~SeqList() { delete []data; }			//析构函数
	int Size()const { return maxSize; }		//计算表最大可容纳表项个数
	int Length()const { return last + 1; }	//计算表长度
	T* getHead()const { return data; }      //返回数组地址
	int Search(T& x)const;					//搜索x在表中的位置，函数返回表项序号
	void Sort();							//排序
	int Locate(int i)const;					//定位第i个表项，函数返回表项序号
	bool getData(int i, T& x)const			//取第i个表项的值
	{
		if (i > 0 && i <= last + 1)
		{
			x = data[i - 1];
			return true;
		}
		else return false;
	};
	void setData(int i, T& x)				//用x修改第i个表项的值
	{
		if (i > 0 && i <= last + 1)
			data[i - 1] = x;

	};
	bool Insert(int i, T & x);				//插入x在第i个表项之后
	bool Remove(int i, T & x);				//删除第i个表项，通过x返回表项的值
	bool IsEmpty()							//判断表空否
	{//空返回true，否则返回false
		return (last == -1) ? true : false;
	}
	bool IsFull()							//判断表满否
	{//满则返回true，否则返回false
		return (last == maxSize - 1) ? true : false;
	}
	void input();							//输入
	void output();							//输出
	SeqList<T> operator =(SeqList<T> & L);	//表整体赋值
};
	template<class T>
	inline void SeqList<T>::reSize(int newSize)
	{//私有函数：扩充顺序表的存储数组空间大小，新数组的元素个数为newSize.
		if (newSize <= 0)					//检查参数的合理性
		{
			cerr << "无效的数组大小" << endl;
			return;
		}
		if (newSize != maxSize)				//修改
		{
			T* newarray = new T[newSize];	//建立新数组
			if (newarray == NULL)
			{
				cerr << "存储分配错误" << endl;
				exit(1);
			}
			int n = last + 1;
			T* srcptr = data;				//源数组首地址
			T* destptr = newarray;			//目的数组首地址
			while (n--)* destptr++ = *srcptr++;//复制
			delete[]data;					//删除老数组
			data = newarray; maxSize = newSize;//复制新数组
		}
	};

	template<class T>
	inline SeqList<T>::SeqList(int sz)
	{//构造函数，通过指定参数sz定义数组的长度。
		if (sz > 0) {
			maxSize = sz; last = -1;	//置表的实际长度为空
			data = new T[maxSize];		//创建顺序表存储数组
			if (data == NULL)			//动态分配失败
			{
				cerr << "储存分配失败！" << endl; exit(1);
			}
		}
	};

	template<class T>
	inline SeqList<T>::SeqList(SeqList<T> & L)
	{//复制构造函数，用参数表中给出的已有顺序表初始化新建的顺序表
		maxSize = L.Size();
		last = L.Length() - 1;
		T value;
		data = new T[maxSize];		//创建顺序表存储数组
		if (data == NULL)			//动态分配失败
		{
			cerr << "存储分配错误！" << endl; exit(1);
		}
		for (int i = 1; i <= last + 1; i++)
		{
			L.getData(i, value);
			data[i - 1] = value;
		}
	}
	template<class T>
	inline int SeqList<T>::Search(T & x) const
	{//搜索函数：在表中搜索与给定值x匹配的表项，
	 //	找到则返回该表项是第几个元素,否则函数返回0，表示搜索失败
		for (int i = 0; i <= last; i++)
			if (data[i] == x)return i + 1;		//顺序搜索
		return 0;								//搜索失败
	}
	template<class T>
	inline void SeqList<T>::Sort()
	{//冒泡排序
		for (int i = 0; i < last; i++) {
			//比较两个相邻的元素   
			for (int j = 0; j < last - i - 1; j++) {
				if (data[j] > data[j + 1]) {
					int t = data[j];
					data[j] = data[j + 1];
					data[j + 1] = t;
				}
			}
		}
	}
	template<class T>
	inline int SeqList<T>::Locate(int i) const
	{//定位函数：函数返回第i(1<=i<=last+1)个表项的位置，否则函数返回0，表示定位失败。
		if (i >= 1 && i <= last + 1)return i;
		else return 0;
	};

	template<class T>
	inline bool SeqList<T>::Insert(int i, T & x)
	{//将新元素x插入到表中第i(0<=i<=lat+1)个表项之后。
	 //函数返回插入成功的信息，若插入成功，则返回true；否则返回false
	 //i=0是虚拟的，实际是插入到第1个元素的位置
		if (last == maxSize - 1) return false;	//表满，不能插入
		if (i<0 || i>last + 1)return false;		//参数i不合理，不能插入
		for (int j = last; j >= i; j--)
			data[j + 1] = data[j];				//依次后移，空出第i号位置
		data[i] = x;							//插入
		last++;									//最后位置加1
		return true;							//插入成功

	};
	template<class T>
	inline bool SeqList<T>::Remove(int i, T & x)
	{//从表中删除第i(1<=i<=last+1)个表项，通过引用形参x返回删除的元素值
	 //函数返回成功的信息，若删除成功则返回true，否则返回false
		if (last == -1)return false;			//表空，不能删除
		if (i<1 || i>last + 1)return false;		//参数i不合理，不能删除
		x = data[i - 1];						//存被删除元素的值
		for (int j = i; j <= last; j++)
			data[j - 1] = data[j];				//依次前移,填补
		last--;									//最后位置减1
		return true;							//删除成功

	};
	template<class T>
	inline void SeqList<T>::input()
	{//从标准输入（键盘）逐个数据输入，建立顺序表
		cout << "开始建立顺序表，请输入表中元素个数（从0开始）：";
		while (1) {
			cin >> last;
			if (last <= maxSize - 1)break;
			cout << "表元素个数输入有误，范围不得超过" << maxSize - 1 << ":";
		}
		for (int i = 0; i <= last; i++)
		{
			cout << "第" << i  << "个元素" << endl;
			cin >> data[i];
		}
	};
	template<class T>
	inline void SeqList<T>::output()
	{//将顺序表全部元素输入到屏幕上。
		cout << "顺序表当前元素最后位置为：" << last << endl;
		for (int i = 0; i <= last; i++)
			cout << "#" << i + 1 << ":" << data[i] << endl;
	};
	template<class T>
	inline SeqList<T> SeqList<T>::operator=(SeqList<T> & L)
	{//重载操作：顺序表整体赋值。
	 //若当前调用此操作的表对象为L1，代换形参L的表对象为L2，则使用方式为L1=L2，

		this.maxSize = L.Size();
		this.last = L.Length() - 1;
		T value;
		this.data = new T[maxSize];		//创建顺序表存储数组
		if (this.data == NULL)			//动态分配失败
		{
			cerr << "存储分配错误！" << endl; exit(1);
		}
		for (int i = 1; i <= last + 1; i++)
		{
			L.getData(i, value);
			this.data[i - 1] = value;
		}
		return this;
	};

