#include <stdio.h>
#define OK 0
#define ERROR -1
#define Status int
#define MAXSIZE 100			//顺序表最大长度
#define true 1
#define false 0
typedef int ElemType;
typedef struct _sequlist{
   ElemType data[MAXSIZE];	//顺序表数组
   int len; 				//顺序表长度
}Sequlist;

Status InitList(Sequlist *list);
//初始化顺序表list
Status DestroyList(Sequlist *list);
//销毁顺序表list
Status ListLength(Sequlist list);
//返回顺序表list的长度
Status ListEmpty(Sequlist list);
//若顺序表为空表，则返回true，否则返回false
Status ListInsert(Sequlist *list,int position,ElemType e);
//在顺序表list的position位置[0,len-1]插入数据元素e。若position位置非法或list已满，返回ERROR
Status ListDelete(Sequlist *list,int position,ElemType *e);
//删除顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status GetElem(Sequlist list,int position,ElemType *e);
//返回顺序表list的position位置上的数据元素，储存在e中，若position位置非法返回ERROR
Status ListTraverse(Sequlist list,Status (*visit)(ElemType));
//依次对顺序表list的每个元素调用visit()，一旦调用失败，则操作失败
Status Print(ElemType e);
//遍历函数的功能函数，打印数据元素e的内容

Status InitList(Sequlist *list){
	if(list == NULL)return ERROR;
	list->len=0;
	return OK;
}
Status DestroyList(Sequlist *list){
	return InitList(list);
}
Status ListLength(Sequlist list){
	return list.len;
}
Status ListEmpty(Sequlist list){
	return list.len==0?true:false;
}
Status ListInsert(Sequlist *list,int position,ElemType e){
	int i;
	if(list ==NULL)return ERROR;
	if(position<0 || position>list->len)return ERROR;	//判断position是否合法
	if(list->len == MAXSIZE)return ERROR;				//判断顺序表是否已满
	for(i=list->len-1;i>=position;i--){					//将position及其以后的元素向后移动一位
		list->data[i+1]=list->data[i];
	}
	list->data[position]=e;								//插入新的元素，长度增加
	list->len++;
	return OK;
}
Status ListDelete(Sequlist *list,int position,ElemType *e){
	int i;
	if(list == NULL)return ERROR;
	if(position<0 || position>=list->len)return ERROR;	//判断position是否合法
	*e=list->data[position];							//取出待删除元素
	for(i=position+1;i<list->len;i++){					//将position以后的元素(不包括position)向前移动一位
		list->data[i-1]=list->data[i];
	}
	list->len--;
	return OK;
}
Status GetElem(Sequlist list,int position,ElemType *e){
	if(position<0 || position>=list.len)return ERROR;
	*e=list.data[position];
	return OK;
}
Status ListTraverse(Sequlist list,Status (*visit)(ElemType)){
	int i;
	for(i=0;i<list.len;i++)
		if(visit(list.data[i]) == ERROR)
			return ERROR;
	return OK;
}
Status Print(ElemType e){
	printf("%2d  ",e);
	return OK;
}
int main(){
	Sequlist list;
	int i;
	InitList(&list);
	for(i=0;i<10;i++)
		ListInsert(&list,i,i);
	ListTraverse(list,Print);
	printf("\n");
	ListInsert(&list,5,15);
	printf("%d\n",ListLength(list));
	ListTraverse(list,Print);
	printf("\n");
	ListDelete(&list,0,&i);
	ListDelete(&list,5,&i);
	printf("%d\n",ListLength(list));
	ListTraverse(list,Print);
	printf("\n");
	return 0;
}
