#include <stdlib.h>
#include "BinarySortTree.h"

Status SearchBST(BiTNode *tree, int target, BiTNode *parent, BiTNode **ptr) {
	if (tree == NULL) {
		*ptr = parent;
		return ERROR;
	}
	else if (tree->data == target) {
		*ptr = tree;
		return OK;
	}
	else if (target < tree->data)
		return SearchBST(tree->lchild, target, tree, ptr);
	else
		return SearchBST(tree->rchild, target, tree, ptr);
}

Status InsertBST(BiTNode **tree, int target) {
	BiTNode *ptr;
	BiTNode *parent;
	if (SearchBST(*tree, target, NULL, &parent) == ERROR) {
		ptr = (BiTNode*)malloc(sizeof(BiTNode));
		if(!ptr)
			return OVERFLOW;
		ptr->data = target;
		ptr->lchild = NULL;
		ptr->rchild = NULL;

		if (parent == NULL)
			*tree = ptr;
		else if (target < parent->data)
			parent->lchild = ptr;
		else
			parent->rchild = ptr;
		return OK;
	}
	else
		return ERROR;
}

Status DeleteBST(BiTNode **tree, int target) {
	BiTNode *ptr;
	return SearchBST(*tree, target, NULL, &ptr) == OK ? Delete(&ptr) : ERROR;
}

Status Delete(BiTNode **node) {
	BiTNode *temp;
	if (node == NULL || *node == NULL)
		return ERROR;
	if ((*node)->lchild == NULL) {	//左子树为空
		temp = *node;
		*node = (*node)->rchild;
	}
	else if ((*node)->rchild == NULL) {	//右子树为空
		temp = *node;
		*node = (*node)->lchild;
	}
	else {							//左右子树均不空
		BiTNode *parent;
		parent = *node;
		temp = (*node)->lchild;		//被删除结点的左孩子
		while (temp->rchild) {		//走到右尽头
			parent = temp;
			temp = temp->rchild;
		}
		(*node)->data = temp->data;	//右尽头移接到被删除结点
		if (parent == *node)parent->lchild = temp->lchild;
		else parent->rchild = temp->lchild;
	}
	free(temp);
	return OK;
}

Status DeleteBST_recursion(BiTNode **tree, int target) {
	if (*tree == NULL)
		return ERROR;
	else if ((*tree)->data == target)
		return Delete(tree);
	else if (target < (*tree)->data)
		return DeleteBST_recursion(&(*tree)->lchild, target);
	else
		return DeleteBST_recursion(&(*tree)->rchild, target);
}

Status isBST(BiTNode *root) {
	if (root) {
		if (root->lchild && root->lchild->data >= root->data)return false;
		if (root->rchild && root->rchild->data <= root->data)return false;
		if (isBST(root->lchild) == false)return false;
		if (isBST(root->rchild) == false)return false;
	}
	return true;
}
