#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define N 9
#define SQUARE 3
#define true 1
#define false 0
#define bool int
#define FILL ' '

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
bool generate(char a[N][N]);
//初始化棋面为空格，然后生成数独
bool generateSudoku(char a[N][N], int i, int j);
//生成数独
int getRandomNum(int start, int len);
//随机生成[start,start+len)之间的随机数

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
			if (a[i][j] != FILL)
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
			if (a[i][j] != FILL)
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
					if (a[k][l] != FILL)
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
	else if (a[i][j] != FILL) {
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
			a[i][j] = FILL;
		}
	}
}

int getRandomNum(int start, int len) {
	int r;
	int bucket_size = RAND_MAX / len;
	do {
		r = rand() / bucket_size;
	} while (r >= len);
	return r + start;
}

bool generateSudoku(char a[N][N], int i, int j) {
	if (i == N)
		return true;

	int n, x;
	int flag[N + 1] = { 0 };
	int _i, _j;
	for (n = 0; n < N; ++n) {
		do {
			x = getRandomNum(1, 9);
		} while (flag[x]);
		flag[x] = true;

		a[i][j] = x + '0';

		if (checkMap(a)) {
			_i = i;
			_j = j;
			next(&_i, &_j);
			if (generateSudoku(a, _i, _j))
				return true;
		}
	}
	a[i][j] = ' ';
	return false;
}

bool generate(char a[N][N]) {
	int i, j;
	for (i = 0; i < N; ++i)
		for (j = 0; j < N; ++j)
			a[i][j] = ' ';
	return generateSudoku(a, 0, 0);
}

int main() {
	char map[N][N];
	input(map);
	//srand(time(NULL));
	//generate(map);
	//output(map);
	solve(map, 0, 0);
	return 0;
}
