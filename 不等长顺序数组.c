#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#define ERROR 0
#define OK 1
#define Status int
#define MAX_ARRAY_DIM 8
typedef int ElemType;
typedef struct {
	ElemType *base;					//数组元素首地址
	int dim;						//数组维度
	int *bounds;					//数组维界首地址。分配长度为dim的数组，每个元素为每一位维度的长度
	int *constants;					//数组映像函数常量首地址
}Array;
Status InitArray(Array *arr,int dim,...);
//若维数dim和随后的各维长度合法，则构造相应的数组arr，并返回OK
Status DestroyArray(Array *arr);
//销毁数组arr
Status Value(Array arr,ElemType *e,...);
//arr是n维数组，e为元素变量，随后是n个下标值。若各下标不越界，则e赋值为所指定的arr的元素值，并返回OK
Status Assign(Array *arr,ElemType e,...);
//arr是n维数组，e为元素变量，随后是n个下标值。若各下标不越界，则将e的值赋给所指定的arr的元素，并返回OK
Status InitArray(Array *arr,int dim,...){	//dim表示维数，接下来接着dim个整数，表示每一维的长度
	int i,elemnum;
	va_list ap;
	if(dim<1||dim>MAX_ARRAY_DIM)return ERROR;
	arr->dim=dim;
	arr->bounds=(int *)malloc(sizeof(int)*dim); //bounds是长度为dim的数组，存每一维度的长度
	if(!arr->bounds)return ERROR;
	arr->constants=(int *)malloc(sizeof(int)*dim);
	if(!arr->constants)return ERROR;
	va_start(ap,dim);
	for(i=0,elemnum=1;i<dim;i++){
		arr->bounds[i]=va_arg(ap,int);
		elemnum*=arr->bounds[i];			//数组总个数等于每一维长度相乘，不是相加
	}
	va_end(ap);
	arr->base=(ElemType *)calloc(elemnum,sizeof(ElemType));
	if(!arr->base)return ERROR;
	arr->constants[dim-1]=1;			//若数组维度为3，每维长度为[3][4][3]，则constants长度为3，元素内容为{4*3,3,1}
	for(i=dim-2;i>=0;i--)arr->constants[i]=arr->bounds[i+1]*arr->constants[i+1];//表示每一维的权，第三维跨越12个元素，第二维跨越3个维度，以此类推
	return OK;
}
Status DestroyArray(Array *arr){
	if(!arr->base)return ERROR;
	free(arr->base);
	arr->base=NULL;
	if(!arr->bounds)return ERROR;
	free(arr->bounds);
	arr->bounds=NULL;
	if(!arr->constants)return ERROR;
	free(arr->constants);
	arr->constants=NULL;
	arr->dim=0;
	return OK;
}
Status Value(Array arr,ElemType *e,...){
	int i;
	int bounds;
	ElemType *add;
	va_list ap;
	va_start(ap,e);						//把e之后的参数地址放在ap中
	for(i=0,add=arr.base;i<arr.dim;i++){
		bounds=va_arg(ap,int);			//提取出每维的长度bounds，并判断合法性
		if(bounds<0||bounds>arr.bounds[i]-1)return ERROR;
		add+=arr.constants[i]*bounds;		//确定那个地址，如[1][1][1]，则add=1*12+1*3+1*1=16.
	}
	va_end(ap);
	*e=*add;
	return OK;
}
Status Assign(Array *arr,ElemType e,...){
	int i;
	int bounds;
	ElemType *add;
	va_list ap;
	va_start(ap,e);
	for(i=0,add=arr->base;i<arr->dim;i++){
		bounds=va_arg(ap,int);
		if(bounds<0||bounds>arr->bounds[i]-1)return ERROR;
		add+=arr->constants[i]*bounds;
	}
	va_end(ap);
	*add=e;
	return OK;
}
int main(){
	Array arr;
	InitArray(&arr,3,4,3,2);
	printf("%d\n",*(arr.base+9));
	if(!Assign(&arr,15,1,3,1))printf("yes\n");;
	printf("%d\n",*(arr.base+9));
	printf("%d %d %d\n",arr.bounds[0],arr.bounds[1],arr.bounds[2]);

	return 0;
}
