#include<iostream>
#include"SeqStack.h"		//头文件，顺序栈
#include"LinkQueue.h"		//头文件，链式队列
using namespace std;
 int I = 0;
template<class T>
struct BinTreeNode {											//二叉树结点类定义
	T data;														//数据域
	BinTreeNode<T>* leftChild, * rightChild;					//左子女，右子女链域
	BinTreeNode() :leftChild(NULL), rightChild(NULL) { }		//无参数构造函数
	BinTreeNode(T x, BinTreeNode<T> * l = NULL, BinTreeNode<T>* r = NULL)//有参数构造函数，
			//在类定义体中，如果采用通用数据类型的成员，函数参数的前面需加上T
		:data(x), leftChild(l), rightChild(r) { }
};

template<class T>												//二叉树类定义
class BinaryTree
{
public:
	BinaryTree() :root(NULL) { }								//无参数构造函数
	BinaryTree(T value) :RefValue(value), root(NULL) { }		//构造函数，用value初始化数据输入停止标志
	BinaryTree(BinaryTree<T>& s);								//复制构造函数
	~BinaryTree() { destroy(root); }							//析构函数，调用destroy函数对二叉树进行删除
	bool IsEmpty() { return (root == NULL) ? true : false; }	//判断二叉树是否为空
	BinTreeNode<T>* CreateBinaryTree(T* VLR, T* LVR, int n);	//利用前序序列和中序序列构造二叉树
	BinTreeNode<T>* Convert(const T* expression);	//利用所给表达式构造二叉树
	BinTreeNode<T>* Parent(BinTreeNode<T> * current)			//返回父结点，
	{						//如果不是根节点，调用Parent函数返回父节点
		return (root == NULL || root == current) ? NULL : Parent(root, current);
	}
	BinTreeNode<T>* LeftChild(BinTreeNode<T> * current)			//返回左子女
	{
		return (current != NULL) ? current->leftChild : NULL;
	}
	BinTreeNode<T>* RightChild(BinTreeNode<T> * current)		//返回右子女
	{
		return (current != NULL) ? current->rightChild : NULL;
	}


	int Height() {  return Height(root); }			//返回树高度，调用Height函数
	int Size() { return Size(root); }				//返回结点数，调用Size函数
	int count2() { return count2(root); }			//返回度为2的结点数
	int leafnum() { return leafnum(root); }			//返回叶结点数
	BinTreeNode<T>* getRoot()const { return root; }		//取根，root为保护成员，储存二叉树的根


	void preOrder(void (*visit)(BinTreeNode<T>* p));  //前序遍历，调用preOrder函数
	
	void inOrder(void(*visit)(BinTreeNode<T>* p));	//中序遍历，调用保护成员中的inOrder函数
	
	void postOrder(void (*visit)(BinTreeNode<T>* p)); //后序遍历
	
	void levelOrder(void(*visit)(BinTreeNode<T>* p));	
		//利用队列实现层次序遍历
	void preOrder1(void(*visit)(BinTreeNode<T>* p));
		//二叉树先序遍历的非递归算法
	void preOrder2(void(*visit)(BinTreeNode<T>* p));
		//另一种二叉树前序遍历的非递归算法
	void inOrder1(void(*visit)(BinTreeNode<T>* p)); 
		//利用栈的中序遍历非递归算法
	void postOrder1(void (*visit)(BinTreeNode<T>* p));
		//利用栈的后序遍历非递归算法

	int Insert(const T & item);							//插入新元素
	BinTreeNode<T>* Find(T & item)const;				//搜索

	
	friend istream& operator >> (istream& in, BinaryTree<T>& Tree)//重载操作：输入
	{
	//重载操作：输入并建立一颗二叉树Tree，in是输入流对象
		Tree.CreateBinTree(in, Tree.root);			//建立二叉树
		return in;
	};
	friend ostream& operator << (ostream& out, BinaryTree<T>& Tree)//重载操作：输出
	{
		//重载操作：输出一颗二叉树Tree，out是输出流对象
		out << "二叉树的前序遍历\n";		//提示：搜索二叉树
		Tree.Travers(Tree.root, out);		//从根开始输出
		out << endl;
		out << "二叉树的中序遍历\n";		//提示：搜索二叉树
		Tree.Travers1(Tree.root, out);		//从根开始输出
		out << endl;
		out << "二叉树的后序遍历\n";		//提示：搜索二叉树
		Tree.Travers2(Tree.root, out);		//从根开始输出
		out << endl;
		return out;
	};

protected:
	BinTreeNode<T>* root;								//二叉树的根指针
	T RefValue;											//数据输入停止标志
	 void CreateBinTree(istream & in, BinTreeNode<T> * &subTree);//从文件中读入建立树
	bool Insert(BinTreeNode<T> * &subTree, const T & x);	
		//插入 在结点subTree插入值为value的新子女，失败返回False*&为传递引用，这样可以改变指针http://www.cnblogs.com/djtycm/p/7192858.html
	bool Find(BinTreeNode<T> * subTree, const T & x)const;		//查找
	BinTreeNode<T>* Copy(BinTreeNode<T> * orignode);			//复制
	void destroy(BinTreeNode<T> * subTree);          			//删除
	int Height(BinTreeNode<T> * subTree);						//返回树的高度
	int Size(BinTreeNode<T> * subTree);					//返回结点数
	int count2(BinTreeNode<T>* subTree);					//返回度为2结点数
	int leafnum(BinTreeNode<T>* subTree);					//返回叶结点数
	BinTreeNode<T>* Parent(BinTreeNode<T> * subTree,
		BinTreeNode<T> * current);				//返回父结点
	void Travers(BinTreeNode<T> * subTree, ostream & out);       //前序遍历输出
	void Travers1(BinTreeNode<T>* subTree, ostream& out);       //中序遍历输出
	void Travers2(BinTreeNode<T>* subTree, ostream& out);       //后序遍历输出
	
	void preOrder(BinTreeNode<T> & subTree,						//前序遍历
		void(*visit)(BinTreeNode<T> * p));
	void inOrder(BinTreeNode<T> & subTree,						//中序遍历
		void(*visit)(BinTreeNode<T> * p));
	void postOrder(BinTreeNode<T> & Tree,						//后序遍历
		void(*visit)(BinTreeNode<T> * p));
};

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> * subTree) {
	//私有函数，若指针subTree不为空，则删除根为subTree的子树
	if (subTree != NULL) {
		destroy(subTree->leftChild);					//递归删除subTree的左子树
		destroy(subTree->rightChild);					//递归删除subTree的右子树
		delete subTree;									//递归subTree
	}
};




template<class T>
inline void BinaryTree<T>::preOrder(void(*visit)(BinTreeNode<T>* p))
{
		preOrder(root, visit);
	
}

template<class T>
inline void BinaryTree<T>::inOrder(void(*visit)(BinTreeNode<T>* p))
{
	
		inOrder(root, visit);
	
}

template<class T>
inline void BinaryTree<T>::postOrder(void(*visit)(BinTreeNode<T>* p))
{
	
		postOrder(root, visit);
	
}

template<class T>
inline void BinaryTree<T>::levelOrder(void(*visit)(BinTreeNode<T>* p))
{//利用队列实现层次序遍历的算法
	LinkQueue<BinTreeNode<T>*>Q;
	BinTreeNode<T>* p = root;
	Q.EnQueue(p);
	while (!Q.IsEmpty()) {		//队列不空
		Q.EnQueue(p); visit(p);		//退出一个节点，访问
		if (p->leftChild != NULL)Q.EnQueue(p->leftChild);//左子女进队
		if (p->rightChild != NULL)Q.EnQueue(p->rightChild);//右子女进队
	}
}

template<class T>
inline void BinaryTree<T>::preOrder1(void(*visit)(BinTreeNode<T>* p))
{
	//二叉树先序遍历的非递归算法
		SeqStack<BinTreeNode<T>*> S;
		BinTreeNode<T>* p = root;		//初始化
		S.Push(NULL);
		while (p != NULL) {
			visit(p);					//访问结点
			if (p->rightChild != NULL)S.Push(p->rightChild);//预留右子树指针在栈中
			if (p->leftChild != NULL)p = p->leftChild;//进左子树
			else S.Push(p);				//左子树为空
		}
	
}

template<class T>
inline void BinaryTree<T>::preOrder2(void(*visit)(BinTreeNode<T>* p))
{//另一种二叉树前序遍历的非递归算法
	SeqStack<BinTreeNode<T>*> S;
	BinTreeNode<T>* p;
	S.Push(root);
	while (!S.IsEmpty()) {
		S.Pop(p); visit(p);			//退栈，访问。出栈时，先左子树后右子树
		if (p->rightChild != NULL)S.Push(p->rightChild);//进栈时，先进右子树
		if (p->leftChild != NULL)S.Push(p->leftChild);//再进左子树
	}

}
template<class T>
inline void BinaryTree<T>::inOrder1(void(*visit)(BinTreeNode<T>* p))
{//
	SeqStack<BinTreeNode<T>*> S;
	BinTreeNode<T>* p = root;	//p是遍历指针，从根结点开始
	do {
		while (p != NULL) {//遍历指针未到最左下的结点，不空
			S.Push(p);	//该子树沿途结点进栈
			p = p->leftChild;	//遍历指针到左子女结点
		}
		if (!S.IsEmpty()) {		//栈不空时退栈
			S.Pop(p); visit(p);//退栈，访问根结点
			p = p->rightChild;//遍历指针进到右子女结点
		}
	} while (p != NULL || !S.IsEmpty());
}
template<class T>
inline void BinaryTree<T>::postOrder1(void(*visit)(BinTreeNode<T>* p))
{
	
}
;

template<class T>
inline BinTreeNode<T>* BinaryTree<T>::Find(T& item) const
{
	if (root == NULL) return NULL;	//	
	else {
		if(Find(root, item))     return root;

	}
	
}

template<class T>
inline void BinaryTree<T>::CreateBinTree(istream & in, BinTreeNode<T> * &subTree)
{//私有函数：以递归方式建立二叉树
	T item;
	if (!in.eof()) {				//未读完，读入并建立树
		in >> item;					//读入根结点的值
		if (item != RefValue) {
			subTree = new BinTreeNode<T>(item);			//建立根结点
			if (subTree == NULL)
			{
				cerr << "存储分配错！" << endl; exit(1);
			}
			CreateBinTree(in, subTree->leftChild);		//递归建立左子树
			CreateBinTree(in, subTree->rightChild);		//递归建立右子树
		}
		else  subTree = NULL;						//封闭指向空子树的指针
	}
}

template<class T>
inline bool BinaryTree<T>::Insert(BinTreeNode<T> * &subTree, const T & x)
{
	if (LeftChild(subTree) == NULL)	//若左子树为空，将值作为新结点插入,返回true
	{
		subTree->leftChild = new BinTreeNode<T>(x);
		return true;
	}
	else if (RightChild(subTree) == NULL)//若右子树为空，将值作为新结点插入,返回true
	{
		subTree->rightChild = new BinTreeNode<T>(x);
		return true;
	}
	else                                 //左右子树都不为空，返回false
		return false;
}
template<class T>
inline bool BinaryTree<T>::Find(BinTreeNode<T> * subTree, const T & x) const
{//私有函数：从结点subTree开始，搜索元素x所在的结点。
//若找到元素x所在的结点，则函数返回true，否则函数返回false
	if (subTree->data == NULL)	return false;//递归结束：空树
	else {
		if (subTree->data == x)			//递归结束：找到x
			return true;
		else {
			Find(subTree->leftChild, x);
			Find(subTree->rightChild, x);
		}
	}

}
;


template<class T>
inline BinTreeNode<T>* BinaryTree<T>::Copy(BinTreeNode<T> * orignode)
{//私有函数：这个函数返回一个指针，它给出一个以orignode为根的二叉树的副本
	if (orignode == NULL) return NULL;				//根为空，返回空指针
	BinTreeNode<T> * temp = new BinTreeNode<T>;		//创建根节点
	temp->data = orignode->data;					//传送数据
	temp->leftChild = Copy(orignode->leftChild);	//复制左子树
	temp->rightChild = Copy(orignode->rightChild);	//复制右子树
	return temp;									//返回根结点
};

template<class T>
inline int BinaryTree<T>::Height(BinTreeNode<T> * subTree)
{//私有函数，计算以*subTree为根的二叉树的高度或者深度
	if (subTree == NULL)return 0;				//递归结束：空树高度为0
	else {
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i < j) ? j + 1 : i + 1;
	}
};

template<class T>
inline int BinaryTree<T>::Size(BinTreeNode<T> * subTree)
{//私有函数，计算以*subTree为根的二叉树的结点个数
	if (subTree == NULL)return 0;				//递归结束：空节点个数为0
	else return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
}

template<class T>
inline int BinaryTree<T>::count2(BinTreeNode<T>* subTree)
{//私有函数，计算以*subTree为根的二叉树的度为2结点个数
	
	if (subTree == NULL)return 0;				//递归结束：空节点个数为0
	else {
		if ((LeftChild(subTree) != NULL) && (RightChild(subTree) != NULL))
			 return  1 + count2(subTree->leftChild) + count2(subTree->rightChild);
		else return count2(subTree->leftChild) + count2(subTree->rightChild);
	}


	

	
}

template<class T>
inline int BinaryTree<T>::leafnum(BinTreeNode<T>* subTree)
{
	//私有函数，计算以*subTree为根的二叉树的叶结点个数

	if (subTree == NULL)return 0;				//递归结束：空节点个数为0
	else {
		if ((LeftChild(subTree) == NULL) && (RightChild(subTree) == NULL))
			return  1 + leafnum(subTree->leftChild) + leafnum(subTree->rightChild);
		else return leafnum(subTree->leftChild) + leafnum(subTree->rightChild);
	}

	
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::
Parent(BinTreeNode<T> * subTree, BinTreeNode<T> * current) {
	//私有函数：从结点subTree开始，搜索结点current的父结点。
	//若找到结点current的父结点，则函数返回父结点地址，否则函数返回NULL
	if (subTree == NULL)return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current)
		return subTree;					//找到，返回父结点subTree
	BinTreeNode <T> * p;
	if ((p = Parent(subTree->leftChild, current)) != NULL)return p; //递归，在左子树中搜索
	else return Parent(subTree->rightChild, current);//递归，在右子树中搜索
};

template<class T>
inline void BinaryTree<T>::Travers(BinTreeNode<T> * subTree, ostream & out)
{//私有函数，搜索并输出根为subTree的二叉树
	if (subTree != NULL) {							//subTree为空则返回，
		out << subTree->data << ' ';			//否则输出subTree的数据值
		Travers(subTree->leftChild, out);		//递归搜索并输出subTree的左子树
		Travers(subTree->rightChild, out);	   //递归搜索并输出subTree的右子树
	}
}
template<class T>
inline void BinaryTree<T>::Travers1(BinTreeNode<T>* subTree, ostream& out)
{//私有函数，搜索并输出根为subTree的二叉树
	if (subTree != NULL) {							//subTree为空则返回，
		
		Travers1(subTree->leftChild, out);		//递归搜索并输出subTree的左子树
		out << subTree->data << ' ';			//输出subTree的数据值
		Travers1(subTree->rightChild, out);	   //递归搜索并输出subTree的右子树
	}
}
template<class T>
inline void BinaryTree<T>::Travers2(BinTreeNode<T>* subTree, ostream& out)
{//私有函数，搜索并输出根为subTree的二叉树
	if (subTree != NULL) {							//subTree为空则返回，

		Travers2(subTree->leftChild, out);		//递归搜索并输出subTree的左子树
		Travers2(subTree->rightChild, out);	   //递归搜索并输出subTree的右子树
		out << subTree->data << ' ';			//输出subTree的数据值
	}
	
}
;

template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T> & subTree, void(*visit)(BinTreeNode<T> * p))
{//递归函数：此算法按照前序次序遍历以subTree为根的二叉树
	if (subTree != NULL) {						//递归结束条件
		visit(subTree);							//访问根节点
		PreOrder(subTree->leftChild, visit); //前序遍历根的左子树
		PreOrder(subTree->rightChild, visit);//前序遍历根的右子树
	}
};

template<class T>
inline void BinaryTree<T>::inOrder(BinTreeNode<T> & subTree, void(*visit)(BinTreeNode<T> * p))
{//递归函数：此算法按照中序次序遍历以subTree为根的二叉树
	if (subTree != NULL) {					//递归结束条件

		InOrder(subTree->leftChild, visit);	//中序遍历根的左子树
		visit(subTree);						//访问根节点
		InOrder(subTree->rightChild, visit);//中序遍历根的右子树
	}
};

template<class T>
inline void BinaryTree<T>::postOrder(BinTreeNode<T> & subTree, void(*visit)(BinTreeNode<T> * p))
{//递归函数：此算法按照后序次序遍历以subTree为根的二叉树
	if (subTree != NULL) {					//递归结束条件

		PostOrder(subTree->leftChild, visit);//后序遍历根的左子树
		PostOrder(subTree->rightChild, visit);	//后序遍历根的右子树
		visit(subTree);						//访问根节点
	}
};






template<class T>
inline BinaryTree<T>::BinaryTree(BinaryTree<T> & s)
{//公共函数：复制构造函数
	root = Copy(s, root);
}
template<class T>
inline BinTreeNode<T>* BinaryTree<T>::CreateBinaryTree(T* VLR, T* LVR, int n)
{//利用前序序列和中序序列构造二叉树
//VLR是二叉树的前序序列，LVR是二叉树的中序序列，构造出的二叉树指针由函数返回
	if (n == 0) return NULL;
	int k = 0;
	while (VLR[0] != LVR[k])k++;	//在中序序列中寻找根
	BinTreeNode<T>* t = new BinTreeNode<T>(VLR[0]);
	t->leftChild = CreateBinaryTree(VLR + 1, LVR, k);
		//从前序VLR+1开始对中序的0~k-1左子树的k个元素递归建立左子树
	t->rightChild = CreateBinaryTree(VLR  +k+1, LVR+k+1,n- k-1);
	//从前序VLR+k+1开始对中序的k+1~n-1右子树的n-k-1个元素递归建立右子树
	
	return t;
}



