#include<iostream>
using namespace std;

template<class T>
struct ThreadNode		//�����������Ľ����
{
	int ltag, rtag;		//������־
	ThreadNode<T>* leafChild, * rightChild;//����������ָ��
	T data;				//����а���������
	ThreadNode(const T item):data(item),leafChild(NULL),
		rightChild(NULL),ltag(0),rtag(0){}  //���캯��

};

template <class T>
class ThreadTree {		//��������������
protected:
	ThreadNode<T>* root;	//���ĸ�ָ��
	void createInThread(ThreadNode<T>* current, ThreadNode<T>*& pre);
	//���������������������
	ThreadNode<T>* parent(ThreadNode<T>* t);//Ѱ�ҽ��t�ĸ����
public:
	ThreadTree():root(NULL){ }	//���캯�����������
	void createInThread();		//������������������
	ThreadNode<T>* First(ThreadNode<T>* currrent);
	//Ѱ�������µ�һ���ڵ�
	ThreadNode<T>* Next(ThreadNode<T>* currrent);
	//Ѱ�ҽ���������µĺ�̽ڵ�
	ThreadNode<T>* Last(ThreadNode<T>* currrent);
	//Ѱ�����������һ���ڵ�
	ThreadNode<T>* Prior(ThreadNode<T>* currrent);
	//Ѱ�ҽ���������µ�ǰ���ڵ�
	void Inorder(void(*visit)(ThreadNode<T>* p));//�������
	void Preorder(void(*visit)(ThreadNode<T>* p));//ǰ�����
	void Postorder(void(*visit)(ThreadNode<T>* p));//�������
	void InsertRight(ThreadNode<T>* s, ThreadNode<T>* r);//��Ϊ����Ů����
	void InsertLeaf(ThreadNode<T>* s, ThreadNode<T>* r);//��Ϊ����Ů����


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
{//�������������������󸸽��
	ThreadNode<T>* p;
	if (t == root) return NULL;		//������޸����
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
{//����������*currentΪ���������������������������µĵ�һ�����
	ThreadNode<T>* p = current;
	while (p->ltag == 0)p = p->leafChild;//�����½�㣨��һ����Ҷ�ڵ㣩
	return p;
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::Next(ThreadNode<T>* currrent)
{//�������������������������н��current�������µĺ�̽��
	ThreadNode<T>* p = currrent->rightChild;
	if (currrent->rtag == 0)return First(p);//���������²��������µ�һ�����
	else return p;//rtag==1,���غ�̽��
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::Last(ThreadNode<T>* currrent)
{//����������*currentΪ���������������������������µ����һ�����
	ThreadNode<T>* p = current;
	while (p->rtag == 0)p = p->rightChild;//�����½�㣨��һ����Ҷ�ڵ㣩
	return p;
}

template<class T>
inline ThreadNode<T>* ThreadTree<T>::Prior(ThreadNode<T>* currrent)
{////�������������������������н��current�������µ�ǰ�����
	ThreadNode<T>* p = currrent->leafChild;
	if (currrent->ltag == 0)return Last(p);//�������������������һ�����
	else return p;//ltag==1��ֱ�ӷ�����ǰ�����
}

template<class T>
inline void ThreadTree<T>::Inorder(void(*visit)(ThreadNode<T>* p))
{
	ThreadNode<T>* p;
	for (p = First(root); p != NULL; p = Next(p)) visit(p);
		//������First()�ҵ������������������µĵ�һ����㣬������Ϊ��ǰ���
}		//Ȼ���������̽�������Next()�����������������
		//ֱ�������������һ�����

template<class T>
inline void ThreadTree<T>::Preorder(void(*visit)(ThreadNode<T>* p))
{//������������������ʵ��ǰ�����
	ThreadNode<T>* p = root;
	while (p != NULL) {
		visit(p);			//���ʸ����
		if (p->ltag == 0)p = p->leafChild;//������Ů����Ϊ���
		else if (p->rtag == 0)p = p->rightChild;//����������Ů����Ϊ���
		else {
			while (p != NULL && p->rtag == 1)//�غ���������
				p = p->rightChild;//ֱ��������Ů�Ľ��
			if (p != NULL)p = p->rightChild;//����Ů��Ϊ���
		}
	}
}

template<class T>
inline void ThreadTree<T>::Postorder(void(*visit)(ThreadNode<T>* p))
{//���������������ĺ�������㷨
	ThreadNode<T>* t = root;
	while (t->ltag == 0 || t->rtag == 0)	//Ѱ�Һ���ĵ�һ�����
		if (t->ltag == 0)t = t->leafChild;
		else if (t->rtag == 0)t = t->rightChild;
	visit(t);	//���ʵ�һ�����
	ThreadNode<T>* p;
	while((p=parent(t))!=NULL){
		if(p->rightChild == t || p->rtag == 1)//*t��*p�ĺ�����
		t = p;
		else {								//����
			t = p->rightChild;				//t�Ƶ�*p��������
			while (t->ltag == 0 || t->rtag == 0)
				if (t->ltag == 0)t = t->leafChild;
				else if (t->rtag == 0)t = t->rightChild;
		}
		visit(t);
}
}

template<class T>
inline void ThreadTree<T>::InsertRight(ThreadNode<T>* s, ThreadNode<T>* r)
{//���½��*r����*s������Ů����
	r->rightChild = s->rightChild;//s������Ůָ�������������r
	r->rtag = s->rtag;//���������־һͬ����
	r->leafChild = s; r->ltag = 1;//r��leftChild��Ϊǰ������
	s->rightChild = r; s->rtag = 0;//r��Ϊs������Ů
	if (r->rtag == 0) {//sԭ��������Ů
		ThreadNode<T>* temp;
		temp = First(r->rightChild);//��sԭ�����������������һ�����
		temp->leafChild = r;//����ָ��r��ǰ������
	}
}

template<class T>
inline void ThreadTree<T>::InsertLeaf(ThreadNode<T>* s, ThreadNode<T>* r)
{


}
