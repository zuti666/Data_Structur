#include<iostream>
#include<assert.h>
#include"SeqQueue.h"
using namespace std;

int main() {
	SeqQueue<int> A(10);
	for (int i = 0; i < 5; i++)
		A.EnQueue(i);
	cout << A;

	return 0;
}