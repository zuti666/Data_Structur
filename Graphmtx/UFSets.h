#include<iostream>
using namespace std;
#define DefaultSize  10
class UFSets {//并查集 集合中的子集合互不相交
public:
	UFSets(int sz = DefaultSize);//构造函数
	~UFSets() { delete[] parent; }//析构函数
	UFSets& operator =(UFSets& R);//重载函数：集合赋值
	void Union(int Root1, int Root2);//两个子集合合并
	int Find(int x);//寻找集合x的根（非递归）
	void WeightedUnion(int Root1, int Root2);//加权的合并算法
	int CollapsingFind(int i);//按照折叠规则压缩路径的算法
private:
	int* parent;//
	int size;//
};
