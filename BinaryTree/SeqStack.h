#include<iostream>
#include<assert.h>
using namespace std;
const int stackIncreament = 20;				//ջ���ʱ��չ�ռ������
template<class T>
class SeqStack {							//˳����Ķ���
public:
	SeqStack(int sz = 50);					//����һ����ջ
	~SeqStack() { delete[]elements; }		//��������
	void Push(const T& x);	//���IsFull()����������������x���뵽ջ��ջ��
	bool Pop(T& x);		//���IsEmpty()����ִ����ջ������false;�����˵�λ��ջ����Ԫ�أ�����true
						//�˳���Ԫ��ͨ�������Ͳ���x����
	bool getTop(T& x);  //���IsEmpty()���򷵻�false;���򷵻�true
						//ͨ�������Ͳ���x�õ�ջ��Ԫ�ص�ֵ
	bool IsEmpty()const { return (top == -1) ? true : false; }
	//���ջ��Ԫ�ظ���Ϊ0�򷵻�true;���򷵻�false
	bool IsFull()const { return (top == maxSize - 1) ? true : false; }
	//���ջ��Ԫ�ظ���ΪmaxSize�򷵻�true;���򷵻�false
	int getSize()const { return top + 1; }	//��������ջ��Ԫ�ظ���		
	void MakeEmpty() { top = -1; }			//���ջ������
	void convert(int num, int n);			//����������numת��Ϊn������
	friend ostream& operator <<(ostream & os, SeqStack<T> & s);
	//���ջ��Ԫ�ص����ز���<<
private:
	T* elements;							//���ջ��Ԫ�ص�����
	int top;								//ջ��ָ��
	int maxSize;							//ջ��������Ԫ�ظ���
	void overflowProcess();					//ջ���������
};

template<class T>
inline SeqStack<T>::SeqStack(int sz) :top(-1), maxSize(sz)
{//����һ�����ߴ�Ϊsz�Ŀ�ջ�������䲻�ɹ��������
	elements = new T[maxSize];			//����ջ������ռ�
	assert(elements != NULL);			//���ԣ���̬�洢����ɹ����
};

template<class T>
inline void SeqStack<T>::Push(const T & x)
{//������������ջ��������Ԫ��x���뵽��ջ��ջ���������������
	if (IsFull() == true)overflowProcess();	//ջ�����������
	elements[++top] = x;					//ջ��ָ���ȼ�1���ٽ�ջ
};

template<class T>
inline bool SeqStack<T>::Pop(T & x)
{//������������ջ�����������ظ�ջջ��Ԫ�ص�ֵ��Ȼ��ջ��ָ����1
	if (IsEmpty() == true)return false;		//�ж�ջ�շ�ջ�պ�������false
	x = elements[top--];					//ջ��ָ����1
	return true;							//��ջ�ɹ�
};

template<class T>
inline bool SeqStack<T>::getTop(T & x)
{//������������ջ�����������ظ�ջջ��Ԫ�صĵ�ַ
	if (IsEmpty() == true)return false;
	x = elements[top];
	return true;
};

template<class T>
inline void SeqStack<T>::convert(int num, int n)
{
	int yushu;
	while (num != 0)
	{
		yushu = num % n;
		num = num / n;
		Push(yushu);
	}
	int x;
	while (Pop(x)) {

		cout << "  " << x << "  ";
	}
	cout << endl;


}

template<class T>
inline void SeqStack<T>::overflowProcess()
{//˽�к���������ջ�Ĵ洢�ռ�
	T* newArray = new T[maxSize + stackIncreament];
	if (newArray == NULL) { cerr << "�洢����ʧ�ܣ�" << endl; exit(1); }
	for (int i = 0; i <= top; i++)newArray[i] = elements[i];
	maxSize = maxSize + stackIncreament;
	delete[]elements;
};

