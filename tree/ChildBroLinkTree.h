#ifndef CHILD_BRO_LINK_TREE_H
#define CHILD_BRO_LINK_TREE_H

#include "../DataStructureBase.h"

#ifndef TElemType
#define TElemType ElemType
#endif

typedef struct _cstree {				//孩子兄弟链表树
	TElemType data;
	struct _cstree *firstchild;			//左孩子
	struct _cstree *nextsibling;		//右孩子
}CSTNode;

Status DestroyCSTree(CSTNode **root);
//销毁树root，使其为空树
Status DestroyCSForest(CSTNode **root);
//销毁森林root，循环删除root及其后续的nextsibling.使其成为空森林
Status PreOrderTraverseCSTrees(CSTNode *root, Status(*visit)(CSTNode *));
//先序遍历(递归法)树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PreOrderTraverseCSForest(CSTNode *root, Status(*visit)(CSTNode *));
//先序遍历(递归法)森林root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status InOrderTraverseCSTrees(CSTNode *root, Status(*visit)(CSTNode *));
//中序遍历(递归法)树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status InOrderTraverseCSForest(CSTNode *root, Status(*visit)(CSTNode *));
//中序遍历(递归法)森林root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintCSTree(CSTNode *node);
//遍历函数的功能函数，打印节点的数据值

#endif