#ifndef strsort_h
#define strsort_h
#include <stdio.h>
#include <string.h>
void display(char *p[],int n);
//打印字符串数组
void StrSelectSort(char *p[],int n);
//字符串选择排序
void StrBubbleSort(char *p[],int n);
//字符串冒泡排序
void StrInsertSort(char *p[],int n);
//字符串插入排序
void StrShellSort(char *p[],int n);
//字符串希尔排序
void StrSort(char *p[],int n);
//自己瞎捣鼓的字符串排序
void StrQuickSort_sub(char *p[],int start,int end);
//字符串快速排序的子过程
void StrQuickSort(char *p[],int length);
//字符串快速排序，封装了快速排序具体实现的子过程，只需要提供长度即可
void StrMergeSort_sub(char *a[],int start,int end,int *p[]);
//字符串归并排序的子过程
void StrMergeSort(char *p[],int length);
//字符串归并排序，封装了归并排序具体实现的子过程，为其申请辅助空间p，调用子过程后释放，只需要提供长度即可
void StrHeapSort_sub(char *p[],int start,int length);
//堆排序的子过程，假设[start,length)中除start外均满足堆的定义，调整start的位置使成为一个堆
void StrHeapSort(char *p[],int length);
//堆排序，先建立初始堆，再循环处理，将堆顶元素移到末尾，对其余元素调整成为新堆
void StrSearch(char *p[],int length,char *target);
//字符串折半查找排序(迭代法)
int StrSearch2_sub(char *p[],int start,int end,char *target);
//字符串折半查找排序(递归法)的子过程
int StrSearch2(char *p[],int length,char *target);
//字符串折半查找排序(递归法)
#endif
