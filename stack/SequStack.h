#ifndef SEQU_STACK_H
#define SEQU_STACK_H

#include "../DataStructureBase.h"

#ifndef SElemType
#define SElemType ElemType
#endif // !SElemType

#define INITSIZE 100		//初始容量
#define INCREMENT 10 		//容量增量

typedef struct _stack {
	SElemType *base;		//栈底
	SElemType *top;			//栈顶
	int capacity;			//栈容量
}SqStack;

Status InitStack(SqStack *stack);
//构造一个空栈S
Status DestroyStack(SqStack *stack);
//栈S被销毁
Status ClearStack(SqStack *stack);
//将栈stack置为空栈
Status StackEmpty(SqStack stack);
//若栈为空栈，则返回true，否则返回false
int StackLength(SqStack stack);
//返回S的元素个数，即栈的长度
Status GetTop(SqStack stack, SElemType *e);
//用e返回S的栈顶元素,若是空栈，则返回ERROR
Status Pop(SqStack *stack, SElemType *e);
//删除S的栈顶元素，并用e返回其值,若是空栈则返回ERROR
Status Push(SqStack *stack, SElemType e);
//插入元素e为新的栈顶元素，若栈已满，则返回ERROR
Status StackTraverse(SqStack stack, Status(*visit)(SElemType));
//从栈低到栈顶依次对S的每个数据元素调用函数visit(),一旦visit()调用失败，则操作失败

#endif