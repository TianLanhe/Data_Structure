#ifndef LINK_LIST_H
#define LINK_LIST_H

#include "../DataStructureBase.h"
#undef ElemType

#define FreeNode(p) _FreeNode(&(p))	//传入一级指针即可

typedef struct _elemtype{			//节点数据域类型
	double coef;				   	//系数
	int expn;						//指数
}*ElemType;

typedef struct LNode {				//节点类型
	ElemType data;
	struct LNode *next;
}Link;

typedef struct _linklist {			//链表类型
	Link *head;
	Link *tail;
	int len;
}LinkList;

void _FreeNode(Link **p);
//释放p所指节点
Status MakeNode(Link **p, ElemType data);
//分配由p指向的值为e的结点，并返回OK；若分配失败，则返回ERROR
Status InitList(LinkList *linklist);
//构造一个空的线性链表linklist
Status DestroyList(LinkList *linklist);
//销毁线性链表linklist，linklist不再存在
Status ClearList(LinkList *linklist);
//将线性链表linklist重置为空表，并释放原链表的结点空间
Status InsFirst(Link *head, Link *p);
//已知head指向线性链表的头结点，将p所指的一个(串)结点插入在第一个结点之前
Status DelFirst(Link *head, Link **p);
//已知head指向线性链表的头结点，删除链表中的第一个结点并以q返回
Status Append(LinkList *linklist, Link *p);
//将指针p所指（彼此以指针相链）的一串结点链接在线性链表linklist的最后一个节点
//之后，并改变链表linklist的尾指针指向新的尾结点
Status Remove(LinkList *linklist, Link **p);
//删除线性链表的尾结点并以p返回，改变链表linklist的尾指针指向新的尾结点
Status InsBefore(LinkList *linklist, Link **p, Link *h);
//已知p指向线性链表中的一个结点，将h所指结点插入在p所指结点之前，
//并修改指针p指向新插入的节点
Status InsAfter(LinkList *linklist, Link **p, Link *h);
//已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之后，
//并修改指针p指向新插入的节点
Status LinkListInsert(LinkList *linklist, int position, ElemType e);
//在带结点的线性链表linklist的第i个元素之前插入元素e
Status SetCurElem(Link *p, ElemType e);
//已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
ElemType GetCurElem(Link *p);
//已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
Status ListEmpty(LinkList linklist);
//若线性链表为空表，则返回TRUE，否则返回FALSE
int ListLength(LinkList linklist);
//返回线性链表linklist的元素个数
Link *GetHead(LinkList linklist);
//返回线性链表linklist头结点
Link *GetLast(LinkList linklist);
//返回线性链表linklist尾结点
Link *PriorPos(LinkList linklist, Link *p);
//已知p指向线性链表的一个结点，返回p所指结点的直接前驱的位置
//若无前驱，则返回NULL
Link *NextPos(LinkList linklist, Link *p);
//已知p指向线性链表的一个结点，返回p所指结点的直接后继的位置
//若无后继，则返回NULL
Status LocatePos(LinkList linklist, int i, Link **p);
//返回p指示线性链表linklist中第i个结点的位置并返回OK，i值不合法时返回ERROR
Status PrintLinkList(Link *p);
//遍历函数用的功能函数，其功能是打印节点p中的数据域各项成员
Status ListTraverse(LinkList linklist, Status(*visit)(Link*));
//依次对linklist的每个元素调用visit()，一旦调用失败，则操作失败

#endif