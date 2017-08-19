#ifndef STATIC_LINK_LIST_H
#define STATIC_LINK_LIST_H

#include "../DataStructureBase.h"

#define MAXSIZE 100			//静态链表最大长度

typedef struct _element {
	ElemType data;			//数据元素的数据域
	int cur;				//数元素的游标，模拟链表的指针域
}Element;
typedef struct _staticlist {
	Element data[MAXSIZE];	//静态链表数组
	int len; 				//静态链表长度
}Staticlist;

Status InitList(Staticlist *list);
//初始化静态链表list，将未用元素链成备用链表，将staticlist的0号元素作为备用链表的头指针
//将staticlist的最后一号元素作为已用链表的头指针
Status DestroyList(Staticlist *list);
//销毁静态链表list
Status ClearLsit(Staticlist *list);
//将静态链表list置空
Status ListLength(Staticlist list);
//返回静态链表list的长度
Status ListEmpty(Staticlist list);
//若静态链表为空表，则返回true，否则返回false
int StaticAlloc(Staticlist *list);
//从备用链表中取下第一个未用结点，返回其下标
Status StaticFree(Staticlist *list, int cursor);
//将下标为cursor的空闲结点加入备用链表中，若cursor不合法，则返回ERROR
Status GetPriorElem(Staticlist list, ElemType e, ElemType *p);
//取得顺序表list中元素e的前驱存放在p中，若e是第一个元素，则操作失败返回ERROR，否则返回OK
Status GetNextElem(Staticlist list, ElemType e, ElemType *n);
//取得顺序表list中元素e的后继存放在n中，若e是最后一个，则操作失败返回ERROR，否则返回OK
Status ListInsert(Staticlist *list, int position, ElemType e);
//在静态链表list已分配链表的position位置插入数据元素e。若position位置非法或list已满，返回ERROR
Status ListDelete(Staticlist *list, int position, ElemType *e);
//删除静态链表list已分配链表的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status GetElem(Staticlist list, int position, ElemType *e);
//返回静态链表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListTraverse(Staticlist list, Status(*visit)(Element));
//依次对静态链表list的每个元素调用visit()，一旦调用失败，则操作失败
Status Print(Element e);
//遍历函数的功能函数，打印数据元素e的内容

#endif