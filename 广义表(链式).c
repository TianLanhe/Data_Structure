#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define AtomType int
#define OK 1
#define ERROR 0
#define Status int
#define TRUE 1
#define FALSE 0
typedef enum _tag{
	ATOM,
	LIST
}ElemTag;
typedef struct _genenode{
	ElemTag tag;
	union {
		AtomType atom;
		struct _genenode *hp;
	};
	struct _genenode *next;
}GLNode;
Status RemBracket(char **substr,char *str);
//删除（广义表书写形式）字符串外面的括号
Status SplitStr(char ***arrstr,char *str,int *len);
//将字符串str以逗号为分隔符分为若干个子串，存在arrstr字符串数组里，并将子串的个数储存在len中
Status InitGList(GLNode **glist);
//初始化广义表glist，设定其为LIST，表头指针和后继指针均为空
Status DestroyGList(GLNode **glist);
//销毁广义表glist
Status CreateGList(GLNode **glist,char *str);
//str是广义表的书写形式串，由str创建广义表
Status CopyGList(GLNode **newglist,GLNode *glist);
//由广义表glist复制得到newglist
int GListLength(GLNode *glist);
//求广义表glist的长度，即元素个数
int GListDepth(GLNode *glist);
//求广义表glist的深度，即广义表括弧的重数
Status GListEmpty(GLNode *glist);
//判断广义表是否为空表，是则返回TRUE,否则返回FALSE
GLNode *GetGLHead(GLNode *glist);
//取广义表glist的表头
GLNode *GetGLTail(GLNode *glist);
//取广义表glist的表尾
Status InsetFirst_GL(GLNode **glist,GLNode *node);
//插入元素node作为广义表glist的第一元素
Status DeleteFirst_GL(GLNode **glist,GLNode **node);
//删除广义表glist的第一元素，并用node返回其值
Status PrintGList(GLNode *glist);
//打印广义表的书写形式字符串
Status Add(GLNode *node);
//遍历广义表的功能函数，将每个原子的atom值加一
Status TraverseGList(GLNode *glist,Status (*visit)(GLNode *));
//遍历广义表glist，用函数visit处理每个元素
Status InitGList(GLNode **glist){
	*glist=(GLNode *)malloc(sizeof(GLNode));
	if(!(*glist))return ERROR;
	(*glist)->tag=LIST;
	(*glist)->hp=NULL;
	(*glist)->next=NULL;
	return OK;
}
Status DestroyGList(GLNode **glist){
	if((*glist)->tag==LIST&&!(*glist)->hp||(*glist)->tag==ATOM){
		free(*glist);
		*glist=NULL;
	}else{
		int length;
		GLNode *node;
		GLNode *temp;
		length=GListLength(*glist);
		node=(*glist)->hp;
		while(node){
			temp=node->next;
			DestroyGList(&node);
			node=temp;
		}
		free(*glist);
		*glist=NULL;
	}
	return OK;
}
Status RemBracket(char **substr,char *str){
	int len;
	int i,num;
	len=strlen(str);
	if(str[0]!='('||str[len-1]!=')')return ERROR;
	(*substr)=(char *)malloc(sizeof(char)*len-1);
	if(!(*substr))return ERROR;
	for(i=1,num=0;i<len-1;i++)(*substr)[num++]=str[i];
	(*substr)[num]='\0';
	return OK;
}
Status SplitStr(char ***arrstr,char *str,int *len){
	int i,k,num;
	int *pos;
	int start,end;
	int count;
	pos=(int *)malloc(sizeof(int)*1000);
	if(!pos)return ERROR;
	for(i=0,k=0,num=0;str[i];i++){
		if(str[i]=='(')k++;
		else if(str[i]==')')k--;
		else if(str[i]==','&&!k)pos[num++]=i;
	}
	*len=num+1;
	(*arrstr)=(char **)malloc(sizeof(char*)*(1+num));
	if(!(*arrstr))return ERROR;
	for(i=0;i<num+1;i++){
		if(!i)start=0;
		else start=pos[i-1]+1;
		if(i!=num)end=pos[i];
		else end=strlen(str);
		(*arrstr)[i]=(char *)malloc(sizeof(char)*(end-start+1));
		if(!(*arrstr)[i])return ERROR;
		count=0;
		for(k=start;k<end;k++){
			(*(*arrstr+i))[count++]=str[k];
		}
		(*(*arrstr+i))[count]='\0';
	}
	free(pos);
	return OK;
}
Status CreateGList(GLNode **glist,char *str){
	InitGList(glist);
	if(strlen(str)==1){
		(*glist)->tag=ATOM;
		(*glist)->atom=*str;
		(*glist)->next=NULL;
	}else if(strcmp(str,"()")){
		char *substr;
		char **splitstr;
		int n,i;
		GLNode *temp;
		GLNode *p;
		if(!RemBracket(&substr,str))return ERROR;
		if(!SplitStr(&splitstr,substr,&n))return ERROR;
		for(i=0,p=*glist;i<n;i++){
			CreateGList(&temp,splitstr[i]);
			if(!i){
				p->hp=temp;
				p=p->hp;
			}else{
				p->next=temp;
				p=p->next;
			}
		}
		for(i=0;i<n;i++)free(splitstr[i]);
		free(splitstr);
	}
	return OK;
}
Status PrintGList(GLNode *glist){
	if(glist->tag==ATOM)printf("%c",glist->atom);
	else if(!glist->hp)printf("()");
	else if(glist->tag==LIST){
		GLNode *node;
		printf("(");
		for(node=glist->hp;node;node=node->next){
			PrintGList(node);
			if(node->next)printf(",");
		}
		printf(")");
	}
	return OK;
}
Status CopyGList(GLNode **newglist,GLNode *glist){
	InitGList(newglist);
	if(glist->tag==ATOM){
		(*newglist)->tag=ATOM;
		(*newglist)->atom=glist->atom;
		(*newglist)->next=NULL;
	}else if(glist->tag==LIST&&glist->hp){
		GLNode *node;
		GLNode *newnode;
		GLNode *p;
		for(node=glist->hp,p=*newglist;node;node=node->next){
			CopyGList(&newnode,node);
			if(node==glist->hp){
				p->hp=newnode;
				p=p->hp;
			}else{
				p->next=newnode;
				p=p->next;
			}
		}
	}
	return OK;
}
int GListLength(GLNode *glist){
	int i;
	if(!glist||!glist->hp)return 0;
	for(glist=glist->hp,i=0;glist;glist=glist->next,i++);
	return i;
}
Status GListEmpty(GLNode *glist){
	if(!glist||!glist->hp)return TRUE;
	else return FALSE;
}
GLNode *GetGLHead(GLNode *glist){
	if(!glist||!glist->hp)return ERROR;
	return glist->hp;
}
GLNode *GetGLTail(GLNode *glist){
	if(!glist||!glist->hp)return ERROR;
	return glist->hp->next;
}
int GListDepth(GLNode *glist){
	if(glist->tag==LIST&&!glist->hp)return 1;
	else if(glist->tag==ATOM)return 0;
	else{
		int length;
		int max;
		GLNode *node;
		length=GListLength(glist);
		for(node=GetGLHead(glist),max=0;node;node=node->next){
			if(max<GListDepth(node))max=GListDepth(node);
		}
		return max+1; 
	}
	return OK;
}
Status InsetFirst_GL(GLNode **glist,GLNode *node){
	GLNode *head;
	if(!*glist||!node)return ERROR;
	CopyGList(&head,node);
	head->next=(*glist)->hp;
	(*glist)->hp=head;
	return OK;
}
Status DeleteFirst_GL(GLNode **glist,GLNode **node){
	if(!*glist||!(*glist)->hp)return ERROR;
	*node=(*glist)->hp;
	(*glist)->hp=(*glist)->hp->next;
	(*node)->next=NULL;
	return OK;
}
Status Add(GLNode *node){
	if(!node||!node->tag==ATOM)return ERROR;
	node->atom++;
	return OK;
}
Status TraverseGList(GLNode *glist,Status (*visit)(GLNode*)){
	if(!glist||!glist->hp)return ERROR;
	if(glist->tag==ATOM){
		if(!visit(glist))return ERROR;
	}else if(glist->tag==LIST&&glist->hp){
		GLNode *node;
		for(node=glist->hp;node;node=node->next)TraverseGList(node,visit);
	}
	return OK;
}
int main(){
	char *str="(((b,c,d),a),(),(e))";
	GLNode *glist=NULL;
	GLNode *head=NULL;
	GLNode *node;
	CreateGList(&glist,str);
	PrintGList(glist);
	printf("\n");
	TraverseGList(glist,Add);
	PrintGList(glist);
	printf("\n");
	printf("depth=%d  length=%d\n",GListDepth(glist),GListLength(glist));
	return 0;
}
