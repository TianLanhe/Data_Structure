#include "LinkQueue.h"
#include <stdio.h>
#include <stdlib.h>

Status InitQueue(LinkQueue *Q) {
	if (InitList(Q) == ERROR)return ERROR;
	else return OK;
}
Status DestroyQueue(LinkQueue *Q) {
	if (DestroyList(Q) == ERROR)return ERROR;
	else return OK;
}
Status ClearQueue(LinkQueue *Q) {
	if (ClearList(Q) == ERROR)return ERROR;
	else return OK;
}
Status QueueEmpty(LinkQueue Q) {
	return ListEmpty(Q);
}
int QueueLength(LinkQueue Q) {
	return ListLength(Q);
}
Status EnQueue(LinkQueue *Q, QData e) {
	QNode *t;
	if (MakeNode(&t, e) == ERROR)return ERROR;
	if (Append(Q, t) == ERROR)return ERROR;		//在链表尾插入节点模拟入队列
	return OK;
}
Status GetQHead(LinkQueue Q, QData *e) {
	QNode *t;
	if ((t = GetHead(Q)) == NULL)return ERROR;		//若链表(队列)为空，则GetHead返回NULL
	*e = t->data;
	return OK;
}
Status DeQueue(LinkQueue *Q, QData *e) {
	QNode *t;								//删除链表第一个结点，模拟出队列
	t = Q->head->next;
	if (!t)return ERROR;					//队列为空，无法出队列，返回ERROR
	if (!t->next)Q->tail = Q->head;
	Q->head->next = t->next;
	*e = t->data;
	free(t);
	Q->len--;
	return OK;
}
void PrintQueue(QData data) {
	printf("%d %d  ", (int)data->coef, data->expn);
}
Status QueueTraverse(LinkQueue Q, void(*visit)(QData)) {
	QNode *p;
	for (p = (Q.head)->next; p; p = p->next)visit(p->data);
	return OK;
}