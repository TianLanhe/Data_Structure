#include <stdio.h>
#define MAXQSIZE 100
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
#define Status int
typedef int QElemType;
typedef struct queue{
	int front;
	int rear;
	QElemType *base;
}SqQueue;

Status InitQueue(SqQueue *q);
//构造一个空队列Q
Status DestroyQueue(SqQueue *Q);
//销毁队列Q，Q不再存在
Status ClearQueue(SqQueue *Q);
//将Q清为空队列
int QueueLength(SqQueue q);
//返回Q的元素个数，即队列的长度
Status EnQueue(SqQueue *q,QElemType e);
//插入元素e为Q的队尾元素
Status DeQueue(SqQueue *q,QElemType *e);
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回FALSE
Status GetHead(SqQueue Q,QElemType *e);
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
Status QueueEmpty(SqQueue Q);
//若队列Q为空队列，则返回TRUE，否则返回FALSE
Status QueueTraverse(SqQueue Q,void (*visit)(QElemType));
//从队头到队尾依次对队列Q中每个元素调用函数visit(),一旦visit调用失败，则操作失败

Status InitQueue(SqQueue *q){
	q->base=(QElemType *)malloc(sizeof(QElemType)*MAXQSIZE);
	if(!q->base)return ERROR;
	q->front=q->rear=0;
	return OK;
}
int QueueLength(SqQueue q){
	return (q.rear+MAXQSIZE-q.front)%MAXQSIZE;
}
Status EnQueue(SqQueue *q,QElemType e){
	if((q->rear+1)%MAXQSIZE==q->front)return ERROR;
	q->base[q->rear]=e;
	q->rear=(q->rear+1)%MAXQSIZE;
	return OK;
}
Status DeQueue(SqQueue *q,QElemType *e){
	if(q->rear==q->front)return ERROR;
	*e=q->base[q->front];
	q->front=(q->front+1)%MAXQSIZE;
	return OK;
}
Status DestroyQueue(SqQueue *q){
	if(!free(q->base))return ERROR;
	q->front=q->rear=0;
	return OK;
}
Status ClearQueue(SqQueue *q){
	if(q->rear>=MAXQSIZE||q->front>=MAXQSIZE||q->rear<0||q->front<0)return ERROR;
	else q->front=q->rear=0;
	return OK;
}
Status GetHead(SqQueue q,QElemType *e){
	if(q.rear>=MAXQSIZE||q.front>=MAXQSIZE||q.rear<0||q.front<0)return ERROR;
	*e=q.base[q.front];
	return OK;
}
Status QueueEmpty(SqQueue q){
	if(q.front==q.rear)return TRUE;
	else return FALSE;
}
Status QueueTraverse(SqQueue Q,void (*visit)(QElemType)){
	
}
int main(){
	
	return 0;
}
