//邻接矩阵表示带权有向图
#include<iostream>
#include"LinkQueue.h"
using namespace std;
const int DefaultVertices = 30;
const int maxWight = 9999;
bool visited[30]; //访问标记数组
template <class T,class E>
class Graphmtx {
	friend istream& operator >>(istream& in, Graphmtx<T, E>& G)
	{//通过从输入流对象 in 输入n个顶点信息和e条无向图的信息建立用邻接矩阵
	//表示的图G。邻接矩阵初始化工作在构造函数中完成
		int i, j, k, n, m; T e1, e2; E weight;
		cout << "请输入顶点数和边数：" << endl;
		in >> n >> m;
		for (i = 0; i < n; i++) {
			cout << "请输入顶点：" << endl;
			in >> e1;
			G.insertVertex(e1);
			k = G.getVertexPos(e1);
			cout << "顶点号" << k << "顶点值" << G.getValue(k) << endl;
		}
		i = 0;
		while (i < m) {
			cout << "请输入顶点e1和顶点e2以及它们之间边上的权重(若边不存在则为9999)：" << endl;
			in >> e1 >> e2 >> weight;
			j = G.getVertexPos(e1); k = G.getVertexPos(e2);//查顶点号

			if (j == -1 || k == -1)
				cout << "边两端信息有误，请重新输入！" << endl;
			else {
				G.insertEdge(j, k, weight); i++;
				cout << "边号(" << j << ", " << k << ") 权值" << weight<< endl;
				cout << "边数 " << G.NumberOfEdges() << endl;
			}

		}
		return in;
	}
	friend ostream& operator <<(ostream& out, Graphmtx<T, E>& G)
	{//输出图的所有顶点和边的信息
		int i, j, n, m; T e1, e2; E w;
		n = G.NumberOfVertices(); m = G.NumberOfEdges();
		out <<"顶点数： "<< n << "   ，边数： " << m << endl;
		for(i=0;i<n;i++)
			for (j = n; j < n; j++) {
				w = G.getWeight(i, j); //取边上权值
				if (w > 0 && w < maxWight) {//有效
					e1 = G.getValue(i); e2 = G.getValue(j);//输出
					out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
				}
			}
		return out;
	}
	
private:
	int maxVertices;//图中最大顶点数
	int numEdges;//当前边数
	int numVertices;//当前顶点数
	T* VerticesList;//顶点表
	E** Edge;//邻接矩阵
	

public:
	Graphmtx(int sz = DefaultVertices);//构造函数
	~Graphmtx()//析构函数
	{
		delete[]  VerticesList;//删除顶点表
		delete[] Edge;//删除邻接矩阵
	}
	int NumberOfVertices() { return numVertices;}//返回当前顶结数
	int NumberOfEdges() { return numEdges; }//返回当前边数
	T getValue(int i)//取顶点i的值，i不合理返回0
	{
		return (i >= 0 && i <= numVertices) ? VerticesList[i] : NULL;
	}
	E getWeight(int v1, int v2)
	{//取边(v1.v2)上的权值
		return (v1 != -1 && v2 != -1) ? Edge[v1][v2] : 0;
	}
	int getVertexPos(T vertex) {//给出顶点vertex在图中的位置
		for (int i = 0; i < numVertices; i++)
			if (VerticesList[i] == vertex) return i;
		return -1;
	}
	bool insertVertex(const T& vertex);//在图中插入一个顶点vertex
	bool removeVertex(int v);//在图中删除一个顶点v和所有与它相关的边
	bool insertEdge(int v1, int v2, E const);//在图中插入一条边(v1,v2)
	bool removeEdge(int v1, int v2);//在图中删除一条边(v1,v2)
	int getFirstNeighbor(int v);//取v的第一个邻接顶点
	int getNextNeighbor(int v, int w);//取v的邻接顶点w的下一个邻接顶点
	void BFSTraverse();//广度优先遍历BFS
	void BFS( int v);//子函数
	void DFSTraverse(); //深度优先遍历DFS
	void DFS( int v); //子函数

};

template<class T, class E>
inline Graphmtx<T, E>::Graphmtx(int sz)
{//构造函数
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
{//插入顶点vertex
	if (numVertices == vertex)return false;//表满，不插入
	VerticesList[numVertices++] = vertex;
	return true;
}

template<class T, class E>
inline bool Graphmtx<T, E>::removeVertex(int v)
{//删去顶点v和所有与它关联的边
	if (v < 0 || v >= numVertices)return false; //v不在图中，不删除
	if (numVertices == 1)return false;//只剩下一个顶点不删除
	int i, j;
	VerticesList[v] = VerticesList[numVertices - 1];
		//顶点表中删除该结点，赋值空值
	for (i = 0; i < numVertices; i++)//减去与v相关联边数
		if (Edge[i][v] > 0 && Edge[i][v] < maxWight)
			numEdges--;
	for (i = 0; i < numVertices; i++)//用最后一列填补第v列
		Edge[i][v] = Edge[i][numVertices - 1];
	numVertices--;	//顶点数减一
	for (j = 0; j < numVertices; j++)
		Edge[v][j] = Edge[numVertices][j];//用最后一行填补第v行
	return true;
}

template<class T, class E>
inline bool Graphmtx<T, E>::insertEdge(int v1, int v2, E cost)
{//插入边(v1,v2)，权值为cost
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices
		&& Edge[v1][v2] == maxWight) {//插入条件，顶点v1,v2在图中并且没有链接边
		Edge[v1][v2] = cost;
		numEdges++;		//边数加一
		return true;
	}
	else
	return false;
}

template<class T, class E>
inline bool Graphmtx<T, E>::removeEdge(int v1, int v2)
{//在图中删去边(v1,v2)
	if (v1 > -1 && v1<numVertices && v2>-1 && v2 < numVertices &&
		Edge[v1][v2]>0 && Edge[v1][v2] < maxWight) {
		Edge[v1][v2] = Edge[v2][v1] = maxWight;//删除边
		numEdges--;//边的条数减一
		return true;
	}
	else   return false;
}

template<class T, class E>
inline int Graphmtx<T, E>::getFirstNeighbor(int v)
{//给出顶点为v的第一个邻接顶点的位置，如果找不到，则函数返回-1
	if (v != -1) {
		for (int col = 0; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWight)return col;
	}
	return -1;
}

template<class T, class E>
inline int Graphmtx<T, E>::getNextNeighbor(int v, int w)
{//给出顶点v的某邻接顶点w的下一个邻接顶点
	if (v != -1 && w != -1) {
		for (int col = w + 1; col < numVertices; col++)
			if (Edge[v][col] > 0 && Edge[v][col] < maxWight)
				return col;
	}
	return -1;
}

template<class T, class E>
inline void Graphmtx<T, E>::BFSTraverse()
{//对图G进行广度优先遍历，
	int i, vexnum = NumberOfVertices();
	for (i = 0; i < vexnum; i++) //访问标记数组初始化
		visited[i] = false;
	cout << "广度优先遍历序列" << endl;
	for (i = 0; i < vexnum; i++) //从0号开始遍历
		if (!visited[i])   //对每个连通分量进行调用一次BFS
			BFS(i);
	cout <<endl;
}

template<class T, class E>
inline void Graphmtx<T, E>::BFS( int v)
{//从顶点v出发，广度优先遍历图G，算法借助一个辅助队列Q
	int  w;
	cout << this->getValue(v) << " ";  //访问顶点v 
	visited[v] = true; //做访问标记
	LinkQueue<int> Q;    //建立空队列
	Q.EnQueue(v);   //顶点进队列，实现分层访问
	while (!Q.IsEmpty()) {
		Q.DeQueue(v);
		for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v,w))
			if (visited[w] == false) {
				cout <<"顶点"<< this->getValue(w) << " ";
				visited[w] = true;
				Q.EnQueue(w);
			}
	}
}

template<class T, class E>
inline void Graphmtx<T, E>::DFSTraverse()
{//对图进行深度优先遍历
	int i, vexnum = this->NumberOfVertices();
	for (i = 0; i < vexnum; i++)
		visited[i] = false;
	cout << "深度优先遍历序列" << endl;
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
{//从顶点v出发，递归深度优先遍历
	int w;
	cout << this->getValue(v) << " ";
	visited[v] = true;
	for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v, w))
		if (visited[w] == false)
			DFS(w);
}
