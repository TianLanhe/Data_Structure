#include "../SequStack.h"
#include <stdio.h>

Status PrintChar(SElemType e);
//遍历函数的功能函数，打印字符
void LineEdit(char back, char clear);
//行编辑

Status PrintChar(SElemType e) {
	printf("%c", e);
	return OK;
}

void LineEdit(char back, char clear) {
	SqStack stack;
	char ch;
	SElemType e;
	InitStack(&stack);
	do {
		ch = getchar();
		if (ch == back)Pop(&stack, &e);
		else if (ch == clear)ClearStack(&stack);
		else if (ch == '\n') {
			StackTraverse(stack, PrintChar);
			printf("\n");
			ClearStack(&stack);
		}
		else if (ch != EOF)
			Push(&stack, ch);
	} while (ch != EOF);
	StackTraverse(stack, PrintChar);
	DestroyStack(&stack);
}

int main() {
	LineEdit('#','@');
	return 0;
}
