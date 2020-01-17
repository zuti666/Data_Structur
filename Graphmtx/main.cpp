#include<iostream>
#include"Graphmtx.h"
#include"MinHeap.h"
#include"UFSets.h"
#include"MinSpanTree.h"
using namespace std;

template <class T,class E>
void Kruskal(Graphmtx<T, E>& G, MinSpanTree<T, E>& MST) {
	//Kruskal算法的实现
	MSTEdgeNode<T, E> ed; int u, v, count;//边结点辅助单元
	int n = G.NumberOfVertices();//顶点数
	int m = G.NumberOfEdges();//边数
	MinHeap<MSTEdgeNode<T, E>> H(m);//最小堆，关键码类型为E
	UFSets F(n);//并查集
	for(u = 0; u < n; u++)
		for(v=u+1;v<n;v++)
			if (G.getWeight(u, v) != maxValue) {
				ed.tail = u; ed.head = v;//插入堆
				ed.key = G.getWeight(u, v);
				H.Insert(ed);
			}
	count = 1;//最小生成树加入边数计数
	while (count < n) {//反复执行，取n-1条边
		H.RemoveMin(ed);//从最小堆中退出具有最小权值的边ed
		u = F.Find(ed.tail);
		v = F.Find(ed.head);//取两个顶点所在集合的根u和v
		if (u != v) {//不是同一结点，说明不连通
			F.Union(u, v);//合并，连通他们
			MST.Insert(ed);//该边存入最小树
			count++;
		}
	}
}
template<class T, class E>
void Prim(Graphmtx<T, E>& G, const T u0, MinSpanTree<T, E>& MST) {
	//Prim的实现
	MSTEdgeNode<T, E> ed; int i, u, v, count;//边结点辅助单元
	int n = G.NumberOfVertices();//顶点数
	int m = G.NumberOfEdges();//边数
	int u = G.getVertexPos(u0);//求起始顶点号
	MinHeap<MSTEdgeNode<T, E>>H(m);//最小堆，关键码类型为E
	bool Vmst = new bool[n];//最小生成树顶点集合
	for (i = 0; i < n; i++) Vmst[i] = false;
	Vmst[u] = true;
	count = 1;// u加入生成树
	do { //迭代
		v = G.getFirstNeighbor(u);
		while (v != -1) {//重复检测u的所有邻接点
			if (Vmst[v] == false) {//若v不在生成树，(u,v)加入堆
				ed.tail = u; ed.head = v;
				ed.key = G.getWeight(u, v);//tail在树内，head不在树内
				H.Insert(ed);
			}
			v = G.getNextNeighbor(u, v);//找顶点u的下一个邻接顶点v
		}
		while (H.IsEmpty() == false && count < n) {
			H.RemoveMin(ed);//从堆中退出具有最小权值的边ed
			if (Vmst[ed.head] == false) {
				MST.Insert(ed);//加入最小生成树
				u = ed.head; Vmst[u] = true;//u加入生成树顶点集合
				count++; break;
			}
		}
	} while (count < n);

};

template<class T, class E>
void ShortestPath(Graphmtx<T, E>& G, T v, E dist[], int path[]) {
	//Dijkstra求最短路径
	//Graphmtx是带权有向图的邻接矩阵，
	//v为起始顶点，从v开始找到所有其他顶点的路径
	//数组dist[j],0<j<n,是当前求得从顶点v到顶点j的最短路径长度
	//数组path[j],0<j<n，存放求到的最短路径
	int n = G.NumberOfVertices();
	v = G.getVertexPos(v);
	bool* S = new bool[n];//
	int i, j, k; E w, min;
	for (i = 0; i < n; i++) {
		dist[i] = G.getWeight(v, i); //数组初始化
		S[i] = false;
		if (i != v && dist[i] < maxValue) path[i] = v;
		else path[i] = -1;
	}
	S[v] = true; dist[v] = 0;//顶点v加入顶点集合
	for (i = 0; i < n - 1; i++) {
		min = maxValue; int u = v;//选不在S中具有最短路径的顶点u
		for (j = 0; j < n; j++)
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		S[u] = true;//将顶点u加入集合S
		for (k = 0; k < n; k++) { //修改
			w = G.getWeight(u, k);
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k]) {
				//顶点k未加入S，且绕过u可以缩短路径
				dist[k] = dist[u] + w;
				path[k] = u; //修改到k的最短路径
			}
		}
	}
};
template<class T, class E>
void Bellman_Ford(Graphmtx<T, E> & G, int v, E dist[], int path[]) {
	//Bellman-Ford求最短路径,在带权有向图中有的边具有负的权值
	//Graphmtx是带权有向图的邻接矩阵，
	//v为起始顶点，从v开始找到所有其他顶点的路径
	//数组dist[j],0<j<n,是当前求得从顶点v到顶点j的最短路径长度
	//数组path[j],0<j<n，存放求到的最短路径
	int  i, k, u, n = G.NumberOfVertices(); E w;
	for (i = 0; i < n; i++) {
		dist[i] = G.getWeight(v, i);
		if (i != v && dist[i] < maxValue)path[i] = v;
		else path[i] = -1;
	}
	for (k = 2; k < n; k++)
		for (u = 0; u < n; u++)
			if (u != v)
				for (i = 0; i < n; i++) {
					w = G.getWeight(i, u);
					if (w > 0 && w<maxValue && dist[u]>dist[i] + w) {
						dist[u] = dist[i] + w;
						path[u] = i;
					}
				}
};
template<class T, class E>
void Floyd(Graphmtx<T, E> & G, E * *a, int** path) {
	//Floyd算法，计算每一对顶点间最短路径及最短路径长度
	//a[i][j]是顶点i和j之间的最短路径长度
	//path[i][j]是相应路径上顶点j的前一顶点的顶点号
	int i, j, k, n = G.NumberOfVertices();
	for (i = 0; i < n; i++)//矩阵a与path的初始化
		for (j = 0; j < n; j++) {
			a[i][j] = G.getWeight(i, j);
			if (i != j && a[i][j] < maxValue)path[i][j] = i;
			else path[i][j] = 0;
		}
	for (k = 0; k < n; k++) //针对每一个k，产生a(k)及path(k)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (a[i][k] + a[k][j] < a[i][j]) {
					a[i][j] = a[i][k] + a[k][j];
					path[i][j] = path[k][j];//缩短路径长度，绕过k到j
				}
}

template<class T, class E>
void printShortestPath(Graphmtx<T, E> & G, T w, E dist[], int path[]) {
	//从path中读取最短路径
	int v = G.getVertexPos(w);
	cout << "从顶点" << G.getValue(v) << "到其他各顶点的最短路径为:" << endl;
	int i, j, k, n = G.NumberOfVertices();
	int* d = new int[n];

	for (i = 0; i < n; i++)
		if (i != v) {
			j = i; k = 0;
			while (j != v) { d[k++] = j; j = path[j]; }
			cout << "顶点" << G.getValue(i) << "的最短路径为：" << G.getValue(v);
			while (k > 0) { cout << G.getValue(d[--k]) << " "; }
			cout << "最短路径长度为：" << dist[i] << endl;
		}
	delete[]d;
}
template<class T, class E>
void TopologicalSort(Graphmtx<T, E> & G) {
	//拓扑排序算法的实现
	int i, j, w, v;
	int top = -1;//入度为零顶点的栈的初始化
	int n = G.NumberOfVertices();//网络中顶点个数
	int* count = new int[n];//入度数组兼入度为零顶点栈
	for (i = 0; i < n; i++) count[i] = 0;
	for (i = 0; i < n; i++) //检查网络中所有顶点
		if (count[i] == 0) { count[i] = top; top = i; }//入度为零的顶点进栈
	cout << "拓扑排序序列：" << endl;
	for (i = 0; i < n; i++)//期望输出n个顶点
		if (top == -1)//中途栈空，转出
		{
			cout << "网络中有回路！" << endl;
			return;
		}
		else {//继续拓扑排序
			v = top; top = count[top];//退栈v
			cout << G.getValue(v) << " " << endl;//输出
			w = G.getFirstNeighbor(v);
			while (w != -1) {//扫描出边表
				if (--count[w] == 0)//邻接顶点入度减1，
				{
					count[w] = top; //顶点入度减至零，进栈
					top = w;
				}
				w = G.getNextNeighbor(v, w);
			}

		}
}
template<class T, class E>
void CriticalPath(Graphmtx<T, E> & G) {
	//求关键路径算法
	int i, j, k; E Ae, Al, w;
	int n = G.NumberOfVertices();
	E* Ve = new E[n];
	E* Vl = new E[n];
	for (i = 0; i < n; i++) Ve[i] = 0;
	for (i = 0; i < n; i++) { //正向计算Ve[]
		j = G.getFirstNeighbor(i);
		while (j != -1) {
			w = G.getWeight(i, j);
			if (Ve[i] + w > Ve[j]) Ve[j] = Ve[i] + w;
			j = G.getNextNeighbor(i, j);
		}
	}
	cout << "最早开始时间Ve" << endl;
	for (i = 0; i < n; i++)
		cout << G.getValue(i) << ": " << Ve[i] << endl;
	Vl[n - 1] = Ve[n - 1];

	for (j = n - 2; j > 0; j--) {//逆向计算Vl[]
		k = G.getFirstNeighbor(j);
		cout << "k" << k;
		while (k != -1) {
			w = G.getWeight(j, k);
			cout << "(j,k)w" << j << k << w << endl;
			if ((Vl[k] - w )< Vl[j]) Vl[j] = Vl[k] - w;
			k = G.getNextNeighbor(j, k);
		}
	}
	cout << "最迟开始时间Vl" << endl;
	for (i = 0; i < n; i++)
		cout << G.getValue(i) << ": " << Vl[i] << endl;

	for (i = 0; i < n; i++) {// 求各活动的e，l
		j = G.getFirstNeighbor(i);
		while (j != -1) {
			Ae = Ve[i]; Al = Vl[k] - G.getWeight(i, j);
			if (Al == Ae)
				cout << "<" << G.getValue(i) << ","
				<< G.getValue(j) << ">是关键活动" << endl;
			j = G.getNextNeighbor(i, j);
		}
	}
	delete[]Ve; delete[]Vl;
};




int main()
{
	Graphmtx<char,int> G;
	cin >> G; //输入图
	cout << G; //输出图
	G.BFSTraverse(); //广度优先遍历
	G.DFSTraverse();//深度优先遍历
	//MinSpanTree <int, int> M;
	//Kruskal(G, M);//Kruskal算法
	//Prim(G,0, M);//Prim算法
	char a = 'a';//开始顶点
	int dist[20]; //存放路径长度的矩阵
	int path[20];//存放最短路径矩阵
	ShortestPath(G, a, dist, path);//Dijkstra算法
	printShortestPath(G, a, dist, path);//路径输出
	CriticalPath(G);//关键路径
	return 0;
}