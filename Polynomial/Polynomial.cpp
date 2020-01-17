#include "Polynomial.h"

Term* Term::InsertAfter(float c, int e)
{//在当前由this指针指示的项(即调用此函数的对象)后面插入一个新项
	link = new Term(c, e, link);	//创建一个新结点，自动连接
	return link;					//插入到this结点后面
};

ostream& operator<<(ostream& out, const Term& x)
{//Term的友元函数：输出一个项x的内容到输出流out中。
	if (x.coef == 0.0)return out;
	out << x.coef;
	switch (x.exp) {
	case 0:break;
	case 1:out << "X"; break;
	default:out << "X^" << x.exp; break;
	}
	return out;
};

ostream& operator<<(ostream& out, const Polynomal& x)
{//Polynomal的友元函数：输出带附加头结点的多项式链表x。
	Term* current = x.getHead()->link;
	cout << "The Polynomial Is:" << endl;
	bool h = true;
	while (current != NULL) {
		if (h == false && current->coef > 0.0)  out << "+";
		h = false;
		out << *current;
		current = current->link;
	}
	out << endl;
	return out;

};

istream& operator>>(istream& in, Polynomal& x)
{//Polynomal类的友元函数：从输入流In输入各项，用尾插法建立一个多项式。
	Term* rear = x.getHead(); int c, e;
	while (1) {
		cout << "Input a term(coef,exp):" << endl;
		in >> c >> e;
		if (e < 0)break;
		rear = rear->InsertAfter(c, e);
	}
	return in;
};

Polynomal operator+(Polynomal& A, Polynomal& B)
{//友元函数：两个带附加头结点的按升幂排列的多项式链表的头指针分别是A.first和B.first
 //返回的是结果多项式链表。
	Term* pa, * pb, * pc, * p; float temp;
	Polynomal C; pc = C.first;
												//pc为结果多项式C在创建过程中的尾指针
	pa = A.getHead()->link; pb = B.getHead()->link;

	while (pa != NULL && pb != NULL) {			//两两比较
		if (pa->exp == pb->exp) {				//对应指数相等
			temp = pa->coef + pb->coef;			//系数相加
			if (fabs(temp) > 0.001)				//相加后系数不等于0
				pc = pc->InsertAfter(temp, pa->exp);
			pa = pa->link; pb = pb->link;
		}
		else if (pa->exp < pb->exp) {			//pa指数小
			pc = pc->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;						//pa指向下一个结点
		}
		else {									//pb指数小，加入C链
			pc = pc->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;						//pb指向下一结点
		}
	}
	if (pa != NULL)p = pa;						//p指示剩余链的地址
	else p = pb;
	while (p != NULL) {							//处理链剩余部分
		pc = pc->InsertAfter(p->coef, p->exp);
		p = p->link;
	}
	return C;
};

Polynomal& operator*(Polynomal& A, Polynomal& B)
{//将一元多项式A和B相乘，乘积用附加头结点的单链表存储
 //返回值为指向存储乘积多项式的单链表头结点
	Term* pa, * pb, * pc; int AL, BL, i, k, maxExp;
	Polynomal C;
	pc = C.getHead();
	AL = A.maxOrder(); BL = B.maxOrder();
	if (AL != -1 || BL != -1) {
		maxExp = AL + BL;
		float* result = new float[maxExp + 1];
		for (i = 0; i < maxExp; i++)result[i] = 0.0;
		pa = A.getHead()->link;
		while (pa != NULL) {
			pb = B.getHead()->link;
			while (pb != NULL)
			{
				k = pa->exp + pb->exp;
				result[k] = result[k] + pa->coef + pb->coef;
				pb = pb->link;
			}
			pa = pa->link;
		}
		for (i = 0; i < maxExp; i++)
			if (fabs(result[i] > 0.001))
				pc = pc->InsertAfter(result[i], i);
		
	}
	pc->link = NULL;
	return C;
};

Polynomal::Polynomal(Polynomal& R)
{//复制构造函数：用已有多项式对象R初始化多项式对象R
	first = new Term(0, -1);
	Term * destptr = first, *srcptr = R.getHead()->link;
	while (srcptr != NULL) {
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		//在destptr所指结点后插入新结点，再让destptr指到这个新结点
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
};

int Polynomal::maxOrder()
{//计算最大阶数，当多项式按升序排列时，最后一项是指数最大者。
	Term* current = first;
	while (current->link != NULL)current = current->link;
	//空表情形，current停留在first，否则current停留在尾结点
	return current->exp;
};
