#ifndef BALANCED_BINART_TREE
#define BALANCED_BINART_TREE

#include "../DataStructureBase.h"

#define LH (+1)		//左高
#define RH (-1)		//右高
#define EH (0)		//等高
#define LOH (2)		//左失衡
#define ROH (-2)	//右失衡
#define INDENT (2)	//打印时的缩进格数

typedef struct _bitree {
	int data;
	int bf;					//平衡因子
	struct _bitree *lchild;
	struct _bitree *rchild;
}BiTNode;

Status PreOrderTraverse(BiTNode *root, Status(*visit)(BiTNode *));
//先序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status InOrderTraverse(BiTNode *root, Status(*visit)(BiTNode *));
//中序遍历(递归法)二叉树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintBiTree(BiTNode *node);
//遍历函数的功能函数，打印节点的数据值
void PrintBiTreeFriendly(BiTNode *root);
//凹入表打印友好的树形界面，省略缩进参数
void PrintBiTreeFriendly_sub(BiTNode *root, int indent) {
//打印树形界面的子函数

Status Left_Rotate(BiTNode **root);
//将以root为根的子树进行左旋处理，并使root指向旋转后的根
Status Right_Rotate(BiTNode **root);
//将以root为根的子树进行右旋处理，并使root指向旋转后的根
Status Left_Balance(BiTNode **root);
//对以root为根的子树进行左平衡处理，并使root指向旋转后的根(在上面两个函数中实现)
Status Right_Balance(BiTNode **root);
//对以root为根的子树进行右平衡处理，并使root指向旋转后的根(在上面两个函数中实现)
Status InsertAVL(BiTNode **root, int target, Status *taller);
//向二叉排序树中插入关键字为target的节点。若已存在target关键字的节点，则插入失败，返回ERROR
//若不存在target，则在相应位置插入节点，并进行旋转(若需要)，返回OK
Status DeleteAVL_sub(BiTNode **root, int target, Status *shorter, Status *flag);
//删除二叉排序树中关键字为target的节点，若不存在target关键字的节点，则删除失败，返回ERROR
//若存在target，则在删除该节点并调整节点位置与平衡因子，返回OK
Status DeleteAVL(BiTNode **root, int target, Status *shorter);
//封装了上述的删除函数，隐藏了flag参数
BiTNode *SearchAVL(BiTNode *root, int target);
//搜索二叉平衡树，若存在关键字为target的节点，则返回该节点的地址，否则返回NULL
Status isAVL(BiTNode *root);
//判断该数是否是二叉平衡树，是则返回true，否则返回false

#endif
