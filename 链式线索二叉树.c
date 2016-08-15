#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define Status int
#define TElemType int
#define TRUE 1
#define FALSE 0
typedef enum _pointtag{			//用枚举变量表示，当然也可以用宏
	LINK,						//表示是孩子
	THREAD 						//表示是线索
}PointTag;
typedef struct _bitree{
	TElemType data;				//数据域
	PointTag LTag;				//左标志，等于LINK为左孩子，等于THREAD为前驱
	PointTag RTag;				//右标志，等于LINK为右孩子，等于THREAD为后继
	struct _bitree *lchild;		//左孩子指针
	struct _bitree *rchild;		//右孩子指针
}BiTNode;
BiTNode *pre;					//需要一个pre指向其前驱，不能在递归函数中定义，因此只能在全局或者传参给递归函数，这里选择了前者
Status CreateBiTree_sub(BiTNode **root);
//创建线索二叉树的子函数，先序创建二叉树root
void InOrderThreading_sub(BiTNode *root);
//线索化二叉树的子函数，中序遍历并线索化二叉树root
Status InOrderThreading(BiTNode **thrt,BiTNode *root);
//线索化二叉树，为二叉树分配虚头结点，进行所有结点的线索化
Status CreateBiTree(BiTNode **thrt);
//先序创建线索二叉树，包括创建二叉树和线索化两个过程，可选择先序线索化或者中序线索化
Status InitBiTree(BiTNode **root);
//初始化空树，创建虚头结点
Status DestroyBiTree(BiTNode **root);
//销毁二叉树root，使其为空
Status ClearBiTree_sub(BiTNode **root);
//清空二叉树的子函数
Status ClearBiTree(BiTNode *root);
//清空二叉树，使其只剩头结点
Status BiTreeEmpty(BiTNode *root);
//判断二叉树是否为空，若root为空二叉树，则返回TRUE，否则返回FALSE
Status InOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//中序遍历(非递归线索化法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintBiTree(BiTNode *node);
//遍历函数的功能函数，打印节点的数据值
Status InitBiTree(BiTNode **root){
	*root=(BiTNode *)malloc(sizeof(BiTNode));
	if(!*root)return ERROR;
	(*root)->lchild=*root;
	(*root)->rchild=*root;
	(*root)->LTag=THREAD;
	(*root)->RTag=THREAD;
	(*root)->data=0;
	return OK;
}
Status PrintBiTree(BiTNode *node){
	if(!node)return ERROR;
	printf("%c",node->data);
	return OK;
}
Status BiTreeEmpty(BiTNode *root){
	if(root->lchild==root)return TRUE;
	else return FALSE;
}
Status CreateBiTree_sub(BiTNode **root){
	char ch;
	do{
		ch=getchar();
	}while(ch=='\n');
	if(ch==' ')(*root)=NULL;
	else{
		(*root)=(BiTNode *)malloc(sizeof(BiTNode));
		if(!(*root))return ERROR;
		(*root)->data=ch;
		CreateBiTree_sub(&(*root)->lchild);
		CreateBiTree_sub(&(*root)->rchild);
	}
	return OK;
}
void InOrderThreading_sub(BiTNode *root){
	if(root){
		InOrderThreading_sub(root->lchild);
		if(!root->lchild){
			root->LTag=THREAD;
			root->lchild=pre;
		}else root->LTag=LINK;
		if(!pre->rchild){
			pre->RTag=THREAD;
			pre->rchild=root;
		}else pre->RTag=LINK;
		pre=root;
		InOrderThreading_sub(root->rchild);
	}
}
Status InOrderThreading(BiTNode **thrt,BiTNode *root){
	InitBiTree(thrt);
	if(root){
		(*thrt)->lchild=root;
		(*thrt)->LTag=LINK;
		pre=(*thrt);
		InOrderThreading_sub(root);
		pre->rchild=(*thrt);
		pre->RTag=THREAD;
		(*thrt)->rchild=pre;
	}
	return OK;
}
Status CreateBiTree(BiTNode **thrt){
	BiTNode *root;
	if(!CreateBiTree_sub(&root))return ERROR;
	if(!InOrderThreading(thrt,root))return ERROR;
	return OK;
}
Status ClearBiTree_sub(BiTNode **root){
	if(*root){
		if((*root)->LTag==LINK)ClearBiTree_sub(&(*root)->lchild);
		if((*root)->RTag==LINK)ClearBiTree_sub(&(*root)->rchild);
		free(*root);
		*root=NULL;
	}
	return OK;
}
Status ClearBiTree(BiTNode *thrt){
	if(!thrt||thrt->lchild==thrt)return ERROR;
	if(ClearBiTree_sub(&thrt->lchild) == ERROR)return ERROR;
	thrt->lchild=thrt;
	thrt->LTag=THREAD;
	thrt->rchild=thrt;
	thrt->RTag=THREAD;
	return OK;
}
Status DestroyBiTree(BiTNode **thrt){
	if(ClearBiTree(*thrt) == ERROR)return ERROR;
	free(*thrt);
	*thrt=NULL;
}
Status InOrderTraverse(BiTNode *thrt,Status (*visit)(BiTNode *)){
	BiTNode *node;
	node=thrt->lchild;
	while(node!=thrt){
		while(node->LTag==LINK)node=node->lchild;
		if(visit(node) == ERROR)return ERROR;
		while(node->RTag==THREAD&&node->rchild!=thrt){
			node=node->rchild;
			if(visit(node) == ERROR)return ERROR;
		}
		node=node->rchild;
	}
	return OK;
}
int main(){
	BiTNode *bitree=NULL;
	CreateBiTree(&bitree);
	InOrderTraverse(bitree,PrintBiTree);
	printf("\n");
	DestroyBiTree(&bitree);
	return 0;
}
