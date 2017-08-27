#include <stdio.h>
#define N 9
#define SQUARE 3
#define true 1
#define false 0
#define bool int

void input(char a[N][N]);
//输入待填充数独 
void output(char a[N][N]);
//输出数独结果 
bool checkRow(char a[N][N]);
//检查每行是否符合要求 
bool checkColumn(char a[N][N]);
//检查每列是否符合要求 
bool checkSquare(char a[N][N]);
//检查每个方块是否符合要求 
bool checkMap(char a[N][N]);
//检查数独是否同时符合以上三个要求 
void next(int* i, int *j);
//求数独下一个位置 
void solve(char a[N][N], int i, int j);
//求解数独 

void input(char a[N][N]) {
	int i, j;
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			scanf("%c", &a[i][j]);
		}
		scanf("%*c");
	}
}

void output(char a[N][N]) {
	int i, j;
	printf("\n");
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			printf("%c ", a[i][j]);
			if ((j + 1) % 3 == 0)printf(" ");
		}
		printf("\n");
		if ((i + 1) % 3 == 0)printf("\n");
	}
}

bool checkColumn(char a[N][N]) {
	int i, j;
	for (j = 0; j < N; ++j) {
		int flag[N + 1] = { 0 };
		for (i = 0; i < N; ++i) {
			if (flag[a[i][j] - '0'] == true)
				return false;
			if (a[i][j] != ' ')
				flag[a[i][j] - '0'] = true;
		}
	}
	return true;
}

bool checkRow(char a[N][N]) {
	int i, j;
	for (i = 0; i < N; ++i) {
		int flag[N + 1] = { 0 };
		for (j = 0; j < N; ++j) {
			if (flag[a[i][j] - '0'] == true)
				return false;
			if (a[i][j] != ' ')
				flag[a[i][j] - '0'] = true;
		}
	}
	return true;
}

bool checkSquare(char a[N][N]) {
	int i, j;
	int k, l;
	for (i = 0; i < N; i += SQUARE) {
		for (j = 0; j < N; j += SQUARE) {
			int flag[SQUARE*SQUARE + 1] = { 0 };
			for (k = i; k < SQUARE + i; ++k) {
				for (l = j; l < SQUARE + j; ++l) {
					if (flag[a[k][l] - '0'] == true)
						return false;
					if (a[k][l] != ' ')
						flag[a[k][l] - '0'] = true;
				}
			}
		}
	}
	return true;
}

void next(int* i, int *j) {
	++*j;
	if (*j == N) {
		*j = 0;
		++*i;
	}
}

bool checkMap(char a[N][N]) {
	return checkSquare(a) && checkColumn(a) && checkRow(a);
}

void solve(char a[N][N], int i, int j) {
	if (i == N) {
		output(a);
		return;
	}
	else if (a[i][j] != ' ') {
		next(&i, &j);
		solve(a, i, j);
	}
	else {
		int n;
		int _i, _j;
		for (n = 1; n <= N; ++n) {
			a[i][j] = n + '0';
			if (checkMap(a)) {
				_i = i;
				_j = j;
				next(&_i, &_j);
				solve(a, _i, _j);
			}
			a[i][j] = ' ';
		}
	}
}

int main() {
	char map[N][N];
	input(map);
	solve(map, 0, 0);
	return 0;
}
