#include<stdio.h>
#include<ctype.h>
#include<string.h>
#define STACK_INIT_SIZE 100
#define INCREMENT 10
#define ERROR 0
#define TRUE 1
#define FALSE 0
#define OK 1
#define INFEASIBLE -1
#define OVERFLOW -2
#define Status int
typedef int SElemType;
typedef struct _stack{
	SElemType *bottom;
	SElemType *top;
	int stacksize;
}SqStack;
Status InitStack(SqStack *stack);			    			//构造一个空栈S
Status DestroyStack(SqStack *stack);						//栈S被销毁
Status ClearStack(SqStack *stack);							//将栈清为空栈
Status StackEmpty(SqStack stack);							//若栈为空栈，则返回TRUE，否则返回FALSE
int StackLength(SqStack stack);								//返回S的元素个数，即栈的长度
Status GetTop(SqStack stack,SElemType *e);					//用e返回S的栈顶元素
Status Pop(SqStack *stack,SElemType *e);					//删除S的栈顶元素，并用e返回其值
Status Push(SqStack *stack,SElemType e);					//插入元素e为新的栈顶元素
Status StackTraverse(SqStack stack,void (*visit)(SElemType));//从栈低到栈顶依次对S的每个数据元素调用函数visit(),一旦visit()调用失败，则操作失败
void Conversion(int num,int base);							//将十进制数num转化为base进制的整数
Status BracketMatch(char *str);								//括号匹配
void PrintStr(SElemType e);
void PrintNum(SElemType e);
void LineEdit(char back,char clear);
Status isNum(char ch);
SElemType Calculator(char *str);
int Precede(char ch1,char ch2);
SElemType Operator(char _num1,char operator,char _num2);
Status InitStack(SqStack *stack){
	stack->bottom=(SElemType *)malloc(STACK_INIT_SIZE*sizeof(SElemType));
	if(!stack->bottom)return ERROR;
	stack->top=stack->bottom;
	stack->stacksize=STACK_INIT_SIZE;
	return OK;
}
Status DestroyStack(SqStack *stack){
	if(!stack->bottom)return ERROR;
	free(stack->bottom);
	stack->bottom=stack->top=NULL;
	stack->stacksize=0;
	return OK;
}
Status ClearStack(SqStack *stack){
	if(!stack->bottom)return ERROR;
	stack->top=stack->bottom;
	stack->stacksize=0;
	return OK;
}
Status StackEmpty(SqStack stack){
	if(StackLength(stack))return FALSE;
	else return TRUE;
}
void PrintStr(SElemType e){
	printf("%c",e);
}
void PrintNum(SElemType e){
	printf("%d ",e);
}
Status StackTraverse(SqStack stack,void (*visit)(SElemType)){
	if(stack.top<=stack.bottom)return ERROR;
	SElemType *e;
	for(e=stack.bottom;e<stack.top;e++)visit(*e);
	printf("\n");
	return OK;
}
int StackLength(SqStack stack){
	if(!stack.bottom)return 0;
	int i;
	SElemType *p;
	p=stack.bottom;
	for(i=0;p<stack.top;p++,i++);
	return i;
}
Status GetTop(SqStack stack,SElemType *e){
	if(stack.top<=stack.bottom){
		*e=0;
		return ERROR;
	}
	*e=*(stack.top-1);
	return OK;
}
Status Pop(SqStack *stack,SElemType *e){
	if(stack->top<=stack->bottom)return ERROR;
	stack->top--;
	*e=*stack->top;
	return OK;
}
Status Push(SqStack *stack,SElemType e){
	if(stack->top<stack->bottom)return ERROR;
	if(stack->top-stack->bottom>=stack->stacksize){
		stack->bottom=(SElemType *)realloc(stack->bottom,sizeof(SElemType)*(stack->stacksize+INCREMENT));
		if(!stack->bottom)return ERROR;
		stack->top=stack->bottom+stack->stacksize;
		stack->stacksize+=INCREMENT;
	}
	*stack->top=e;
	stack->top++;
	return OK;
}
void Conversion(int num,int base){
	SqStack stack;
	InitStack(&stack);
	if(!num)printf("0\n");
	while(num){
		Push(&stack,num%base);
		num/=base;
	}
	while(!StackEmpty(stack)){
		Pop(&stack,&num);
		printf("%d",num);
	}
	printf("\n");
	DestroyStack(&stack);
}
Status BracketMatch(char *str){
	SqStack stack;
	int t;
	InitStack(&stack);
	while(*str){
		switch(*str){
			case '[':Push(&stack,1);break;
			case ']':
				if(StackEmpty(stack))return ERROR;
				GetTop(stack,&t);
				if(t==1)Pop(&stack,&t);
				break;
			case '(':Push(&stack,2);break;
			case ')':
				if(StackEmpty(stack))return ERROR;
				GetTop(stack,&t);
				if(t==2)Pop(&stack,&t);
				break;
		}
		str++;
	}
	if(StackEmpty(stack)){
		DestroyStack(&stack);
		return OK;
	}else{
		DestroyStack(&stack);
		return ERROR;
	}
}
void LineEdit(char back,char clear){
	SqStack stack;
	char ch;
	SElemType e;
	InitStack(&stack);
	ch=getchar();
	while(ch!=EOF&&ch!='\n'){
		if(ch==back)Pop(&stack,&e);
		else if(ch==clear)ClearStack(&stack);
		else Push(&stack,ch);
		ch=getchar();
	}
	StackTraverse(stack,PrintStr);
	DestroyStack(&stack);
}
int main(){
	SElemType result;
	result=Operator('2','*','4');
	printf("%c\n",result);
	return 0;
}