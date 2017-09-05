#ifndef SEARCHING_H
#define SEARCHING_H

#include "../DataStructureBase.h"

Status Sequ_Search(int a[], int length, int target, int *ret);
//顺序查找，设置哨兵在最后一个元素之后(可能有越界的风险)
Status Binary_Search(int a[], int length, int target, int *ret);
//折半查找(迭代法)
Status BinarySearch_sub(int a[], int start, int end, int target, int *ret);
//折半查找(递归法)的子过程
Status BinarySearch(int a[], int length, int target, int *ret);
//折半查找(递归法)，封装了具体实现的子过程，只需要提供长度即可

#endif
