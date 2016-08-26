#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERROR -1
#define Status int
#define true 1
#define false 0
typedef struct _bitree{
    int data;
    int bf;						//平衡因子
    struct _bitree *lchild;
    struct _bitree *rchild;
}BiTNode;
Status InOrderTraverse(BiTNode *root,Status (*visit)(BiTNode *));
//中序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintBiTree(BiTNode *node);
//遍历函数的功能函数，打印节点的数据值
Status Left_Rotate(BiTNode **root);
//将以root为根的子树进行左旋处理，并使root指向旋转后的根
Status Right_Rotate(BiTNode **root);
//将以root为根的子树进行右旋处理，并使root指向旋转后的根
Status Left_Balance(BiTNode **root);
//对以root为根的子树进行左平衡处理，并使root指向旋转后的根(在上面两个函数中实现)
Status Right_Balance(BiTNode **root);
//对以root为根的子树进行右平衡处理，并使root指向旋转后的根(在上面两个函数中实现)
Status InsertAVL(BiTNode **root,int target,Status *taller);
//向二叉排序树中插入关键字为target的节点。若已存在target关键字的节点，则插入失败，返回ERROR
//若不存在target，则在相应位置插入节点，并进行旋转(若需要)，返回OK
BiTNode *SearchAVL(BiTNode *root,int target);
//搜索二叉平衡树，若存在关键字为target的节点，则返回该节点的地址，否则返回NULL

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
Status Left_Rotate(BiTNode **node){
	BiTNode *lr;
	if(node == NULL || *node == NULL)return ERROR;
	lr=(*node)->rchild;
	(*node)->rchild=lr->lchild;
	lr->lchild=*node;
	*node=lr;
	return OK;
}
Status Right_Rotate(BiTNode **node){
	BiTNode *ll;
	if(node == NULL || *node == NULL)return ERROR;
	ll=(*node)->lchild;
	(*node)->lchild=ll->rchild;
	ll->rchild=*node;
	*node=ll;
	return OK;
}
Status Left_Balance(BiTNode **node){
	BiTNode *lch;
	if(node == NULL || *node == NULL)return ERROR;
	if((*node)->bf != 2)return ERROR;		//要左旋的根节点的bf必为+2
	lch=(*node)->lchild;
	if(lch->bf == 1){						//同符号则直接旋转
		(*node)->bf=0;
		lch->bf=0;
		if(Right_Rotate(node) == ERROR)return ERROR;
	}else if(lch->bf == -1){				//符号不同则根节点的左孩子先反方向(左旋)，再将根节点右旋
		BiTNode *grandson;
		grandson=lch->rchild;				//判断左孩子的右孩子(孙子)的bf，修改他们的bf
		if(grandson->bf == 1){
			(*node)->bf=-1;
			lch->bf=0;
		}else if(grandson->bf == 0){
			(*node)->bf=0;
			lch->bf=0;
		}else if(grandson->bf == -1){
			(*node)->bf=0;
			lch->bf=1;
		}else return ERROR;			//应该不会有其他情况，但加上好像更容易阅读，上面三种看起来也清晰些
		grandson->bf=0;
		if(Left_Rotate(&(*node)->lchild) == ERROR)return ERROR;	//注意这里不能传入lch，否则无法将改变传回主函数
		if(Right_Rotate(node) == ERROR)return ERROR;
	}else return ERROR;				//lch的bf不应该出现0或其他情况
	return OK;
}
Status Right_Balance(BiTNode **node){
	BiTNode *rch;
	if(node == NULL || *node == NULL)return ERROR;
	if((*node)->bf != -2)return ERROR;		//要左旋的根节点的bf必为-2
	rch=(*node)->rchild;
	if(rch->bf == -1){						//同符号则直接旋转
		(*node)->bf=0;
		rch->bf=0;
		if(Left_Rotate(node) == ERROR)return ERROR;
	}else if(rch->bf == 1){					//符号不同则根节点的左孩子先反方向(右旋)，再将根节点左旋
		BiTNode *grandson;
		grandson=rch->lchild;
		if(grandson->bf == 1){
			(*node)->bf=0;
			rch->bf=-1;
		}else if(grandson->bf == 0){
			(*node)->bf=0;
			rch->bf=0;
		}else if(grandson->bf == -1){
			(*node)->bf=1;
			rch->bf=0;
		}else return ERROR;			//应该不会有其他情况，但加上好像更容易阅读，上面三种看起来也清晰些
		grandson->bf=0;
		if(Right_Rotate(&(*node)->rchild) == ERROR)return ERROR;	//注意这里不能传入rch，否则无法将改变传回主函数
		if(Left_Rotate(node) == ERROR)return ERROR;
	}else return ERROR;				//注意这里不能传入lch，否则无法将改变传回主函数
	return OK;
}
Status InsertAVL(BiTNode **root,int target,Status *taller){
	if(*root == NULL){					//递归搜索二叉平衡树，若到了尽头，则插入新节点
		BiTNode *temp;					//对二级指针解引用赋值，起到插入的作用
		temp=(BiTNode*)malloc(sizeof(BiTNode));
		temp->lchild=NULL;
		temp->rchild=NULL;
		temp->data=target;
		temp->bf=0;
		*(root)=temp;
		*taller=true;					//这个taller必不可少，用它反应树是否高度增加，以此判断是否需要旋转
		return OK;
	}else if((*root)->data == target){			//已存在关键值为target的节点，添加失败，树没有长高(taller为false)
		*taller=false;
		return ERROR;
	}else if(target < (*root)->data){			//对左子树进行搜索并插入
		if(InsertAVL(&(*root)->lchild,target,taller) == ERROR)return ERROR;
		if(*taller == true){					//插入成功后，对上面的节点进行判断，看是否需要旋转
			
			switch((*root)->bf){
				case -1:*taller=false;
						(*root)->bf++;
						break;
				case 0:*taller=true;
						(*root)->bf++;
						break;
				case 1:(*root)->bf++;
						if(Left_Balance(root) == ERROR)return ERROR;
						*taller=false;
						break;
				default:return ERROR;
			}
		}
		return OK;
	}else{									//对右子树进行搜索并插入
		if(InsertAVL(&(*root)->rchild,target,taller) == ERROR)return ERROR;
		if(*taller == true){
			switch((*root)->bf){
				case 1:*taller=false;
						(*root)->bf--;
						break;
				case 0:*taller=true;
						(*root)->bf--;
						break;
				case -1:(*root)->bf--;
						if(Right_Balance(root) == ERROR)return ERROR;
						*taller=false;
						break;
				default:return ERROR;
			}
		}
		return OK;
	}
}
BiTNode *SearchAVL(BiTNode *root,int target){
	if(root == NULL)return NULL;
	else if(root->data == target)return root;
	else if(target < root->data)return SearchAVL(root->lchild,target);
	else return SearchAVL(root->rchild,target);
}

int main(){
	BiTNode *root=NULL;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	int i;
	int flag;
	for(i=0;i<10;i++)
		if(InsertAVL(&root,a[i],&flag) == ERROR)printf("ERROR\n");
	InOrderTraverse(root,PrintBiTree);
	printf("\n");
	return 0;
}
