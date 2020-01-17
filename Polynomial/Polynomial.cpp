#include "Polynomial.h"

Term* Term::InsertAfter(float c, int e)
{//�ڵ�ǰ��thisָ��ָʾ����(�����ô˺����Ķ���)�������һ������
	link = new Term(c, e, link);	//����һ���½�㣬�Զ�����
	return link;					//���뵽this������
};

ostream& operator<<(ostream& out, const Term& x)
{//Term����Ԫ���������һ����x�����ݵ������out�С�
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
{//Polynomal����Ԫ���������������ͷ���Ķ���ʽ����x��
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
{//Polynomal�����Ԫ��������������In��������β�巨����һ������ʽ��
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
{//��Ԫ����������������ͷ���İ��������еĶ���ʽ�����ͷָ��ֱ���A.first��B.first
 //���ص��ǽ������ʽ����
	Term* pa, * pb, * pc, * p; float temp;
	Polynomal C; pc = C.first;
												//pcΪ�������ʽC�ڴ��������е�βָ��
	pa = A.getHead()->link; pb = B.getHead()->link;

	while (pa != NULL && pb != NULL) {			//�����Ƚ�
		if (pa->exp == pb->exp) {				//��Ӧָ�����
			temp = pa->coef + pb->coef;			//ϵ�����
			if (fabs(temp) > 0.001)				//��Ӻ�ϵ��������0
				pc = pc->InsertAfter(temp, pa->exp);
			pa = pa->link; pb = pb->link;
		}
		else if (pa->exp < pb->exp) {			//paָ��С
			pc = pc->InsertAfter(pa->coef, pa->exp);
			pa = pa->link;						//paָ����һ�����
		}
		else {									//pbָ��С������C��
			pc = pc->InsertAfter(pb->coef, pb->exp);
			pb = pb->link;						//pbָ����һ���
		}
	}
	if (pa != NULL)p = pa;						//pָʾʣ�����ĵ�ַ
	else p = pb;
	while (p != NULL) {							//������ʣ�ಿ��
		pc = pc->InsertAfter(p->coef, p->exp);
		p = p->link;
	}
	return C;
};

Polynomal& operator*(Polynomal& A, Polynomal& B)
{//��һԪ����ʽA��B��ˣ��˻��ø���ͷ���ĵ�����洢
 //����ֵΪָ��洢�˻�����ʽ�ĵ�����ͷ���
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
{//���ƹ��캯���������ж���ʽ����R��ʼ������ʽ����R
	first = new Term(0, -1);
	Term * destptr = first, *srcptr = R.getHead()->link;
	while (srcptr != NULL) {
		destptr->InsertAfter(srcptr->coef, srcptr->exp);
		//��destptr��ָ��������½�㣬����destptrָ������½��
		srcptr = srcptr->link;
		destptr = destptr->link;
	}
};

int Polynomal::maxOrder()
{//������������������ʽ����������ʱ�����һ����ָ������ߡ�
	Term* current = first;
	while (current->link != NULL)current = current->link;
	//�ձ����Σ�currentͣ����first������currentͣ����β���
	return current->exp;
};
