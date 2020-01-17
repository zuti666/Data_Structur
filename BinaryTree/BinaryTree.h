#include<iostream>
#include"SeqStack.h"		//ͷ�ļ���˳��ջ
#include"LinkQueue.h"		//ͷ�ļ�����ʽ����
using namespace std;
 int I = 0;
template<class T>
struct BinTreeNode {											//����������ඨ��
	T data;														//������
	BinTreeNode<T>* leftChild, * rightChild;					//����Ů������Ů����
	BinTreeNode() :leftChild(NULL), rightChild(NULL) { }		//�޲������캯��
	BinTreeNode(T x, BinTreeNode<T> * l = NULL, BinTreeNode<T>* r = NULL)//�в������캯����
			//���ඨ�����У��������ͨ���������͵ĳ�Ա������������ǰ�������T
		:data(x), leftChild(l), rightChild(r) { }
};

template<class T>												//�������ඨ��
class BinaryTree
{
public:
	BinaryTree() :root(NULL) { }								//�޲������캯��
	BinaryTree(T value) :RefValue(value), root(NULL) { }		//���캯������value��ʼ����������ֹͣ��־
	BinaryTree(BinaryTree<T>& s);								//���ƹ��캯��
	~BinaryTree() { destroy(root); }							//��������������destroy�����Զ���������ɾ��
	bool IsEmpty() { return (root == NULL) ? true : false; }	//�ж϶������Ƿ�Ϊ��
	BinTreeNode<T>* CreateBinaryTree(T* VLR, T* LVR, int n);	//����ǰ�����к��������й��������
	BinTreeNode<T>* Convert(const T* expression);	//�����������ʽ���������
	BinTreeNode<T>* Parent(BinTreeNode<T> * current)			//���ظ���㣬
	{						//������Ǹ��ڵ㣬����Parent�������ظ��ڵ�
		return (root == NULL || root == current) ? NULL : Parent(root, current);
	}
	BinTreeNode<T>* LeftChild(BinTreeNode<T> * current)			//��������Ů
	{
		return (current != NULL) ? current->leftChild : NULL;
	}
	BinTreeNode<T>* RightChild(BinTreeNode<T> * current)		//��������Ů
	{
		return (current != NULL) ? current->rightChild : NULL;
	}


	int Height() {  return Height(root); }			//�������߶ȣ�����Height����
	int Size() { return Size(root); }				//���ؽ����������Size����
	int count2() { return count2(root); }			//���ض�Ϊ2�Ľ����
	int leafnum() { return leafnum(root); }			//����Ҷ�����
	BinTreeNode<T>* getRoot()const { return root; }		//ȡ����rootΪ������Ա������������ĸ�


	void preOrder(void (*visit)(BinTreeNode<T>* p));  //ǰ�����������preOrder����
	
	void inOrder(void(*visit)(BinTreeNode<T>* p));	//������������ñ�����Ա�е�inOrder����
	
	void postOrder(void (*visit)(BinTreeNode<T>* p)); //�������
	
	void levelOrder(void(*visit)(BinTreeNode<T>* p));	
		//���ö���ʵ�ֲ�������
	void preOrder1(void(*visit)(BinTreeNode<T>* p));
		//��������������ķǵݹ��㷨
	void preOrder2(void(*visit)(BinTreeNode<T>* p));
		//��һ�ֶ�����ǰ������ķǵݹ��㷨
	void inOrder1(void(*visit)(BinTreeNode<T>* p)); 
		//����ջ����������ǵݹ��㷨
	void postOrder1(void (*visit)(BinTreeNode<T>* p));
		//����ջ�ĺ�������ǵݹ��㷨

	int Insert(const T & item);							//������Ԫ��
	BinTreeNode<T>* Find(T & item)const;				//����

	
	friend istream& operator >> (istream& in, BinaryTree<T>& Tree)//���ز���������
	{
	//���ز��������벢����һ�Ŷ�����Tree��in������������
		Tree.CreateBinTree(in, Tree.root);			//����������
		return in;
	};
	friend ostream& operator << (ostream& out, BinaryTree<T>& Tree)//���ز��������
	{
		//���ز��������һ�Ŷ�����Tree��out�����������
		out << "��������ǰ�����\n";		//��ʾ������������
		Tree.Travers(Tree.root, out);		//�Ӹ���ʼ���
		out << endl;
		out << "���������������\n";		//��ʾ������������
		Tree.Travers1(Tree.root, out);		//�Ӹ���ʼ���
		out << endl;
		out << "�������ĺ������\n";		//��ʾ������������
		Tree.Travers2(Tree.root, out);		//�Ӹ���ʼ���
		out << endl;
		return out;
	};

protected:
	BinTreeNode<T>* root;								//�������ĸ�ָ��
	T RefValue;											//��������ֹͣ��־
	 void CreateBinTree(istream & in, BinTreeNode<T> * &subTree);//���ļ��ж��뽨����
	bool Insert(BinTreeNode<T> * &subTree, const T & x);	
		//���� �ڽ��subTree����ֵΪvalue������Ů��ʧ�ܷ���False*&Ϊ�������ã��������Ըı�ָ��http://www.cnblogs.com/djtycm/p/7192858.html
	bool Find(BinTreeNode<T> * subTree, const T & x)const;		//����
	BinTreeNode<T>* Copy(BinTreeNode<T> * orignode);			//����
	void destroy(BinTreeNode<T> * subTree);          			//ɾ��
	int Height(BinTreeNode<T> * subTree);						//�������ĸ߶�
	int Size(BinTreeNode<T> * subTree);					//���ؽ����
	int count2(BinTreeNode<T>* subTree);					//���ض�Ϊ2�����
	int leafnum(BinTreeNode<T>* subTree);					//����Ҷ�����
	BinTreeNode<T>* Parent(BinTreeNode<T> * subTree,
		BinTreeNode<T> * current);				//���ظ����
	void Travers(BinTreeNode<T> * subTree, ostream & out);       //ǰ��������
	void Travers1(BinTreeNode<T>* subTree, ostream& out);       //����������
	void Travers2(BinTreeNode<T>* subTree, ostream& out);       //����������
	
	void preOrder(BinTreeNode<T> & subTree,						//ǰ�����
		void(*visit)(BinTreeNode<T> * p));
	void inOrder(BinTreeNode<T> & subTree,						//�������
		void(*visit)(BinTreeNode<T> * p));
	void postOrder(BinTreeNode<T> & Tree,						//�������
		void(*visit)(BinTreeNode<T> * p));
};

template <class T>
void BinaryTree<T>::destroy(BinTreeNode<T> * subTree) {
	//˽�к�������ָ��subTree��Ϊ�գ���ɾ����ΪsubTree������
	if (subTree != NULL) {
		destroy(subTree->leftChild);					//�ݹ�ɾ��subTree��������
		destroy(subTree->rightChild);					//�ݹ�ɾ��subTree��������
		delete subTree;									//�ݹ�subTree
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
{//���ö���ʵ�ֲ����������㷨
	LinkQueue<BinTreeNode<T>*>Q;
	BinTreeNode<T>* p = root;
	Q.EnQueue(p);
	while (!Q.IsEmpty()) {		//���в���
		Q.EnQueue(p); visit(p);		//�˳�һ���ڵ㣬����
		if (p->leftChild != NULL)Q.EnQueue(p->leftChild);//����Ů����
		if (p->rightChild != NULL)Q.EnQueue(p->rightChild);//����Ů����
	}
}

template<class T>
inline void BinaryTree<T>::preOrder1(void(*visit)(BinTreeNode<T>* p))
{
	//��������������ķǵݹ��㷨
		SeqStack<BinTreeNode<T>*> S;
		BinTreeNode<T>* p = root;		//��ʼ��
		S.Push(NULL);
		while (p != NULL) {
			visit(p);					//���ʽ��
			if (p->rightChild != NULL)S.Push(p->rightChild);//Ԥ��������ָ����ջ��
			if (p->leftChild != NULL)p = p->leftChild;//��������
			else S.Push(p);				//������Ϊ��
		}
	
}

template<class T>
inline void BinaryTree<T>::preOrder2(void(*visit)(BinTreeNode<T>* p))
{//��һ�ֶ�����ǰ������ķǵݹ��㷨
	SeqStack<BinTreeNode<T>*> S;
	BinTreeNode<T>* p;
	S.Push(root);
	while (!S.IsEmpty()) {
		S.Pop(p); visit(p);			//��ջ�����ʡ���ջʱ������������������
		if (p->rightChild != NULL)S.Push(p->rightChild);//��ջʱ���Ƚ�������
		if (p->leftChild != NULL)S.Push(p->leftChild);//�ٽ�������
	}

}
template<class T>
inline void BinaryTree<T>::inOrder1(void(*visit)(BinTreeNode<T>* p))
{//
	SeqStack<BinTreeNode<T>*> S;
	BinTreeNode<T>* p = root;	//p�Ǳ���ָ�룬�Ӹ���㿪ʼ
	do {
		while (p != NULL) {//����ָ��δ�������µĽ�㣬����
			S.Push(p);	//��������;����ջ
			p = p->leftChild;	//����ָ�뵽����Ů���
		}
		if (!S.IsEmpty()) {		//ջ����ʱ��ջ
			S.Pop(p); visit(p);//��ջ�����ʸ����
			p = p->rightChild;//����ָ���������Ů���
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
{//˽�к������Եݹ鷽ʽ����������
	T item;
	if (!in.eof()) {				//δ���꣬���벢������
		in >> item;					//���������ֵ
		if (item != RefValue) {
			subTree = new BinTreeNode<T>(item);			//���������
			if (subTree == NULL)
			{
				cerr << "�洢�����" << endl; exit(1);
			}
			CreateBinTree(in, subTree->leftChild);		//�ݹ齨��������
			CreateBinTree(in, subTree->rightChild);		//�ݹ齨��������
		}
		else  subTree = NULL;						//���ָ���������ָ��
	}
}

template<class T>
inline bool BinaryTree<T>::Insert(BinTreeNode<T> * &subTree, const T & x)
{
	if (LeftChild(subTree) == NULL)	//��������Ϊ�գ���ֵ��Ϊ�½�����,����true
	{
		subTree->leftChild = new BinTreeNode<T>(x);
		return true;
	}
	else if (RightChild(subTree) == NULL)//��������Ϊ�գ���ֵ��Ϊ�½�����,����true
	{
		subTree->rightChild = new BinTreeNode<T>(x);
		return true;
	}
	else                                 //������������Ϊ�գ�����false
		return false;
}
template<class T>
inline bool BinaryTree<T>::Find(BinTreeNode<T> * subTree, const T & x) const
{//˽�к������ӽ��subTree��ʼ������Ԫ��x���ڵĽ�㡣
//���ҵ�Ԫ��x���ڵĽ�㣬��������true������������false
	if (subTree->data == NULL)	return false;//�ݹ����������
	else {
		if (subTree->data == x)			//�ݹ�������ҵ�x
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
{//˽�к����������������һ��ָ�룬������һ����orignodeΪ���Ķ������ĸ���
	if (orignode == NULL) return NULL;				//��Ϊ�գ����ؿ�ָ��
	BinTreeNode<T> * temp = new BinTreeNode<T>;		//�������ڵ�
	temp->data = orignode->data;					//��������
	temp->leftChild = Copy(orignode->leftChild);	//����������
	temp->rightChild = Copy(orignode->rightChild);	//����������
	return temp;									//���ظ����
};

template<class T>
inline int BinaryTree<T>::Height(BinTreeNode<T> * subTree)
{//˽�к�����������*subTreeΪ���Ķ������ĸ߶Ȼ������
	if (subTree == NULL)return 0;				//�ݹ�����������߶�Ϊ0
	else {
		int i = Height(subTree->leftChild);
		int j = Height(subTree->rightChild);
		return (i < j) ? j + 1 : i + 1;
	}
};

template<class T>
inline int BinaryTree<T>::Size(BinTreeNode<T> * subTree)
{//˽�к�����������*subTreeΪ���Ķ������Ľ�����
	if (subTree == NULL)return 0;				//�ݹ�������սڵ����Ϊ0
	else return 1 + Size(subTree->leftChild) + Size(subTree->rightChild);
}

template<class T>
inline int BinaryTree<T>::count2(BinTreeNode<T>* subTree)
{//˽�к�����������*subTreeΪ���Ķ������Ķ�Ϊ2������
	
	if (subTree == NULL)return 0;				//�ݹ�������սڵ����Ϊ0
	else {
		if ((LeftChild(subTree) != NULL) && (RightChild(subTree) != NULL))
			 return  1 + count2(subTree->leftChild) + count2(subTree->rightChild);
		else return count2(subTree->leftChild) + count2(subTree->rightChild);
	}


	

	
}

template<class T>
inline int BinaryTree<T>::leafnum(BinTreeNode<T>* subTree)
{
	//˽�к�����������*subTreeΪ���Ķ�������Ҷ������

	if (subTree == NULL)return 0;				//�ݹ�������սڵ����Ϊ0
	else {
		if ((LeftChild(subTree) == NULL) && (RightChild(subTree) == NULL))
			return  1 + leafnum(subTree->leftChild) + leafnum(subTree->rightChild);
		else return leafnum(subTree->leftChild) + leafnum(subTree->rightChild);
	}

	
}

template <class T>
BinTreeNode<T>* BinaryTree<T>::
Parent(BinTreeNode<T> * subTree, BinTreeNode<T> * current) {
	//˽�к������ӽ��subTree��ʼ���������current�ĸ���㡣
	//���ҵ����current�ĸ���㣬�������ظ�����ַ������������NULL
	if (subTree == NULL)return NULL;
	if (subTree->leftChild == current || subTree->rightChild == current)
		return subTree;					//�ҵ������ظ����subTree
	BinTreeNode <T> * p;
	if ((p = Parent(subTree->leftChild, current)) != NULL)return p; //�ݹ飬��������������
	else return Parent(subTree->rightChild, current);//�ݹ飬��������������
};

template<class T>
inline void BinaryTree<T>::Travers(BinTreeNode<T> * subTree, ostream & out)
{//˽�к����������������ΪsubTree�Ķ�����
	if (subTree != NULL) {							//subTreeΪ���򷵻أ�
		out << subTree->data << ' ';			//�������subTree������ֵ
		Travers(subTree->leftChild, out);		//�ݹ����������subTree��������
		Travers(subTree->rightChild, out);	   //�ݹ����������subTree��������
	}
}
template<class T>
inline void BinaryTree<T>::Travers1(BinTreeNode<T>* subTree, ostream& out)
{//˽�к����������������ΪsubTree�Ķ�����
	if (subTree != NULL) {							//subTreeΪ���򷵻أ�
		
		Travers1(subTree->leftChild, out);		//�ݹ����������subTree��������
		out << subTree->data << ' ';			//���subTree������ֵ
		Travers1(subTree->rightChild, out);	   //�ݹ����������subTree��������
	}
}
template<class T>
inline void BinaryTree<T>::Travers2(BinTreeNode<T>* subTree, ostream& out)
{//˽�к����������������ΪsubTree�Ķ�����
	if (subTree != NULL) {							//subTreeΪ���򷵻أ�

		Travers2(subTree->leftChild, out);		//�ݹ����������subTree��������
		Travers2(subTree->rightChild, out);	   //�ݹ����������subTree��������
		out << subTree->data << ' ';			//���subTree������ֵ
	}
	
}
;

template<class T>
inline void BinaryTree<T>::preOrder(BinTreeNode<T> & subTree, void(*visit)(BinTreeNode<T> * p))
{//�ݹ麯�������㷨����ǰ����������subTreeΪ���Ķ�����
	if (subTree != NULL) {						//�ݹ��������
		visit(subTree);							//���ʸ��ڵ�
		PreOrder(subTree->leftChild, visit); //ǰ���������������
		PreOrder(subTree->rightChild, visit);//ǰ���������������
	}
};

template<class T>
inline void BinaryTree<T>::inOrder(BinTreeNode<T> & subTree, void(*visit)(BinTreeNode<T> * p))
{//�ݹ麯�������㷨����������������subTreeΪ���Ķ�����
	if (subTree != NULL) {					//�ݹ��������

		InOrder(subTree->leftChild, visit);	//�����������������
		visit(subTree);						//���ʸ��ڵ�
		InOrder(subTree->rightChild, visit);//�����������������
	}
};

template<class T>
inline void BinaryTree<T>::postOrder(BinTreeNode<T> & subTree, void(*visit)(BinTreeNode<T> * p))
{//�ݹ麯�������㷨���պ�����������subTreeΪ���Ķ�����
	if (subTree != NULL) {					//�ݹ��������

		PostOrder(subTree->leftChild, visit);//�����������������
		PostOrder(subTree->rightChild, visit);	//�����������������
		visit(subTree);						//���ʸ��ڵ�
	}
};






template<class T>
inline BinaryTree<T>::BinaryTree(BinaryTree<T> & s)
{//�������������ƹ��캯��
	root = Copy(s, root);
}
template<class T>
inline BinTreeNode<T>* BinaryTree<T>::CreateBinaryTree(T* VLR, T* LVR, int n)
{//����ǰ�����к��������й��������
//VLR�Ƕ�������ǰ�����У�LVR�Ƕ��������������У�������Ķ�����ָ���ɺ�������
	if (n == 0) return NULL;
	int k = 0;
	while (VLR[0] != LVR[k])k++;	//������������Ѱ�Ҹ�
	BinTreeNode<T>* t = new BinTreeNode<T>(VLR[0]);
	t->leftChild = CreateBinaryTree(VLR + 1, LVR, k);
		//��ǰ��VLR+1��ʼ�������0~k-1��������k��Ԫ�صݹ齨��������
	t->rightChild = CreateBinaryTree(VLR  +k+1, LVR+k+1,n- k-1);
	//��ǰ��VLR+k+1��ʼ�������k+1~n-1��������n-k-1��Ԫ�صݹ齨��������
	
	return t;
}



