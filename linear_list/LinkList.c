#include "LinkList.h"
#include <stdio.h>
#include <stdlib.h>

void _FreeNode(Link **p) {
	if (p&&*p) {
		if ((*p)->data)
			free((*p)->data);
		(*p)->data = NULL;
		free(*p);
		*p = NULL;
	}
}
Status MakeNode(Link **node, ElemType data) {
	if (!node)
		return ERROR;
	*node = (Link*)malloc(sizeof(Link));
	if (!*node)
		return OVERFLOW;
	(*node)->data = data;
	(*node)->next = NULL;
	return OK;
}
Status InitList(LinkList *linklist) {
	if (!linklist)
		return ERROR;
	linklist->tail = linklist->head = (Link *)malloc(sizeof(Link));	//分配虚头节点，链表头和尾均指向头结点表示空链表
	if (!linklist->head)
		return OVERFLOW;
	linklist->head->data = NULL;
	linklist->head->next = NULL;
	linklist->len = 0;
	return OK;
}
Status DestroyList(LinkList *linklist) {
	if (!linklist)
		return ERROR;
	if (ClearList(linklist) == ERROR)
		return ERROR;
	free(linklist->head);
	linklist->len = 0;
	linklist->tail = NULL;
	linklist->head = NULL;
	return OK;
}
Status ClearList(LinkList *linklist) {
	if (!linklist)
		return ERROR;
	Link *pf, *pb;
	pb = linklist->head->next;			//将结点都释放了
	while (pb) {
		pf = pb->next;
		FreeNode(pb);
		pb = pf;
	}
	linklist->len = 0;					//修改长度
	linklist->head->next = NULL;			//修改虚头结点
	linklist->tail = linklist->head;		//修改链尾指针
	return OK;
}
Status InsFirst(Link *head, Link *p) {
	Link *tail;
	if (!p || !head)
		return ERROR;
	for (tail = p; tail->next; tail = tail->next);	//找到p的尾巴
	tail->next = head->next;					//连接
	head->next = p;
	return OK;
}
Status DelFirst(Link *head, Link **p) {
	if (!head || !head->next)
		return ERROR;					//如果是空链表，无法删除，返回ERROR
	*p = head->next;						//取出第一个结点
	head->next = (*p)->next;				//修改指向第二个结点
	(*p)->next = NULL;
	return OK;
}
Status Append(LinkList *linklist, Link *p) {
	Link *t;
	int i;
	if (!p || !linklist)
		return ERROR;
	for (i = 1, t = p; t->next; t = t->next, ++i);	//找到p的尾巴，同时统计结点个数
	linklist->tail->next = p;				//连接
	linklist->tail = t;
	linklist->len += i;
	return OK;
}
Status Remove(LinkList *linklist, Link **p) {
	Link *t;
	if (!linklist || linklist->len == 0)
		return ERROR;
	*p = linklist->tail;
	--linklist->len;
	for (t = linklist->head; t->next != linklist->tail; t = t->next);
	t->next = NULL;
	linklist->tail = t;
	return OK;
}
Status InsBefore(LinkList *linklist, Link **p, Link *h) {
	Link *t;
	if (!linklist || linklist->len == 0 || !h)
		return ERROR;
	for (t = linklist->head; t->next&&t->next != *p; t = t->next);
	if (!t->next)			// p不是链表中的节点
		return ERROR;
	if (InsFirst(t, h) == ERROR)
		return ERROR;
	++linklist->len;
	*p = h;
	return OK;
}
Status InsAfter(LinkList *linklist, Link **p, Link *h) {
	Link *t;
	if (!linklist || linklist->len == 0 || !h)
		return ERROR;
	for (t = linklist->head; t&&t != *p; t = t->next);
	if (!t)						// p不是链表中的节点
		return ERROR;
	++linklist->len;			// 修改长度
	h->next = t->next;			// 修改指针指向
	t->next = h;
	if (t == linklist->tail)		// 如果p是尾节点，还需要修改linklist.tail
		linklist->tail = h;
	return OK;
}
Status LinkListInsert(LinkList *linklist, int position, ElemType e) {
	Link *t;									//只能插入到[0,len)之间的位置，不会改变尾结点
	Link *newnode;
	if (!linklist)
		return ERROR;
	if (position != 0) {
		if (LocatePos(*linklist, position - 1, &t) == ERROR)return ERROR;
	}
	else {
		t = linklist->head;
	}
	if (MakeNode(&newnode, e) == ERROR)return ERROR;
	if (InsFirst(t, newnode) == ERROR)return ERROR;
	linklist->len++;
	return OK;
}
Status SetCurElem(Link *p, ElemType e) {
	if (p == NULL)
		return ERROR;
	p->data = e;
	return OK;
}
ElemType GetCurElem(Link *p) {
	return p ? p->data : NULL;
}
Status ListEmpty(LinkList linklist) {
	return linklist.len ? false : true;
}
int ListLength(LinkList linklist) {
	Link *t;							//不根据linklist.len直接获得
	int i;								//遍历链表并计算节点个数
	for (t = linklist.head, i = 0; t->next; t = t->next, i++);
	return i;
}
Link *GetHead(LinkList linklist) {
	return (linklist.head)->next;		//根据linklist.head直接返回第一个
}
Link *GetLast(LinkList linklist) {
	Link *t; 							//不根据linklist.tail直接获得，通过遍历链表得到最后一个
	if (ListEmpty(linklist) == true)
		return NULL;					//如果是空表，则没有最后一个，返回ERROR
	for (t = linklist.head; t->next; t = t->next); //一直走到头，返回该节点
	return t;
}
Link *PriorPos(LinkList linklist, Link *p) {
	Link *t;
	if (p == linklist.head || p == NULL)return NULL;		//该节点已是首节点，无上一个结点，返回NULL
	for (t = linklist.head; t->next&&t->next != p; t = t->next);	//一直走到p的上一个
	if (!t->next)
		return NULL;						//若没找到下一个是p，即p不是链表中的结点，返回ERROR
	else
		return t;
}
Link *NextPos(LinkList linklist, Link *p) {
	Link *t;
	if (p == NULL)
		return NULL;
	for (t = linklist.head; t&&t != p; t = t->next);	//找到结点p
	if (!t)
		return NULL;						//若没找到结点p返回ERROR
	else
		return t->next;					//否则返回p的下一个节点
}
Status LocatePos(LinkList linklist, int i, Link **p) {
	int count;
	Link *t;
	if (i < 0 || i >= linklist.len)
		return ERROR;		//位置非法返回ERROR
	for (count = 0, t = (linklist.head)->next; count < i&&t; t = t->next, count++);
	if (!t)
		return ERROR;
	*p = t;
	return OK;
}
Status PrintLinkList(Link *p) {
	if (!p)
		return ERROR;
	printf("%d  %f\n", p->data->expn, p->data->coef);
	return OK;
}
Status ListTraverse(LinkList linklist, Status(*visit)(Link*)) {
	Link *p;
	for (p = (linklist.head)->next; p; p = p->next)
		if (visit(p) == ERROR)
			return ERROR;
	return OK;
}