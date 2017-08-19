#include "SequMatrix.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Status SetMData(Element *data, int x, int y, double value) {
	if (!data)
		return ERROR;
	data->x = x;
	data->y = y;
	data->value = value;
	return OK;
}

Status CreatMatrix_Num(RLSMatrix *matrix) {
	int row, column, num;
	int i;
	int x, y;
	double value;
	if (!matrix)return ERROR;

	row = 0;
	printf("请输入稀疏矩阵的行数：");
	scanf("%d", &row);
	if (row <= 0) {
		printf("矩阵行数不合法！\n");
		return ERROR;
	}

	column = 0;
	printf("请输入稀疏矩阵的列数：");
	scanf("%d", &column);
	if (column <= 0) {
		printf("矩阵列数不合法！\n");
		return ERROR;
	}

	num = -1;
	printf("请输入稀疏矩阵非零元素的个数：");
	scanf("%d", &num);
	if (num > row*column || num < 0) {
		printf("元素个数不合法！\n");
		return ERROR;
	}

	matrix->num = num;
	matrix->row = row;
	matrix->column = column;

	if (!num) {
		matrix->data = NULL;
		matrix->rowpos = NULL;
	}
	else {
		matrix->data = (Element *)malloc(sizeof(Element)*num);
		if (!matrix->data)
			return OVERFLOW;

		matrix->rowpos = (int *)malloc(row * sizeof(int));
		if (!matrix->rowpos)
			return OVERFLOW;

		for (i = 0; i < num; ++i) {
			do {
				value = x = y = 0;
				printf("请输入第 %d 个非零元素的行数、列数和值：", i + 1);
				scanf("%d%d%lf", &x, &y, &value);
				if (x > row || y > column || x <= 0 || y <= 0)printf("元素的行数或列数不合法！请重新输入\n");
				if (fabs(value) < 1e-6)printf("元素的值不能为0！请重新输入\n");
			} while (x > row || y > column || x <= 0 || y <= 0 || fabs(value) < 1e-6);

			if (SetMData(&matrix->data[i], x, y, value) == ERROR)
				return ERROR;
		}

		Status status;
		if ((status = SortMatrix(matrix)) != OK)
			return status;
	}
	return OK;
}

Status CreatMatrix_All(RLSMatrix *matrix) {
	int row, column, num;
	double value;
	int i, j;
	int *rownum;
	Element *data;
	Status status;
	if (!matrix)return ERROR;

	row = 0;
	printf("请输入矩阵的行数：");
	scanf("%d", &row);
	if (row <= 0) {
		printf("矩阵行数不合法！\n");
		return ERROR;
	}

	column = 0;
	printf("请输入矩阵的列数：");
	scanf("%d", &column);
	if (column <= 0) {
		printf("矩阵列数不合法！\n");
		return ERROR;
	}

	rownum = (int *)calloc(row, sizeof(int));
	if (!rownum)
		return OVERFLOW;

	data = (Element *)malloc(sizeof(Element)*row*column);
	if (!data)
		return OVERFLOW;

	num = 0;
	printf("请输入矩阵：\n");
	for (i = 0; i < row; i++) {
		for (j = 0; j < column; j++) {
			scanf("%lf", &value);
			if (fabs(value) > 1e-6) {
				if ((status = SetMData(data + num, i + 1, j + 1, value)) != OK) {
					free(data);
					free(rownum);
					return status;
				}
				++num;
				++rownum[i];
			}
		}
	}

	matrix->row = row;
	matrix->column = column;
	matrix->num = num;

	if (!num) {
		matrix->data = NULL;
		matrix->rowpos = NULL;
		free(data);
	}
	else {
		data = (Element *)realloc(data, sizeof(Element)*num);
		if (!data)
			return OVERFLOW;
		matrix->data = data;

		matrix->rowpos = (int *)malloc(sizeof(int)*row);
		if (!matrix->rowpos)
			return OVERFLOW;

		matrix->rowpos[0] = 0;
		for (i = 1; i < row; i++) {
			matrix->rowpos[i] = matrix->rowpos[i - 1] + rownum[i - 1];
		}
	}
	free(rownum);
	return OK;
}

Status InitMatrix(RLSMatrix *matrix) {
	if (!matrix)
		return ERROR;
	matrix->row = matrix->column = matrix->num = 0;
	matrix->data = NULL;
	matrix->rowpos = NULL;
	return OK;
}

Status DestroyMatrix(RLSMatrix *matrix) {
	if (!matrix)
		return ERROR;
	matrix->row = matrix->column = matrix->num = 0;
	if (matrix->data)
		free(matrix->data);
	if (matrix->rowpos)
		free(matrix->rowpos);
	matrix->data = NULL;
	matrix->rowpos = NULL;
	return OK;
}

Status PrintMatrix(RLSMatrix matrix) {
	int i, j;
	int num = 0;
	if (!matrix.row && !matrix.column)return ERROR;
	for (i = 0; i < matrix.row; i++) {
		for (j = 0; j < matrix.column; j++) {
			if (matrix.num &&
				i == matrix.data[num].x - 1 && j == matrix.data[num].y - 1)
				printf("%3.0f", matrix.data[num++].value);
			else printf("  0");
		}
		printf("\n");
	}
	return OK;
}

Status SortMatrix(RLSMatrix *matrix) {
	int i, j, index;
	Element temp;
	int *rownum;
	if (!matrix || !matrix->num || !matrix->data)
		return ERROR;

	rownum = (int*)calloc(matrix->row, sizeof(int));
	if (!rownum)
		return OVERFLOW;

	for (i = 0; i < matrix->num; i++) {
		index = i;
		for (j = i + 1; j < matrix->num; j++) {
			if (matrix->data[j].x < matrix->data[index].x ||
				(matrix->data[j].x == matrix->data[index].x && matrix->data[j].y < matrix->data[index].y)) {
				index = j;
			}
		}
		if (index != i) {
			temp = matrix->data[i];
			matrix->data[i] = matrix->data[index];
			matrix->data[index] = temp;
		}
		++rownum[matrix->data[i].x - 1];
	}
	matrix->rowpos[0] = 0;
	for (i = 1; i < matrix->row; ++i)
		matrix->rowpos[i] = matrix->rowpos[i - 1] + rownum[i - 1];
	free(rownum);
	return OK;
}

Status isEqualMatrix(RLSMatrix m1, RLSMatrix m2) {
	int i;
	if (m1.row != m2.row || m1.column != m2.column || m1.num != m2.num)
		return false;

	for (i = 0; i < m1.num; ++i) {
		if (m1.data[i].x != m2.data[i].x ||
			m1.data[i].y != m2.data[i].y ||
			m1.data[i].value != m2.data[i].value)
			return false;
	}
	return true;
}

Status isSameMatrix(RLSMatrix m1, RLSMatrix m2) {
	return m1.data == m2.data && m2.rowpos == m1.rowpos &&
		m1.num == m2.num && m1.row == m2.row &&
		m1.column == m2.column;
}

Status CopyMatrix(RLSMatrix *result, RLSMatrix matrix) {
	int i;
	RLSMatrix temp;
	if ((!matrix.row && !matrix.column) || !result)
		return ERROR;

	if (isEqualMatrix(*result, matrix) && !isSameMatrix(*result, matrix)) {
		return OK;
	}

	InitMatrix(&temp);
	temp.num = matrix.num;
	temp.column = matrix.column;
	temp.row = matrix.row;
	if (temp.num) {
		temp.rowpos = (int *)malloc(sizeof(int)*matrix.row);
		if (!temp.rowpos)
			return OVERFLOW;

		for (i = 0; i < matrix.row; i++)
			temp.rowpos[i] = matrix.rowpos[i];

		temp.data = (Element *)malloc(sizeof(Element)*matrix.num);
		if (!temp.data)
			return OVERFLOW;

		for (i = 0; i < matrix.num; i++)
			if (SetMData(&temp.data[i], matrix.data[i].x, matrix.data[i].y, matrix.data[i].value) == ERROR)return ERROR;
	}
	else {
		temp.data = NULL;
		temp.rowpos = NULL;
	}
	if (!isSameMatrix(*result, matrix))
		DestroyMatrix(result);
	*result = temp;
	return OK;
}

Status AddMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2) {
	Element *data;
	int num;
	int num1, num2;
	int *rownum;

	if ((!matrix1.row && !matrix1.column) || (!matrix2.row && !matrix2.column))
		return ERROR;
	if (!result)
		return ERROR;
	if (matrix1.row != matrix2.row || matrix1.column != matrix2.column)
		return ERROR;

	if (!isSameMatrix(*result, matrix1) && !isSameMatrix(*result, matrix2))
		DestroyMatrix(result);
	num = 0;
	data = (Element *)malloc(sizeof(Element)*(matrix1.num + matrix2.num));
	if (!data)
		return OVERFLOW;
	rownum = (int *)calloc(matrix1.row, sizeof(int));
	if (!rownum)
		return OVERFLOW;

	num1 = 0;
	num2 = 0;
	while (num1 < matrix1.num && num2 < matrix2.num) {
		if (matrix1.data[num1].x < matrix2.data[num2].x || (matrix1.data[num1].x == matrix2.data[num2].x && matrix1.data[num1].y < matrix2.data[num2].y)) {
			if (SetMData(data + num++, matrix1.data[num1].x, matrix1.data[num1].y, matrix1.data[num1].value) == ERROR)return ERROR;
			rownum[matrix1.data[num1].x - 1]++;
			num1++;
		}
		else if (matrix1.data[num1].x > matrix2.data[num2].x || (matrix1.data[num1].x == matrix2.data[num2].x && matrix1.data[num1].y > matrix2.data[num2].y)) {
			if (SetMData(data + num++, matrix2.data[num2].x, matrix2.data[num2].y, matrix2.data[num2].value) == ERROR)return ERROR;
			rownum[matrix2.data[num2].x - 1]++;
			num2++;
		}
		else {
			if (fabs(matrix1.data[num1].value + matrix2.data[num2].value) > 1e-5) {
				if (SetMData(data + num++, matrix1.data[num1].x, matrix1.data[num1].y, matrix1.data[num1].value + matrix2.data[num2].value) == ERROR)return ERROR;
				rownum[matrix1.data[num1].x - 1]++;
			}
			num1++;
			num2++;
		}
	}
	while (num1 < matrix1.num) {
		if (SetMData(&data[num++], matrix1.data[num1].x, matrix1.data[num1].y, matrix1.data[num1].value) == ERROR)return ERROR;
		rownum[matrix1.data[num1].x - 1]++;
		++num1;
	}
	while (num2 < matrix2.num) {
		if (SetMData(&data[num++], matrix2.data[num2].x, matrix2.data[num2].y, matrix2.data[num2].value) == ERROR)return ERROR;
		rownum[matrix2.data[num2].x - 1]++;
		++num2;
	}
	result->row = matrix1.row;
	result->column = matrix1.column;
	result->num = num;
	if (!num) {
		result->data = NULL;
		result->rowpos = NULL;
		free(data);
	}
	else {
		int i;
		result->data = realloc(data, sizeof(Element)*num);
		result->rowpos = (int *)malloc(sizeof(int)*result->row);
		result->rowpos[0] = 0;
		for (i = 1; i < result->row; i++) {
			result->rowpos[i] = result->rowpos[i - 1] + rownum[i - 1];
		}
	}
	free(rownum);
	return OK;
}

Status SubMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2) {
	RLSMatrix temp;
	Status status;
	InitMatrix(&temp);
	if ((status = CopyMatrix(&temp, matrix2)) != OK)return status;
	if ((status = MatrixTraverse(&temp, minverse)) != OK)return status;
	if ((status = AddMatrix(result, matrix1, temp)) != OK)return status;
	if ((status = DestroyMatrix(&temp)) != OK)return status;
	return OK;
}

Status minverse(double *value) {
	*value *= -1;
	return OK;
}

Status MatrixTraverse(RLSMatrix *matrix, Status(*visit)(double*)) {
	int i;
	if (!matrix || !matrix->row && !matrix->column)return ERROR;
	for (i = 0; i < matrix->num; i++) {
		if (visit(&matrix->data[i].value) == ERROR)return ERROR;
	}
	return OK;
}

Status ScalarMatrix(RLSMatrix *result, RLSMatrix matrix, double num) {
	int i;
	Status status;
	if (!matrix.row && !matrix.column)
		return ERROR;
	if ((status = CopyMatrix(result, matrix)) != OK)return status;
	if (fabs(num) < 1e-6) {
		result->num = 0;
		free(result->data);
		free(result->rowpos);
		result->rowpos = NULL;
		result->data = NULL;
	}
	else
		for (i = 0; i < result->num; ++i)result->data[i].value *= num;
	return OK;
}

Status TransMatrix(RLSMatrix *result, RLSMatrix matrix) {
	// int i, tmp;
	// Status status;
	// if (!matrix.row && !matrix.column)
	// 	return ERROR;

	// if ((status = CopyMatrix(result, matrix)) != OK)
	// 	return status;

	// result->row = matrix.column;
	// result->column = matrix.row;
	// for (i = 0; i < result->num; ++i) {
	// 	tmp = result->data[i].x;
	// 	result->data[i].x = result->data[i].y;
	// 	result->data[i].y = tmp;
	// }
	// return SortMatrix(result);

	// 以上算法比较简单易懂，但下面的算法用到了 rowpos ，效率更高
	int i, index;
	int *temp, *rownum;
	if (!matrix.row && !matrix.column)return ERROR;

	if (!isSameMatrix(*result, matrix))
		DestroyMatrix(result);
	result->column = matrix.row;
	result->row = matrix.column;
	result->num = matrix.num;
	if (result->num) {
		result->data = (Element *)malloc(sizeof(Element)*matrix.num);
		if (!result->data)return OVERFLOW;

		result->rowpos = (int *)malloc(sizeof(int)*result->row);
		if (!result->rowpos)return OVERFLOW;

		rownum = (int *)calloc(result->row, sizeof(int));
		if (!rownum)return OVERFLOW;

		for (i = 0; i < matrix.num; i++)
			rownum[matrix.data[i].y - 1]++;
		result->rowpos[0] = 0;
		for (i = 1; i < result->row; i++)
			result->rowpos[i] = result->rowpos[i - 1] + rownum[i - 1];

		temp = (int *)malloc(sizeof(int)*result->row);
		if (!temp)return OVERFLOW;

		for (i = 0; i < result->row; i++)
			temp[i] = result->rowpos[i];
		for (i = 0; i < matrix.num; i++) {
			index = temp[matrix.data[i].y - 1];
			if (SetMData(&result->data[index], matrix.data[i].y, matrix.data[i].x, matrix.data[i].value) == ERROR)return ERROR;
			++temp[matrix.data[i].y - 1];
		}
		free(temp);
		free(rownum);
	}
	return OK;
}

Status MultMatrix(RLSMatrix *result, RLSMatrix matrix1, RLSMatrix matrix2) {
	int i, k, j, q;
	int num;
	int start1, end1, start2, end2;
	double *temp;//存一行结果的值
	Element *data;

	if ((!matrix1.row && !matrix1.column) || (!matrix2.row && !matrix2.column))return ERROR;
	if (!result)return ERROR;
	if (matrix1.column != matrix2.row)return ERROR;

	if (!isSameMatrix(*result, matrix1) && !isSameMatrix(*result, matrix2))
		DestroyMatrix(result);
	result->row = matrix1.row;
	result->column = matrix2.column;
	result->num = 0;
	result->data = NULL;
	result->rowpos = NULL;
	if (matrix1.num && matrix1.num) {
		result->rowpos = (int *)malloc(sizeof(int)*result->row);
		if (!result->rowpos)
			return OVERFLOW;

		temp = (double *)malloc(sizeof(double)*result->column);
		if (!temp)
			return OVERFLOW;

		data = (Element *)malloc(sizeof(Element) * result->row*result->column);
		if (!data)
			return OVERFLOW;

		num = 0;
		for (i = 0; i < matrix1.row; i++) {
			for (k = 0; k < result->column; k++) // 初始化缓存一行结果的数组为0
				temp[k] = 0;

			start1 = matrix1.rowpos[i];		//记录matrix1中第i行的起始位置start1
			if (i == matrix1.row - 1)		//和结束位置end1
				end1 = matrix1.num;
			else
				end1 = matrix1.rowpos[i + 1];

			result->rowpos[i] = num;

			for (j = start1; j < end1; j++) {
				start2 = matrix2.rowpos[matrix1.data[j].y - 1];	//记录matrix2中某一行
				if (matrix1.data[j].y == matrix2.row)			//的起始位置start2
					end2 = matrix2.num;							//和结束位置end2
				else
					end2 = matrix2.rowpos[matrix1.data[j].y];

				for (q = start2; q < end2; q++)
					temp[matrix2.data[q].y - 1] += matrix1.data[j].value*matrix2.data[q].value;
			}

			for (k = 0; k < result->column; k++)
				if (fabs(temp[k]) > 10e-6)
					if (SetMData(data + num++, i + 1, k + 1, temp[k]) == ERROR)
						return ERROR;
		}
		result->data = (Element *)realloc(data, sizeof(Element)*num);
		if (!data)
			return OVERFLOW;
		result->num = num;
		if (!num) {
			free(result->data);
			free(result->rowpos);
			result->rowpos = NULL;
			result->data = NULL;
		}
		free(temp);
	}
	return OK;
}

Status PowMatrix(RLSMatrix *result, RLSMatrix matrix, int n) {
	int i;
	Status status;
	RLSMatrix temp;
	if (!matrix.row && !matrix.column || !result || n < 0 || matrix.row != matrix.column)
		return ERROR;

	if (!isSameMatrix(*result, matrix))
		DestroyMatrix(result);
	result->num = result->row = result->column = matrix.row;
	result->rowpos = (int *)malloc(sizeof(int)*result->row);
	result->data = (Element *)malloc(sizeof(Element)*result->row);
	for (i = 0; i < result->num; i++) {
		result->rowpos[i] = i;
		if (SetMData(&result->data[i], i + 1, i + 1, 1) == ERROR)return ERROR;
	}

	InitMatrix(&temp);
	for (i = 0; i < n; i++) {
		if ((status = CopyMatrix(&temp, *result)) != OK)return status;
		if ((status = MultMatrix(result, temp, matrix)) != OK)return status;
	}
	DestroyMatrix(&temp);
	return OK;
}
