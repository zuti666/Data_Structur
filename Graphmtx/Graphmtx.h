//�ڽӾ����ʾ��Ȩ����ͼ
#include<iostream>
#include"LinkQueue.h"
using namespace std;
const int DefaultVertices = 30;
const int maxWight = 9999;
bool visited[30]; //���ʱ������
template <class T,class E>
class Graphmtx {
	friend istream& operator >>(istream& in, Graphmtx<T, E>& G)
	{//ͨ�������������� in ����n��������Ϣ��e������ͼ����Ϣ�������ڽӾ���
	//��ʾ��ͼG���ڽӾ����ʼ�������ڹ��캯�������
		int i, j, k, n, m; T e1, e2; E weight;
		cout << "�����붥�����ͱ�����" << endl;
		in >> n >> m;
		for (i = 0; i < n; i++) {
			cout << "�����붥�㣺" << endl;
			in >> e1;
			G.insertVertex(e1);
			k = G.getVertexPos(e1);
			cout << "�����" << k << "����ֵ" << G.getValue(k) << endl;
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
				cout << "�ߺ�(" << j << ", " << k << ") Ȩֵ" << weight<< endl;
				cout << "���� " << G.NumberOfEdges() << endl;
			}

		}
		return in;
	}
	friend ostream& operator <<(ostream& out, Graphmtx<T, E>& G)
	{//���ͼ�����ж���ͱߵ���Ϣ
		int i, j, n, m; T e1, e2; E w;
		n = G.NumberOfVertices(); m = G.NumberOfEdges();
		out <<"�������� "<< n << "   �������� " << m << endl;
		for(i=0;i<n;i++)
			for (j = n; j < n; j++) {
				w = G.getWeight(i, j); //ȡ����Ȩֵ
				if (w > 0 && w < maxWight) {//��Ч
					e1 = G.getValue(i); e2 = G.getValue(j);//���
					out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
				}
			}
		return out;
	}
	
private:
	int maxVertices;//ͼ����󶥵���
	int numEdges;//��ǰ����
	int numVertices;//��ǰ������
	T* VerticesList;//�����
	E** Edge;//�ڽӾ���
	

public:
	Graphmtx(int sz = DefaultVertices);//���캯��
	~Graphmtx()//��������
	{
		delete[]  VerticesList;//ɾ�������
		delete[] Edge;//ɾ���ڽӾ���
	}
	int NumberOfVertices() { return numVertices;}//���ص�ǰ������
	int NumberOfEdges() { return numEdges; }//���ص�ǰ����
	T getValue(int i)//ȡ����i��ֵ��i��������0
	{
		return (i >= 0 && i <= numVertices) ? VerticesList[i] : NULL;
	}
	E getWeight(int v1, int v2)
	{//ȡ��(v1.v2)�ϵ�Ȩֵ
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int getVertexPos(T vertex) {//��������vertex��ͼ�е�λ��
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex) return i;
		return -1;
	}
	bool insertVertex(const T& vertex);//��ͼ�в���һ������vertex
	bool removeVertex(int v);//��ͼ��ɾ��һ������v������������صı�
	bool insertEdge(int v1, int v2, E const);//��ͼ�в���һ����(v1,v2)
	bool removeEdge(int v1, int v2);//��ͼ��ɾ��һ����(v1,v2)
	int getFirstNeighbor(int v);//ȡv�ĵ�һ���ڽӶ���
	int getNextNeighbor(int v, int w);//ȡv���ڽӶ���w����һ���ڽӶ���
	void BFSTraverse();//������ȱ���BFS
	void BFS( int v);//�Ӻ���
	void DFSTraverse(); //������ȱ���DFS
	void DFS( int v); //�Ӻ���

};

template<class T, class E>
inline Graphmtx<T, E>::Graphmtx(int sz)
{//���캯��
	maxVertices = sz; numVertices = 0; numEdges = 0;
	int i, j;
	VerticesList = new T[maxVertices];
	Edge = (E * *)new E * [maxVertices];
	for (i = 0; i < maxVertices; i++)
		Edge[i] = new E[maxVertices];
	for (i = 0; i < maxVertices; i++)
		for (j = 0; j < maxVertices; j++)
			Edge[j][i] = (i == j) ? 0 :	maxWight;
}

template<class T, class E>
inline bool Graphmtx<T, E>::insertVertex(const T& vertex)
{//���붥��vertex
	if (numVertices == vertex)return false;//������������
	VerticesList[numVertices++] = vertex;
	return true;
}

template<class T, class E>
inline bool Graphmtx<T, E>::removeVertex(int v)
{//ɾȥ����v���������������ı�
	if (v < 0 || v >= numVertices)return false; //v����ͼ�У���ɾ��
	if (numVertices == 1)return false;//ֻʣ��һ�����㲻ɾ��
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];
		//�������ɾ���ý�㣬��ֵ��ֵ
	for (i = 0; i < numVertices; i++)//��ȥ��v���������
		if (Edge[i][v] > 0 && Edge[i][v] < maxWight)
			numEdges--;
	for (i = 0; i < numVertices; i++)//�����һ�����v��
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;	//��������һ
	for (j = 0; j < numVertices; j++)
		Edge[v][j] = Edge[numVertices][j];//�����һ�����v��
	return true;
}

template<class T, class E>
inline bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{//�����(v1,v2)��ȨֵΪcost
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices
		&& Edge[v1][v2] == maxWight) {//��������������v1,v2��ͼ�в���û�����ӱ�
		Edge[v1][v2] = cost;
		numEdges++;		//������һ
		return true;
	}
	else
	return false;
}

template<class T, class E>
inline bool Graphmtx<T, E>::removeEdge(int v1, int v2)
{//��ͼ��ɾȥ��(v1,v2)
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices &&
		Edge[v1][v2]>0 && Edge[v1][v2] < maxWight) {
		Edge[v1][v2] = Edge[v2][v1] = maxWight;//ɾ����
		numEdges--;//�ߵ�������һ
		return true;
	}
	else   return false;
}

template<class T, class E>
inline int Graphmtx<T, E>::getFirstNeighbor(int v)
{//��������Ϊv�ĵ�һ���ڽӶ����λ�ã�����Ҳ�������������-1
	if (v != -1) {
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWight)return col;
	}
	return -1;
}

template<class T, class E>
inline int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{//��������v��ĳ�ڽӶ���w����һ���ڽӶ���
	if (v != -1 && w != -1) {
		for (int col = w + 1; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWight)
				return col;
	}
	return -1;
}

template<class T, class E>
inline void Graphmtx<T, E>::BFSTraverse()
{//��ͼG���й�����ȱ�����
	int i, vexnum = NumberOfVertices();
	for (i = 0; i < vexnum; i++) //���ʱ�������ʼ��
		visited[i] = false;
	cout << "������ȱ�������" << endl;
	for (i = 0; i < vexnum; i++) //��0�ſ�ʼ����
		if (!visited[i])   //��ÿ����ͨ�������е���һ��BFS
			BFS(i);
	cout <<endl;
}

template<class T, class E>
inline void Graphmtx<T, E>::BFS( int v)
{//�Ӷ���v������������ȱ���ͼG���㷨����һ����������Q
	int  w;
	cout << this->getValue(v) << " ";  //���ʶ���v 
	visited[v] = true; //�����ʱ��
	LinkQueue<int> Q;    //�����ն���
	Q.EnQueue(v);   //��������У�ʵ�ֲַ����
	while (!Q.IsEmpty()) {
		Q.DeQueue(v);
		for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v,w))
			if (visited[w] == false) {
				cout <<"����"<< this->getValue(w) << " ";
				visited[w] = true;
				Q.EnQueue(w);
			}
	}
}

template<class T, class E>
inline void Graphmtx<T, E>::DFSTraverse()
{//��ͼ����������ȱ���
	int i, vexnum = this->NumberOfVertices();
	for (i = 0; i < vexnum; i++)
		visited[i] = false;
	cout << "������ȱ�������" << endl;
	for (i = 0; i < vexnum; i++)
	{
		if (!visited[i]) {
			DFS(i);
			cout << endl;
		}
	}
}

template<class T, class E>
inline void Graphmtx<T, E>::DFS(int v)
{//�Ӷ���v�������ݹ�������ȱ���
	int w;
	cout << this->getValue(v) << " ";
	visited[v] = true;
	for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v, w))
		if (visited[w] == false)
			DFS(w);
}
