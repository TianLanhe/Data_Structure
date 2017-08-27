#include <stdio.h>
#include <stdlib.h>
#include "ThreadedLinkBinaryTree.h"

Status InitBiTree(TBiTNode **root) {
	*root = (TBiTNode *)malloc(sizeof(TBiTNode));
	if (!*root)return OVERFLOW;
	(*root)->lchild = *root;
	(*root)->rchild = *root;
	(*root)->LTag = THREAD;
	(*root)->RTag = THREAD;
	(*root)->data = 0;
	return OK;
}

Status DestroyBiTree(TBiTNode **thrt) {
	if (ClearBiTree(*thrt) == ERROR)return ERROR;
	free(*thrt);
	*thrt = NULL;
	return OK;
}

Status ClearBiTree_sub(TBiTNode **root) {
	if (*root) {
		if ((*root)->LTag == LINK)
			ClearBiTree_sub(&(*root)->lchild);
		if ((*root)->RTag == LINK)
			ClearBiTree_sub(&(*root)->rchild);
		free(*root);
		*root = NULL;
	}
	return OK;
}

Status ClearBiTree(TBiTNode *thrt) {
	if (!thrt)return ERROR;
	if (thrt->lchild == thrt)return OK;
	if (ClearBiTree_sub(&thrt->lchild) == ERROR)return ERROR;
	thrt->lchild = thrt;
	thrt->LTag = THREAD;
	thrt->rchild = thrt;
	thrt->RTag = THREAD;
	return OK;
}

Status PrintBiTree(TBiTNode *node) {
	if (!node)return ERROR;
	printf("%c", node->data);
	return OK;
}

Status CreateBiTree_sub(TBiTNode **root) {
	char ch;
	do {
		ch = getchar();
	} while (ch == '\n');
	if (ch == ' ')(*root) = NULL;
	else {
		(*root) = (TBiTNode *)malloc(sizeof(TBiTNode));
		if (!(*root))return OVERFLOW;
		(*root)->data = ch;
		CreateBiTree_sub(&(*root)->lchild);
		CreateBiTree_sub(&(*root)->rchild);
	}
	return OK;
}

void InOrderThreading_sub(TBiTNode *cur, TBiTNode **pre) {
	if (cur) {
		InOrderThreading_sub(cur->lchild, pre);

		if (!cur->lchild) {
			cur->LTag = THREAD;
			cur->lchild = *pre;
		}
		else cur->LTag = LINK;

		if (!(*pre)->rchild) {
			(*pre)->RTag = THREAD;
			(*pre)->rchild = cur;
		}
		else (*pre)->RTag = LINK;

		*pre = cur;
		InOrderThreading_sub(cur->rchild, pre);
	}
}

Status InOrderThreading(TBiTNode **thrt, TBiTNode *root) {
	Status status;
	if ((status = InitBiTree(thrt)) != OK)
		return status;
	if (root) {
		TBiTNode *pre;
		(*thrt)->lchild = root;
		(*thrt)->LTag = LINK;
		pre = (*thrt);
		InOrderThreading_sub(root, &pre);
		pre->rchild = (*thrt);
		pre->RTag = THREAD;
		(*thrt)->rchild = pre;
		(*thrt)->RTag = THREAD;
	}
	return OK;
}

Status CreateBiTree(TBiTNode **thrt) {
	TBiTNode *root;
	if (CreateBiTree_sub(&root) == ERROR)
		return ERROR;
	if (InOrderThreading(thrt, root) == ERROR)
		return ERROR;
	return OK;
}

Status InOrderTraverse(TBiTNode *thrt, Status(*visit)(TBiTNode *)) {
	TBiTNode *node;
	node = thrt->lchild;
	while (node != thrt) {
		while (node->LTag == LINK)node = node->lchild;

		if (visit(node) == ERROR)
			return ERROR;

		while (node->RTag == THREAD && node->rchild != thrt) {
			node = node->rchild;

			if (visit(node) == ERROR)
				return ERROR;
		}
		node = node->rchild;
	}
	return OK;
}

