#include<iostream>
#include"BinaryTree.h"
using namespace std;

int main()
{
	BinaryTree<int> S(-999);
	cout << "输入树的内容（按左、右子树递归建立）（以-999作为空子树的标志）" << endl;
	cin >> S;
	cout << S;
	cout << "树的结点个数为： " << S.Size() << endl;
	cout << "树的高度为： " << S.Height() << endl;
	//第一题
	cout << "树的度为2的结点个数为： " << S.count2() << endl;
	//第二题
	cout << "树的叶结点个数为： " << S.leafnum() << endl;

	return 0;
}