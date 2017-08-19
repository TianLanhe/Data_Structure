#include <stdio.h>

void Hanoi(int n);
void SubHanoi(int n, char x, char y, char z);
void move(int i, char x, char y);

void EightQueue();
void SubEightQueue(int board[][8], int i, int n);
int isPeace(int board[][8], int i, int j);
void PrintBoard(int board[][8]);

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

void EightQueue() {
	int board[8][8];
	int i, j;
	for (i = 0; i < 8; ++i)
		for (j = 0; j < 8; ++j)
			board[i][j] = 0;
	SubEightQueue(board, 0, 8);
}

void SubEightQueue(int board[][8], int i, int n) {
	if (i == n) {
		PrintBoard(board);
		printf("\n");
	}
	else {
		int j;
		for (j = 0; j < 8; ++j) {
			if (isPeace(board, i, j)) {
				board[i][j] = 1;
				SubEightQueue(board, i + 1, n);
				board[i][j] = 0;
			}
		}
	}
}

int isPeace(int board[][8], int i, int j) {
	int k, l;
	for (k = 0; k < i; ++k)	//检查竖线
		if (board[k][j] == 1)
			return 0;
	for (k = i - 1, l = j - 1; k >= 0 && l >= 0; --k, --l)	// 检查左上斜线
		if (board[k][l] == 1)
			return 0;
	for (k = i - 1, l = j + 1; k >= 0 && l < 8; --k, ++l)	// 检查右上斜线
		if (board[k][l] == 1)
			return 0;
	return 1;
}

void PrintBoard(int board[][8]) {
	int i, j;
	for (i = 0; i < 8; ++i) {
		for (j = 0; j < 8; ++j) {
			printf("%d ", board[i][j]);
		}
		printf("\n");
	}
}

int main() {
	EightQueue();
	return 0;
}
