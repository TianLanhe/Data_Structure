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
Status DeleteAVL_sub(BiTNode **root,int target,Status *shorter,Status *flag);
//删除二叉排序树中关键字为target的节点，若不存在target关键字的节点，则删除失败，返回ERROR
//若存在target，则在删除该节点并调整节点位置与平衡因子，返回OK
Status DeleteAVL(BiTNode **root,int target,Status *shorter);
//封装了上述的删除函数，隐藏了flag参数
BiTNode *SearchAVL(BiTNode *root,int target);
//搜索二叉平衡树，若存在关键字为target的节点，则返回该节点的地址，否则返回NULL
Status isAVL(BiTNode *root);
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
Status DeleteAVL_sub(BiTNode **root,int target,Status *shorter,Status *flag){
	if(*root == NULL){//没找到结点，删除失败//二叉平衡树删除操作基本思路：
		*shorter=false;						//找到该节点，若没有子树或只有一边子树
		return ERROR;						//则删除该节点，并往上回溯修改bf与旋转
	}else if((*root)->data == target){		//若该节点有两边子树，比较复杂，首先与
		if(*flag == true){//第二次到达顶点	//左边的右尽头节点交换关键值，然后继续
			BiTNode *temp;					//往左，当第二次找到该关键值的节点时，
			*shorter=true;					//删除该节点，并接上左子树，再往上回溯
			temp=*root;						//调整节点
			*root=(*root)->lchild;	//接上左子树，可以证明不会影响左子树的bf
			free(temp);				//删除该节点
			return OK;
		}else{
			BiTNode *temp;
			int tmp;
			*flag=true;
			if((*root)->lchild == NULL){
				*shorter=true;
				temp=*root;
				*root=(*root)->rchild;
				free(temp);
				return OK;
			}else if((*root)->rchild == NULL){	//只有左子树或者右子树时，删除该节点即可
				*shorter=true;
				temp=*root;
				*root=(*root)->lchild;
				free(temp);
				return OK;
			}else{
				temp=(*root)->lchild;
				while(temp->rchild)temp=temp->rchild;
				tmp=temp->data;							//交换数据
				temp->data=(*root)->data;
				(*root)->data=tmp;						//往左边继续搜索，一定搜索得到
				if(DeleteAVL_sub(&(*root)->lchild,target,shorter,flag) == ERROR)return ERROR;
				if(*shorter == true){
					switch((*root)->bf){
					case 1:*shorter=true;
							(*root)->bf--;
							break;
					case 0:*shorter=false;
							(*root)->bf--;
							break;
					case -1:(*root)->bf--;
							if(Right_Balance(root) == ERROR)return ERROR;
							*shorter=false;
							break;
					default:return ERROR;
					} 
				}
			}
		}
	}else if(target < (*root)->data){
		if(DeleteAVL_sub(&(*root)->lchild,target,shorter,flag) == ERROR)return ERROR;
		if(*shorter == true){
			switch((*root)->bf){
			case 1:*shorter=true;
					(*root)->bf--;
					break;
			case 0:*shorter=false;
					(*root)->bf--;
					break;
			case -1:(*root)->bf--;
					if(Right_Balance(root) == ERROR)return ERROR;
					*shorter=false;
					break;
			default:return ERROR;
			} 
		}
	}else if(target > (*root)->data){
		if(DeleteAVL_sub(&(*root)->rchild,target,shorter,flag) == ERROR)return ERROR;
		if(*shorter == true){
			switch((*root)->bf){
			case -1:*shorter=true;
					(*root)->bf++;
					break;
			case 0:*shorter=false;
					(*root)->bf++;
					break;
			case 1:(*root)->bf++;
					if(Left_Balance(root) == ERROR)return ERROR;
					*shorter=false;
					break;
			default:return ERROR;
			} 
		}
	}
	return OK;
}
Status DeleteAVL(BiTNode **root,int target,Status *shorter){
	int flag=false;
	return DeleteAVL_sub(root,target,shorter,&flag);
}
BiTNode *SearchAVL(BiTNode *root,int target){
	if(root == NULL)return NULL;
	else if(root->data == target)return root;
	else if(target < root->data)return SearchAVL(root->lchild,target);
	else return SearchAVL(root->rchild,target);
}
Status isAVL(BiTNode *root){
	if(root == NULL)return true;
	else{
		if(root->bf > 1 || root->bf < -1)return false;
		if(root->lchild && root->lchild->data >= root->data)return false;
		if(root->rchild && root->rchild->data <= root->data)return false;
		if(isAVL(root->lchild) == false)return false;
		if(isAVL(root->rchild) == false)return false;
		return true;
	}
}
int main(){
	BiTNode *root=NULL;
	int a[10]={62,88,58,47,35,73,51,99,37,93};
	int i;
	int flag=false;
	int shorter;
	for(i=0;i<10;i++)
		if(InsertAVL(&root,a[i],&shorter) == ERROR)printf("ERROR\n");
	InOrderTraverse(root,PrintBiTree);
	printf("\n");
	printf("%d\n",isAVL(root));
	if(DeleteAVL(&root,93,&shorter) == ERROR)printf("ERROR\n");
	InOrderTraverse(root,PrintBiTree);
	printf("\n");
	printf("%d\n",isAVL(root));
	return 0;
}
