#include<iostream>
#include<string.h>
#include<stdio.h>
#include"SeqStack.h"
using namespace std;
const  int  maxLength = 100;			//����ַ�������
void BooleanCheck(const char* expression) {
	SeqStack<int> s1(maxLength);		//ջs1�洢()
	SeqStack<int> s2(maxLength);		//ջs2�洢[]
	SeqStack<int> s3(maxLength);		//ջs2�洢{}
	int j, length = strlen(expression);

	for (int i = 1; i <= length; i++) {
		//�ڱ��ʽ������()
		if (expression[i - 1] == '(') {  s1.Push(i); }	//��Բ���Ű�λ�ý�ջ
		else {			
			if (expression[i - 1] == ')') {		//��Բ����
				if (s1.Pop(j) == true)					//ջ���գ���ջ�ɹ�
					cout << j << "��" << i << "ƥ��" << endl;
				else cout << "û�����" << i << "����Բ����ƥ�����Բ���ţ�" << endl;
				
			}
			
		}
		//�ڱ��ʽ������[]
		if (expression[i - 1] == '[')s2.Push(i);	//�����Ű�λ�ý�ջ
		else if (expression[i - 1] == ']') {		//�ҷ�����
			if (s2.Pop(j) == true)					//ջ���գ���ջ�ɹ�
				cout << j << "��" << i << "ƥ��" << endl;
			else cout << "û�����" << i << "����Բ����ƥ��������ţ�" << endl;

		}
		//�ڱ��ʽ������{}
		if (expression[i - 1] == '{')s3.Push(i);	//������Ű�λ�ý�ջ
		else if (expression[i - 1] == '}') {		//�Ҵ�����
			if (s3.Pop(j) == true)					//ջ���գ���ջ�ɹ�
				cout << j << "��" << i << "ƥ��" << endl;
			else cout << "û�����" << i << "����Բ����ƥ���������ţ�" << endl;

		}


	}
	while (s1.IsEmpty() == false) {				//ջ�л�����Բ����
		s1.Pop(j);
		cout << "û�����" << j << "����Բ����ƥ�����Բ���ţ�" << endl;
	}
	while (s2.IsEmpty() == false) {				//ջ�л���������
		s2.Pop(j);
		cout << "û�����" << j << "��������ƥ����ҷ����ţ�" << endl;
	}
	while (s3.IsEmpty() == false) {				//ջ�л����������
		s3.Pop(j);
		cout << "û�����" << j << "��������ƥ����Ҵ����ţ�" << endl;
	}
}


int main()
{
//��
	SeqStack<int> A;
	A.convert(3, 2);  //��3תΪ2������
	A.convert(2, 2);  //��2תΪ2������
//��
	const char* a = ")]}";	//ƥ����ź���
	BooleanCheck(a);



	return 0;
}
