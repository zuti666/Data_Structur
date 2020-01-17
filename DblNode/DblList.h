#include<iostream>
#include<cstdlib>
using namespace std;

template<class T>
struct DblNode						//�������ඨ��
{
	T data;							//����������
	DblNode<T>* lLink, * rLink;		//����ǰ��������������̣�������
	DblNode(DblNode<T> *left=NULL,DblNode<T>*right=NULL)
		:lLink(left),rLink(right){} //���캯��
	DblNode(T value, DblNode<T>* left = NULL, DblNode<T>* right = NULL)
		:data(value),lLink(left), rLink(right) {}//���캯��
};

template<class T>
class DblList {						//�����ඨ��
public:
	DblList(T uniqueVal);			//���캯������������ͷ���
	~DblList();						//�����������ͷ����ô洢
	int Length()const;				//����˫����ĳ���
	bool IsEmpty() { return first->rlink == first; }//�жϱ��Ƿ�Ϊ��
	DblNode<T>* getHead()const { return first; }	//ȡ����ͷ���λ��
	void setHead(DblNode<T>* ptr) { first = ptr; }	//���ø���ͷ����ַ
	DblNode<T>* Search(const T& x);//�������غ�̷���Ѱ�ҵ��ڸ���ֵx�Ľ��
	DblNode<T>* Locate(int i, int d);//������λ���Ϊi�Ľ�㡣d=0��ǰ������
	bool Insert(int i, const T& x, int d);//��i���������һ��������ֵx���½�㡣d=0��ǰ������
	bool Remove(int i, T& x, int d);//ɾ����i����㣬x������ֵ��d=0��ǰ������
	int Swap(T x);	//���ҵ�һ��Ԫ��Ϊx�Ľ�㣬������ǰ����㽻��
private:
	DblNode<T>* first;
};

template<class T>
inline DblList<T>::DblList(T uniqueVal)
{//���캯��������˫��ѭ������ĸ���ͷ��㣬��������һ������ĳЩ�ض������ֵ
	first = new DblNode<T>(uniqueVal);
	if (first == NULL) { cerr << "�洢�������" << endl; exit(1); }
	first->rLink = first->lLink = first;
}
template<class T>
inline DblList<T>::~DblList()
{
	T x;
	int changdu = Length();
	for (int i = 1; i < changdu; i++)
		Remove(i, x, 1);
}
;

template<class T>
inline int DblList<T>::Length() const
{//���������ͷ����˫��ѭ������ĳ��ȣ�ͨ����������
	DblNode<T>* current = first->rLink; int count = 0;
	while (current != first) { current = current->rLink; count++; }
	return count;
}

template<class T>
inline DblNode<T>* DblList<T>::Search(const T& x)
{//�ڸ���ͷ����˫��ѭ��������Ѱ����ֵ����x�Ľ��
//���ҵ����������ظý���ַ������������NULL
	DblNode<T>* current = first->rLink;
	while (current != first && current->data != x)
		current = current->rLink;
	if (current != first)return current;		//�����ɹ�
	else return NULL;							//����ʧ��
}

template<class T>
inline DblNode<T>* DblList<T>::Locate(int i, int d)
{//�ڴ�����ͷ����˫��ѭ�������а�d��ָ����Ѱ�ҵ�i������λ��
 //��d=0����ǰ������Ѱ�ҵ�i����㣬��d��=0,�ں�̷���Ѱ�ҵ�i�����
	if (first->rLink == first || i == 0)return first;
	DblNode<T>* current;
	if (d == 0)current = first->lLink;			//��������
	else current = first->rLink;
	for (int j = 1; j < i; j++)					//��������
		if (current == first) break;			//��̫���˳�����
		else if (d == 0)current = current->lLink;
		else current = current->rLink;

	if (current != first)return current;		//�����ɹ�
	else return NULL;							//����ʧ��
}

template<class T>
inline bool DblList<T>::Insert(int i, const T& x, int d)
{//����һ��������ֵx���½�㣬�����䰴dָ��������뵽��i��������
	DblNode<T>* current = Locate(i, d);		//���ҵ�i�����
	if (current == NULL) { cout <<i<< "������"; return false; }
				//i����������ʽʧ��
	DblNode<T>* newNode = new DblNode<T>(x);
		if (newNode == NULL) { cerr << "�洢����ʧ�ܣ�" << endl; exit(1); }
	if (d == 0) {							//ǰ���������
		newNode->lLink = current->lLink;
		current->lLink = newNode;
		newNode->lLink->rLink = newNode;
		newNode->rLink = current;
	}
	else {									//�����������
		newNode->rLink = current->rLink;
		current->rLink = newNode;
		newNode->rLink->lLink = newNode;
		newNode->lLink = current;
	}
	return true;							//����ɹ�
};

template<class T>
inline bool DblList<T>::Remove(int i, T& x, int d)
{//�ڴ�����ͷ����˫��ѭ�������а���d��ָ����ɾ����i����㡣
	DblNode<T>* current = Locate(i, d);		//���ҵ�i�����
	if (current == NULL)return false;		//i������ɾ��ʧ��
	else {
		current->rLink->lLink = current->lLink; //��lLink����ժ��
		current->lLink->rLink = current->rLink; //��rlink����ժ��
		x = current->data; delete current;		//ɾ��
		return true;
	}						//ɾ���ɹ�
}

template<class T>
inline int DblList<T>::Swap(T x)
{
	DblNode<T>* current;
	T data;
	current = Search(x);			//����Ԫ��ֵΪx�Ľ��
	if (current == NULL)	return 0;//��û�в��ҵ�Ԫ��ֵΪx�Ľ��
	else {							//��������ǰ�̽���ֵ
		data = current->data;
		current->data = current->lLink->data;
		current->lLink->data = data;
		return 1;
	}
}
