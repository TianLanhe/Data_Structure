#ifndef BINART_SORT_TREE_H
#define BINART_SORT_TREE_H

#include "../tree/LinkBinaryTree.h"

Status SearchBST(BiTNode *tree,int target,BiTNode *parent,BiTNode **ptr);
//递归查找target在二叉树的位置，若查找成功，则返回OK，ptr返回指向该节点的指针
//若查找失败，则返回ERROR，ptr返回最后访问到的节点的指针
Status InsertBST(BiTNode **tree,int target);
//向二叉排序树中插入关键字为target的节点。若已存在target关键字的节点，则插入失败，返回ERROR
//若不存在target，则在相应位置插入节点，返回OK
Status DeleteBST(BiTNode **tree,int target);
//删除二叉排序树中关键字为target的节点(迭代法)，若已不存在target关键字的节点，则删除失败，返回ERROR
//若存在target，则在删除该节点并调整节点，返回OK
Status DeleteBST_recursion(BiTNode **tree,int target);
//删除二叉排序树中关键字为target的节点(递归法)，若不存在target关键字的节点，则删除失败，返回ERROR
//若存在target，则在删除该节点并调整节点，返回OK
Status Delete(BiTNode **node);
//删除二叉树节点递归法的子函数，进行node节点的具体删除操作
Status isBST(BiTNode *root);
//判断该数是否是二叉排序树，是则返回true，否则返回false

#endif
