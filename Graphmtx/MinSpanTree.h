#include<iostream>

using namespace std;

const int maxValue = 9999;
template<class T,class E>
struct MSTEdgeNode {
	int tail, head; E key; //
	MSTEdgeNode():tail(-1),head(-1),key(0){}//
	bool operator <= (MSTEdgeNode<T, E>& R) { return key <= R.key; }
	bool operator > (MSTEdgeNode<T, E>& R) { return key >R.key; }
};
template<class T, class  E>
class MinSpanTree
{
public:
	MinSpanTree(int sz = DefaultSize - 1) :maxSize(sz), n(0) {
		edgevalue = new MSTEdgeNode<T, E>[sz];
	}
	int Insert(MSTEdgeNode<T,E>& item);

private:
	MSTEdgeNode<T, E>* edgevalue;//
	int maxSize, n;//

};

template<class T, class E>
inline int MinSpanTree<T, E>::Insert(MSTEdgeNode<T,E>& item)
{
	int i = n++;
	if (i< maxValue)
	{
		edgevalue[i].head = item.head;
		edgevalue[i].tail = item.tail;
		edgevalue[i].key = item.key;

	}
	return 0;
}
