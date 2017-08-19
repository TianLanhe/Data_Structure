#ifndef SEQU_QUEUE_H
#define SEQU_QUEUE_H

#include "../DataStructureBase.h"

#ifndef QElemType
#define QElemType ElemType
#endif // !QElemType

#define MAXQSIZE 100

typedef struct queue {
	int front;				//队首
	int rear;				//队尾
	QElemType base[MAXQSIZE];
}SqQueue;

Status InitQueue(SqQueue *q);
//构造一个空队列Q
Status DestroyQueue(SqQueue *Q);
//销毁队列Q，Q不再存在
Status ClearQueue(SqQueue *Q);
//将Q清为空队列
int QueueLength(SqQueue q);
//返回Q的元素个数，即队列的长度
Status EnQueue(SqQueue *q, QElemType e);
//插入元素e为Q的队尾元素
Status DeQueue(SqQueue *q, QElemType *e);
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR
Status GetHead(SqQueue Q, QElemType *e);
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
Status QueueEmpty(SqQueue Q);
//若队列Q为空队列，则返回true，否则返回false
Status QueueTraverse(SqQueue Q, Status(*visit)(QElemType));
//从队头到队尾依次对队列Q中每个元素调用函数visit(),一旦visit调用失败，则操作失败
Status Print(QElemType e);
//遍历函数的功能函数
int NextIndex(int index);
//计算下一个下标

#endif
