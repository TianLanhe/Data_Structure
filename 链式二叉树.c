#include <stdio.h>
#include <stdlib.h>
#define OK 1
#define ERROR 0
#define Status int
#define TRUE 1
#define FALSE 0
#define LEFT 0
#define RIGHT 1
#define NUM 100			//栈和队列的长度(数组长度)
typedef int TElemType;
typedef struct _bitree{
	TElemType data;
	struct _bitree *lchild;
	struct _bitree *rchild;
}BiTNode;
typedef struct _stack{
	BiTNode **arr;
	int top;
	int base;
}TreeStack;
typedef TreeStack TreeQueue;
Status InitTreeStack(TreeStack *stack);
//初始化栈，为arr分配长度为NUM的数组，并设置top与base指向栈尾后一个单位
Status TreePop(TreeStack *stack,BiTNode **bitnode);
//出栈，将栈顶元素返回到bitnode中
Status TreePush(TreeStack *stack,BiTNode *bitnode);
//入栈，将bitnode的指针存到stack的栈顶
Status TStackEmpty(TreeStack stack);
//若栈Q为空栈，则返回TRUE，否则返回FALSE
Status TStackGetTop(TreeStack stack,BiTNode **bitnode);
//若栈不空，则用bitnode返回stack的栈顶元素，并返回OK，否则返回ERROR与NULL
Status InitTreeQueue(TreeQueue *queue);
//初始化队列
Status TreeEnQueue(TreeQueue *queue,BiTNode *node);
//入队列
Status TreeDeQueue(TreeQueue *queue,BiTNode **node);
//出队列
Status TQueueEmpty(TreeQueue queue);
//若队列为空，则返回TRUE,否则返回FALSE
Status InitTreeStack(TreeStack *stack){
	stack->arr=(BiTNode **)malloc(sizeof(BiTNode*)*NUM);
	if(!stack->arr)return ERROR;
	stack->top=stack->base=NUM;
	return OK;
}
Status TreePush(TreeStack *stack,BiTNode *bitnode){
	if(!stack->top)return ERROR;
	stack->top--;
	stack->arr[stack->top]=bitnode;
	return OK;
}
Status TreePop(TreeStack *stack,BiTNode **bitnode){
	if(stack->top==stack->base)return ERROR;
	*bitnode=stack->arr[stack->top];
	stack->top++;
	return OK;
}
Status TStackEmpty(TreeStack stack){
	if(stack.top==stack.base)return TRUE;
	else return FALSE;
}
Status TStackGetTop(TreeStack stack,BiTNode **bitnode){
	if(stack.top==stack.base){
		*bitnode=NULL;
		return ERROR;
	}else{
		*bitnode=stack.arr[stack.top];
		return OK;
	}
}
Status InitTreeQueue(TreeQueue *queue){
	int i;
	queue->arr=(BiTNode **)malloc(sizeof(BiTNode*)*NUM);
	if(!queue->arr)return ERROR;
	queue->top=queue->base=-1;
	for(i=0;i<NUM;i++)queue->arr[i]=0;	//多余
	return OK;
}
Status TreeEnQueue(TreeQueue *queue,BiTNode *node){
	if(queue->top-queue->base==NUM-1||queue->base-queue->top==1)return ERROR;
	queue->top=(queue->top+1)%NUM;	//队列满可以判断为(top+1)%NUM==base
	queue->arr[queue->top]=node;
	return OK;
}
Status TreeDeQueue(TreeQueue *queue,BiTNode **node){
	if(queue->top==queue->base)return ERROR;
	queue->base=(queue->base+1)%NUM;
	*node=queue->arr[queue->base];
	return OK;
}
Status TQueueEmpty(TreeQueue queue){
	if(queue.top==queue.base)return TRUE;
	else return FALSE;
}
Status CreateBiTree(BiTNode **root);
//先序创建二叉树
Status InitBiTree(BiTNode **root);
//初始化空树，创建空二叉树root
Status DestroyBiTree(BiTNode **root);
//销毁二叉树root，使其为空树
Status BiTreeEmpty(BiTNode *root);
//判断二叉树是否为空，若root为空二叉树，则返回TRUE，否则返回FALSE
int BiTreeDepth(BiTNode *root);
//返回二叉树root的深度
int BiTNodeLevel(BiTNode *root,BiTNode *node);
//求结点node在二叉树root中的层数
Status isSubBiTree(BiTNode *root,BiTNode *node);
//判断node是否为二叉树root的结点
TElemType Value(BiTNode *root,BiTNode *node);
//node是二叉树root的某个结点，返回结点node的数据值
Status Assign(BiTNode *root,BiTNode *node,TElemType data);
//node是二叉树root的某个结点，将结点node的数据值赋值为data
BiTNode *GetParent(BiTNode *root,BiTNode *node);
//返回结点node在二叉树root中的父结点
BiTNode *Parent(BiTNode *root,BiTNode *node);
//node是二叉树root中的节点，当node是root的非根结点时，返回node的父亲结点，否则返回空
BiTNode *LeftChild(BiTNode *root,BiTNode *node);
//node是二叉树root中的节点，返回node的左儿子结点，(若node无左儿子)否则返回空
BiTNode *RightChild(BiTNode *root,BiTNode *node);
//node是二叉树root中的节点，返回node的右儿子结点，(若node无右儿子)否则返回空
BiTNode *LeftSiblint(BiTNode *root,BiTNode *node);
//node是二叉树root中的节点，返回node的左兄弟结点，(若node无左兄弟或node是root的左孩子)否则返回空
BiTNode *RightSiblint(BiTNode *root,BiTNode *node);
//node是二叉树root中的节点，返回node的右兄弟结点，(若node无右兄弟或node是root的右孩子)否则返回空
Status InsertChild(BiTNode *root,BiTNode *node,int lr,BiTNode *newnode);
//二叉树root存在，node为root中的某个结点，lr为0(left)或1(right)，非空二叉树newnode与root不相交且
//右子树为空，根据lr的值插入newnode为root中node的左或右子树。node的原左或右子树则成为newnode的右子树
Status DeleteChile(BiTNode *root,BiTNode *node,int lr,BiTNode **newnode);
//二叉树root存在，node为root中的某个结点，lr为0(left)或1(right)，根据lr的值删除node的左或右子树，并赋给newnode
Status PreOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//先序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PostOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//后序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status InOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//中序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PreOrderTraverse_stack(BiTNode *root,Status (*visit)(BiTNode *));
//先序遍历(非递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status InOrderTraverse_stack(BiTNode *root,Status (*visit)(BiTNode *));
//中序遍历(非递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PostOrderTraverse_stack(BiTNode *root,Status (*visit)(BiTNode *));
//后序遍历(非递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status LevelOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//层序遍历(利用队列)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintBiTree(BiTNode *node);
//遍历函数的功能函数，打印节点的数据值
Status InitBiTree(BiTNode **root){
	*root=NULL;
	return OK;
}
Status DestroyBiTree(BiTNode **root){
	if(*root){
		DestroyBiTree(&(*root)->lchild);
		DestroyBiTree(&(*root)->rchild);
		free(*root);
		*root=NULL;
	}
	return OK;
}
Status CreateBiTree(BiTNode **root){
	char ch;
	do{
		ch=getchar();
	}while(ch=='\n');
	if(ch==' ')(*root)=NULL;
	else{
		(*root)=(BiTNode *)malloc(sizeof(BiTNode));
		if(!(*root))return ERROR;
		(*root)->data=ch;
		CreateBiTree(&(*root)->lchild);
		CreateBiTree(&(*root)->rchild);
	}
	return OK;
}
Status BiTreeEmpty(BiTNode *root){
	if(!root)return TRUE;
	else return FALSE;
}
Status isSubBiTree(BiTNode *root,BiTNode *node){
	if(root){
		if(root==node)return TRUE;
		if(isSubBiTree(root->lchild,node) == TRUE)return TRUE;
		if(isSubBiTree(root->rchild,node) == TRUE)return TRUE;
	}
	return FALSE;
}
TElemType Value(BiTNode *root,BiTNode *node){
	if(!node || !root || isSubBiTree(root,node) == FALSE)return 0;
	return node->data;
}
int BiTreeDepth(BiTNode *root){
	if(root){
		int ldepth,rdepth;
		ldepth=BiTreeDepth(root->lchild);
		rdepth=BiTreeDepth(root->rchild);
		return (ldepth>rdepth?ldepth:rdepth)+1;
	}
	return 0;
}
int BiTNodeLevel(BiTNode *root,BiTNode *node){
	if(root){
		if(node==root)return 1;
		if(isSubBiTree(root->lchild,node) == TRUE)
			return BiTNodeLevel(root->lchild,node)+1;
		if(isSubBiTree(root->rchild,node) == TRUE)
			return BiTNodeLevel(root->rchild,node)+1;		
	}
	return 0;
}
Status Assign(BiTNode *root,BiTNode *node,TElemType data){
	if(!node || !root || isSubBiTree(root,node) == FALSE)return ERROR;
	node->data=data;
	return OK;
}
BiTNode *GetParent(BiTNode *root,BiTNode *node){
	if(root){
		BiTNode *temp;
		if(root->lchild==node || root->rchild==node)return root;
		if(temp=GetParent(root->lchild,node))return temp;
		if(temp=GetParent(root->rchild,node))return temp;
	}
	return NULL;
}
BiTNode *Parent(BiTNode *root,BiTNode *node){
	if(!node || !root || isSubBiTree(root,node) == FALSE || root==node)
		return NULL;
	return GetParent(root,node);
}
BiTNode *LeftChild(BiTNode *root,BiTNode *node){
	if(!node || !root || isSubBiTree(root,node) == FALSE)return NULL;
	return node->lchild;
}
BiTNode *RightChild(BiTNode *root,BiTNode *node){
	if(!node || !root || isSubBiTree(root,node) == FALSE)return NULL;
	return node->rchild;
}
BiTNode *LeftSiblint(BiTNode *root,BiTNode *node){
	BiTNode *parent;
	parent=Parent(root,node);
	if(!parent||node==parent->lchild)return NULL;
	return parent->lchild;
}
BiTNode *RightSiblint(BiTNode *root,BiTNode *node){
	BiTNode *parent;
	parent=Parent(root,node);
	if(!parent||node==parent->rchild)return NULL;
	return parent->rchild;
}
Status InsertChild(BiTNode *root,BiTNode *node,int lr,BiTNode *newnode){
	if(!root||!newnode||(lr!=0&&lr!=1)||!node||isSubBiTree(root,node)==FALSE)return ERROR;
	if(newnode->rchild||isSubBiTree(root,newnode)==TRUE)return ERROR;
	if(lr==LEFT){
		newnode->rchild=node->lchild;
		node->lchild=newnode;
	}else if(lr==RIGHT){
		newnode->rchild=node->rchild;
		node->rchild=newnode;
	}
	return OK;
}
Status DeleteChild(BiTNode *root,BiTNode *node,int lr,BiTNode **newnode){
	if(!root||(lr!=0&&lr!=1)||!node||isSubBiTree(root,node)==FALSE)return ERROR;
	if(lr==0){
		*newnode=node->lchild;
		node->lchild=NULL;
	}else if(lr==1){
		*newnode=node->rchild;
		node->rchild=NULL;
	}
	return OK;
}
Status PreOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *)){
	if(root){
		if(!visit(root))return ERROR;
		if(!PreOrderTraverse(root->lchild,visit))return ERROR;
		if(!PreOrderTraverse(root->rchild,visit))return ERROR;
	}
	return OK;
}
Status InOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *)){
	if(root){
		if(!InOrderTraverse(root->lchild,visit))return ERROR;
		if(!visit(root))return ERROR;
		if(!InOrderTraverse(root->rchild,visit))return ERROR;
	}
	return OK;
}
Status PostOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *)){
	if(root){
		if(!PostOrderTraverse(root->lchild,visit))return ERROR;
		if(!PostOrderTraverse(root->rchild,visit))return ERROR;
		if(!visit(root))return ERROR;
	}
	return OK;
}
Status PreOrderTraverse_stack(BiTNode *root,Status (*visit)(BiTNode *)){
	TreeStack stack;
	BiTNode *temp;
	int i;
	if(!root)return ERROR;
	InitTreeStack(&stack);
	temp=root;
	if(!TreePush(&stack,temp))return ERROR;
	if(!visit(temp))return ERROR;
	while(!TStackEmpty(stack)){
		while(TStackGetTop(stack,&temp)&&temp){
			if(!TreePush(&stack,temp->lchild))return ERROR;
			if(temp->lchild)if(!visit(temp->lchild))return ERROR;
		}
		if(!TreePop(&stack,&temp))return ERROR;
		if(!TStackEmpty(stack)){
			if(!TreePop(&stack,&temp))return ERROR;
			if(!TreePush(&stack,temp->rchild))return ERROR;
			if(temp->rchild)if(!visit(temp->rchild))return ERROR;
		}
	}
	return OK;
}
Status InOrderTraverse_stack(BiTNode *root,Status (*visit)(BiTNode *)){
	TreeStack stack;
	BiTNode *temp;
	InitTreeStack(&stack);
	temp=root;
	if(!TreePush(&stack,temp))return ERROR;
	while(!TStackEmpty(stack)){
		while(TStackGetTop(stack,&temp)&&temp)if(!TreePush(&stack,temp->lchild))return ERROR;
		if(!TreePop(&stack,&temp))return ERROR;
		if(!TStackEmpty(stack)){
			if(!TreePop(&stack,&temp))return ERROR;
			if(!visit(temp))return ERROR;
			if(!TreePush(&stack,temp->rchild))return ERROR;
		}
	}
	return OK;
}
Status PostOrderTraverse_stack(BiTNode *root,Status (*visit)(BiTNode *)){
	TreeStack stack;
	BiTNode *temp;
	BiTNode *pre;
	InitTreeStack(&stack);
	temp=root;
	pre=NULL;
	while(temp||!TStackEmpty(stack)){
		if(temp){
			TreePush(&stack,temp);
			temp=temp->lchild;
		}else if(TStackGetTop(stack,&temp)&&(!temp->rchild||temp->rchild==pre)){
			TreePop(&stack,&temp);
			if(!visit(temp))return ERROR;
			pre=temp;
			temp=NULL;
		}else{
			temp=temp->rchild;
		}
	}
	return OK;
}
Status LevelOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *)){
	TreeQueue queue;
	BiTNode *node;
	InitTreeQueue(&queue);
	TreeEnQueue(&queue,root);
	while(!TQueueEmpty(queue)){
		TreeDeQueue(&queue,&node);
		if(!visit(node))return ERROR;
		if(node->lchild)TreeEnQueue(&queue,node->lchild);
		if(node->rchild)TreeEnQueue(&queue,node->rchild);
	}
}
Status PrintBiTree(BiTNode *node){
	if(!node)return ERROR;
	printf("%c",node->data);
	return OK;
}
int main(){
	BiTNode *bitree;
	BiTNode *node;
	int level;
	CreateBiTree(&bitree);
	PreOrderTraverse_stack(bitree,PrintBiTree);
	printf("\n");
	InOrderTraverse_stack(bitree,PrintBiTree);
	printf("\n");
	PostOrderTraverse_stack(bitree,PrintBiTree);
	printf("\n");
	LevelOrderTraverse(bitree,PrintBiTree);
	printf("\n");
	return 0;
}
