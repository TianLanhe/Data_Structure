#include "LinkStack.h"

Status InitStack(LinkStack *stack) {
	if (InitList(stack) == ERROR)return ERROR;
	return OK;
}
Status DestroyStack(LinkStack *stack) {
	if (DestroyList(stack) == ERROR)return ERROR;
	return OK;
}
Status ClearStack(LinkStack *stack) {
	if (ClearList(stack) == ERROR)return ERROR;
	return OK;
}
Status StackEmpty(LinkStack stack) {
	return ListEmpty(stack);
}
Status GetTop(LinkStack stack, SElemType **e) {
	if (StackEmpty(stack))return ERROR;
	if (!GetHead(stack))return ERROR;
	*e = GetHead(stack);					//若空栈，即空链表，
	return OK;								//则GetLast返回NULL
}
int StackLength(LinkStack stack) {
	return ListLength(stack);
}
Status Push(LinkStack *stack, SElemType *e) {
	if (InsFirst(stack->head, e) == ERROR)return ERROR;//在链表插入一个结点，模拟入栈
	++stack->len;
	return OK;
}
Status Pop(LinkStack *stack, SElemType **e) {
	if (DelFirst(stack->head, e) == ERROR)return ERROR;//在链表删除一个结点，模拟出栈
	--stack->len;
	if (stack->len == 0)
		stack->tail = stack->head;
	return OK;
}
Status StackTraverse(LinkStack stack, void(*visit)(SElemType)) {
	if (StackEmpty(stack))return ERROR;
	SElemType *e;							//这里用了void的，应该用Status比较好
	for (e = (stack.head)->next; e; e = e->next)visit(*e);
	return OK;
}
