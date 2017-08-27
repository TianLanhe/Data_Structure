#include "ChildBroLinkTree.h"
#include <stdlib.h>
#include <stdio.h>

Status DestroyCSTree(CSTNode **root) {
	CSTNode *node;
	CSTNode *temp;
	node = (*root)->firstchild;
	free(*root);
	*root = NULL;
	while (node) {
		temp = node->nextsibling;
		if (DestroyCSTree(&node) == ERROR)return ERROR;
		node = temp;
	}
	return OK;
}

Status DestroyCSForest(CSTNode **root) {
	CSTNode *tree, *temp;
	tree = *root;
	while (tree) {
		temp = tree->nextsibling;
		if (DestroyCSTree(&tree) == ERROR)return ERROR;
		tree = temp;
	}
	(*root) = NULL;
	return OK;
}

Status PreOrderTraverseCSTrees(CSTNode *root, Status(*visit)(CSTNode *)) {
	CSTNode *node;
	if (visit(root) == ERROR)return ERROR;
	for (node = root->firstchild; node; node = node->nextsibling) {
		if (PreOrderTraverseCSTrees(node, visit) == ERROR)return ERROR;
	}
	return OK;
}

Status PreOrderTraverseCSForest(CSTNode *root, Status(*visit)(CSTNode *)) {
	CSTNode *trees;
	for (trees = root; trees; trees = trees->nextsibling) {		//对森林root的每棵树都调用一次前序遍历
		if (PreOrderTraverseCSTrees(trees, visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}

Status InOrderTraverseCSTrees(CSTNode *root, Status(*visit)(CSTNode *)) {
	CSTNode *node;
	for (node = root->firstchild; node; node = node->nextsibling) {
		if (InOrderTraverseCSTrees(node, visit) == ERROR)return ERROR;
	}
	if (visit(root) == ERROR)return ERROR;
	return OK;
}

Status InOrderTraverseCSForest(CSTNode *root, Status(*visit)(CSTNode *)) {
	CSTNode *trees;
	for (trees = root; trees; trees = trees->nextsibling) {		//对森林root的每棵树都调用一次中序遍历
		if (InOrderTraverseCSTrees(trees, visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}

Status PrintCSTree(CSTNode *node) {
	printf("%3d", node->data);
	return OK;
}
