#include "GeneralList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Status InitGList(GLNode **glist) {
	CHECK_ERROR(glist);

	*glist = (GLNode *)malloc(sizeof(GLNode));
	CHECK_OVERFLOW(glist);

	(*glist)->tag = LIST;
	(*glist)->hp = NULL;
	(*glist)->next = NULL;
	return OK;
}

Status DestroyGList(GLNode **glist) {
	if ((*glist)->tag == LIST && !(*glist)->hp || (*glist)->tag == ATOM) {
		free(*glist);
		*glist = NULL;
	}
	else {
		GLNode *node;
		GLNode *temp;
		node = (*glist)->hp;
		while (node) {
			temp = node->next;
			DestroyGList(&node);
			node = temp;
		}
		free(*glist);
		*glist = NULL;
	}
	return OK;
}

Status RemBracket(char **substr, char *str) {
	int len;
	int i;
	len = strlen(str);
	CHECK_ERROR(str[0] == '(' && str[len - 1] == ')');

	(*substr) = (char *)malloc(sizeof(char)*(len - 1));
	CHECK_OVERFLOW(*substr);

	for (i = 1; i < len - 1; i++)
		(*substr)[i - 1] = str[i];
	(*substr)[i - 1] = '\0';
	return OK;
}

Status SplitStr(char ***arrstr, char *astr, int *len) {
	int i, k, num;
	int start;

	// 复制原字符串，可以用来修改，不会影响到原字符串
	char *str;
	str = (char*)malloc(sizeof(char)*(strlen(astr) + 1));
	CHECK_OVERFLOW(str);
	strcpy(str, astr);

	(*arrstr) = (char **)malloc(sizeof(char*)*(strlen(str) + 1));
	CHECK_OVERFLOW(*arrstr);

	start = 0;
	k = 0;
	num = 0;
	for (i = 0; str[i]; i++) {
		if (str[i] == '(')k++;
		else if (str[i] == ')')k--;
		else if (str[i] == ',' && !k) {
			str[i] = '\0';
			if (strlen(str + start) != 0) {
				(*arrstr)[num] = (char*)malloc(sizeof(char)*(strlen(str + start) + 1));
				CHECK_OVERFLOW((*arrstr)[num]);

				strcpy((*arrstr)[num], str + start);
				++num;
			}
			str[i] = ',';
			start = i + 1;
		}
	}
	if (strlen(str + start) != 0) {
		(*arrstr)[num] = (char*)malloc(sizeof(char)*(strlen(str + start) + 1));
		CHECK_OVERFLOW((*arrstr)[num]);

		strcpy((*arrstr)[num], str + start);
		++num;
	}
	*len = num;

	(*arrstr) = (char **)realloc(*arrstr, sizeof(char*)*num);
	CHECK_OVERFLOW(*arrstr);
	free(str);
	return OK;
}

Status CreateGList(GLNode **glist, char *str) {
	BEFORE_CHECK_RESULT();
	CHECK_RESULT(InitGList(glist));
	if (strlen(str) == 1) {
		(*glist)->tag = ATOM;
		(*glist)->atom = *str;
	}
	else if (strcmp(str, "()")) {
		char *substr;
		char **splitstr;
		int n, i;
		GLNode *temp, *p;

		CHECK_RESULT(RemBracket(&substr, str));
		CHECK_RESULT(SplitStr(&splitstr, substr, &n));
		free(substr);

		for (i = 0, p = *glist; i < n; i++) {
			CHECK_RESULT(CreateGList(&temp, splitstr[i]));
			if (!i) {
				p->hp = temp;
				p = p->hp;
			}
			else {
				p->next = temp;
				p = p->next;
			}
		}

		for (i = 0; i < n; i++)
			free(splitstr[i]);
		free(splitstr);
	}
	AFTER_CHECK_RESULT();
}

Status PrintGList(GLNode *glist) {
	if (glist->tag == ATOM)printf("%c", glist->atom);
	else if (!glist->hp)printf("()");
	else if (glist->tag == LIST) {
		GLNode *node;
		printf("(");
		for (node = glist->hp; node; node = node->next) {
			PrintGList(node);
			if (node->next)printf(",");
		}
		printf(")");
	}
	return OK;
}

Status CopyGList(GLNode **newglist, GLNode *glist) {

	InitGList(newglist);
	if (glist->tag == ATOM) {
		(*newglist)->tag = ATOM;
		(*newglist)->atom = glist->atom;
	}
	else if (glist->tag == LIST&&glist->hp) {
		GLNode *node;
		GLNode *newnode;
		GLNode *p;
		for (node = glist->hp, p = *newglist; node; node = node->next) {
			CopyGList(&newnode, node);
			if (node == glist->hp) {
				p->hp = newnode;
				p = p->hp;
			}
			else {
				p->next = newnode;
				p = p->next;
			}
		}
	}
	return OK;
}

int GListLength(GLNode *glist) {
	int i;
	if (!glist || !glist->hp)return 0;
	for (glist = glist->hp, i = 0; glist; glist = glist->next, i++);
	return i;
}

Status GListEmpty(GLNode *glist) {
	if (!glist || !glist->hp)return true;
	else return false;
}

GLNode *GetGLHead(GLNode *glist) {
	if (!glist || !glist->hp)
		return NULL;
	return glist->hp;
}

GLNode *GetGLTail(GLNode *glist) {
	if (!glist || !glist->hp)
		return NULL;
	return glist->hp->next;
}

int GListDepth(GLNode *glist) {
	if (glist->tag == LIST && !glist->hp)return 1;
	if (glist->tag == ATOM)return 0;
	int max;
	GLNode *node;
	for (node = GetGLHead(glist), max = 0; node; node = node->next)
		if (max < GListDepth(node))
			max = GListDepth(node);
	return max + 1;
}

Status InsetFirst_GL(GLNode **glist, GLNode *node) {
	GLNode *head;
	CHECK_ERROR(glist && *glist && node);
	CopyGList(&head, node);
	head->next = (*glist)->hp;
	(*glist)->hp = head;
	return OK;
}

Status DeleteFirst_GL(GLNode **glist, GLNode **node) {
	CHECK_ERROR(glist && *glist && (*glist)->hp);
	*node = (*glist)->hp;
	(*glist)->hp = (*glist)->hp->next;
	(*node)->next = NULL;
	return OK;
}

Status Add(GLNode *node) {
	CHECK_ERROR(node && node->tag == ATOM);
	node->atom++;
	return OK;
}

Status TraverseGList(GLNode *glist, Status(*visit)(GLNode*)) {
	if (!glist || !glist->hp)
		return ERROR;
	if (glist->tag == ATOM) {
		if (!visit(glist))return ERROR;
	}
	else if (glist->tag == LIST) {
		GLNode *node;
		for (node = glist->hp; node; node = node->next)
			TraverseGList(node, visit);
	}
	return OK;
}
