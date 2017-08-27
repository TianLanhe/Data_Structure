#include "../SequStack.h"
#include <stdio.h>

Status BracketMatch(char *str);
//括号匹配(只能匹配小括号和中括号)，括号合法返回OK,不合法返回ERROR


Status BracketMatch(char *str) {
	SqStack stack;
	SElemType t;
	InitStack(&stack);
	while (*str) {
		switch (*str) {
		case '[':Push(&stack, 1); break;
		case ']':
			if (StackEmpty(stack))return ERROR;
			Pop(&stack, &t);
			if (t != 1)return ERROR;
			break;
		case '(':Push(&stack, 2); break;
		case ')':
			if (StackEmpty(stack))return ERROR;
			Pop(&stack, &t);
			if (t != 2)return ERROR;
			break;
		}
		str++;
	}
	Status status;
	if (StackEmpty(stack))
		status = OK;
	else
		status = ERROR;
	DestroyStack(&stack);
	return status;
}

int main() {
	printf("%d\n", BracketMatch("([(]])])"));
	return 0;
}
