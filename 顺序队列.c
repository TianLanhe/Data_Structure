#include <stdio.h>
#define MAXQSIZE 100
#define ERROR -1
#define true 1
#define false 0
#define OK 0
#define Status int
typedef int QElemType;
typedef struct queue{
	int front;				//队首
	int rear;				//队尾
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
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR
Status GetHead(SqQueue Q,QElemType *e);
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
Status QueueEmpty(SqQueue Q);
//若队列Q为空队列，则返回true，否则返回false
Status QueueTraverse(SqQueue Q,Status (*visit)(QElemType));
//从队头到队尾依次对队列Q中每个元素调用函数visit(),一旦visit调用失败，则操作失败
Status Print(QElemType e);
//遍历函数的功能函数


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
	if((q->rear+1)%MAXQSIZE==q->front)return ERROR;	//队列已满
	q->base[q->rear]=e;
	q->rear=(q->rear+1)%MAXQSIZE;
	return OK;
}
Status DeQueue(SqQueue *q,QElemType *e){
	if(q->rear==q->front)return ERROR;	//队列已空
	*e=q->base[q->front];
	q->front=(q->front+1)%MAXQSIZE;
	return OK;
}
Status DestroyQueue(SqQueue *q){
	free(q->base);
	q->front=q->rear=0;
	return OK;
}
Status ClearQueue(SqQueue *q){
	q->front=q->rear=0;
	return OK;
}
Status GetHead(SqQueue q,QElemType *e){
	if(q.rear == q.front)return ERROR;		//队列是空的
	*e=q.base[q.front];
	return OK;
}
Status QueueEmpty(SqQueue q){
	return q.front==q.rear?true:false;
}
Status QueueTraverse(SqQueue q,Status (*visit)(QElemType)){
	int i;
	if(q.front == q.rear)return ERROR;
	for(i=q.front;i!=q.rear;i=(i+1)%MAXQSIZE)
		if(visit(q.base[i]) == ERROR)
			return ERROR;
	return OK;
}
Status Print(QElemType e){
	printf("%2d  ",e);
	return OK;
}
int main(){
	SqQueue queue;
	int i,num;
	InitQueue(&queue);
	for(i=0;i<10;i++){
		EnQueue(&queue,i);
	}
	QueueTraverse(queue,Print);
	printf("\n");
	for(i=0;i<3;i++){
		DeQueue(&queue,&num);
	}
	QueueTraverse(queue,Print);
	printf("\n");
	return 0;
}
