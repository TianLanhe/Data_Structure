#include "PriorityQueue.h"
#include <stdlib.h>

Status InitQueue(PriorityQueue *q, int(*comparator)(QElemType, QElemType)) {
	if (comparator == NULL || q == NULL)
		return ERROR;
	q->comparator = comparator;
	q->capacity = INITSIZE;
	q->front = q->rear = (QElemType*)malloc(sizeof(QElemType)*INITSIZE);
	if (!q->front)
		return OVERFLOW;
	return OK;
}

Status DestroyQueue(PriorityQueue *q) {
	if (!q)
		return ERROR;
	free(q->front);
	q->front = q->rear = NULL;
	q->comparator = NULL;
	q->capacity = 0;
	return OK;
}

Status ClearQueue(PriorityQueue *q) {
	if (!q)
		return ERROR;
	q->rear = q->front;
	return OK;
}

Status SetComparator(PriorityQueue *q, int(**old_cmp)(QElemType, QElemType), int(*new_cmp)(QElemType, QElemType)) {
	int(*func)(QElemType, QElemType);
	if (new_cmp == NULL)
		return ERROR;

	func = new_cmp;
	if (old_cmp)
		*old_cmp = q->comparator;

	q->comparator = func;
	return UpdateOrder(q);
}

Status UpdateHead(PriorityQueue *q) {
	QElemType *ptr;
	QElemType temp;
	int size, cur, i;

	if (!q || QueueEmpty(*q))
		return ERROR;

	ptr = q->front;
	temp = *ptr;
	size = QueueLength(*q);
	cur = 1;
	for (i = cur * 2; i < size + 1; i *= 2) {
		if (i < size && q->comparator(ptr[i - 1], ptr[i]) > 0)
			++i;

		if (q->comparator(temp, ptr[i - 1]) <= 0)
			break;

		ptr[cur - 1] = ptr[i - 1];
		cur = i;
	}
	ptr[cur - 1] = temp;
	return OK;
}

Status UpdateTail(PriorityQueue *q) {
	QElemType *ptr;
	QElemType temp;
	int cur, parent;

	if (!q || QueueEmpty(*q))
		return ERROR;

	ptr = q->front;
	cur = QueueLength(*q);
	temp = ptr[cur - 1];
	for (parent = cur / 2; parent > 0; parent /= 2) {
		if (q->comparator(ptr[parent - 1], temp) <= 0)
			break;

		ptr[cur - 1] = ptr[parent - 1];
		cur = parent;
	}
	ptr[cur - 1] = temp;
	return OK;
}

Status UpdateOrder(PriorityQueue *q) {
	int i;
	int cur, child;
	int size;
	QElemType *ptr;
	QElemType temp;

	if (!q || QueueEmpty(*q))
		return ERROR;

	ptr = q->front;
	size = QueueLength(*q);
	for (i = size / 2; i > 0; --i) {
		cur = i;
		temp = ptr[cur - 1];
		for (child = cur * 2; child < size + 1; child *= 2) {
			if (child < size &&q->comparator(ptr[child - 1], ptr[child]) > 0)
				++child;

			if (q->comparator(temp, ptr[child - 1]) <= 0)
				break;

			ptr[cur - 1] = ptr[child - 1];
			cur = child;
		}
		ptr[cur - 1] = temp;
	}
	return OK;
}

Status QueueEmpty(PriorityQueue q) {
	return q.front == q.rear;
}

int QueueLength(PriorityQueue q) {
	return q.rear - q.front;
}

Status EnQueue(PriorityQueue *q, QElemType e) {
	if (!q)
		return ERROR;
	if (QueueLength(*q) == q->capacity) {
		q->front = (QElemType*)realloc(q->front, sizeof(QElemType)*(q->capacity + INCREMENT));
		if (!q->front)
			return OVERFLOW;

		q->rear = q->front + q->capacity;
		q->capacity += INCREMENT;
	}
	*(q->rear) = e;
	++(q->rear);

	return UpdateTail(q);
}

Status DeQueue(PriorityQueue *q, QElemType *e) {
	if (!q || !e)
		return ERROR;

	if (QueueEmpty(*q))
		return ERROR;

	*e = *(q->front);
	--(q->rear);
	*(q->front) = *(q->rear);

	return UpdateHead(q);
}

Status GetHead(PriorityQueue q, QElemType *e) {
	if (QueueEmpty(q))
		return ERROR;
	*e = *(q.front);
	return OK;
}

Status QueueTraverse(PriorityQueue q, Status(*visit)(QElemType)) {
	QElemType *ptr;
	Status status;
	for (ptr = q.front; ptr != q.rear; ++ptr)
		if ((status = visit(*ptr)) != OK)
			return status;
	return OK;
}
