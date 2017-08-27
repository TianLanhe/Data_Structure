#include "sorting.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void creatarr(int **a, int n, int ran) {
	int i;
	*a = (int*)malloc(sizeof(int)*n);
	srand(time(NULL));
	for (i = 0; i < n; i++)(*a)[i] = rand() % ran;
}

void destroyarr(int **a) {
	if (a) {
		free(*a);
		*a = NULL;
	}
}

void display(int a[], int n) {
	int i;
	for (i = 0; i < n; i++) {
		printf("%2d ", a[i]);
		if ((i + 1) % 10 == 0)
			printf("\n");
	}
	printf("\n");
}

void SelectSort(int a[], int n) {
	int i, j, index;
	for (i = 0; i < n; i++) {
		index = i;
		for (j = i + 1; j < n; j++)
			if (a[index] > a[j])
				index = j;
		if (index != i) {
			int t;
			t = a[index];
			a[index] = a[i];
			a[i] = t;
		}
	}
}

void BubbleSort(int a[], int n) {
	int t, i, j;
	int issort;
	for (i = n; i > 0; i--) {
		issort = 0;
		for (j = 0; j < i - 1; j++) {
			if (a[j] > a[j + 1]) {
				issort = 1;
				t = a[j];
				a[j] = a[j + 1];
				a[j + 1] = t;
			}
		}
		if (issort == 0)break;
	}
}

void InsertSort(int a[], int n) {
	int i, j;
	int tmp;
	for (i = 1; i < n; ++i) {
		if (a[i] < a[i - 1]) {
			tmp = a[i];
			for (j = i - 1; j >= 0 && tmp < a[j]; --j)
				a[j + 1] = a[j];
			a[j + 1] = tmp;
		}
	}
}

void BinInsertSort(int a[], int n) {
	int low, high, mid;
	int i, j, temp;
	for (i = 1; i < n; ++i) {
		low = 0;
		high = i - 1;
		while (low <= high) {
			mid = (low + high) / 2;
			if (a[mid] <= a[i])low = mid + 1;
			else high = mid - 1;
		}
		temp = a[i];
		for (j = i - 1; j > high; --j)
			a[j + 1] = a[j];
		a[j + 1] = temp;
	}
}

void ShellSort(int a[], int n) {
	int i, j, d;
	int tmp, dt;
	int dt_arr[] = { 9, 5, 3, 1 };	//增量序列。两两互质的整数效果比较好，如9,5,3,1或40,23,17,13,9,5,3,1
	for (d = 0; d < 4; ++d) {
		dt = dt_arr[d];
		for (i = dt; i < n; ++i) {
			if (a[i] < a[i - dt]) {
				tmp = a[i];
				for (j = i - dt; j >= 0 && a[j] > tmp; j -= dt)
					a[j + dt] = a[j];
				a[j + dt] = tmp;
			}
		}
	}
}

void QuickSort_sub(int a[], int start, int end) {
	int low = start, high = end;
	int key = a[low];
	while (low != high) {
		for (; low != high && key <= a[high]; high--);
		a[low] = a[high];
		for (; low != high && key >= a[low]; low++);
		a[high] = a[low];
	}
	a[low] = key;
	if (high > start)QuickSort_sub(a, start, high - 1);
	if (end > low)QuickSort_sub(a, low + 1, end);
}

void QuickSort(int a[], int length) {
	QuickSort_sub(a, 0, length - 1);
}

void MergeSort_sub(int a[], int start, int end, int *p) {
	if (start != end) {
		int mid = (start + end) / 2;
		int i, j, n;

		MergeSort_sub(a, start, mid, p);
		MergeSort_sub(a, mid + 1, end, p);

		i = start;
		j = mid + 1;
		n = start;
		while (i <= mid && j <= end) {
			if (a[i] < a[j])
				p[n++] = a[i++];
			else
				p[n++] = a[j++];
		}
		while (i <= mid)p[n++] = a[i++];
		while (j <= end)p[n++] = a[j++];

		for (i = start; i <= end; ++i)
			a[i] = p[i];
	}
}

void MergeSort(int a[], int length) {
	int *p;
	p = (int*)malloc(sizeof(int)*length);
	MergeSort_sub(a, 0, length - 1, p);
	free(p);
}

void HeapSort_sub(int a[], int start, int end) {
	int t, i;
	t = a[start];
	start++;                        //将[0,end)元素映射到[1,end+1)
	for (i = start * 2; i < end + 1; i *= 2) { //否则0*2会出错
		if (i < end && a[i - 1] < a[i])i++;
		if (t >= a[i - 1])break;
		a[start - 1] = a[i - 1];
		start = i;
	}
	a[start - 1] = t;
}

void HeapSort(int a[], int length) {                  //堆排序
	int i, t;
	for (i = length / 2 - 1; i >= 0; --i)
		HeapSort_sub(a, i, length);
	for (i = length - 1; i >= 0; --i) {
		t = a[i];
		a[i] = a[0];
		a[0] = t;
		HeapSort_sub(a, 0, i);
	}
}
