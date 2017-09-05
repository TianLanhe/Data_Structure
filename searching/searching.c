#include "searching.h"

Status Sequ_Search(int a[], int length, int target, int *ret) {
	int i;
	a[length] = target;
	for (i = 0; a[i] != target; i++);    //不用判断i是否小于length，提高效率
	(i != length) && (*ret = i);
	return i == length ? ERROR : OK;
}

Status Binary_Search(int a[], int length, int target, int *ret) {
	int high = length - 1;
	int low = 0;
	int mid;
	while (low <= high) {
		mid = (low + high) / 2;
		if (target == a[mid]) {
			*ret = mid;
			return OK;
		}
		else if (target > a[mid])low = mid + 1;
		else high = mid - 1;
	}
	return ERROR;
}

Status BinarySearch_sub(int a[], int start, int end, int target, int *ret) {    //递归法折半查找
	int mid = (start + end) / 2;
	if (target == a[mid]) {
		*ret = mid;
		return OK;
	}
	else if (start > end)
		return ERROR;
	else if (target < a[mid])
		return BinarySearch_sub(a, start, mid - 1, target, ret);
	else if (target > a[mid])
		return BinarySearch_sub(a, mid + 1, end, target, ret);
}

Status BinarySearch(int a[], int length, int target, int *ret) {
	return BinarySearch_sub(a, 0, length - 1, target, ret);
}
