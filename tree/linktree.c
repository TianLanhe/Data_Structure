#include "LinkBinaryTree.h"

int main() {
	BiTNode *bitree;
	BiTNode *node;
	int level;

	CreateBiTree(&bitree);
	// PreOrderTraverse_stack(bitree, PrintBiTree);
	// printf("\n");
	InOrderTraverse_stack(bitree, PrintBiTree);
	printf("\n");
	// PostOrderTraverse_stack(bitree, PrintBiTree);
	// printf("\n");
	LevelOrderTraverse(bitree, PrintBiTree);
	printf("\n");
	return 0;
}
