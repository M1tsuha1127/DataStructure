#pragma once
#define STACK_INIT_SIZE 20
#define OK 1
//字符栈的结构体定义
typedef struct {
	char* base;
	char* top;
	int stacksize;
}CharStack;
//数栈的结构体定义
typedef struct {
	int* base;
	int* top;
	int stacksize;
}NumStack;
//字符栈的创建
void CreatStack(CharStack& S)
{
	S.base = new char(STACK_INIT_SIZE);//申请空间
	if (!S.base) {
		printf("Error:can not creat the stack!");
		return;
	}
	S.top = S.base;//顶指针归底
	S.stacksize = STACK_INIT_SIZE;
	return;
}
//数栈的创建
void CreatnStack(NumStack& S)
{
	S.base = new int(STACK_INIT_SIZE);//申请空间
	if (!S.base) {
		printf("Error:can not creat the stack!");
		return;
	}
	S.top = S.base;//顶指针归底
	S.stacksize = STACK_INIT_SIZE;
	return;
}
//获取字符栈顶元素 返回值为char型
char GetTop(CharStack S)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		exit ;
	}
	return*(S.top - 1);
}
//获取数栈顶元素 返回值为int型
int GetnTop(NumStack S)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		return 0;
	}
	return*(S.top - 1);
}
//将字符元素e压入字符栈中
void Push(CharStack& S, char e)
{
	*(S.top++) = e;//注意为S.top++ 此为运算式 伴随着指针上移
	return;
}
//将整型变量e压入数栈中
void nPush(NumStack& S, int e)
{
	*(S.top++) = e;//注意为S.top++ 此为运算式 伴随着指针上移
	return;
}
//弹出顶部元素 并放入变量e中储存
void Pop(CharStack& S, char& e)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		return;
	}
	e = *--S.top;//同样为运算式
	return;
}
//弹出顶部元素 并放入变量e中储存
void nPop(NumStack& S, int& e)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		return;
	}
	e = *--S.top;//同样为运算式
	return;
}
//进行运算 通过op的运算符号 进行a与b的运算 返回运算结果
int Opreate(int a, char op, int b)
{
	switch (op)
	{
	case'+':
		return a+b;
	case'-':
		return a-b;
	case'*':
		return a*b;
	case'/':
		return a/b;
	case'%':
		return a % b;
	default:
		break;
	}
}
//判断元素是数字还是运算符 若为数字返回true
bool Cmpnum(char e)
{
	if (e <= '9' && e >= '0')
		return true;
	else return false;
}
//比较a与b的优先级  返回值为><=
char Cmppri(char a, char b)
{
	if (a == '+') {
		switch (b)
		{
		case'+':
			return '>';
		case'-':
			return '>';
		case'*':
			return '<';
		case'/':
			return '<';
		case'%':
			return '<';
		case'(':
			return'<';
		case')':
			return'>';
		case'#':
			return'>';
		default:
			break;
		}
	}
	if (a == '-') {
		switch (b)
		{
		case'+':
			return '>';
		case'-':
			return '>';
		case'*':
			return '<';
		case'/':
			return '<';
		case'%':
			return '<';
		case'(':
			return'<';
		case')':
			return'>';
		case'#':
			return'>';
		default:
			break;
		}
	}
	if (a == '*') {
		switch (b)
		{
		case'+':
			return '>';
		case'-':
			return '>';
		case'*':
			return '>';
		case'/':
			return '>';
		case'%':
			return '>';
		case'(':
			return'<';
		case')':
			return'>';
		case'#':
			return'>';
		default:
			break;
		}
	}
	if (a == '/') {
		switch (b)
		{
		case'+':
			return '>';
		case'-':
			return '>';
		case'*':
			return '>';
		case'/':
			return '>';
		case'%':
			return '>';
		case'(':
			return'<';
		case')':
			return'>';
		case'#':
			return'>';
		default:
			break;
		}
	}
	if (a == '%') {
		switch (b)
		{
		case'+':
			return '>';
		case'-':
			return '>';
		case'*':
			return '>';
		case'/':
			return '>';
		case'%':
			return '>';
		case'(':
			return'<';
		case')':
			return'>';
		case'#':
			return'>';
		default:
			break;
		}
	}
	if (a == '(') {
		switch (b)
		{
		case'+':
			return '<';
		case'-':
			return '<';
		case'*':
			return '<';
		case'/':
			return '<';
		case'%':
			return '<';
		case'(':
			return'<';
		case')':
			return'=';
		default:
			break;
		}
	}
	if (a == ')') {
		switch (b)
		{
		case'+':
			return '>';
		case'-':
			return '>';
		case'*':
			return '>';
		case'/':
			return '>';
		case'%':
			return '>';
		case')':
			return'>';
		case'#':
			return'>';
		default:
			break;
		}
	}
	if (a == '#') {
		switch (b)
		{
		case'+':
			return '<';
		case'-':
			return '<';
		case'*':
			return '<';
		case'/':
			return '<';
		case'%':
			return '<';
		case'(':
			return'<';
		case'#':
			return'=';
		default:
			break;
		}
	}
	else { printf("Error:the formula is irregular!"); return 'w'; }
}

