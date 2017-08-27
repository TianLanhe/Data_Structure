#include "../SequStack.h"
#include <stdio.h>

void Conversion(int num, int base);
//将十进制数num转化为base进制数

void Conversion(int num, int base) {
	SqStack stack;
	int i;
	int basenum[100];
	InitStack(&stack);
	for (i = 0; i < base; i++) {			//因为超过十进制就要用ABCD了
		if (i < 10)basenum[i] = '0' + i;	//所以用一个数组储存一张表，该表是该进制所用的符号集合
		else basenum[i] = 'A' + i - 10;
	}
	if (num == 0)printf("0\n");
	while (num) {
		Push(&stack, basenum[num%base]);	//把该进制所用的符号入栈，低数位先入栈，高位后入栈
		num /= base;
	}
	while (!StackEmpty(stack)) {
		Pop(&stack, &num);			//出栈并打印
		printf("%c", num);
	}
	printf("\n");
	DestroyStack(&stack);
}

int main() {
	Conversion(12345,16);
	return 0;
}
