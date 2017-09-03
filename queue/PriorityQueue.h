#ifndef PRIORITY_QUEUE_H
#define PRIORITY_QUEUE_H

#include "../DataStructureBase.h"

#define INITSIZE 100		//初始容量
#define INCREMENT 10 		//容量增量

#ifndef QElemType
#define QElemType ElemType
#endif

/*这里为了使数据结构抽象化，适配所有抽象类型，使用一级指针指向元素故这
* 里优先队列维护的数组元素是一级指针，使用两个二级指针维护该数组同时对
* 元素的处理是对外界提供元素指针的接口，函数内处理均将该指针指向的元素
* 拷贝后通过指针链接的形式加入数组，这样可以达到适配所有抽象类型的效果
*/
typedef struct _priority_queue {
	QElemType **front;			//优先队列队首
	QElemType **rear;			//优先队列队尾
	int capacity;				//优先队列容量
	int elemSize;				//指示实际抽象类型的大小
	int(*comparator)(QElemType*, QElemType*);	//用于比较优先队列元素的函数指针
}PriorityQueue;

Status InitQueue(PriorityQueue *q, int elemSize, int(*comparator)(QElemType*, QElemType*));
//构造一个空优先队列Q，传入一个函数指针，用于判断优先队列元素的先后顺序
Status DestroyQueue(PriorityQueue *Q);
//销毁优先队列Q，Q不再存在
Status ClearQueue(PriorityQueue *Q);
//清空优先队列Q
Status SetComparator(PriorityQueue *q, int(**old_cmp)(QElemType*, QElemType*), int(*new_cmp)(QElemType*, QElemType*));
//设置优先队列的比较函数
Status UpdateHead(PriorityQueue *Q);
//调整堆顶元素的位置
Status UpdateTail(PriorityQueue *Q);
//调整最后一个元素在堆中的位置
Status UpdateOrder(PriorityQueue *Q);
//更新优先队列Q的元素顺序
Status QueueEmpty(PriorityQueue Q);
//若优先队列Q为空队列，则返回true，否则返回false
int QueueLength(PriorityQueue q);
//返回Q的元素个数，即优先队列的长度
Status EnQueue(PriorityQueue *q, QElemType *e);
//向优先队列Q插入元素e
Status DeQueue(PriorityQueue *q, QElemType *e);
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回ERROR
Status GetHead(PriorityQueue Q, QElemType *e);
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
Status QueueTraverse(PriorityQueue Q, Status(*visit)(QElemType*));
//从队头到队尾依次对队列Q中每个元素调用函数visit(),一旦visit调用失败，则操作失败

#endif
