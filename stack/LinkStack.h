#ifndef LINK_STACK_H
#define LINK_STACK_H value

#include "../linear_list/LinkList.h"

#define LinkStack LinkList			//重定义链表类型为栈类型
#define SElemType Link				//重定义节点类型为栈节点类型

#ifndef SData
#define SData ElemType				//重定义节点数据域类型为栈节点的数据域类型
#endif

//链栈的基本操作：
Status InitStack(LinkStack *stack);
//构造一个空栈stack
Status DestroyStack(LinkStack *stack);
//销毁栈stack，栈stack不再存在
Status ClearStack(LinkStack *stack);
//将栈stack置为空栈，并释放原链表的结点空间
Status StackEmpty(LinkStack stack);
//若栈stack为空栈，则返回TRUE，否则返回FALSE
int StackLength(LinkStack stack);
//返回栈stack的节点个数，即栈的长度
Status GetTop(LinkStack stack, SElemType **e);
//用e返回栈Stack的栈顶节点
Status Pop(LinkStack *stack, SElemType **e);
//删除栈stack的栈顶节点，并用e返回其值
Status Push(LinkStack *stack, SElemType *e);
//插入节点为e为新的栈顶节点
Status StackTraverse(LinkStack stack, void(*visit)(SElemType));
//从栈低到栈顶依次对S的每个数据元素调用函数visit(),一旦visit()调用失败，则操作失败

#endif