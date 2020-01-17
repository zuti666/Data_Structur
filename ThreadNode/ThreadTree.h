#include<iostream>
using namespace std;

template<class T>
struct ThreadNode		//线索二叉树的结点类
{
	int ltag, rtag;		//线索标志
	ThreadNode<T>* leafChild, * rightChild;//线索或左右指针
	T data;				//结点中包含的数据
	ThreadNode(const T item):data(item),leafChild(NULL),
		rightChild(NULL),ltag(0),rtag(0){}  //构造函数

};

template <class T>
class ThreadTree {		//线索化二叉树类
protected:
	ThreadNode<T>* root;	//树的根指针
	void createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre);
	//中序遍历建立线索二叉树
	ThreadNode<T>* parent(ThreadNode<T>* t);//寻找结点t的父结点
public:
	ThreadTree():root(NULL){ }	//构造函数：构造空树
	void createInThread();		//建立中序线索二叉树
	ThreadNode<T>* First(ThreadNode<T>* currrent);
	//寻找中序下第一个节点
	ThreadNode<T>* Next(ThreadNode<T>* currrent);
	//寻找结点在中序下的后继节点
	ThreadNode<T>* Last(ThreadNode<T>* currrent);
	//寻找中序下最后一个节点
	ThreadNode<T>* Prior(ThreadNode<T>* currrent);
	//寻找结点在中序下的前驱节点
	void Inorder(void(*visit)(ThreadNode<T>* p));//中序遍历
	void Preorder(void(*visit)(ThreadNode<T>* p));//前序遍历
	void Postorder(void(*visit)(ThreadNode<T>* p));//后序遍历
	void InsertRight(ThreadNode<T>* s, ThreadNode<T>* r);//作为右子女插入
	void InsertLeaf(ThreadNode<T>* s, ThreadNode<T>* r);//作为左子女插入


template<class T>
inline void ThreadTree<T>::createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre)
{//
	if (current == NULL) return;
	createInThread(current->leafChild, pre);
	if (current->leafChild == NULL)
	{
		current->leafChild = pre;
		current->ltag = 1;
	}
	if (pre != NULL&&pre->rightChild==NULL)
	{
		pre->rightChild = current;
		pre->rtag = 1;
	}
	pre = current;
	createInThread(current->rightChild, pre);

}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::parent(ThreadNode<T>* t)
{//在中序线索二叉树中求父结点
	ThreadNode<T>* p;
	if (t == root) return NULL;		//根结点无父结点
	for (p = t; p->ltag == 0; p = p->leafChild);
	if (p->leafChild != NULL)
		for (p = p->leafChild; p != NULL && p->leafChild != t && p->rightChild != t;
			p = p->rightChild);
	if (p == NULL || p->leafChild == NULL) {
		for (p = t; p->rtag == 0; p = p->rightChild);
		for (p = p->rightChild; p != NULL && p->leafChild != t && p->rightChild != t;
			p = p->leafChild);
	}
	return p;
}

template<class T>
inline void ThreadTree<T>::createInThread()
{
	ThreadNode<T>* pre = NULL;
	if (root != NULL) {
		createInThread(root, pre);
		pre->rightChild = NULL;
		pre->rtag = 1;
	}
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::First(ThreadNode<T>* currrent)
{//函数返回以*current为根的中序线索二叉树中序序列下的第一个结点
	ThreadNode<T>* p = current;
	while (p->ltag == 0)p = p->leafChild;//最左下结点（不一定是叶节点）
	return p;
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* currrent)
{//函数返回在中序线索二叉树中结点current在中序下的后继结点
	ThreadNode<T>* p = currrent->rightChild;
	if (currrent->rtag == 0)return First(p);//在右子树下查找中序下第一个结点
	else return p;//rtag==1,返回后继结点
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T>* currrent)
{//函数返回以*current为根的中序线索二叉树中序序列下的最后一个结点
	ThreadNode<T>* p = current;
	while (p->rtag == 0)p = p->rightChild;//最右下结点（不一定是叶节点）
	return p;
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* currrent)
{////函数返回在中序线索二叉树中结点current在中序下的前驱结点
	ThreadNode<T>* p = currrent->leafChild;
	if (currrent->ltag == 0)return Last(p);//在左子树中找中序最后一个结点
	else return p;//ltag==1，直接返回其前驱结点
}

template<class T>
inline void ThreadTree<T>::Inorder(void(*visit)(ThreadNode<T>* p))
{
	ThreadNode<T>* p;
	for (p = First(root); p != NULL; p = Next(p)) visit(p);
		//先利用First()找到二叉树在中序序列下的第一个结点，把他作为当前结点
}		//然后利用求后继结点的运算Next()按中序序列逐个访问
		//直到二叉树的最后一个结点

template<class T>
inline void ThreadTree<T>::Preorder(void(*visit)(ThreadNode<T>* p))
{//在中序线索二叉树上实现前序遍历
	ThreadNode<T>* p = root;
	while (p != NULL) {
		visit(p);			//访问根结点
		if (p->ltag == 0)p = p->leafChild;//有左子女，即为后继
		else if (p->rtag == 0)p = p->rightChild;//否则有右子女，即为后继
		else {
			while (p != NULL && p->rtag == 1)//沿后继线索检测
				p = p->rightChild;//直到有右子女的结点
			if (p != NULL)p = p->rightChild;//右子女即为后继
		}
	}
}

template<class T>
inline void ThreadTree<T>::Postorder(void(*visit)(ThreadNode<T>* p))
{//中序线索二叉树的后序遍历算法
	ThreadNode<T>* t = root;
	while (t->ltag == 0 || t->rtag == 0)	//寻找后序的第一个结点
		if (t->ltag == 0)t = t->leafChild;
		else if (t->rtag == 0)t = t->rightChild;
	visit(t);	//访问第一个结点
	ThreadNode<T>* p;
	while((p=parent(t))!=NULL){
		if(p->rightChild == t || p->rtag == 1)//*t是*p的后序后继
		t = p;
		else {								//否则
			t = p->rightChild;				//t移到*p的右子树
			while (t->ltag == 0 || t->rtag == 0)
				if (t->ltag == 0)t = t->leafChild;
				else if (t->rtag == 0)t = t->rightChild;
		}
		visit(t);
}
}

template<class T>
inline void ThreadTree<T>::InsertRight(ThreadNode<T>* s, ThreadNode<T>* r)
{//将新结点*r当做*s的右子女插入
	r->rightChild = s->rightChild;//s的右子女指针或后继线索传给r
	r->rtag = s->rtag;//后继线索标志一同传送
	r->leafChild = s; r->ltag = 1;//r的leftChild成为前驱线索
	s->rightChild = r; s->rtag = 0;//r成为s的右子女
	if (r->rtag == 0) {//s原来有右子女
		ThreadNode<T>* temp;
		temp = First(r->rightChild);//在s原来右子树中找中序第一个结点
		temp->leafChild = r;//建立指向r的前驱线索
	}
}

template<class T>
inline void ThreadTree<T>::InsertLeaf(ThreadNode<T>* s, ThreadNode<T>* r)
{


}
