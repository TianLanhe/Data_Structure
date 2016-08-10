#include <stdio.h>
#define ERROR -1
#define true 1
#define false 0
#define OK 0
#define Status int
#define MAXSIZE 100
typedef int SElemType;
typedef struct _stack{
	SElemType data[MAXSIZE];
	int top;
}SqStack;
Status InitStack(SqStack *stack);
//构造一个空栈S
Status DestroyStack(SqStack *stack);
//栈S被销毁
Status StackEmpty(SqStack stack);
//若栈为空栈，则返回true，否则返回false
int StackLength(SqStack stack);
//返回S的元素个数，即栈的长度
Status GetTop(SqStack stack,SElemType *e);
//用e返回S的栈顶元素,若是空栈，则返回ERROR
Status Pop(SqStack *stack,SElemType *e);
//删除S的栈顶元素，并用e返回其值,若是空栈则返回ERROR
Status Push(SqStack *stack,SElemType e);
//插入元素e为新的栈顶元素，若栈已满，则返回ERROR
Status StackTraverse(SqStack stack,Status (*visit)(SElemType));
//从栈低到栈顶依次对S的每个数据元素调用函数visit(),一旦visit()调用失败，则操作失败


void Conversion(int num,int base);
//将十进制数num转化为base进制数
Status BracketMatch(char *str);
//括号匹配(只能匹配小括号和中括号)，括号合法返回ERROR,不合法返回ERROR
Status PrintStr(SElemType e);
//遍历函数的功能函数，打印字符
Status PrintNum(SElemType e);
//遍历函数的功能函数，打印整数
void LineEdit(char back,char clear);
//行编辑
void rpn2result(char *rpn,int len);
//根据逆波兰序列计算结果
Status Caculate(char *str,int len);
//利用栈进行四则运算，只允许一位数字进行加减乘除和括号的四则运算
int GetPriority(char ch);
//计算优先级，( < +、- < *、/

Status InitStack(SqStack *stack){
	stack->top=-1;
	return OK;
}
Status DestroyStack(SqStack *stack){
	return InitStack(stack);
}
Status StackEmpty(SqStack stack){
	return stack.top==-1?true:false;
}
int StackLength(SqStack stack){
	return stack.top+1;
}
Status GetTop(SqStack stack,SElemType *e){
	if(stack.top == -1)return ERROR;	//空栈则返回ERROR
	*e=stack.data[stack.top];
	return OK;
}
Status PrintStr(SElemType e){
	printf("%c",e);
	return OK;
}
Status PrintNum(SElemType e){
	printf("%d ",e);
	return OK;
}
Status StackTraverse(SqStack stack,Status (*visit)(SElemType)){
	int i;
	if(stack.top == -1)return ERROR;	//空栈则返回ERROR	
	for(i=0;i<=stack.top;i++)			//从栈底到栈顶依次遍历每个元素
		if(visit(stack.data[i]) == ERROR)
			return ERROR;
	return OK;
}
Status Pop(SqStack *stack,SElemType *e){
	if(stack->top == -1)return ERROR;	//空栈则返回ERROR
	*e=stack->data[stack->top];
	stack->top--;
	return OK;
}
Status Push(SqStack *stack,SElemType e){
	if(stack->top == MAXSIZE-1)return ERROR;	//栈满则返回ERROR
	stack->top++;
	stack->data[stack->top]=e;
	return OK;
}
void Conversion(int num,int base){
	SqStack stack;
	int i;
	int basenum[100];
	InitStack(&stack);
	for(i=0;i<base;i++){			//因为超过十进制就要用ABCD了
		if(i<10)basenum[i]='0'+i;	//所以用一个数组储存一张表，该表是该进制所用的符号集合
		else basenum[i]='A'+i-10;
	}
	if(num == 0)printf("0\n");
	while(num){
		Push(&stack,basenum[num%base]);	//把该进制所用的符号入栈，低数位先入栈，高位后入栈
		num/=base;
	}
	while(!StackEmpty(stack)){
		Pop(&stack,&num);			//出栈并打印
		printf("%c",num);
	}
	printf("\n");
	DestroyStack(&stack);
}
Status BracketMatch(char *str){
	SqStack stack;
	SElemType t;
	InitStack(&stack);
	while(*str){
		switch(*str){
			case '[':Push(&stack,1);break;
			case ']':if(StackEmpty(stack))return ERROR;
					 GetTop(stack,&t);
					 if(t==1)Pop(&stack,&t);
					 break;
			case '(':Push(&stack,2);break;
			case ')':if(StackEmpty(stack))return ERROR;
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
		else if(ch==clear)DestroyStack(&stack);
		else Push(&stack,ch);
		ch=getchar();
	}
	StackTraverse(stack,PrintStr);
	DestroyStack(&stack);
}
void rpn2result(char *rpn,int len){
	SqStack stack;
	int i;
	int num1,num2,result;
	InitStack(&stack);
	for(i=0;i<len;i++){
		if(rpn[i]<='9' && rpn[i]>='0')Push(&stack,rpn[i]-48);	//遇到数字则入栈
		else{
			Pop(&stack,&num2);
			Pop(&stack,&num1);					//遇到符号则将栈顶两个元素取出进行计算
			switch(rpn[i]){
				case '+':result=num1+num2;break;
				case '-':result=num1-num2;break;
				case '*':result=num1*num2;break;
				case '/':result=num1/num2;break;
			}
			Push(&stack,result);				//将计算后的结果入栈
		}
	}
	Pop(&stack,&result);						//所有计算过后，栈内应该只有一个元素，即最终结果
	if(!StackEmpty(stack))return ;
	printf("%d\n",result);						//打印结果
}
int GetPriority(char ch){
	switch(ch){
		case '(':return 0;
		case '+':
		case '-':return 1;
		case '*':
		case '/':return 2;
	}
}
Status Caculate(char *str,int len){
	SqStack stack;
	char rpn[100];
	int i,count;
	int top;
	if(BracketMatch(str) == ERROR)return ERROR;
	InitStack(&stack);
	count=0;
	for(i=0;i<len;i++){								//由中缀表达式转化为后缀表达式
		if(str[i]>='0' && str[i]<='9')rpn[count++]=str[i];	//遇到数字则输出
		else if(str[i] == '(')Push(&stack,str[i]);			//左括号入栈
		else if(str[i] == ')'){								//右括号则将左右括号之间的所有符号出栈
			if(GetTop(stack,&top) == ERROR)return ERROR;
			while(top != '('){
				if(Pop(&stack,&top) == ERROR)return ERROR;
				rpn[count++]=top;
				if(GetTop(stack,&top) == ERROR)return ERROR;
			}
			if(Pop(&stack,&top) == ERROR)return ERROR;
		}else{
			int priority1,priority2;
			priority1=GetPriority(str[i]);
			if(!StackEmpty(stack)){
				if(GetTop(stack,&top) == ERROR)return ERROR;
				priority2=GetPriority((char)top);
				while(priority1 <= priority2){
					if(Pop(&stack,&top) == ERROR)return ERROR;
					rpn[count++]=top;
					if(StackEmpty(stack))break;
					if(GetTop(stack,&top) == ERROR)return ERROR;
					priority2=GetPriority((char)top);
				}
			}
			Push(&stack,str[i]);
		}
	}
	while(!StackEmpty(stack)){
		Pop(&stack,&top);
		rpn[count++]=top;
	}
	rpn[count]='\0';
	rpn2result(rpn,count);			//将所得的后缀表达式进行计算得到最终结果
}
int main(){
	SElemType result;
	Caculate("3*(4+6-5)/(7-4)",15);
	return 0;
}
