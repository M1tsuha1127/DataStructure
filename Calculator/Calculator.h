#pragma once
#define STACK_INIT_SIZE 20
#define OK 1
//�ַ�ջ�Ľṹ�嶨��
typedef struct {
	char* base;
	char* top;
	int stacksize;
}CharStack;
//��ջ�Ľṹ�嶨��
typedef struct {
	int* base;
	int* top;
	int stacksize;
}NumStack;
//�ַ�ջ�Ĵ���
void CreatStack(CharStack& S)
{
	S.base = new char(STACK_INIT_SIZE);//����ռ�
	if (!S.base) {
		printf("Error:can not creat the stack!");
		return;
	}
	S.top = S.base;//��ָ����
	S.stacksize = STACK_INIT_SIZE;
	return;
}
//��ջ�Ĵ���
void CreatnStack(NumStack& S)
{
	S.base = new int(STACK_INIT_SIZE);//����ռ�
	if (!S.base) {
		printf("Error:can not creat the stack!");
		return;
	}
	S.top = S.base;//��ָ����
	S.stacksize = STACK_INIT_SIZE;
	return;
}
//��ȡ�ַ�ջ��Ԫ�� ����ֵΪchar��
char GetTop(CharStack S)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		exit ;
	}
	return*(S.top - 1);
}
//��ȡ��ջ��Ԫ�� ����ֵΪint��
int GetnTop(NumStack S)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		return 0;
	}
	return*(S.top - 1);
}
//���ַ�Ԫ��eѹ���ַ�ջ��
void Push(CharStack& S, char e)
{
	*(S.top++) = e;//ע��ΪS.top++ ��Ϊ����ʽ ������ָ������
	return;
}
//�����ͱ���eѹ����ջ��
void nPush(NumStack& S, int e)
{
	*(S.top++) = e;//ע��ΪS.top++ ��Ϊ����ʽ ������ָ������
	return;
}
//��������Ԫ�� ���������e�д���
void Pop(CharStack& S, char& e)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		return;
	}
	e = *--S.top;//ͬ��Ϊ����ʽ
	return;
}
//��������Ԫ�� ���������e�д���
void nPop(NumStack& S, int& e)
{
	if (S.top == S.base) {
		printf("Error:The Stack is empty!");
		return;
	}
	e = *--S.top;//ͬ��Ϊ����ʽ
	return;
}
//�������� ͨ��op��������� ����a��b������ ����������
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
//�ж�Ԫ�������ֻ�������� ��Ϊ���ַ���true
bool Cmpnum(char e)
{
	if (e <= '9' && e >= '0')
		return true;
	else return false;
}
//�Ƚ�a��b�����ȼ�  ����ֵΪ><=
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

