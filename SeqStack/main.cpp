#include<iostream>
#include<string.h>
#include<stdio.h>
#include"SeqStack.h"
using namespace std;
const  int  maxLength = 100;			//最大字符串长度
void BooleanCheck(const char* expression) {
	SeqStack<int> s1(maxLength);		//栈s1存储()
	SeqStack<int> s2(maxLength);		//栈s2存储[]
	SeqStack<int> s3(maxLength);		//栈s2存储{}
	int j, length = strlen(expression);

	for (int i = 1; i <= length; i++) {
		//在表达式中搜索()
		if (expression[i - 1] == '(') {  s1.Push(i); }	//左圆括号按位置进栈
		else {			
			if (expression[i - 1] == ')') {		//右圆括号
				if (s1.Pop(j) == true)					//栈不空，退栈成功
					cout << j << "与" << i << "匹配" << endl;
				else cout << "没有与第" << i << "个右圆括号匹配的左圆括号！" << endl;
				
			}
			
		}
		//在表达式中搜索[]
		if (expression[i - 1] == '[')s2.Push(i);	//左方括号按位置进栈
		else if (expression[i - 1] == ']') {		//右方括号
			if (s2.Pop(j) == true)					//栈不空，退栈成功
				cout << j << "与" << i << "匹配" << endl;
			else cout << "没有与第" << i << "个右圆括号匹配的左方括号！" << endl;

		}
		//在表达式中搜索{}
		if (expression[i - 1] == '{')s3.Push(i);	//左大括号按位置进栈
		else if (expression[i - 1] == '}') {		//右大括号
			if (s3.Pop(j) == true)					//栈不空，退栈成功
				cout << j << "与" << i << "匹配" << endl;
			else cout << "没有与第" << i << "个大圆括号匹配的左大括号！" << endl;

		}


	}
	while (s1.IsEmpty() == false) {				//栈中还有左圆括号
		s1.Pop(j);
		cout << "没有与第" << j << "个左圆括号匹配的右圆括号！" << endl;
	}
	while (s2.IsEmpty() == false) {				//栈中还有左方括号
		s2.Pop(j);
		cout << "没有与第" << j << "个方括号匹配的右方括号！" << endl;
	}
	while (s3.IsEmpty() == false) {				//栈中还有左大括号
		s3.Pop(j);
		cout << "没有与第" << j << "个大括号匹配的右大括号！" << endl;
	}
}


int main()
{
//六
	SeqStack<int> A;
	A.convert(3, 2);  //将3转为2进制数
	A.convert(2, 2);  //将2转为2进制数
//八
	const char* a = ")]}";	//匹配符号函数
	BooleanCheck(a);



	return 0;
}
