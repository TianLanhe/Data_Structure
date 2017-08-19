#ifndef LINK_QUEUE_H
#define LINK_QUEUE_H

#include "../linear_list/LinkList.h"

#define LinkQueue LinkList			//重定义链表类型为队列类型
#define QNode Link					//重定义链表节点类型为队列节点类型

#ifndef QData
#define QData ElemType				//重定义节点数据域类型为队列节点的数据域类型
#endif

Status InitQueue(LinkQueue *Q);
//构造一个空队列Q
Status DestroyQueue(LinkQueue *Q);
//销毁队列Q，Q不再存在
Status ClearQueue(LinkQueue *Q);
//将Q清为空队列
Status QueueEmpty(LinkQueue Q);
//若队列Q为空队列，则返回TRUE，否则返回FALSE
int QueueLength(LinkQueue Q);
//返回Q的元素个数，即队列的长度
Status GetQHead(LinkQueue Q, QData *e);
//若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
Status EnQueue(LinkQueue *Q, QData e);
//插入元素e为Q的队尾元素
Status DeQueue(LinkQueue *Q, QData *e);
//若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回FALSE
void PrintQueue(QData data);
//队列遍历函数的功能函数，其功能是打印队列元素的数据值
Status QueueTraverse(LinkQueue Q, void(*visit)(QData));
//从队头到队尾依次对队列Q中每个元素调用函数visit(),一旦visit调用失败，则操作失败

#endif