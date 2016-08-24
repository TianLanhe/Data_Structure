#ifndef sort_h
#define sort_h
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
void creatarr(int **a,int n,int ran);
//初始化动态数组,为a分配长为n的数字，内容大小在区间[0,ran)中
//举例：int *a;
//      creatarr(&a,100,1000)   产生100个内容在0到1000的动态数组
void display(int a[],int n);
//打印数组的内容
void SelectSort(int a[],int n);
//选择排序
void Sort(int a[],int n);
//自己随便搞的排序
void BubbleSort(int a[],int n);
//冒泡排序
void InsertSort(int a[],int n);
//插入排序
void BinInsertSort(int a[],int n);
//折半插入排序
void ShellSort(int a[],int n);
//希尔排序
void QuickSort_sub(int a[],int start,int end);
//快速排序的子过程
void QuickSort(int a[],int length);
//快速排序，封装了快速排序具体实现的子过程，只需要提供长度即可
void MergeSort_sub(int a[],int start,int end,int *p);
//归并排序的子过程
void MergeSort(int a[],int length);
//归并排序，封装了归并排序具体实现的子过程，为其申请辅助空间p，调用子过程后释放，只需要提供长度即可
void HeapSort_sub(int a[],int start,int length);
//堆排序的子过程，假设[start,length)中除start外均满足堆的定义，调整start的位置使成为一个堆
void HeapSort(int a[],int length);
//堆排序，先建立初始堆，再循环处理，将堆顶元素移到末尾，对其余元素调整成为新堆
#endif
