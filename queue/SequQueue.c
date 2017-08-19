#include <stdio.h>
#include "SequQueue.h"

Status InitQueue(SqQueue *q) {
	if (!q)
		return ERROR;
	q->front = q->rear = 0;
	return OK;
}

Status DestroyQueue(SqQueue *q) {
	return InitQueue(q);
}

Status ClearQueue(SqQueue *q) {
	return InitQueue(q);
}

Status QueueEmpty(SqQueue q) {
	return q.front == q.rear ? true : false;
}

int QueueLength(SqQueue q) {
	return (q.rear + MAXQSIZE - q.front) % MAXQSIZE;
}

Status EnQueue(SqQueue *q, QElemType e) {
	if (!q)
		return ERROR;
	if (NextIndex(q->rear) == q->front)	//队列已满
		return ERROR;
	q->base[q->rear] = e;
	q->rear = NextIndex(q->rear);
	return OK;
}

Status DeQueue(SqQueue *q, QElemType *e) {
	if (!q || !e)
		return ERROR;
	if (q->rear == q->front)	//队列已空
		return ERROR;
	*e = q->base[q->front];
	q->front = NextIndex(q->front);
	return OK;
}

Status GetHead(SqQueue q, QElemType *e) {
	if (q.rear == q.front)		//队列是空的
		return ERROR;
	*e = q.base[q.front];
	return OK;
}

Status QueueTraverse(SqQueue q, Status(*visit)(QElemType)) {
	int i;
	if (q.front == q.rear)return ERROR;
	for (i = q.front; i != q.rear; i = NextIndex(i))
		if (visit(q.base[i]) == ERROR)
			return ERROR;
	return OK;
}

Status Print(QElemType e) {
	printf("%2d  ", e);
	return OK;
}

int NextIndex(int index) {
	return (index + 1) % MAXQSIZE;
}
