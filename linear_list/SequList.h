#ifndef SEQU_LIST_H
#define SEQU_LIST_H

#include "../DataStructureBase.h"

#define INITSIZE 100		//初始容量
#define INCREMENT 10 		//容量增量

typedef struct _sequlist {
	ElemType *data;			//顺序表数组
	int len; 				//顺序表长度
	int capacity;			//顺序表容量
}Sequlist;

Status InitList(Sequlist *list);
//初始化顺序表list
Status DestroyList(Sequlist *list);
//销毁顺序表list
Status ClearLsit(Sequlist *list);
//将顺序表list置为空表
Status ListLength(Sequlist list);
//返回顺序表list的长度
Status ListEmpty(Sequlist list);
//若顺序表为空表，则返回true，否则返回false
Status GetPriorElem(Sequlist list, ElemType e, ElemType *p);
//取得顺序表list中元素e的前驱存放在p中，若e是第一个元素，则操作失败返回ERROR，否则返回OK
Status GetNextElem(Sequlist list, ElemType e, ElemType *n);
//取得顺序表list中元素e的后继存放在n中，若e是最后一个，则操作失败返回ERROR，否则返回OK
Status ListInsert(Sequlist *list, int position, ElemType e);
//在顺序表list的position位置[0,len]插入数据元素e。若position位置非法或list已满，返回ERROR
Status ListDelete(Sequlist *list, int position, ElemType *e);
//删除顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status GetElem(Sequlist list, int position, ElemType *e);
//返回顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListTraverse(Sequlist list, Status(*visit)(ElemType));
//依次对顺序表list的每个元素调用visit()，一旦调用失败，则操作失败
Status Print(ElemType e);
//遍历函数的功能函数，打印数据元素e的内容

#endif