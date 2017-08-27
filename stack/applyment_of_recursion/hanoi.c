#include <stdio.h>

void Hanoi(int n);
void SubHanoi(int n, char x, char y, char z);
void move(int i, char x, char y);

void Hanoi(int n) {
	if (n > 0)
		SubHanoi(n, 'A', 'B', 'C');
}
void SubHanoi(int n, char x, char y, char z) {
	if (n == 1) {
		move(n, x, y);
	}
	else {
		SubHanoi(n - 1, x, z, y);
		move(n, x, y);
		SubHanoi(n - 1, z, y, x);
	}
}
void move(int i, char x, char y) {
	printf("将第 %d 层从 %c 移动到 %c.\n", i, x, y);
}

int main() {
	Hanoi(5);
	return 0;
}
