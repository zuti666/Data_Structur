
#define POLYNOMAL_H
#include<iostream>
using namespace std;
struct Term
{
	float coef;
	int	exp;
	Term* link;
	Term(float c, int e, Term* next = NULL)
	{
		coef = c; exp = e; link = next;
	}
	Term* InsertAfter(float c, int e);
	friend ostream& operator<<(ostream&, const Term&);
};

class Polynomal {
public:
	Polynomal() { first = new Term(0, -1); }
	Polynomal(Polynomal& R);
	int maxOrder();
	Term* getHead()const { return first; }
private:
	Term* first;
	friend ostream& operator<<(ostream&, const Polynomal&);
	friend istream& operator>>(istream&,  Polynomal&);
	friend Polynomal operator+(Polynomal&,  Polynomal&);
	friend Polynomal& operator*(Polynomal&,  Polynomal&);


};



























