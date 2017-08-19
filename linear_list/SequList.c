#include <stdio.h>
#include <stdlib.h>
#include "SequList.h"

Status InitList(Sequlist *list) {
	if (!list)
		return ERROR;
	list->data = (ElemType*)malloc(sizeof(ElemType)*INITSIZE);
	if (!list->data)
		return OVERFLOW;
	list->len = 0;
	list->capacity = INITSIZE;
	return OK;
}
Status DestroyList(Sequlist *list) {
	if (!list)
		return ERROR;
	free(list->data);
	list->data = NULL;
	list->len = list->capacity = 0;
	return OK;
}
Status ClearLsit(Sequlist *list) {
	if (!list)
		return ERROR;
	list->len = 0;
	return OK;
}
Status ListLength(Sequlist list) {
	return list.len;
}
Status ListEmpty(Sequlist list) {
	return list.len == 0 ? true : false;
}
Status GetPriorElem(Sequlist list, ElemType e, ElemType *p) {
	int i;
	for (i = 1; i < list.len; ++i) {
		if (list.data[i] == e) {
			*p = list.data[i - 1];
			return OK;
		}
	}
	return ERROR;
}
Status GetNextElem(Sequlist list, ElemType e, ElemType *n) {
	int i;
	for (i = 0; i < list.len - 1; ++i) {
		if (list.data[i] == e) {
			*n = list.data[i + 1];
			return OK;
		}
	}
	return ERROR;
}
Status ListInsert(Sequlist *list, int position, ElemType e) {
	int i;
	if (list == NULL)
		return ERROR;
	if (position<0 || position>list->len)		//判断position是否合法
		return ERROR;
	if (list->len == list->capacity) {			//判断顺序表是否已满，若空间不足则拓展空间
		ElemType* new_base = (ElemType*)realloc(list->data, sizeof(ElemType)*(list->capacity + INCREMENT));
		if (!new_base)
			return OVERFLOW;
		list->data = new_base;
		list->capacity += INCREMENT;
	}
	for (i = list->len - 1; i >= position; i--) {			//将position及其以后的元素向后移动一位
		list->data[i + 1] = list->data[i];
	}
	list->data[position] = e;						//插入新的元素，长度增加
	++list->len;
	return OK;
}
Status ListDelete(Sequlist *list, int position, ElemType *e) {
	int i;
	if (list == NULL)
		return ERROR;
	if (position < 0 || position >= list->len)		//判断position是否合法
		return ERROR;
	*e = list->data[position];					//取出待删除元素
	for (i = position + 1; i < list->len; i++) {			//将position以后的元素向前移动一位
		list->data[i - 1] = list->data[i];
	}
	--list->len;
	return OK;
}
Status GetElem(Sequlist list, int position, ElemType *e) {
	if (position < 0 || position >= list.len)
		return ERROR;
	*e = list.data[position];
	return OK;
}
Status ListTraverse(Sequlist list, Status(*visit)(ElemType)) {
	int i;
	for (i = 0; i < list.len; i++)
		if (visit(list.data[i]) == ERROR)
			return ERROR;
	return OK;
}
Status Print(ElemType e) {
	printf("%2d  ", e);
	return OK;
}
