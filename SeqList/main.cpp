#include<iostream>
#include<stdlib.h>
#include"seqList.h"
using namespace std;
void union1(SeqList<int>& LA, SeqList<int>& LB) {
	//合并顺序表LA与LB，结果存于LA，重复元素只留一个。
	int n = LA.Length(), m = LB.Length(), i, k, x;
	for (i = 1; i <= m; i++) {
		LB.getData(i, x);
		k = LA.Search(x);
		if (k == 0)
		{
			LA.Insert(n, x);
			n++;
		}
	}
};
void combine(int* a, int* b, int len1, int len2)
{//采用从后往前合并，首先计算出总长度，设置一个指针从a数组最后往前移动。
 //给两个数组分别定义一个下标，最大长度是数组长度减一，按位循环比较两个数组，
 //较小元素的放入新数组，下标加一（注意，较大元素对应的下标不加一）,直到某一个下标超过数组长度时退出循环，
 //此时较短数组已经全部放入新数组，较长数组还有部分剩余，
 //最后将剩下的部分元素放入新数组，大功告成
	if (a == NULL || b == NULL )
		return ;

	int new_point;
	int a_point = len1 - 1;
	int b_point = len2 - 1;

	new_point = len1 + len2 - 1;	//总的长度

	while (a_point >= 0 && b_point >= 0)
	{
		if (a[a_point] > b[b_point])
		{
			a[new_point--] = a[a_point--];
		}
		else
		{
			a[new_point--] = b[b_point--];
		}
	}

	while (a_point >= 0)
	{
		a[new_point--] = a[a_point--];
	}

	while (b_point >= 0)
	{
		a[new_point--] = b[b_point--];
	}

}

int main()
{
	SeqList <int> LA(10); SeqList <int> LB(10);
	LA.input(); LA.Sort(); 
	cout << "有序表LA：" << endl;
	LA.output();

	LB.input(); LB.Sort(); 
	cout << "有序表LA：" << endl;
	LB.output();
//方法一，先合并再排序，因为已经有了合并和排序函数就直接调用了
//	cout << "合并后的链表" << endl;
//	union1(LA, LB); LA.output();	cout << "排序后的链表" << endl;
//	LA.Sort(); LA.output();
//

//方法二，
	combine(LA.getHead(), LB.getHead(), LA.Length(), LB.Length());

	return 0;
}