#include<iostream>
#include"Graphlnk.h"
using namespace std;
const int maxValue = 9999;
template<class T, class E>
void ShortestPath(Graphlnk<T, E>& G, T v, E dist[], int path[]) {
	//Dijkstra�����·��
	//Graphmtx�Ǵ�Ȩ����ͼ���ڽӾ���
	//vΪ��ʼ���㣬��v��ʼ�ҵ��������������·��
	//����dist[j],0<j<n,�ǵ�ǰ��ôӶ���v������j�����·������
	//����path[j],0<j<n������󵽵����·��
	int n = G.NumberOfVertices();
	v = G.getVertexPos(v);
	bool* S = new bool[n];//
	int i, j, k; E w, min;
	for (i = 0; i < n; i++) {
		dist[i] = G.getWeight(v, i); //�����ʼ��
		S[i] = false;
		if (i != v && dist[i] < maxValue) path[i] = v;
		else path[i] = -1;
	}
	S[v] = true; dist[v] = 0;//����v���붥�㼯��
	for (i = 0; i < n - 1; i++) {
		min = maxValue; int u = v;//ѡ����S�о������·���Ķ���u
		for (j = 0; j < n; j++)
			if (S[j] == false && dist[j] < min)
			{
				u = j;
				min = dist[j];
			}
		S[u] = true;//������u���뼯��S
		for (k = 0; k < n; k++) { //�޸�
			w = G.getWeight(u, k);
			if (S[k] == false && w < maxValue && dist[u] + w < dist[k]) {
				//����kδ����S�����ƹ�u��������·��
				dist[k] = dist[u] + w;
				path[k] = u; //�޸ĵ�k�����·��
			}
		}
	}
};
template<class T, class E>
void Bellman_Ford(Graphmtx<T, E>& G, int v, E dist[], int path[]) {
	//Bellman-Ford�����·��,�ڴ�Ȩ����ͼ���еı߾��и���Ȩֵ
	//Graphmtx�Ǵ�Ȩ����ͼ���ڽӾ���
	//vΪ��ʼ���㣬��v��ʼ�ҵ��������������·��
	//����dist[j],0<j<n,�ǵ�ǰ��ôӶ���v������j�����·������
	//����path[j],0<j<n������󵽵����·��
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
	//Floyd�㷨������ÿһ�Զ�������·�������·������
	//a[i][j]�Ƕ���i��j֮������·������
	//path[i][j]����Ӧ·���϶���j��ǰһ����Ķ����
	int i, j, k, n = G.NumberOfVertices();
	for (i = 0; i < n; i++)//����a��path�ĳ�ʼ��
		for (j = 0; j < n; j++) {
			a[i][j] = G.getWeight(i, j);
			if (i != j && a[i][j] < maxValue)path[i][j] = i;
			else path[i][j] = 0;
		}
	for (k = 0; k < n; k++) //���ÿһ��k������a(k)��path(k)
		for (i = 0; i < n; i++)
			for (j = 0; j < n; j++)
				if (a[i][k] + a[k][j] < a[i][j]) {
					a[i][j] = a[i][k] + a[k][j];
					path[i][j] = path[k][j];//����·�����ȣ��ƹ�k��j
				}
}
template<class T, class E>
void printShortestPath(Graphlnk<T, E>& G, T w, E dist[], int path[]) {
	//��path�ж�ȡ���·��
	
	int v = G.getVertexPos(w);
	cout << "�Ӷ���" << G.getValue(v) << "����������������·��Ϊ:" << endl;
	int i, j, k, n = G.NumberOfVertices();
	int* d = new int[n];

	for (i = 0; i < n; i++)
		if (i != v) {
			j = i; k = 0;
			while (j != v) { d[k] = j; k++; j = path[j]; }
			cout << "����" << G.getValue(i) << "�����·��Ϊ��" << G.getValue(v);
			while (k > 0) { cout << G.getValue(d[k]) << " "; k--; }
			cout << "���·������Ϊ��" << dist[i] << endl;
		}
	delete[]d;
};
template<class T, class E>
void TopologicalSort(Graphmtx<T, E>& G) {
	//���������㷨��ʵ��
	int i, j, w, v;
	int top = -1;//���Ϊ�㶥���ջ�ĳ�ʼ��
	int n = G.NumberOfVertices();//�����ж������
	int* count = new int[n];//�����������Ϊ�㶥��ջ
	for (i = 0; i < n; i++) count[i] = 0;
	cout << "����һ���ߣ�i,j)" << endl;//����һ����
	cin >> i >> j;
	while (i > -1 && i<n && j>-1 && j < n) {
		G.insertEdge(i, j); count[j]++;
		cout << "����һ���ߣ�i,j)" << endl;
		cin >> i >> j;
	}
	for (i = 0; i < n; i++) //������������ж���
		if (count[i] == 0) { count[i] = top; top = i; }//���Ϊ��Ķ����ջ
	for (i = 0; i < n; i++)//�������n������
		if (top == -1)//��;ջ�գ�ת��
		{
			cout << "�������л�·��" << endl;
			return;
		}
		else {//������������
			v = top; top = count[top];//��ջv
			cout << G.getValue(v) << " " << endl;//���
			w = G.getFirstNeighbor(v);
			while (w != -1) {//ɨ����߱�
				if (--count[w] == 0)//�ڽӶ�����ȼ�1��
				{
					count[w] = top; //������ȼ����㣬��ջ
					top = w;
				}
				w = G.getNextNeighbor(v, w);
			}

		}
}
template<class T, class E>
void CriticalPath(Graphmtx<T, E>& G) {
	//��ؼ�·���㷨
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
				<< G.getValue(j) << ">�ǹؼ��" << endl;
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
	G.BFSTraverse(); //������ȱ���
	G.DFSTraverse();//������ȱ���
	char a = 'b';//��ʼ����
	int dist[20]; //���·�����ȵľ���
	int path[20];//������·������
	ShortestPath(G, a, dist, path);//Dijkstra�㷨
	printShortestPath(G, a, dist, path);//·�����
	return 0;
}