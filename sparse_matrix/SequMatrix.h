#ifndef MATRIX_SEQU_H
#define MATRIX_SEQU_H

#include "../DataStructureBase.h"

typedef struct _Element {
	int x;							//非零元素的行
	int y;							//非零元素的列
	double value;					//非零元素的值
}Element;

typedef struct _RLSMatrix {
	Element *data;					//储存非零元素的一维数组
	int *rowpos;					//矩阵每一行第一个非零元素在一位数组的位置
	int row;						//矩阵的行数
	int column;						//矩阵的列数
	int num;						//矩阵非零元素的个数
}RLSMatrix;

Status SetMData(Element *data, int x, int y, double value);
//设置三元组的值，赋予其行列与值
Status CreatMatrix_Num(RLSMatrix *matrix);
//根据非零元素个数创建稀疏矩阵
Status CreatMatrix_All(RLSMatrix *matrix);
//直接输入矩阵所有元素创建稀疏矩阵
Status SortMatrix(RLSMatrix *matrix);
//将稀疏矩阵matrix的成员data中的非零元素的行列按从小到大的顺序排列
Status InitMatrix(RLSMatrix *matrix);
//初始化稀疏矩阵
Status DestroyMatrix(RLSMatrix *matrix);
//销毁稀疏矩阵
Status PrintMatrix(RLSMatrix matrix);
//打印稀疏矩阵
Status isEqualMatrix(RLSMatrix matrix1, RLSMatrix matrix2);
//判断两个矩阵是否相等
Status isSameMatrix(RLSMatrix matrix1, RLSMatrix matrix2);
//判断两个矩阵是否引用同一份数据
Status CopyMatrix(RLSMatrix *result, RLSMatrix matrix);
//由稀疏矩阵matrix复制得到result
Status AddMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2);
//求稀疏矩阵的和result=matrix1+matrix2
Status SubMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2);
//求稀疏矩阵的差result=matrix1-matrix2
Status ScalarMatrix(RLSMatrix *result, RLSMatrix matrix1, double num);
//求稀疏矩阵的数乘result=matrix1*num
Status MultMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2);
//求稀疏矩阵的乘积result=matrix1*matrix2
Status TransMatrix(RLSMatrix *result, RLSMatrix matrix);
//求稀疏矩阵的转置
Status PowMatrix(RLSMatrix *result, RLSMatrix matrix, int n);
//求稀疏矩阵matrix的n次幂result=matrix^n
Status minverse(double *value);
//遍历函数的功能函数，将稀疏矩阵的每个非零元素取反
Status MatrixTraverse(RLSMatrix *matrix, Status(*visit)(double*));
//依次对稀疏矩阵的每个非零元素调用visit()，一旦调用失败，则操作失败
#endif
