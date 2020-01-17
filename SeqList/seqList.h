//����������Ϊ˳���Ĵ洢�ṹ������װ�����˽������
#include<iostream>
#include<stdlib.h>

using namespace std;
const int defaultSize = 100;
template <class T>
class SeqList  {
protected:
	T* data;								//�������
	int maxSize;							//�������ɱ��������
	int last;								//��ǰ�Ѵ�ű�������λ�ã���0��ʼ��
	void reSize(int newSize);				//�ı�data����ռ��С
public:
	SeqList(int sz = defaultSize);			//���캯��
	SeqList(SeqList<T>& L);					//���ƹ��캯��
	~SeqList() { delete []data; }			//��������
	int Size()const { return maxSize; }		//������������ɱ������
	int Length()const { return last + 1; }	//�������
	T* getHead()const { return data; }      //���������ַ
	int Search(T& x)const;					//����x�ڱ��е�λ�ã��������ر������
	void Sort();							//����
	int Locate(int i)const;					//��λ��i������������ر������
	bool getData(int i, T& x)const			//ȡ��i�������ֵ
	{
		if (i > 0 && i <= last + 1)
		{
			x = data[i - 1];
			return true;
		}
		else return false;
	};
	void setData(int i, T& x)				//��x�޸ĵ�i�������ֵ
	{
		if (i > 0 && i <= last + 1)
			data[i - 1] = x;

	};
	bool Insert(int i, T & x);				//����x�ڵ�i������֮��
	bool Remove(int i, T & x);				//ɾ����i�����ͨ��x���ر����ֵ
	bool IsEmpty()							//�жϱ�շ�
	{//�շ���true�����򷵻�false
		return (last == -1) ? true : false;
	}
	bool IsFull()							//�жϱ�����
	{//���򷵻�true�����򷵻�false
		return (last == maxSize - 1) ? true : false;
	}
	void input();							//����
	void output();							//���
	SeqList<T> operator =(SeqList<T> & L);	//�����帳ֵ
};
	template<class T>
	inline void SeqList<T>::reSize(int newSize)
	{//˽�к���������˳���Ĵ洢����ռ��С���������Ԫ�ظ���ΪnewSize.
		if (newSize <= 0)					//�������ĺ�����
		{
			cerr << "��Ч�������С" << endl;
			return;
		}
		if (newSize != maxSize)				//�޸�
		{
			T* newarray = new T[newSize];	//����������
			if (newarray == NULL)
			{
				cerr << "�洢�������" << endl;
				exit(1);
			}
			int n = last + 1;
			T* srcptr = data;				//Դ�����׵�ַ
			T* destptr = newarray;			//Ŀ�������׵�ַ
			while (n--)* destptr++ = *srcptr++;//����
			delete[]data;					//ɾ��������
			data = newarray; maxSize = newSize;//����������
		}
	};

	template<class T>
	inline SeqList<T>::SeqList(int sz)
	{//���캯����ͨ��ָ������sz��������ĳ��ȡ�
		if (sz > 0) {
			maxSize = sz; last = -1;	//�ñ��ʵ�ʳ���Ϊ��
			data = new T[maxSize];		//����˳���洢����
			if (data == NULL)			//��̬����ʧ��
			{
				cerr << "�������ʧ�ܣ�" << endl; exit(1);
			}
		}
	};

	template<class T>
	inline SeqList<T>::SeqList(SeqList<T> & L)
	{//���ƹ��캯�����ò������и���������˳����ʼ���½���˳���
		maxSize = L.Size();
		last = L.Length() - 1;
		T value;
		data = new T[maxSize];		//����˳���洢����
		if (data == NULL)			//��̬����ʧ��
		{
			cerr << "�洢�������" << endl; exit(1);
		}
		for (int i = 1; i <= last + 1; i++)
		{
			L.getData(i, value);
			data[i - 1] = value;
		}
	}
	template<class T>
	inline int SeqList<T>::Search(T & x) const
	{//�����������ڱ������������ֵxƥ��ı��
	 //	�ҵ��򷵻ظñ����ǵڼ���Ԫ��,����������0����ʾ����ʧ��
		for (int i = 0; i <= last; i++)
			if (data[i] == x)return i + 1;		//˳������
		return 0;								//����ʧ��
	}
	template<class T>
	inline void SeqList<T>::Sort()
	{//ð������
		for (int i = 0; i < last; i++) {
			//�Ƚ��������ڵ�Ԫ��   
			for (int j = 0; j < last - i - 1; j++) {
				if (data[j] > data[j + 1]) {
					int t = data[j];
					data[j] = data[j + 1];
					data[j + 1] = t;
				}
			}
		}
	}
	template<class T>
	inline int SeqList<T>::Locate(int i) const
	{//��λ�������������ص�i(1<=i<=last+1)�������λ�ã�����������0����ʾ��λʧ�ܡ�
		if (i >= 1 && i <= last + 1)return i;
		else return 0;
	};

	template<class T>
	inline bool SeqList<T>::Insert(int i, T & x)
	{//����Ԫ��x���뵽���е�i(0<=i<=lat+1)������֮��
	 //�������ز���ɹ�����Ϣ��������ɹ����򷵻�true�����򷵻�false
	 //i=0������ģ�ʵ���ǲ��뵽��1��Ԫ�ص�λ��
		if (last == maxSize - 1) return false;	//���������ܲ���
		if (i<0 || i>last + 1)return false;		//����i���������ܲ���
		for (int j = last; j >= i; j--)
			data[j + 1] = data[j];				//���κ��ƣ��ճ���i��λ��
		data[i] = x;							//����
		last++;									//���λ�ü�1
		return true;							//����ɹ�

	};
	template<class T>
	inline bool SeqList<T>::Remove(int i, T & x)
	{//�ӱ���ɾ����i(1<=i<=last+1)�����ͨ�������β�x����ɾ����Ԫ��ֵ
	 //�������سɹ�����Ϣ����ɾ���ɹ��򷵻�true�����򷵻�false
		if (last == -1)return false;			//��գ�����ɾ��
		if (i<1 || i>last + 1)return false;		//����i����������ɾ��
		x = data[i - 1];						//�汻ɾ��Ԫ�ص�ֵ
		for (int j = i; j <= last; j++)
			data[j - 1] = data[j];				//����ǰ��,�
		last--;									//���λ�ü�1
		return true;							//ɾ���ɹ�

	};
	template<class T>
	inline void SeqList<T>::input()
	{//�ӱ�׼���루���̣�����������룬����˳���
		cout << "��ʼ����˳������������Ԫ�ظ�������0��ʼ����";
		while (1) {
			cin >> last;
			if (last <= maxSize - 1)break;
			cout << "��Ԫ�ظ����������󣬷�Χ���ó���" << maxSize - 1 << ":";
		}
		for (int i = 0; i <= last; i++)
		{
			cout << "��" << i  << "��Ԫ��" << endl;
			cin >> data[i];
		}
	};
	template<class T>
	inline void SeqList<T>::output()
	{//��˳���ȫ��Ԫ�����뵽��Ļ�ϡ�
		cout << "˳���ǰԪ�����λ��Ϊ��" << last << endl;
		for (int i = 0; i <= last; i++)
			cout << "#" << i + 1 << ":" << data[i] << endl;
	};
	template<class T>
	inline SeqList<T> SeqList<T>::operator=(SeqList<T> & L)
	{//���ز�����˳������帳ֵ��
	 //����ǰ���ô˲����ı����ΪL1�������β�L�ı����ΪL2����ʹ�÷�ʽΪL1=L2��

		this.maxSize = L.Size();
		this.last = L.Length() - 1;
		T value;
		this.data = new T[maxSize];		//����˳���洢����
		if (this.data == NULL)			//��̬����ʧ��
		{
			cerr << "�洢�������" << endl; exit(1);
		}
		for (int i = 1; i <= last + 1; i++)
		{
			L.getData(i, value);
			this.data[i - 1] = value;
		}
		return this;
	};

