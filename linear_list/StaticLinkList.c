#include "StaticLinkList.h"
#include <stdio.h>

Status InitList(Staticlist *list) {
	int i;
	if (list == NULL)
		return ERROR;
	list->len = 0;
	for (i = 0; i < MAXSIZE; i++)
		list->data[i].cur = i + 1;		//将i号元素的游标指向i+1号元素，未用元素指向最后一号元素表示已到链尾
	list->data[MAXSIZE - 1].cur = 0;	//最后一号元素的游标指向0号元素，表示没有已用元素
	return OK;
}
Status DestroyList(Staticlist *list) {
	return InitList(list);
}
Status ClearLsit(Staticlist *list) {
	return InitList(list);
}
Status ListLength(Staticlist list) {
	return list.len;
}
Status ListEmpty(Staticlist list) {
	return list.len == 0 ? true : false;
}
int StaticAlloc(Staticlist *list) {
	int cursor;
	if (!list)
		return ERROR;
	if (list->data[0].cur == MAXSIZE - 1)		//没有未用元素了，返回MAXSIZE-1
		return MAXSIZE - 1;
	cursor = list->data[0].cur;
	list->data[0].cur = list->data[cursor].cur;	//取出第一个未用元素，将0号元素指向第二个未用元素
	list->data[cursor].cur = 0;
	return cursor;
}
Status StaticFree(Staticlist *list, int cursor) {		//默认下标为curosr的节点已从已用链表中取出
	if (cursor < 0 || cursor >= MAXSIZE || !list)
		return ERROR;
	list->data[cursor].cur = list->data[0].cur;		//将它插入未用链表表首
	list->data[0].cur = cursor;
	return OK;
}
Status GetPriorElem(Staticlist list, ElemType e, ElemType *p) {
	int i = list.data[MAXSIZE - 1].cur;
	while (list.data[i].cur) {
		if (list.data[list.data[i].cur].data == e) {
			*p = list.data[i].data;
			return OK;
		}
		i = list.data[i].cur;
	}
	return ERROR;
}
Status GetNextElem(Staticlist list, ElemType e, ElemType *n) {
	int i = MAXSIZE - 1;
	while (list.data[i].cur) {
		if (list.data[i].data == e) {
			*n = list.data[list.data[i].cur].data;
			return OK;
		}
		i = list.data[i].cur;
	}
	return ERROR;
}
Status ListInsert(Staticlist *list, int position, ElemType e) {
	int i, count;
	if (list == NULL)
		return ERROR;
	if (position<0 || position>list->len)	//位置非法则返回ERROR
		return ERROR;
	i = MAXSIZE - 1;
	count = 0;
	while (count < position) {
		i = list->data[i].cur;				//将已用链表移动到待插入位置
		count++;
	}
	count = StaticAlloc(list);				//取出一个未用结点
	if (count == MAXSIZE - 1)
		return ERROR;
	list->data[count].data = e;
	list->data[count].cur = list->data[i].cur;//插入已用链表
	list->data[i].cur = count;
	list->len++;
	return OK;
}
Status ListDelete(Staticlist *list, int position, ElemType *e) {
	int i, count;
	if (list == NULL)
		return ERROR;
	if (position < 0 || position >= list->len)	//位置非法则返回ERROR
		return ERROR;
	i = MAXSIZE - 1;
	count = 0;
	while (count < position) {
		i = list->data[i].cur;							//将已用链表移动到待删除位置
		count++;
	}
	count = list->data[i].cur;
	list->data[i].cur = list->data[count].cur;
	*e = list->data[count].data;
	if (StaticFree(list, count) == ERROR)return ERROR;
	list->len--;
	return OK;
}
Status GetElem(Staticlist list, int position, ElemType *e) {
	int i, count;
	if (position < 0 || position >= list.len)
		return ERROR;
	i = MAXSIZE - 1;
	count = 0;
	while (count <= position) {
		i = list.data[i].cur;
		count++;
	}
	*e = list.data[i].data;
	return OK;
}
Status ListTraverse(Staticlist list, Status(*visit)(Element)) {
	int i;
	i = MAXSIZE - 1;									//末尾元素是已用链表开始的节点
	for (i = list.data[MAXSIZE - 1].cur; i != 0; i = list.data[i].cur)
		if (visit(list.data[i]) == ERROR)
			return ERROR;
	return OK;
}
Status Print(Element e) {
	printf("%2d  ", e.data);
	return OK;
}
