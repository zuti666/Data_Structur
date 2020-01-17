#include<iostream>
#include<cstdlib>
#include"Polynomial.h"
using namespace std;
int main()
{
	Polynomal A, B;
	cout << "输入多项式A" << endl;cin>>A;
	cout<<"多项式A"<<endl;cout<<A; 
	cout << "输入多项式B" << endl;cin>>B;
	cout<<"多项式B"<<endl;cout<<B;
	cout << "多项式A+B" << endl;cout<<A+B;
	cout<<"多项式A*B"<<endl;cout<<A*B;
	return 0;
}
