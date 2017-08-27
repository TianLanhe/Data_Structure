#ifndef THREADED_LINK_BINARY_TREE
#define THREADED_LINK_BINARY_TREE

#include "../DataStructureBase.h"
#define TElemType ElemType

typedef enum _pointtag {		//用枚举变量表示，当然也可以用宏
	LINK,						//表示是孩子
	THREAD 						//表示是线索
}PointTag;

typedef struct _bitree {
	TElemType data;				//数据域
	PointTag LTag;				//左标志，等于LINK为左孩子，等于THREAD为前驱
	PointTag RTag;				//右标志，等于LINK为右孩子，等于THREAD为后继
	struct _bitree *lchild;		//左孩子指针
	struct _bitree *rchild;		//右孩子指针
}TBiTNode;

Status InitBiTree(TBiTNode **root);
//初始化空树，创建虚头结点
Status DestroyBiTree(TBiTNode **root);
//销毁二叉树root，使头结点为空
Status ClearBiTree_sub(TBiTNode **root);
//清空二叉树的子函数
Status ClearBiTree(TBiTNode *root);
//清空二叉树，使其只剩头结点
Status CreateBiTree_sub(TBiTNode **root);
//创建线索二叉树的子函数，先序创建二叉树root
void InOrderThreading_sub(TBiTNode *cur,TBiTNode **pre);
//线索化二叉树的子函数，中序遍历并线索化二叉树root
Status InOrderThreading(TBiTNode **thrt, TBiTNode *root);
//线索化二叉树，为二叉树分配虚头结点，进行所有结点的线索化
Status CreateBiTree(TBiTNode **thrt);
//先序创建线索二叉树，包括创建二叉树和线索化两个过程
Status InOrderTraverse(TBiTNode *root, Status(*visit)(TBiTNode *));
//中序遍历(非递归线索化法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintBiTree(TBiTNode *node);
//遍历函数的功能函数，打印节点的数据值

#endif