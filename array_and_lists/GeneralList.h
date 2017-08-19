#ifndef GENELIST_H
#define GENELIST_H

#include "../DataStructureBase.h"

#ifndef AtomType
#define AtomType ElemType
#endif

typedef enum _tag {
	ATOM,
	LIST
}ElemTag;

typedef struct _genenode {
	ElemTag tag;
	union {
		AtomType atom;
		struct _genenode *hp;
	};
	struct _genenode *next;
}GLNode;

Status RemBracket(char **substr, char *str);
//删除（广义表书写形式）字符串外面的括号
Status SplitStr(char ***arrstr, char *str, int *len);
//将字符串str以逗号为分隔符分为若干个子串，存在arrstr字符串数组里，并将子串的个数储存在len中
Status InitGList(GLNode **glist);
//初始化广义表glist，设定其为LIST，表头指针和后继指针均为空
Status DestroyGList(GLNode **glist);
//销毁广义表glist
Status CreateGList(GLNode **glist, char *str);
//str是广义表的书写形式串，由str创建广义表
Status CopyGList(GLNode **newglist, GLNode *glist);
//由广义表glist复制得到newglist
int GListLength(GLNode *glist);
//求广义表glist的长度，即元素个数
int GListDepth(GLNode *glist);
//求广义表glist的深度，即广义表括弧的重数
Status GListEmpty(GLNode *glist);
//判断广义表是否为空表，是则返回TRUE,否则返回FALSE
GLNode *GetGLHead(GLNode *glist);
//取广义表glist的表头
GLNode *GetGLTail(GLNode *glist);
//取广义表glist的表尾
Status InsetFirst_GL(GLNode **glist, GLNode *node);
//插入元素node作为广义表glist的第一元素
Status DeleteFirst_GL(GLNode **glist, GLNode **node);
//删除广义表glist的第一元素，并用node返回其值
Status PrintGList(GLNode *glist);
//打印广义表的书写形式字符串
Status Add(GLNode *node);
//遍历广义表的功能函数，将每个原子的atom值加一
Status TraverseGList(GLNode *glist, Status(*visit)(GLNode *));
//遍历广义表glist，用函数visit处理每个元素

#endif
