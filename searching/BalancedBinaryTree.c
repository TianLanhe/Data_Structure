#include <stdio.h>
#include <stdlib.h>
#include "BalancedBinaryTree.h"

Status PreOrderTraverse(BiTNode *root, Status(*visit)(BiTNode *)) {
	if (root) {
		if (visit(root) == ERROR)return ERROR;
		if (PreOrderTraverse(root->lchild, visit) == ERROR)return ERROR;
		if (PreOrderTraverse(root->rchild, visit) == ERROR)return ERROR;
	}
	return OK;
}

Status InOrderTraverse(BiTNode *root, Status(*visit)(BiTNode *)) {
	if (root) {
		if (InOrderTraverse(root->lchild, visit) == ERROR)return ERROR;
		if (visit(root) == ERROR)return ERROR;
		if (InOrderTraverse(root->rchild, visit) == ERROR)return ERROR;
	}
	return OK;
}

Status PrintBiTree(BiTNode *node) {
	if (!node)return ERROR;
	printf("%3d", node->data);
	return OK;
}

void PrintBiTreeFriendly(BiTNode *root) {
	printf("\n");
	PrintBiTreeFriendly_sub(root, 0);
	printf("\n");
}

void PrintBiTreeFriendly_sub(BiTNode *root, int indent) {
	if (root) {
		int i;
		PrintBiTree_sub(root->rchild, indent + INDENT);
		for (i = 0; i < indent; ++i)
			printf("%c", ' ');
		printf("%d\n", root->data);
		PrintBiTree_sub(root->lchild, indent + INDENT);
	}
}

Status Left_Rotate(BiTNode **node) {
	BiTNode *lr;
	if (node == NULL || *node == NULL)
		return ERROR;
	lr = (*node)->rchild;
	(*node)->rchild = lr->lchild;
	lr->lchild = *node;
	*node = lr;
	return OK;
}

Status Right_Rotate(BiTNode **node) {
	BiTNode *ll;
	if (node == NULL || *node == NULL)
		return ERROR;
	ll = (*node)->lchild;
	(*node)->lchild = ll->rchild;
	ll->rchild = *node;
	*node = ll;
	return OK;
}

Status Left_Balance(BiTNode **node) {
	BiTNode *lch;
	BiTNode *grandson;

	if (node == NULL || *node == NULL)
		return ERROR;
	if ((*node)->bf != LOH)					//要左平衡的根节点的bf必为+2
		return ERROR;

	lch = (*node)->lchild;
	switch (lch->bf) {						//同符号则直接旋转(右旋)
	case LH:
		(*node)->bf = EH;
		lch->bf = EH;
		if (Right_Rotate(node) == ERROR)
			return ERROR;
		break;
	case EH:
		(*node)->bf = LH;				//插入不可能出现子树bf为0
		lch->bf = RH;				//当删除时才有可能出现另一边子树bf为0
		if (Right_Rotate(node) == ERROR)
			return ERROR;
		break;
	case RH:
		grandson = lch->rchild;		//判断左孩子的右孩子(孙子)的bf，修改他们的bf
		switch (grandson->bf) {
		case LH:
			(*node)->bf = RH;
			lch->bf = EH;
			break;
		case EH:
			(*node)->bf = EH;
			lch->bf = EH;
			break;
		case RH:
			(*node)->bf = EH;
			lch->bf = LH;
			break;
		default:return ERROR;		//应该不会有其他情况，但加上好像更容易阅读，上面三种看起来也清晰些
		}
		grandson->bf = EH;
		if (Left_Rotate(&(*node)->lchild) == ERROR)	//注意这里不能传入lch，否则无法将改变传回主函数
			return ERROR;
		if (Right_Rotate(node) == ERROR)
			return ERROR;
		break;
	default:return ERROR;
	}
	return OK;
}

Status Right_Balance(BiTNode **node) {
	BiTNode *rch;
	BiTNode *grandson;

	if (node == NULL || *node == NULL)
		return ERROR;
	if ((*node)->bf != ROH)				//要左旋的根节点的bf必为-2
		return ERROR;

	rch = (*node)->rchild;
	switch (rch->bf) {
	case RH:
		(*node)->bf = EH;
		rch->bf = EH;
		if (Left_Rotate(node) == ERROR)
			return ERROR;
		break;
	case EH:
		(*node)->bf = RH;					//插入不可能出现子树bf为0
		rch->bf = LH;						//当删除时才有可能出现另一边子树bf为0
		if (Left_Rotate(node) == ERROR)
			return ERROR;
		break;
	case LH:
		grandson = rch->lchild;
		switch (grandson->bf) {
		case LH:
			(*node)->bf = EH;
			rch->bf = RH;
			break;
		case EH:
			(*node)->bf = EH;
			rch->bf = EH;
			break;
		case RH:
			(*node)->bf = LH;
			rch->bf = EH;
			break;
		default:return ERROR;		//应该不会有其他情况，但加上好像更容易阅读，上面三种看起来也清晰些
		}
		grandson->bf = EH;
		if (Right_Rotate(&(*node)->rchild) == ERROR)	//注意这里不能传入rch，否则无法将改变传回主函数
			return ERROR;
		if (Left_Rotate(node) == ERROR)
			return ERROR;
		break;
	default:return ERROR;
	}
	return OK;
}

Status InsertAVL(BiTNode **root, int target, Status *taller) {
	Status status;
	if (*root == NULL) {				//递归搜索二叉平衡树，若到了尽头，则插入新节点
		BiTNode *temp;					//对二级指针解引用赋值，起到插入的作用
		temp = (BiTNode*)malloc(sizeof(BiTNode));
		if (!temp)
			return OVERFLOW;
		temp->lchild = NULL;
		temp->rchild = NULL;
		temp->data = target;
		temp->bf = 0;
		*(root) = temp;
		*taller = true;					//这个taller必不可少，用它反应树是否高度增加，以此判断是否需要旋转
		return OK;
	}
	else if ((*root)->data == target) {	//已存在关键值为target的节点，添加失败，树没有长高(taller为false)
		*taller = false;
		return ERROR;
	}
	else if (target < (*root)->data) {	//对左子树进行搜索并插入
		if ((status = InsertAVL(&(*root)->lchild, target, taller)) != OK)
			return status;
		if (*taller == true) {			//插入成功后，对上面的节点进行判断，看是否需要旋转
			switch ((*root)->bf) {
			case RH:
				*taller = false;
				(*root)->bf++;
				break;
			case EH:
				*taller = true;
				(*root)->bf++;
				break;
			case LH:
				(*root)->bf++;
				if (Left_Balance(root) == ERROR)
					return ERROR;
				*taller = false;
				break;
			default:return ERROR;
			}
		}
		return OK;
	}
	else {									//对右子树进行搜索并插入
		if ((status = InsertAVL(&(*root)->rchild, target, taller)) != OK)
			return status;
		if (*taller == true) {
			switch ((*root)->bf) {
			case LH:
				*taller = false;
				(*root)->bf--;
				break;
			case EH:
				*taller = true;
				(*root)->bf--;
				break;
			case RH:
				(*root)->bf--;
				if (Right_Balance(root) == ERROR)
					return ERROR;
				*taller = false;
				break;
			default:return ERROR;
			}
		}
		return OK;
	}
}

Status DeleteAVL_sub(BiTNode **root, int target, Status *shorter, Status *flag) {
	if (*root == NULL) {//没找到结点，删除失败	//二叉平衡树删除操作基本思路：
		*shorter = false;						//找到该节点，若没有子树或只有一边子树
		return ERROR;							//则删除该节点，并往上回溯修改bf与旋转
	}
	else if ((*root)->data == target) {			//若该节点有两边子树，比较复杂，首先与
		if (*flag == true) {//第二次到达顶点	//左边的右尽头节点交换关键值，然后继续
			BiTNode *temp;						//往左，当第二次找到该关键值的节点时，
			*shorter = true;					//删除该节点，并接上左子树，再往上回溯
			temp = *root;						//调整节点
			*root = (*root)->lchild;			//接上左子树，可以证明不会影响左子树的bf
			free(temp);							//删除该节点
			return OK;
		}
		else {
			BiTNode *temp;
			int tmp;
			*flag = true;
			if ((*root)->lchild == NULL) {
				*shorter = true;
				temp = *root;
				*root = (*root)->rchild;
				free(temp);
				return OK;
			}
			else if ((*root)->rchild == NULL) {	//只有左子树或者右子树时，删除该节点即可
				*shorter = true;
				temp = *root;
				*root = (*root)->lchild;
				free(temp);
				return OK;
			}
			else {
				temp = (*root)->lchild;
				while (temp->rchild)temp = temp->rchild;
				tmp = temp->data;							//交换数据
				temp->data = (*root)->data;
				(*root)->data = tmp;						//往左边继续搜索，一定搜索得到
				if (DeleteAVL_sub(&(*root)->lchild, target, shorter, flag) == ERROR)return ERROR;
				if (*shorter == true) {
					switch ((*root)->bf) {
					case 1:*shorter = true;
						(*root)->bf--;
						break;
					case 0:*shorter = false;
						(*root)->bf--;
						break;
					case -1:(*root)->bf--;
						if (Right_Balance(root) == ERROR)return ERROR;
						*shorter = true;
						break;
					default:return ERROR;
					}
				}
			}
		}
	}
	else if (target < (*root)->data) {
		if (DeleteAVL_sub(&(*root)->lchild, target, shorter, flag) == ERROR)return ERROR;
		if (*shorter == true) {
			switch ((*root)->bf) {
			case 1:*shorter = true;
				(*root)->bf--;
				break;
			case 0:*shorter = false;
				(*root)->bf--;
				break;
			case -1:(*root)->bf--;
				if (Right_Balance(root) == ERROR)return ERROR;
				*shorter = false;
				break;
			default:return ERROR;
			}
		}
	}
	else if (target > (*root)->data) {
		if (DeleteAVL_sub(&(*root)->rchild, target, shorter, flag) == ERROR)return ERROR;
		if (*shorter == true) {
			switch ((*root)->bf) {
			case -1:*shorter = true;
				(*root)->bf++;
				break;
			case 0:*shorter = false;
				(*root)->bf++;
				break;
			case 1:(*root)->bf++;
				if (Left_Balance(root) == ERROR)return ERROR;
				*shorter = false;
				break;
			default:return ERROR;
			}
		}
	}
	return OK;
}

Status DeleteAVL(BiTNode **root, int target, Status *shorter) {
	int flag = false;
	return DeleteAVL_sub(root, target, shorter, &flag);
}

BiTNode *SearchAVL(BiTNode *root, int target) {
	if (root == NULL)return NULL;
	else if (root->data == target)return root;
	else if (target < root->data)return SearchAVL(root->lchild, target);
	else return SearchAVL(root->rchild, target);
}

Status isAVL(BiTNode *root) {
	if (root) {
		if (root->bf > LH || root->bf < RH)return false;
		if (root->lchild && root->lchild->data >= root->data)return false;
		if (root->rchild && root->rchild->data <= root->data)return false;
		if (isAVL(root->lchild) == false)return false;
		if (isAVL(root->rchild) == false)return false;
	}
	return true;
}

int main() {
	BiTNode *root = NULL;
	int a[10] = { 20,10,30,15,25,40,23,46 };//{62,88,58,47,35,73,51,99,37,93};
	int i;
	int flag;
	for (i = 0; i < 8; i++) {
		if (InsertAVL(&root, a[i], &flag) != OK)return 1;
		PreOrderTraverse(root, PrintBiTree);
		printf("\n");
		InOrderTraverse(root, PrintBiTree);
		printf("\n");
		printf("\n");
	}
	// if (DeleteAVL(&root, 15, &flag) == ERROR)printf("ERROR\n");
	// InOrderTraverse(root, PrintBiTree);
	// printf("\n");
	// printf("%d\n", isAVL(root));
	return 0;
}
