#include <stdio.h>
#define OK 0
#define ERROR -1
#define Status int
#define MAXSIZE 100			//静态链表最大长度
#define true 1
#define false 0
typedef int ElemType;
typedef struct _element{
	ElemType data;			//数据元素的数据域
	int cur;				//数元素的游标，模拟链表的指针域
}Element;
typedef struct _staticlist{
   Element data[MAXSIZE];	//静态链表数组
   int len; 				//静态链表长度
}Staticlist;

Status InitList(Staticlist *list);
//初始化静态链表list，将未用元素链成备用链表，将staticlist的0号元素作为备用链表的头指针
//将staticlist的最后一号元素作为已用链表的头指针
Status DestroyList(Staticlist *list);
//销毁静态链表list
Status ListLength(Staticlist list);
//返回静态链表list的长度
Status ListEmpty(Staticlist list);
//若静态链表为空表，则返回true，否则返回false
int StaticAlloc(Staticlist *list);
//从备用链表中取下第一个未用结点，返回其下标
Status StaticFree(Staticlist *list,int cursor);
//将下标为cursor的空闲结点加入备用链表中，若cursor不合法，则返回ERROR
Status ListInsert(Staticlist *list,int position,ElemType e);
//在静态链表list已分配链表的position位置插入数据元素e。若position位置非法或list已满，返回ERROR
Status ListDelete(Staticlist *list,int position,ElemType *e);
//删除静态链表list已分配链表的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status GetElem(Staticlist list,int position,ElemType *e);
//返回静态链表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListTraverse(Staticlist list,Status (*visit)(Element));
//依次对静态链表list的每个元素调用visit()，一旦调用失败，则操作失败
Status Print(Element e);
//遍历函数的功能函数，打印数据元素e的内容

Status InitList(Staticlist *list){
	int i;
	if(list == NULL)return ERROR;
	list->len=0;
	for(i=0;i<MAXSIZE;i++)
		list->data[i].cur=i+1;		//将i号元素的游标指向i+1号元素，未用元素指向最后一号元素表示已到链尾
	list->data[MAXSIZE-1].cur=0;	//最后一号元素的游标指向0号元素，表示没有已用元素
	return OK;
}
Status DestroyList(Staticlist *list){
	return InitList(list);
}
Status ListLength(Staticlist list){
	return list.len;
}
Status ListEmpty(Staticlist list){
	return list.len==0?true:false;
}
int StaticAlloc(Staticlist *list){
	int cursor;
	if(list->data[0].cur == MAXSIZE-1)return MAXSIZE-1;	//没有未用元素了，返回MAXSIZE-1
	cursor=list->data[0].cur;
	list->data[0].cur=list->data[cursor].cur;	//取出第一个未用元素，将0号元素指向第二个未用元素
	list->data[cursor].cur=0;
	return cursor;
}
Status StaticFree(Staticlist *list,int cursor){		//默认下标为curosr的节点已从已用链表中取出
	if(cursor<0 || cursor>=MAXSIZE)return ERROR;
	list->data[cursor].cur=list->data[0].cur;		//将它插入未用链表表首
	list->data[0].cur=cursor;
	return OK;
}
Status ListInsert(Staticlist *list,int position,ElemType e){
	int i,count;
	if(list == NULL)return ERROR;
	if(position<0 || position>list->len)return ERROR;	//位置非法则返回ERROR
	i=MAXSIZE-1;
	count=0;
	while(count<position){
		i=list->data[i].cur;							//将已用链表移动到待插入位置
		count++;
	}
	count=StaticAlloc(list);							//取出一个未用结点
	if(count == MAXSIZE-1)return ERROR;
	list->data[count].data=e;
	list->data[count].cur=list->data[i].cur;			//插入已用链表
	list->data[i].cur=count;
	list->len++;
	return OK;
}
Status ListDelete(Staticlist *list,int position,ElemType *e){
	int i,count;
	if(list == NULL)return ERROR;
	if(position<0 || position>=list->len)return ERROR;	//位置非法则返回ERROR
	i=MAXSIZE-1;
	count=0;
	while(count<position){
		i=list->data[i].cur;							//将已用链表移动到待删除位置
		count++;
	}
	count=list->data[i].cur;
	list->data[i].cur=list->data[count].cur;
	*e=list->data[count].data;
	if(StaticFree(list,count) == ERROR)return ERROR;
	list->len--;
	return OK;
}
Status GetElem(Staticlist list,int position,ElemType *e){
	int i,count;
	if(position<0 || position>=list.len)return ERROR;	//位置非法则返回ERROR
	i=MAXSIZE-1;
	count=0;
	while(count<=position){
		i=list.data[i].cur;
		count++;
	}
	*e=list.data[i].data;
	return OK;
}
Status ListTraverse(Staticlist list,Status (*visit)(Element)){
	int i;
	i=MAXSIZE-1;									//末尾元素是已用链表开始的节点
	for(i=list.data[MAXSIZE-1].cur;i != 0;i=list.data[i].cur)
		if(visit(list.data[i]) == ERROR)
			return ERROR;
	return OK;
}
Status Print(Element e){
	printf("%2d  ",e.data);
	return OK;
}
int main(){
	Staticlist list;
	int i;
	InitList(&list);
	ListTraverse(list,Print);
	printf("\n");
	for(i=0;i<10;i++){
		if(ListInsert(&list,i,i) == ERROR)printf("error!\n");
	}
	ListTraverse(list,Print);
	printf("\n");
	if(ListInsert(&list,5,15) == ERROR)printf("error!\n");
	GetElem(list,5,&i);
	printf("%d\n",i);
	return 0;
}
