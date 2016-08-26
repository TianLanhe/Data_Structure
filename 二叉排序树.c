#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERROR -1
#define Status int
#define true 1
#define false 0 
typedef struct _bitree{
    int data;
    struct _bitree *lchild;
    struct _bitree *rchild;
}BiTNode;
Status InOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//中序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintBiTree(BiTNode *node);
//遍历函数的功能函数，打印节点的数据值
Status SearchBST(BiTNode *tree,int target,BiTNode *parent,BiTNode **ptr);
//递归查找target在二叉树的位置，若查找成功，则返回OK，ptr返回指向该节点的指针
//若查找失败，则返回ERROR，ptr返回最后访问到的节点的指针
Status InsertBST(BiTNode **tree,int target);
//向二叉排序树中插入关键字为target的节点。若已存在target关键字的节点，则插入失败，返回ERROR
//若不存在target，则在相应位置插入节点，返回OK
BiTNode *GetParent(BiTNode *root,BiTNode *node);
//返回结点node在二叉树root中的父结点
Status DeleteBST(BiTNode **tree,int target);
//删除二叉排序树中关键字为target的节点(迭代法)，若已不存在target关键字的节点，则删除失败，返回ERROR
//若存在target，则在删除该节点并调整节点，返回OK
Status DeleteBST_recursion(BiTNode **tree,int target);
//删除二叉排序树中关键字为target的节点(递归法)，若不存在target关键字的节点，则删除失败，返回ERROR
//若存在target，则在删除该节点并调整节点，返回OK
Status Delete(BiTNode **node);
//删除二叉树节点递归法的子函数，进行node节点的具体删除操作
Status isBST(BiTNode *root);
//判断该数是否是二叉平衡树，是则返回true，否则返回false

Status InOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *)){
	if(root){
		if(InOrderTraverse(root->lchild,visit) == ERROR)return ERROR;
		if(visit(root) == ERROR)return ERROR;
		if(InOrderTraverse(root->rchild,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status PrintBiTree(BiTNode *node){
	if(!node)return ERROR;
	printf("%3d",node->data);
	return OK;
}
Status SearchBST(BiTNode *tree,int target,BiTNode *parent,BiTNode **ptr){
	if(tree == NULL){
		*ptr=parent;
		return ERROR;
	}else if(tree->data == target){
		*ptr=tree;
		return OK;
	}else if(target < tree->data)return SearchBST(tree->lchild,target,tree,ptr);
	else return SearchBST(tree->rchild,target,tree,ptr);
}
Status InsertBST(BiTNode **tree,int target){
	BiTNode *ptr;
	BiTNode *parent;
	if(SearchBST(*tree,target,*tree,&parent) == ERROR){
		ptr=(BiTNode*)malloc(sizeof(BiTNode));
		ptr->data=target;
		ptr->lchild=NULL;
		ptr->rchild=NULL;
		if(parent == NULL)*tree=ptr;
		else if(target < parent->data)parent->lchild=ptr;
		else parent->rchild=ptr;
		return OK;
	}else return ERROR;
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
Status DeleteBST(BiTNode **tree,int target){
	BiTNode *parent;
	BiTNode *ptr;
	if(SearchBST(*tree,target,*tree,&ptr) == OK){	//查找成功才能删除
		parent=GetParent(*tree,ptr);			//查找该节点的父亲结点
		if(parent == NULL)parent=*tree;			//若父亲节点为NULL，说明无父亲结点，即本身即是根节点
		if(ptr->lchild == NULL){				//则将parent赋值为ptr本身，即根节点本身
			if(target < parent->data){
				parent->lchild=ptr->rchild;
			}else if(target > parent->data){
				parent->rchild=ptr->rchild;
			}else{
				*tree=ptr->rchild;				//说明ptr->data=parent->data，修改根节点
			}
			free(ptr);
		}else if(ptr->rchild == NULL){
			if(target < parent->data){
				parent->lchild=ptr->lchild;
			}else if(target > parent->data){
				parent->rchild=ptr->lchild;
			}else{
				*tree=ptr->lchild;
			}
			free(ptr);
		}else{
			BiTNode *temp;
			parent=ptr;
			temp=ptr->lchild;
			while(temp->rchild){
				parent=temp;
				temp=temp->rchild;
			}
			ptr->data=temp->data;
			if(ptr == parent){
				parent->lchild=temp->lchild;
			}else{
				parent->rchild=temp->lchild;
			}
			free(temp);
		}
		return OK;
	}else return ERROR;
}
Status Delete(BiTNode **node){
	BiTNode *temp;
	if(node == NULL || *node == NULL)return ERROR;
	if((*node)->lchild == NULL){
		temp=*node;
		*node=(*node)->rchild;
	}else if((*node)->rchild == NULL){
		temp=*node;
		*node=(*node)->lchild;
	}else{
		BiTNode *parent;
		parent=*node;
		temp=(*node)->lchild;
		while(temp->rchild){
			parent=temp;
			temp=temp->rchild;
		}
		(*node)->data=temp->data;
		if(parent == *node)parent->lchild=temp->lchild;
		else parent->rchild=temp->lchild;
	}
	free(temp);
	return OK;
}
Status DeleteBST_recursion(BiTNode **tree,int target){
	if(*tree == NULL)return ERROR;
	else if((*tree)->data == target) return Delete(tree);
	else if(target < (*tree)->data)return DeleteBST_recursion(&(*tree)->lchild,target);
	else return DeleteBST_recursion(&(*tree)->rchild,target);
}
Status isBST(BiTNode *root){
	if(root == NULL)return true;
	else{
		if(root->lchild->data >= root->data)return false;
		if(root->rchild->data <= root->data)return false;
		if(isBST(root->lchild) == false)return false;
		if(isBST(root->rchild) == false)return false;
		return true;
	}
}
int main(){
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	int i;
	BiTNode *root;
	root=NULL;
	for(i=0;i<10;i++){
		if(InsertBST(&root,a[i]) == ERROR)return ERROR;
	}
	InOrderTraverse(root,PrintBiTree);
	printf("\n"); 

	DeleteBST_recursion(&root,65);
	InOrderTraverse(root,PrintBiTree);
	return 0;
}
