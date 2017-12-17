#include "Array.h"
#include <stdlib.h>
#include <stdarg.h>

Status InitArray(Array *arr, int dim, ...) {	//dim表示维数，接下来接着dim个整数，表示每一维的长度
	int i, elemnum;
	va_list ap;

	CHECK_ERROR(dim >= 1 && dim <= MAX_ARRAY_DIM);

	arr->dim = dim;
	arr->bounds = (int *)malloc(sizeof(int)*dim); //bounds是长度为dim的数组，存每一维度的长度
	CHECK_OVERFLOW(arr->bounds);

	arr->constants = (int *)malloc(sizeof(int)*dim);
	CHECK_OVERFLOW(arr->constants);

	va_start(ap, dim);
	for (i = 0, elemnum = 1; i < dim; i++) {
		arr->bounds[i] = va_arg(ap, int);
		CHECK_ERROR(arr->bounds[i] > 0);

		elemnum *= arr->bounds[i];			//数组总个数等于每一维长度相乘，不是相加
	}
	va_end(ap);

	arr->base = (ElemType *)calloc(elemnum, sizeof(ElemType));
	CHECK_OVERFLOW(arr->base);

	arr->constants[dim - 1] = 1;			//若数组维度为3，每维长度为[3][4][3]，则constants长度为3，元素内容为{4*3,3,1}
	for (i = dim - 2; i >= 0; i--)				//表示每一维的权，第三维跨越12个元素，第二维跨越3个维度，以此类推
		arr->constants[i] = arr->bounds[i + 1] * arr->constants[i + 1];

	return OK;
}

Status DestroyArray(Array *arr) {
	CHECK_ERROR(arr->base);
	free(arr->base);
	arr->base = NULL;

	CHECK_ERROR(arr->bounds);
	free(arr->bounds);
	arr->bounds = NULL;

	CHECK_ERROR(arr->constants);
	free(arr->constants);
	arr->constants = NULL;

	arr->dim = 0;
	return OK;
}

Status Value(Array arr, ElemType *e, ...) {
	int i;
	int bounds;
	ElemType *add;
	va_list ap;

	va_start(ap, e);						//把e之后的参数地址放在ap中
	for (i = 0, add = arr.base; i < arr.dim; i++) {
		bounds = va_arg(ap, int);			//提取出每维的长度bounds，并判断合法性
		CHECK_ERROR(bounds >= 0 && bounds <= arr.bounds[i] - 1);

		add += arr.constants[i] * bounds;		//确定那个地址，如[1][1][1]，则add=1*12+1*3+1*1=16.
	}
	va_end(ap);

	*e = *add;
	return OK;
}

Status Assign(Array *arr, ElemType e, ...) {
	int i;
	int bounds;
	ElemType *add;
	va_list ap;

	va_start(ap, e);
	for (i = 0, add = arr->base; i < arr->dim; i++) {
		bounds = va_arg(ap, int);
		CHECK_ERROR(bounds >= 0 && bounds <= arr.bounds[i] - 1);
		add += arr->constants[i] * bounds;
	}
	va_end(ap);

	*add = e;
	return OK;
}
