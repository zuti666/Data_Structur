//���ڽӱ��ʾ��Ȩ�ص�����ͼ
#include<iostream>
#include"LinkQueue.h"
using namespace std;
const int DefaultVertices = 30;//Ĭ����󶥵���30
const int MaxWeight = 9999;//Ĭ�����Ȩֵ
bool visited[30]; //���ʱ������
template<class T,class E>
struct Edge {			//�߽��Ķ���
	int dest;			//������һ����λ��
	E cost;				//���ϵ�Ȩֵ
	Edge<T, E>* link;	//��һ������ָ��
	Edge(){}			//���캯��
	Edge(int num,E weight):dest(num),cost(weight),link(NULL){}
			//���캯��
	bool operator != (Edge<T, E>& R)const {//�жϱ��Ƿ񲻵ȣ����ȷ���ture
		return dest != (Edge<T, E> & R) ? true : false;
	}
};
template<class T,class E>
struct Vertex {			//����Ķ���
	T data;				//����Ķ���
	Edge<T, E>* adj;	//�������ͷָ��
};

template <class T,class E>
class Graphlnk {
	friend istream& operator >>(istream& in, Graphlnk<T, E>& G)//����
	{
	//ͨ�������������� in ����n��������Ϣ��e������ͼ����Ϣ�������ڽӾ���
	//��ʾ��ͼG���ڽӾ����ʼ�������ڹ��캯�������
		int i, j, k, n, m; T e1, e2; E weight;
		cout << "�����붥�����ͱ�����" << endl;
		in >> n >> m;
		for (i = 0; i < n; i++) {
			cout << "�����붥�㣺" << endl;
			in >> e1;
			G.insertVertex(e1);
			cout << "�����" << i << "����ֵ" << G.getValue(i) << endl;
		}
		i = 0;
		while (i < m) {
			cout << "�����붥��e1�Ͷ���e2�Լ�����֮����ϵ�Ȩ��(���߲�������Ϊ9999)��" << endl;
			in >> e1 >> e2 >> weight;
			j = G.getVertexPos(e1); k = G.getVertexPos(e2);//�鶥���
			if (j == -1 || k == -1)
				cout << "��������Ϣ�������������룡" << endl;
			else {
				G.insertEdge(j, k, weight); i++;
				cout << "�ߺ�(" << j << ", " << k << ") Ȩֵ" << weight << endl;
				cout << "���� " << G.NumberOfEdges() << endl;
			}
		}
		return in;

	}
	friend ostream& operator <<(ostream& out, Graphlnk<T, E>& G)//���
	{//���ͼ�����ж���ͱߵ���Ϣ
		int i, j, n, m; T e1, e2; E w;
		n = G.NumberOfVertices(); m = G.NumberOfEdges();
		out << "�������� " << n << "   �������� " << m << endl;
		for (i = 0; i < n; i++)
			for (j = i; j < n; j++) {
				w = G.getWeight(i, j); //ȡ����Ȩֵ
				if (w > 0 && w <MaxWeight) {//��Ч
					e1 = G.getValue(i); e2 = G.getValue(j);//���
					out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
				}
			}
		return out;
	}
private:
	int maxVertices;			//ͼ����󶥵���
	int numEdges;				//��ǰ����
	int numVertices;			//��ǰ������
	Vertex<T, E> * NodeTable;	//�����
	
public:
	int NumberOfVertices() { return numVertices; }//���ص�ǰ������
	int NumberOfEdges() { return numEdges; }	//���ص�ǰ����
	Graphlnk(int sz = DefaultVertices);//���캯��
	~Graphlnk();//��������
	T getValue(int i)//ȡλ��Ϊi�Ķ����ֵ
	{
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);//���ر�(v1,v2)�ϵ�Ȩֵ
	int getVertexPos(const T vertex) {//��������vertex��ͼ�е�λ��
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex)return i;
		return -1;
	}
	bool insertVertex(const T& vertex);//��ͼ�в���һ������vertex
	bool removeVertex(int v);//��ͼ��ɾ��һ������v
	bool insertEdge(int v1, int v2, E const);//��ͼ�в���һ����(v1,v2)
	bool removeEdge(int v1, int v2);//��ͼ��ɾ��һ����(v1,v2)
	int getFirstNeighbor(int v);//ȡv�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);//ȡv���ڽӶ���w����һ���ڽӶ���
	void BFSTraverse();//������ȱ���BFS
	void BFS(int v);//�Ӻ���
	void DFSTraverse(); //������ȱ���DFS
	void DFS(int v); //�Ӻ���
};

template<class T, class E>
inline Graphlnk<T, E>::Graphlnk(int sz)
{//���캯��������һ���յ��ڽӱ�
	maxVertices = sz; numVertices = 0; numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];//������������
	if (NodeTable == NULL) { 
		cerr << "�洢�������" << endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
		NodeTable[i].adj = NULL;
}

template<class T, class E>
inline Graphlnk<T, E>::~Graphlnk()
{//����������ɾ��һ���ڽӱ�
	for (int i = 0; i < numVertices; i++) //ɾ�����������еĽ��
	{
		Edge<T, E>* p = NodeTable[i].adj;//�ҵ����Ӧ�ı�������׽��
		while (p != NULL) {	//����ɾ����һ�����
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete [] NodeTable;//ɾ�����������
}

template<class T, class E>
inline E Graphlnk<T, E>::getWeight(int v1, int v2)
{//�������ر�(v1,v2)�ϵ�Ȩֵ��
 //���ñ߲���ͼ�У���������Ȩֵ0
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj;//v1�ĵ�һ�������ı�
		while (p != NULL && p->dest != v2)//Ѱ���ڽӶ���v2
			p = p->link;
		if (p != NULL)return p->cost;	//�ҵ��˱ߣ�����Ȩֵ
	}
	return 0;				//��(v1,v2)������
}

template<class T, class E>
inline bool Graphlnk<T, E>::insertVertex(const T& vertex)
{//��ͼ�Ķ�����в���һ���¶���vertex
 //����ɹ�����������true�����򷵻�false
	if (numVertices == maxVertices) return false;//������������ܲ���
	NodeTable[numVertices].data = vertex;//���ڱ�����
	numVertices++;return true;
}

template<class T, class E>
inline bool Graphlnk<T, E>::removeVertex(int v)
{//��ͼ��ɾ��һ��ָ������v,v�Ƕ����
//��ɾ���ɹ�����������true,���򷵻�false
	if (numVertices == 1 || v < 0 || v >= numVertices)return false;
	//��ջ��߶���ų�����Χ
	Edge<T, E> * p, *s, *t; int i, k;
	while (NodeTable[v].adj != NULL) {//ɾ����v�������������н��
		p = NodeTable[v].adj; k = p->dest;//ȡ�ڽӶ���k
		s = NodeTable[k].adj; t = NULL;//�ҶԳƴ�ŵı߽��
		while (s != NULL && s->dest != v) {
			t = s; s = s->link;
		}
		if (s != NULL) {	//ɾ���Գƴ�ŵı߽��
			if (t == NULL) NodeTable[k].adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;//�������v�ı�������
		delete p; numEdges--; //�붥��v������ı�����1
	}
	numVertices--; //ͼ�Ķ�������1
	NodeTable[v].data = NodeTable[numVertices].data;//�
	p = NodeTable[v].adj = NodeTable[numVertices].adj;
	while (p != NULL) {
		s = NodeTable[p->dest].adj;
		while (s != NULL)
			if (s->dest == numVertices) {
				s->dest = v;
				break;
			}
			else s = s->link;
	}
	return true;
};

template<class T, class E>
inline bool Graphlnk<T, E>::insertEdge(int v1, int v2, E  weight)
{//�ڴ�Ȩͼ�в���һ����(v1,v2).���˱ߴ��ڻ������������������false,���򷵻�true
 //���ڷǴ�Ȩͼ�����һ������weight��Ҫ���㷨����Ӧ�����Ҳ��Ҫ
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 <= numVertices) {
		Edge<T, E>* q, * p = NodeTable[v1].adj;//v1��Ӧ�ı�����ͷָ��
		while (p != NULL && p->dest != v2)//Ѱ���ڽӶ���v2
			p = p->link;
		if (p != NULL)return false;//�˱��Ѿ����ڣ�������
		p = new Edge<T, E>; q = new Edge<T, E>;//���򣬴����½��
		p->dest = v2; p->cost = weight;
		p->link = NodeTable[v1].adj;//����v1������
		NodeTable[v1].adj = p;
		q->dest = v1; q->cost = weight;
		q->link = NodeTable[v2].adj;   //����v2����
		NodeTable[v2].adj = q;
		numEdges++; return true;
	}



	return false;
}

template<class T, class E>
inline bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{//��ͼ��ɾ��һ����(v1,v2)
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj, * q = NULL, * s = p;
		while (p != NULL && p->dest�� = v2)//v1��Ӧ���������ұ�ɾ�ı�
		{
			q = p;
			p = p->link;
		}
		if (p != NULL) {	//�ҵ���ɾ�߽��
			if (p == s)NodeTable[v1].adj = p->link;//�ý���Ǳ������׽��
			else q->link = p->link;//������������
			delete p;
		}
		else return false;
		p = NodeTable[v2].adj; q = NULL, s = p;
		while (p->dest != v1) {
			q = p;
			p = p->link;
		}
		if (p == s) NodeTable[v2].adj = p->link;
		else q->link = p->link;
		delete p;
		return true;
	}
	return false; //û���ҵ����
}

template<class T, class E>
inline int Graphlnk<T, E>::getFirstNeighbor(int v)
{//��������λ��Ϊv�ĵ�һ���ڽӶ����λ��
 //����Ҳ�������������-1
	if (v != -1) {		//����v����
		Edge<T, E>* p = NodeTable[v].adj;//��Ӧ�������һ���߽��
		if (p != NULL)return p->dest;//���ڣ����ص�һ���ڽӶ���
	}
	return -1;	//��һ���ڽӶ��㲻����
}

template<class T, class E>
inline int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{//��������v���ڽӶ���w����һ���ڽӶ���λ��
 //��û����һ���ڽӶ��㣬��������-1
	if (v != -1) {	//����v����
		Edge<T, E>* p = NodeTable[v].adj;//��Ӧ�������һ���߽��
		while (p != NULL && p->dest != w)//Ѱ���ڽӶ���w
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;	//������һ���ڽӶ���
	}
	return -1;	//��һ�ڽӶ��㲻����
}

template<class T, class E>
inline void Graphlnk<T, E>::BFSTraverse()
{
	//��ͼG���й�����ȱ�����
	int i, vexnum = NumberOfVertices();
	for (i = 0; i < vexnum; i++) //���ʱ�������ʼ��
		visited[i] = false;
	cout << "������ȱ�������" << endl;
	for (i = 0; i < vexnum; i++) //��0�ſ�ʼ����
	{
		if (!visited[i])   //��ÿ����ͨ�������е���һ��BFS
		{
			BFS(i);
			cout << endl;
		}
	}
}

template<class T, class E>
inline void Graphlnk<T, E>::BFS(int v)
{//�Ӷ���v������������ȱ���ͼG���㷨����һ����������Q
	int  w;
	cout << this->getValue(v) << " ";  //���ʶ���v 
	visited[v] = true; //�����ʱ��
	LinkQueue<int> Q;    //�����ն���
	Q.EnQueue(v);   //��������У�ʵ�ֲַ����
	while (!Q.IsEmpty()) {
		Q.DeQueue(v);
		for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v, w))
			if (visited[w] == false) {
				cout << "����" << this->getValue(w) << " ";
				visited[w] = true;
				Q.EnQueue(w);
			}
	}

}

template<class T, class E>
inline void Graphlnk<T, E>::DFSTraverse()
{//��ͼ����������ȱ���
	int i, vexnum = this->NumberOfVertices();
	for (i = 0; i < vexnum; i++)
		visited[i] = false;
	cout << "������ȱ�������" << endl;
	for (i = 0; i < vexnum; i++)
	{
		if (!visited[i]) 
		{
			DFS(i);
			cout << endl;
		}
	}


}

template<class T, class E>
inline void Graphlnk<T, E>::DFS(int v)
{//�Ӷ���v�������ݹ�������ȱ���
	int w;
	cout << this->getValue(v) << " ";
	visited[v] = true;
	for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v, w))
		if (visited[w] == false)
			DFS(w);
}
