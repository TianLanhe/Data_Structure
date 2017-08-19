#ifndef ARRAY_H
#define ARRAY_H

#include "../DataStructureBase.h"

#define MAX_ARRAY_DIM 8

typedef struct {
	ElemType *base;					//数组元素首地址
	int dim;						//数组维度
	int *bounds;					//数组维界首地址。分配长度为dim的数组，每个元素为每一位维度的长度
	int *constants;					//数组映像函数常量首地址
}Array;

Status InitArray(Array *arr, int dim, ...);
//若维数dim和随后的各维长度合法，则构造相应的数组arr，并返回OK
Status DestroyArray(Array *arr);
//销毁数组arr
Status Value(Array arr, ElemType *e, ...);
//arr是n维数组，e为元素变量，随后是n个下标值。若各下标不越界，则e赋值为所指定的arr的元素值，并返回OK
Status Assign(Array *arr, ElemType e, ...);
//arr是n维数组，e为元素变量，随后是n个下标值。若各下标不越界，则将e的值赋给所指定的arr的元素，并返回OK

#endif
