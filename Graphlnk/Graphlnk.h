//用邻接表表示带权重的无向图
#include<iostream>
#include"LinkQueue.h"
using namespace std;
const int DefaultVertices = 30;//默认最大顶点数30
const int MaxWeight = 9999;//默认最大权值
bool visited[30]; //访问标记数组
template<class T,class E>
struct Edge {			//边结点的定义
	int dest;			//边上另一顶点位置
	E cost;				//边上的权值
	Edge<T, E>* link;	//下一条边链指针
	Edge(){}			//构造函数
	Edge(int num,E weight):dest(num),cost(weight),link(NULL){}
			//构造函数
	bool operator != (Edge<T, E>& R)const {//判断边是否不等，不等返回ture
		return dest != (Edge<T, E> & R) ? true : false;
	}
};
template<class T,class E>
struct Vertex {			//顶点的定义
	T data;				//顶点的定义
	Edge<T, E>* adj;	//边链表的头指针
};

template <class T,class E>
class Graphlnk {
	friend istream& operator >>(istream& in, Graphlnk<T, E>& G)//输入
	{
	//通过从输入流对象 in 输入n个顶点信息和e条无向图的信息建立用邻接矩阵
	//表示的图G。邻接矩阵初始化工作在构造函数中完成
		int i, j, k, n, m; T e1, e2; E weight;
		cout << "请输入顶点数和边数：" << endl;
		in >> n >> m;
		for (i = 0; i < n; i++) {
			cout << "请输入顶点：" << endl;
			in >> e1;
			G.insertVertex(e1);
			cout << "顶点号" << i << "顶点值" << G.getValue(i) << endl;
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
				cout << "边号(" << j << ", " << k << ") 权值" << weight << endl;
				cout << "边数 " << G.NumberOfEdges() << endl;
			}
		}
		return in;

	}
	friend ostream& operator <<(ostream& out, Graphlnk<T, E>& G)//输出
	{//输出图的所有顶点和边的信息
		int i, j, n, m; T e1, e2; E w;
		n = G.NumberOfVertices(); m = G.NumberOfEdges();
		out << "顶点数： " << n << "   ，边数： " << m << endl;
		for (i = 0; i < n; i++)
			for (j = i; j < n; j++) {
				w = G.getWeight(i, j); //取边上权值
				if (w > 0 && w <MaxWeight) {//有效
					e1 = G.getValue(i); e2 = G.getValue(j);//输出
					out << "(" << e1 << "," << e2 << "," << w << ")" << endl;
				}
			}
		return out;
	}
private:
	int maxVertices;			//图中最大顶点数
	int numEdges;				//当前边数
	int numVertices;			//当前顶点数
	Vertex<T, E> * NodeTable;	//顶点表
	
public:
	int NumberOfVertices() { return numVertices; }//返回当前顶点数
	int NumberOfEdges() { return numEdges; }	//返回当前边数
	Graphlnk(int sz = DefaultVertices);//构造函数
	~Graphlnk();//析构函数
	T getValue(int i)//取位置为i的顶点的值
	{
		return (i >= 0 && i < numVertices) ? NodeTable[i].data : 0;
	}
	E getWeight(int v1, int v2);//返回边(v1,v2)上的权值
	int getVertexPos(const T vertex) {//给出顶点vertex在图中的位置
		for (int i = 0; i < numVertices; i++)
			if (NodeTable[i].data == vertex)return i;
		return -1;
	}
	bool insertVertex(const T& vertex);//在图中插入一个顶点vertex
	bool removeVertex(int v);//在图中删除一个顶点v
	bool insertEdge(int v1, int v2, E const);//在图中插入一条边(v1,v2)
	bool removeEdge(int v1, int v2);//在图中删除一条边(v1,v2)
	int getFirstNeighbor(int v);//取v的第一个邻接顶点
	int getNextNeighbor(int v, int w);//取v的邻接顶点w的下一个邻接顶点
	void BFSTraverse();//广度优先遍历BFS
	void BFS(int v);//子函数
	void DFSTraverse(); //深度优先遍历DFS
	void DFS(int v); //子函数
};

template<class T, class E>
inline Graphlnk<T, E>::Graphlnk(int sz)
{//构造函数：建立一个空的邻接表
	maxVertices = sz; numVertices = 0; numEdges = 0;
	NodeTable = new Vertex<T, E>[maxVertices];//创建顶点数组
	if (NodeTable == NULL) { 
		cerr << "存储分配错误！" << endl;
		exit(1);
	}
	for (int i = 0; i < maxVertices; i++)
		NodeTable[i].adj = NULL;
}

template<class T, class E>
inline Graphlnk<T, E>::~Graphlnk()
{//析构函数：删除一个邻接表
	for (int i = 0; i < numVertices; i++) //删除各边链表中的结点
	{
		Edge<T, E>* p = NodeTable[i].adj;//找到其对应的边链表的首结点
		while (p != NULL) {	//不断删除第一个结点
			NodeTable[i].adj = p->link;
			delete p;
			p = NodeTable[i].adj;
		}
	}
	delete [] NodeTable;//删除顶点表数组
}

template<class T, class E>
inline E Graphlnk<T, E>::getWeight(int v1, int v2)
{//函数返回边(v1,v2)上的权值，
 //若该边不在图中，则函数返回权值0
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj;//v1的第一条关联的边
		while (p != NULL && p->dest != v2)//寻找邻接顶点v2
			p = p->link;
		if (p != NULL)return p->cost;	//找到此边，返回权值
	}
	return 0;				//边(v1,v2)不存在
}

template<class T, class E>
inline bool Graphlnk<T, E>::insertVertex(const T& vertex)
{//在图的顶点表中插入一个新顶点vertex
 //插入成功，函数返回true，否则返回false
	if (numVertices == maxVertices) return false;//顶点表满，不能插入
	NodeTable[numVertices].data = vertex;//插在表的最后
	numVertices++;return true;
}

template<class T, class E>
inline bool Graphlnk<T, E>::removeVertex(int v)
{//在图中删除一个指定顶点v,v是顶点号
//若删除成功，函数返回true,否则返回false
	if (numVertices == 1 || v < 0 || v >= numVertices)return false;
	//表空或者顶点号超出范围
	Edge<T, E> * p, *s, *t; int i, k;
	while (NodeTable[v].adj != NULL) {//删除第v个边链表中所有结点
		p = NodeTable[v].adj; k = p->dest;//取邻接顶点k
		s = NodeTable[k].adj; t = NULL;//找对称存放的边结点
		while (s != NULL && s->dest != v) {
			t = s; s = s->link;
		}
		if (s != NULL) {	//删除对称存放的边结点
			if (t == NULL) NodeTable[k].adj = s->link;
			else t->link = s->link;
			delete s;
		}
		NodeTable[v].adj = p->link;//清除顶点v的边链表结点
		delete p; numEdges--; //与顶点v相关联的边数减1
	}
	numVertices--; //图的顶点数减1
	NodeTable[v].data = NodeTable[numVertices].data;//填补
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
{//在带权图中插入一条边(v1,v2).若此边存在或参数不合理，函数返回false,否则返回true
 //对于非带权图，最后一个参数weight不要，算法中相应的语句也不要
	if (v1 >= 0 && v1 < numVertices && v2 >= 0 && v2 <= numVertices) {
		Edge<T, E>* q, * p = NodeTable[v1].adj;//v1对应的边链表头指针
		while (p != NULL && p->dest != v2)//寻找邻接顶点v2
			p = p->link;
		if (p != NULL)return false;//此边已经存在，不插入
		p = new Edge<T, E>; q = new Edge<T, E>;//否则，创建新结点
		p->dest = v2; p->cost = weight;
		p->link = NodeTable[v1].adj;//链入v1边链表
		NodeTable[v1].adj = p;
		q->dest = v1; q->cost = weight;
		q->link = NodeTable[v2].adj;   //链入v2链表
		NodeTable[v2].adj = q;
		numEdges++; return true;
	}



	return false;
}

template<class T, class E>
inline bool Graphlnk<T, E>::removeEdge(int v1, int v2)
{//在图中删除一条边(v1,v2)
	if (v1 != -1 && v2 != -1) {
		Edge<T, E>* p = NodeTable[v1].adj, * q = NULL, * s = p;
		while (p != NULL && p->dest！ = v2)//v1对应边链表中找被删的边
		{
			q = p;
			p = p->link;
		}
		if (p != NULL) {	//找到被删边结点
			if (p == s)NodeTable[v1].adj = p->link;//该结点是边链表首结点
			else q->link = p->link;//不是重新链接
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
	return false; //没有找到结点
}

template<class T, class E>
inline int Graphlnk<T, E>::getFirstNeighbor(int v)
{//给出顶点位置为v的第一个邻接顶点的位置
 //如果找不到，则函数返回-1
	if (v != -1) {		//顶点v存在
		Edge<T, E>* p = NodeTable[v].adj;//对应边链表第一个边结点
		if (p != NULL)return p->dest;//存在，返回第一个邻接顶点
	}
	return -1;	//第一个邻接顶点不存在
}

template<class T, class E>
inline int Graphlnk<T, E>::getNextNeighbor(int v, int w)
{//给出顶点v的邻接顶点w的下一个邻接顶点位置
 //若没有下一个邻接顶点，则函数返回-1
	if (v != -1) {	//顶点v存在
		Edge<T, E>* p = NodeTable[v].adj;//对应边链表第一个边结点
		while (p != NULL && p->dest != w)//寻找邻接顶点w
			p = p->link;
		if (p != NULL && p->link != NULL)
			return p->link->dest;	//返回下一个邻接顶点
	}
	return -1;	//下一邻接顶点不存在
}

template<class T, class E>
inline void Graphlnk<T, E>::BFSTraverse()
{
	//对图G进行广度优先遍历，
	int i, vexnum = NumberOfVertices();
	for (i = 0; i < vexnum; i++) //访问标记数组初始化
		visited[i] = false;
	cout << "广度优先遍历序列" << endl;
	for (i = 0; i < vexnum; i++) //从0号开始遍历
	{
		if (!visited[i])   //对每个连通分量进行调用一次BFS
		{
			BFS(i);
			cout << endl;
		}
	}
}

template<class T, class E>
inline void Graphlnk<T, E>::BFS(int v)
{//从顶点v出发，广度优先遍历图G，算法借助一个辅助队列Q
	int  w;
	cout << this->getValue(v) << " ";  //访问顶点v 
	visited[v] = true; //做访问标记
	LinkQueue<int> Q;    //建立空队列
	Q.EnQueue(v);   //顶点进队列，实现分层访问
	while (!Q.IsEmpty()) {
		Q.DeQueue(v);
		for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v, w))
			if (visited[w] == false) {
				cout << "顶点" << this->getValue(w) << " ";
				visited[w] = true;
				Q.EnQueue(w);
			}
	}

}

template<class T, class E>
inline void Graphlnk<T, E>::DFSTraverse()
{//对图进行深度优先遍历
	int i, vexnum = this->NumberOfVertices();
	for (i = 0; i < vexnum; i++)
		visited[i] = false;
	cout << "深度优先遍历序列" << endl;
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
{//从顶点v出发，递归深度优先遍历
	int w;
	cout << this->getValue(v) << " ";
	visited[v] = true;
	for (w = this->getFirstNeighbor(v); w >= 0; w = this->getNextNeighbor(v, w))
		if (visited[w] == false)
			DFS(w);
}
