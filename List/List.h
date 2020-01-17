#include<iostream>
#include<stdlib.h>
using namespace std;
template<class T>
struct LinkNode {							//��������Ķ���
	T data;									//������
	LinkNode<T>* link;						//��ָ����
	LinkNode(LinkNode<T>* ptr = NULL) { link = ptr; }
										    //����ʼ��ָ���Ա�Ĺ��캯��
	LinkNode(const T& item,LinkNode<T> *ptr=NULL)
	{									    //��ʼ��������ָ���Ա�Ĺ��캯��
		data = item;
		link = ptr;
	}


};

template  <class T>
class List  {			//�������ඨ��
public:
	List() { first = new LinkNode<T>; }		//���캯��
	List(const T& x) { first = new LinkNode<T>(x); }//���캯��
	List(List<T>& L);						//���ƹ��캯��
	~List() { makeEmpty(); }				//��������
	void makeEmpty();						//�������ÿ�
	int Length()const;						//��������ĳ���
	LinkNode<T>* getHead()const { return first; }//���ظ���ͷ����ַ
	LinkNode<T>* Search(T x);				//����������x��Ԫ��
	LinkNode<T>* Locate(int i);				//������i��Ԫ�صĵ�ַ
	bool getData(int i, T& x);			//ȡ����i��Ԫ�ص�ֵ
	void setData(int i, T& x);				//��x�޸ĵ�i��Ԫ�ص�ֵ
	bool Insert(int i, T& x);				//�ڵ�i��Ԫ�غ����x
	bool Remove(int i, T& x);				//ɾ����i��Ԫ�أ�x���ظ�Ԫ�ص�ֵ
	bool IsEmpty()const						//�жϱ��Ƿ�Ϊ�գ��շ���true
	{
		return first->link == NULL ? true : false;
	};
	bool IsFull()const { return false; };	//�жϱ��Ƿ�Ϊ������������false
	void Sort();							//����
	void input();							//����
	void inputFront(T endTag);				//ǰ�巨����������
	void inputRear(T endTag);				//��巨��������
	void output();							//���
	List<T>& operator=(List<T>& L);			//���غ���������
protected:
	LinkNode<T>* first;						//�����ͷָ��
};

template<class T>
inline List<T>::List(List<T>& L)
{//���ƹ��캯��
	T value;
	LinkNode<T>* srcptr = L.getHead();		//�����Ʊ�ı�����ͷ����ַ
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {		//�����㸴��
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;

	}
};
template<class T>
inline void List<T>::makeEmpty()
{//��������Ϊ�ձ�
	LinkNode<T>* q;
	while (first->link != NULL) {	//��������ʱ��ɾȥ�������н��
		q = first->link;
		first->link = q->link;		//���汻ɾ��㣬������ժ�¸ý��
		delete q;					//ɾ����������һ����ͷ��㣩
	}
};
template<class T>
inline int List<T>::Length() const
{//���������ͷ���ĵ�����ĳ���
	LinkNode<T>* p = first; int count = 0;
	while (p != NULL)				//ѭ��ɨ������Ѱ����β
	{
		p = p->link;
		count++;
	}
	return count;
};
template<class T>
inline LinkNode<T>* List<T>::Search(T x)
{//�ڱ�������������x�Ľ�㣬
//�����ɹ�ʱ���ظý���ַ�����򷵻�NULLֵ
	LinkNode<T>* current = first->link;
	while (current != NULL)				//ѭ����������Ѱ��x���
		if (current->data == x)break;
		else current = current->link;
	return current;
};
template<class T>
inline LinkNode<T>*  List<T>::Locate(int i)
{//��λ���������ر��е�i��Ԫ�صĵ�ַ����i<0����i�������н�����������NULL
	if (i < 0)return NULL;				//i������
	LinkNode<T>* current = first; int k = 0;
	while (current != NULL && k < i)	//ѭ����������Ѱ�ҵ�i�����
	{
		current = current->link; k++;
	}
	return current;						//���ص�i������ַ��������NULL����ʾIֵ̫��
};
template<class T>
inline bool List<T>::getData(int i, T& x) 
{//ȡ�������е�i��Ԫ�ص�ֵ
	if (i <= 0) return false;			//iֵ̫С
	LinkNode<T> * current = Locate(i);
	if (current == NULL)return false;	//iֵ̫��
	else {
		x = current->data;
		return true;
	}

};
template<class T>
inline void List<T>::setData(int i, T& x)
{//�������е�i��Ԫ�ظ�ֵx
	if (i <= 0)return;					//iֵ̫С
	LinkNode<T> * current = Locate(i);
	if (current == NULL)return;
	else current->data = x;				//iֵ̫��
};
template<class T>
inline bool List<T>::Insert(int i, T& x)
{//����Ԫ��x���������е�i�����֮��
	LinkNode<T>* current = Locate(i);
	if (current == NULL)return false;	//���벻�ɹ�
	LinkNode<T>* newNode = new LinkNode<T>(x);
	if (newNode == NULL) { cerr << "�洢����ʧ��" << endl; exit(1); }
	newNode->link = current->link;		//������current֮��
	current->link = newNode;
	return true;						//����ɹ�
}
template<class T>
inline bool List<T>::Remove(int i, T& x)
{//�������еĵ�i��Ԫ��ɾȥ��ͨ�������Ͳ���x���ظ�Ԫ�ص�ֵ��
	LinkNode<T>* current = Locate(i - 1);
	if (current == NULL || current->link == NULL)return false;
	//ɾ�����ɹ�
	LinkNode<T> * del = current->link;	//��������������ɾ�������ժ��
	current->link = del->link;
	x = del->data; delete del;			//ȡ����ɾ���е�����ֵ
	return true;
};
template<class T>
inline void List<T>::Sort()
{//�������������ð������,��С����˳��
	LinkNode<T>* p=NULL,*q;
	T temp;
	bool isChange = true;
	if (first == NULL || first->link == NULL)return;
	while (p!=first->link&&isChange)
	{
		q = first;
		isChange = false;//��־��һ��û��Ԫ�ط�����������ʾ�Ѿ�����
		for (; q->link!= p && q->link!=NULL; q = q->link)
		{
			
			if (q->data > q->link->data)    /*���ڽڵ�Ƚϣ����ݽ���*/
			{
				temp = q->data;
				q->data = q->link->data;
				q->link->data = temp;
				cout << "����" <<q->data<<"��"<<q->link->data<<endl;
			}
			p = q;
		}
	
	}
};
template<class T>
inline void List<T>::input()
{//����������뺯�����������е��������ݰ����߼�˳���������Ļ��
	int geshu;
	cout << "��ʼ������������������н�������" << endl;
	cin >> geshu;
	int i = 0; T x;
	LinkNode<T>* current = first = new LinkNode<T>;
	while (i<geshu) {
		i++;
		cout << "�������" << i << "��Ԫ�أ�";
		cin >> x;
		current->link = new LinkNode<T>(x);
		current = current->link;
	}
};
template <class T>
inline void List<T>::inputFront(T endTag) {
//endTag��Լ�����������н����ı�־��
//���������������������endTag������0����
//��������������ַ���endTag�������ַ����в�����ֵ��ַ�����"\0"
	LinkNode<T>* newNode;  T val;
	makeEmpty();
	cin >> val;
	while (val != endTag) {
		newNode = new LinkNode<T>(val);		//�����½��
		if (newNode == NULL) { cerr << "�洢�������" << endl; exit(1); }
		newNode->link = first->link;
		first->link= newNode;
		cin >> val;							//���뵽��ǰ��
	}
};
template <class T>
inline void List<T>::inputRear(T endTag) {
	//endTag��Լ�����������н����ı�־��
	//���������������������endTag������0����
	//��������������ַ���endTag�������ַ����в�����ֵ��ַ�����"\0"
	LinkNode<T>* newNode,*last;  T val;
	makeEmpty();
	cin >> val; last = first;				//βָ��last����ָ������������һ�����
	while (val != endTag) {
		newNode = new LinkNode<T>(val);		//�����½��
		if (newNode == NULL) { cerr << "�洢�������" << endl; exit(1); }
		last->link = newNode;
		last = newNode;
		cin >> val;							//���뵽��ǰ��
	}
	last->link = NULL;						//����β���˾����ʡ��
};



template<class T>
inline void List<T>::output()
{//�����������������������е��������ݰ����߼�˳���������Ļ��
	LinkNode<T>* current = first->link;
	while (current != NULL) {
		cout << current->data << endl;
		current = current->link;
	}
};

template<class T>
inline List<T>& List<T>::operator=(List<T>& L)
{//���غ�������ֵ����������A=B������A�ǵ��ô˲�����List����
 //B����������е������Ͳ���L��ϵ�ʵ��
	T value;
	LinkNode<T>* srcptr = L.getHead();		//�����Ʊ��еĸ���ͷ����ַ
	LinkNode<T>* destptr = first = new LinkNode<T>;
	while (srcptr->link != NULL) {			//�����㸴��
		value = srcptr->link->data;
		destptr->link = new LinkNode<T>(value);
		destptr = destptr->link;
		srcptr = srcptr->link;
	}
	destptr->link = NULL;
	return* this;							//���ز��������ַ
		
};
