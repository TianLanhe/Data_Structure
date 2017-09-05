#include "BinarySortTree.h"
#include <stdlib.h>

Status TPrintBiTree(BiTNode *node) {
	if (!node)return ERROR;
	printf("%d ", node->data);
	return OK;
}

int main() {
	int a[10] = { 62,88,58,47,35,73,51,99,37,93 };
	int i;
	BiTNode *root;
	root = NULL;
	for (i = 0; i < 10; i++) {
		if (InsertBST(&root, a[i]) == ERROR)return ERROR;
		PreOrderTraverse(root, TPrintBiTree);
		printf("\n");
		InOrderTraverse(root,TPrintBiTree);
		printf("\n");
		printf("\n");
	}

	DeleteBST(&root, 62);
	PreOrderTraverse(root, TPrintBiTree);
	printf("\n");
	InOrderTraverse(root, TPrintBiTree);
	printf("\n");
	return 0;
}
