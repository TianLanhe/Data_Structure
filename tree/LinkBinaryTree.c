#include <stdio.h>
#include <stdlib.h>
#include "LinkBinaryTree.h"

#define SElemType BiTNode*
#define QElemType BiTNode*

#include "../queue/SequQueue.h"
#include "../stack/SequStack.h"

#define InitTreeQueue InitQueue
#define DestroyTreeQueue DestroyQueue
#define TreeEnQueue EnQueue
#define TreeQueue SqQueue
#define TreeDeQueue DeQueue
#define TQueueEmpty QueueEmpty

#define TreeStack SqStack
#define InitTreeStack InitStack
#define DestroyTreeStack DestroyStack
#define TreePush Push
#define	TreePop Pop
#define TStackEmpty StackEmpty
#define TStackGetTop GetTop

Status InitBiTree(BiTNode **root) {
	*root = NULL;
	return OK;
}

Status DestroyBiTree(BiTNode **root) {
	if (*root) {
		DestroyBiTree(&(*root)->lchild);
		DestroyBiTree(&(*root)->rchild);
		free(*root);
		*root = NULL;
	}
	return OK;
}

Status CreateBiTree(BiTNode **root) {
	char ch;
	do {
		ch = getchar();
	} while (ch == '\n');
	if (ch == ' ')(*root) = NULL;
	else {
		(*root) = (BiTNode *)malloc(sizeof(BiTNode));
		if (!(*root))return OVERFLOW;
		(*root)->data = ch;
		CreateBiTree(&(*root)->lchild);
		CreateBiTree(&(*root)->rchild);
	}
	return OK;
}

Status BiTreeEmpty(BiTNode *root) {
	if (!root)return true;
	else return false;
}

Status isSubBiTree(BiTNode *root, BiTNode *node) {
	if (root) {
		if (root == node)return true;
		if (!isSubBiTree(root->lchild, node) && !isSubBiTree(root->rchild, node))
			return false;
	}
	return false;
}

TElemType Value(BiTNode *root, BiTNode *node) {
	if (!node || !root || !isSubBiTree(root, node))
		return 0; //其实正常返回值也有可能是0
	return node->data;
}

int BiTreeDepth(BiTNode *root) {
	if (root) {
		int ldepth, rdepth;
		ldepth = BiTreeDepth(root->lchild);
		rdepth = BiTreeDepth(root->rchild);
		return (ldepth > rdepth ? ldepth : rdepth) + 1;
	}
	return 0;
}

int BiTNodeLevel(BiTNode *root, BiTNode *node) {
	if (root) {
		int level;
		if (node == root)
			return 1;

		level = BiTNodeLevel(root->lchild, node);
		if (level != -1)
			return level + 1;

		level = BiTNodeLevel(root->rchild, node);
		if (level != -1)
			return level + 1;

		return -1;
	}
	return -1;
}

Status Assign(BiTNode *root, BiTNode *node, TElemType data) {
	if (!node || !root || !isSubBiTree(root, node))
		return ERROR;
	node->data = data;
	return OK;
}

BiTNode *GetParent(BiTNode *root, BiTNode *node) {
	if (root && node) {
		BiTNode *temp;
		if (root->lchild == node || root->rchild == node)return root;
		if (temp = GetParent(root->lchild, node))return temp;
		if (temp = GetParent(root->rchild, node))return temp;
	}
	return NULL;
}

BiTNode *LeftChild(BiTNode *root, BiTNode *node) {
	if (!node || !root || !isSubBiTree(root, node))
		return NULL;	// NULL也是合法的孩子
	return node->lchild;
}

BiTNode *RightChild(BiTNode *root, BiTNode *node) {
	if (!node || !root || !isSubBiTree(root, node))
		return NULL;	// NULL也是合法的孩子
	return node->rchild;
}

BiTNode *LeftSiblint(BiTNode *root, BiTNode *node) {
	BiTNode *parent;
	parent = GetParent(root, node);
	if (!parent || node == parent->lchild)
		return NULL;	// NULL也是合法的孩子
	return parent->lchild;
}

BiTNode *RightSiblint(BiTNode *root, BiTNode *node) {
	BiTNode *parent;
	parent = GetParent(root, node);
	if (!parent || node == parent->rchild)
		return NULL;	// NULL也是合法的孩子
	return parent->rchild;
}

Status InsertChild(BiTNode *root, BiTNode *node, int lr, BiTNode *newnode) {
	if (!root || !newnode || (lr != LEFT && lr != RIGHT) || !node || !isSubBiTree(root, node))
		return ERROR;
	if (newnode->rchild || isSubBiTree(root, newnode))
		return ERROR;
	if (lr == LEFT) {
		newnode->rchild = node->lchild;
		node->lchild = newnode;
	}
	else if (lr == RIGHT) {
		newnode->rchild = node->rchild;
		node->rchild = newnode;
	}
	return OK;
}

Status DeleteChild(BiTNode *root, BiTNode *node, int lr, BiTNode **newnode) {
	if (!root || (lr != LEFT && lr != RIGHT) || !node || !isSubBiTree(root, node))return ERROR;
	if (lr == LEFT) {
		*newnode = node->lchild;
		node->lchild = NULL;
	}
	else if (lr == RIGHT) {
		*newnode = node->rchild;
		node->rchild = NULL;
	}
	return OK;
}

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

Status PostOrderTraverse(BiTNode *root, Status(*visit)(BiTNode *)) {
	if (root) {
		if (PostOrderTraverse(root->lchild, visit) == ERROR)return ERROR;
		if (PostOrderTraverse(root->rchild, visit) == ERROR)return ERROR;
		if (visit(root) == ERROR)return ERROR;
	}
	return OK;
}

Status PreOrderTraverse_stack(BiTNode *root, Status(*visit)(BiTNode *)) {
	TreeStack stack;
	BiTNode *temp;

	InitTreeStack(&stack);
	temp = root;
	if (TreePush(&stack, temp) == ERROR)return ERROR;
	if (visit(temp) == ERROR)return ERROR;

	while (!TStackEmpty(stack)) {
		while (TStackGetTop(stack, &temp) && temp) {
			if (TreePush(&stack, temp->lchild) == ERROR)return ERROR;
			if (temp->lchild)
				if (!visit(temp->lchild))return ERROR;
		}
		if (!TreePop(&stack, &temp))return ERROR;
		if (!TStackEmpty(stack)) {
			if (!TreePop(&stack, &temp))return ERROR;
			if (!TreePush(&stack, temp->rchild))return ERROR;
			if (temp->rchild)if (!visit(temp->rchild))return ERROR;
		}
	}
	return OK;
}

Status InOrderTraverse_stack(BiTNode *root, Status(*visit)(BiTNode *)) {
	TreeStack stack;
	BiTNode *temp;

	// if (!root)
	// 	return OK;

	// InitTreeStack(&stack);
	// temp = root;

	// if (TreePush(&stack, temp) == ERROR)
	// 	return ERROR;

	// while (!TStackEmpty(stack)) {
	// 	while (TStackGetTop(stack, &temp)==OK && temp)
	// 		if (TreePush(&stack, temp->lchild) == ERROR)
	// 			return ERROR;
	// 	if(TreePop(&stack,&temp)==ERROR)return ERROR;

	// 	if (!TStackEmpty(stack)) {
	// 		if (TreePop(&stack, &temp) == ERROR)return ERROR;
	// 		if (visit(temp) == ERROR)return ERROR;
	// 		if (TreePush(&stack, temp->rchild) == ERROR)return ERROR;
	// 	}
	// }

	InitTreeStack(&stack);
	temp = root;
	while (temp) {
		if (TreePush(&stack, temp) == ERROR)return ERROR;
		temp = temp->lchild;
	}
	while (!TStackEmpty(stack)) {
		if (TreePop(&stack, &temp) == ERROR)return ERROR;
		if (visit(temp) == ERROR)return ERROR;

		temp = temp->rchild;
		while (temp) {
			if (TreePush(&stack, temp) == ERROR)return ERROR;
			temp = temp->lchild;
		}
	}

	DestroyTreeStack(&stack);
	return OK;
}

Status PostOrderTraverse_stack(BiTNode *root, Status(*visit)(BiTNode *)) {
	TreeStack stack;
	BiTNode *temp;
	BiTNode *pre;
	InitTreeStack(&stack);
	temp = root;
	pre = NULL;
	while (temp || !TStackEmpty(stack)) {
		if (temp) {
			TreePush(&stack, temp);
			temp = temp->lchild;
		}
		else if (TStackGetTop(stack, &temp) && (!temp->rchild || temp->rchild == pre)) {
			TreePop(&stack, &temp);
			if (!visit(temp))return ERROR;
			pre = temp;
			temp = NULL;
		}
		else {
			temp = temp->rchild;
		}
	}
	return OK;
}

Status LevelOrderTraverse(BiTNode *root, Status(*visit)(BiTNode *)) {
	TreeQueue queue;
	BiTNode *node;
	InitTreeQueue(&queue);
	TreeEnQueue(&queue, root);
	while (!TQueueEmpty(queue)) {
		if (TreeDeQueue(&queue, &node) == ERROR)return ERROR;
		if (visit(node) == ERROR)return ERROR;
		if (node->lchild && TreeEnQueue(&queue, node->lchild) == ERROR)return ERROR;
		if (node->rchild && TreeEnQueue(&queue, node->rchild) == ERROR)return ERROR;
	}
	DestroyTreeQueue(&queue);
	return OK;
}

Status PrintBiTree(BiTNode *node) {
	if (!node)return ERROR;
	printf("%c", node->data);
	return OK;
}
