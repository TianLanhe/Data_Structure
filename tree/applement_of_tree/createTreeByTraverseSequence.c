#include "../LinkBinaryTree.h"
#include "../../string/string.h"
#include <stdlib.h>

Status CreateTreeByPreAndInorder(BiTNode **root, char *preStr, char *inorderStr);
//根据先序和中序遍历结果生成二叉树，成功返回OK，失败返回ERROR
Status sub_CreateTreeByPreAndInorder(BiTNode **root, HString preStr, HString inorderStr);
//生成二叉树的子函数，构建二叉树，成功返回OK，失败返回ERROR
Status CreateTreeByPostAndInorder(BiTNode **root, char *postStr, char *inorderStr);
//根据后序和中序遍历结果生成二叉回树，成功返回OK，失败返ERROR
Status sub_CreateTreeByPostAndInorder(BiTNode **root, HString postStr, HString inorderStr);
//生成二叉树的子函数，构建二叉树，成功返回OK，失败返回ERROR
int isLegalString(char *str);
//判断字符串是否合法，即是否每个字符不重复且均不是空白字符，合法返回true否则返回false

int isLegalString(char *str) {
	int i;
	char flag[256] = { 0 };
	for (i = 0; str[i] != '\0'; ++i) {
		if (str[i] == ' ' || str[i] == '\n' ||
			str[i] == '\t' || str[i] == '\r' ||
			str[i] == '\f' || str[i] == '\v')
			return false;
		if (flag[str[i]])
			return false;
		flag[str[i]] = true;
	}
	return true;
}

Status CreateTreeByPreAndInorder(BiTNode **root, char *preStr, char *inorderStr) {
	HString HpreStr;
	HString HinorderStr;
	Status status;

	InitStr(&HpreStr);
	InitStr(&HinorderStr);
	if ((status = StrAssign(&HpreStr, preStr)) != OK)return status;
	if ((status = StrAssign(&HinorderStr, inorderStr)) != OK)return status;

	if (!isLegalString(preStr) || !isLegalString(inorderStr) || StrLength(HpreStr) != StrLength(HinorderStr))
		return ERROR;

	if ((status = sub_CreateTreeByPreAndInorder(root, HpreStr, HinorderStr)) != OK)return status;

	DestroyStr(&HpreStr);
	DestroyStr(&HinorderStr);
	return OK;
}

Status sub_CreateTreeByPreAndInorder(BiTNode **root, HString preStr, HString inorderStr) {
	if (!StrEmpty(preStr)) {
		HString new_preStr, new_inorderStr;
		Status status;
		int index_inorder;
		int i;

		*root = (BiTNode*)malloc(sizeof(BiTNode));
		if (!*root)
			return OVERFLOW;

		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
		(*root)->data = At(preStr, 0);

		index_inorder = Index(inorderStr, At(preStr, 0), 0);
		if (index_inorder == -1)
			return ERROR;

		InitStr(&new_inorderStr);
		InitStr(&new_preStr);

		if (index_inorder != 0) {
			status = SubString(&new_inorderStr, inorderStr, 0, index_inorder);
			if (status != OK)
				return status;

			status = SubString(&new_preStr, preStr, 1, index_inorder);
			if (status != OK)
				return status;

			for (i = 0; i < StrLength(new_preStr); ++i) {
				if (Index(new_inorderStr, At(new_preStr, i), 0) == -1)
					return ERROR;
			}

			status = sub_CreateTreeByPreAndInorder(&(*root)->lchild, new_preStr, new_inorderStr);
			if (status != OK)
				return status;
		}

		if (index_inorder != StrLength(inorderStr) - 1) {
			status = SubString(&new_inorderStr, inorderStr, index_inorder + 1, StrLength(inorderStr) - index_inorder - 1);
			if (status != OK)
				return status;

			status = SubString(&new_preStr, preStr, index_inorder + 1, StrLength(new_inorderStr));
			if (status != OK)
				return status;

			for (i = 0; i < StrLength(new_preStr); ++i) {
				if (Index(new_inorderStr, At(new_preStr, i), 0) == -1)
					return ERROR;
			}

			status = sub_CreateTreeByPreAndInorder(&(*root)->rchild, new_preStr, new_inorderStr);
			if (status != OK)
				return status;
		}

		DestroyStr(&new_preStr);
		DestroyStr(&new_inorderStr);
	}
	return OK;
}

Status CreateTreeByPostAndInorder(BiTNode **root, char *postStr, char *inorderStr) {
	HString HpostStr;
	HString HinorderStr;
	Status status;

	InitStr(&HpostStr);
	InitStr(&HinorderStr);
	if ((status = StrAssign(&HpostStr, postStr)) != OK)return status;
	if ((status = StrAssign(&HinorderStr, inorderStr)) != OK)return status;

	if (!isLegalString(postStr) || !isLegalString(inorderStr) || StrLength(HpostStr) != StrLength(HinorderStr))
		return ERROR;

	if ((status = sub_CreateTreeByPostAndInorder(root, HpostStr, HinorderStr)) != OK)return status;

	DestroyStr(&HpostStr);
	DestroyStr(&HinorderStr);
	return OK;
}

Status sub_CreateTreeByPostAndInorder(BiTNode **root, HString postStr, HString inorderStr) {
	if (!StrEmpty(postStr)) {
		HString new_postStr, new_inorderStr;
		Status status;
		int index_inorder;
		int i;

		*root = (BiTNode*)malloc(sizeof(BiTNode));
		if (!*root)
			return OVERFLOW;

		(*root)->lchild = NULL;
		(*root)->rchild = NULL;
		(*root)->data = At(postStr, StrLength(postStr) - 1);

		index_inorder = Index(inorderStr, (*root)->data, 0);
		if (index_inorder == -1)
			return ERROR;

		InitStr(&new_inorderStr);
		InitStr(&new_postStr);

		if (index_inorder != StrLength(inorderStr) - 1) {
			status = SubString(&new_inorderStr, inorderStr, index_inorder + 1, StrLength(inorderStr) - index_inorder - 1);
			if (status != OK)
				return status;

			status = SubString(&new_postStr, postStr, StrLength(postStr) - StrLength(new_inorderStr) - 1, StrLength(new_inorderStr));
			if (status != OK)
				return status;

			for (i = 0; i < StrLength(new_postStr); ++i) {
				if (Index(new_inorderStr, At(new_postStr, i), 0) == -1)
					return ERROR;
			}

			status = sub_CreateTreeByPostAndInorder(&(*root)->rchild, new_postStr, new_inorderStr);
			if (status != OK)
				return status;
		}

		if (index_inorder != 0) {
			status = SubString(&new_inorderStr, inorderStr, 0, index_inorder);
			if (status != OK)
				return status;

			status = SubString(&new_postStr, postStr, 0, index_inorder);
			if (status != OK)
				return status;

			for (i = 0; i < StrLength(new_postStr); ++i) {
				if (Index(new_inorderStr, At(new_postStr, i), 0) == -1)
					return ERROR;
			}

			status = sub_CreateTreeByPostAndInorder(&(*root)->lchild, new_postStr, new_inorderStr);
			if (status != OK)
				return status;
		}

		DestroyStr(&new_postStr);
		DestroyStr(&new_inorderStr);
	}
	return OK;
}

int main() {
	char *postStr = "DBEFCA";
	char *inorderStr = "DBAECF";
	BiTNode *root;
	CreateTreeByPostAndInorder(&root, postStr, inorderStr);
	LevelOrderTraverse(root, PrintBiTree);
	DestroyBiTree(&root);
	return 0;
}
