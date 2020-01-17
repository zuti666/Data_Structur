#include "UFSets.h"

UFSets::UFSets(int sz)
{//构造函数：s是集合元素个数。
 //	父指针数组的范围为parent[0]~parent[size-1]

	size=sz;//集合元素个数
	parent=new int[size];//创建父指针数组
	for (int i = 0; i < size; i++)//每个自成单元素集合
		parent[i] = -1;
}

UFSets& UFSets::operator=(UFSets& R)
{//重载操作
	for (int i = 0; i < size; i++)
		parent[i] = R.parent[i];
	return *this;
}

void UFSets::Union(int Root1, int Root2)
{//函数求两个不相交的集合的并。
//要求root1与Root2是不同的，且包含了子集合的名字。
//因为union是C++的关键字，为不致混乱，可使用Set_Union来命名
	parent[Root1] += parent[Root2];
	parent[Root2] = Root1;//将根Root2连接到另一根Root1之后
}

int UFSets::Find(int x)
{//函数搜索并返回元素x的树的根
	while (parent[x] >= 0)x = parent[x];//循链寻找x的根
	return x; //根的parent[]小于0
}

void UFSets::WeightedUnion(int Root1, int Root2)
{//使用结点个数探查方法求两个UFSets型集合的并
	int r1 = Find(Root1), r2 = Find(Root2), temp;
	if (r1 != r2) {
		temp = parent[r1] + parent[r2];//以r2为根的树结点多
		if (parent[r2] < parent[r1]) {//让r1接在r2后面
			parent[r1] = r2;
			parent[r2] = temp;
		}
		else { //让r1成为新的根
			parent[r2] = r1;
			parent[r1] = temp;
		}
	}
}

int UFSets::CollapsingFind(int i)
{//在包含元素i的树中搜索根，并将从j到根的路径上的所有结点都变成根的子女
	int j;
	for ( j = i; parent[j] >= 0; j = parent[j]);//搜索根j
	while (i != j) { //向上逐次压缩
		int temp = parent[i];
		parent[i] = j;
		i = temp;
	}
	return j;  //返回根
}
