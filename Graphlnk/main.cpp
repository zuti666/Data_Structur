#include<iostream>
#include"Graphlnk.h"
using namespace std;
const int maxValue = 9999;
template<class T, class E>
void ShortestPath(Graphlnk<T, E>& G, T v, E dist[], int path[]) {
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
void Bellman_Ford(Graphmtx<T, E>& G, int v, E dist[], int path[]) {
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
void printShortestPath(Graphlnk<T, E>& G, T w, E dist[], int path[]) {
	//从path中读取最短路径
	
	int v = G.getVertexPos(w);
	cout << "从顶点" << G.getValue(v) << "到其他各顶点的最短路径为:" << endl;
	int i, j, k, n = G.NumberOfVertices();
	int* d = new int[n];

	for (i = 0; i < n; i++)
		if (i != v) {
			j = i; k = 0;
			while (j != v) { d[k] = j; k++; j = path[j]; }
			cout << "顶点" << G.getValue(i) << "的最短路径为：" << G.getValue(v);
			while (k > 0) { cout << G.getValue(d[k]) << " "; k--; }
			cout << "最短路径长度为：" << dist[i] << endl;
		}
	delete[]d;
};
template<class T, class E>
void TopologicalSort(Graphmtx<T, E>& G) {
	//拓扑排序算法的实现
	int i, j, w, v;
	int top = -1;//入度为零顶点的栈的初始化
	int n = G.NumberOfVertices();//网络中顶点个数
	int* count = new int[n];//入度数组兼入度为零顶点栈
	for (i = 0; i < n; i++) count[i] = 0;
	cout << "输入一条边（i,j)" << endl;//输入一条边
	cin >> i >> j;
	while (i > -1 && i<n && j>-1 && j < n) {
		G.insertEdge(i, j); count[j]++;
		cout << "输入一条边（i,j)" << endl;
		cin >> i >> j;
	}
	for (i = 0; i < n; i++) //检查网络中所有顶点
		if (count[i] == 0) { count[i] = top; top = i; }//入度为零的顶点进栈
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
void CriticalPath(Graphmtx<T, E>& G) {
	//求关键路径算法
	int i, j, k; E Ae, Al, w;
	int n = G.NumberOfVertices();
	E* Ve = new E[n];
	E* Vl = new E[n];
	for (i = 0; i < n; i++) Ve[i] = 0;
	for (i = 0; i < n; i++) {
		j = G.getFirstNeighbor(i);
		while (j != -1) {
			w = G.getWeight(i, j);
			if (Ve[i] + w > Ve[j]) Ve[j] = Ve[i] + w;
			j = G.getNextNeighbor(i, j);
		}
	}
	Vl[n - 1] = Ve[n - 1];
	for (j = n - 2; j > 0; j--) {//
		k = G.getFirstNeighbor(j);
		while (k != -1) {
			w = G.getWeight(j, k);
			if (Vl[k] - w < Vl[j]) Vl[j] = Vl[k] - w;
			k = G.getNextNeighbor(j, k);
		}
	}
	for (i = 0; i < n; i++) {//
		j = G.getFirstNeighbor(i);
		while (j != -1) {
			Ae = Ve[i]; Al = Vl[k] - G.getWeight(i, j);
			if (Al == Ae)cout << "<" << G.getValue(i) << ","
				<< G.getValue(j) << ">是关键活动" << endl;
			j = G.getNextNeighbor(i, j);
		}
	}
	delete[]Ve; delete[]Vl;
};

int main()
{ 
	Graphlnk<char,int> G;
	cin >> G;
	cout << G;
	G.BFSTraverse(); //广度优先遍历
	G.DFSTraverse();//深度优先遍历
	char a = 'b';//开始顶点
	int dist[20]; //存放路径长度的矩阵
	int path[20];//存放最短路径矩阵
	ShortestPath(G, a, dist, path);//Dijkstra算法
	printShortestPath(G, a, dist, path);//路径输出
	return 0;
}