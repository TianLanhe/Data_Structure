#include "../SequStack.h"
#include <stdio.h>

void rpn2result(char *rpn, int len);
//根据逆波兰序列计算结果
Status Caculate(char *str, int len);
//利用栈进行四则运算，只允许一位数字进行加减乘除和括号的四则运算
int GetPriority(char ch);
//计算优先级，( < +、- < *、/

void rpn2result(char *rpn, int len) {
	SqStack stack;
	int i;
	int num1, num2, result;
	InitStack(&stack);
	for (i = 0; i < len; i++) {
		if (rpn[i] <= '9' && rpn[i] >= '0')Push(&stack, rpn[i] - 48);	//遇到数字则入栈
		else {
			Pop(&stack, &num2);
			Pop(&stack, &num1);					//遇到符号则将栈顶两个元素取出进行计算
			switch (rpn[i]) {
			case '+':result = num1 + num2; break;
			case '-':result = num1 - num2; break;
			case '*':result = num1*num2; break;
			case '/':result = num1 / num2; break;
			}
			Push(&stack, result);				//将计算后的结果入栈
		}
	}
	Pop(&stack, &result);						//所有计算过后，栈内应该只有一个元素，即最终结果
	if (!StackEmpty(stack))return;
	printf("%d\n", result);						//打印结果
}

int GetPriority(char ch) {
	switch (ch) {
	case '(':return 0;
	case '+':
	case '-':return 1;
	case '*':
	case '/':return 2;
	}
}

Status Caculate(char *str, int len) {
	SqStack stack;
	char rpn[100];
	int i, count;
	int top;
	if (BracketMatch(str) == ERROR)return ERROR;
	InitStack(&stack);
	count = 0;
	for (i = 0; i < len; i++) {									//由中缀表达式转化为后缀表达式
		if (str[i] >= '0' && str[i] <= '9')rpn[count++] = str[i];	//遇到数字则输出
		else if (str[i] == '(')Push(&stack, str[i]);			//左括号入栈
		else if (str[i] == ')') {								//右括号则将左右括号之间的所有符号出栈
			if (GetTop(stack, &top) == ERROR)return ERROR;
			while (top != '(') {
				if (Pop(&stack, &top) == ERROR)return ERROR;
				rpn[count++] = top;
				if (GetTop(stack, &top) == ERROR)return ERROR;
			}
			if (Pop(&stack, &top) == ERROR)return ERROR;
		}
		else {
			int priority1, priority2;
			priority1 = GetPriority(str[i]);
			if (!StackEmpty(stack)) {
				if (GetTop(stack, &top) == ERROR)return ERROR;
				priority2 = GetPriority((char)top);
				while (priority1 <= priority2) {
					if (Pop(&stack, &top) == ERROR)return ERROR;
					rpn[count++] = top;
					if (StackEmpty(stack))break;
					if (GetTop(stack, &top) == ERROR)return ERROR;
					priority2 = GetPriority((char)top);
				}
			}
			Push(&stack, str[i]);
		}
	}
	while (!StackEmpty(stack)) {
		Pop(&stack, &top);
		rpn[count++] = top;
	}
	rpn[count] = '\0';
	rpn2result(rpn, count);			//将所得的后缀表达式进行计算得到最终结果
}

int main() {
	Caculate("3*(4+6-5)/(7-4)", 15);
	return 0;
}
