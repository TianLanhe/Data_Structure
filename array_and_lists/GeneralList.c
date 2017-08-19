#include "GeneralList.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

Status InitGList(GLNode **glist) {
	if (!glist)
		return ERROR;
	*glist = (GLNode *)malloc(sizeof(GLNode));
	if (!(*glist))
		return OVERFLOW;
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
	if (str[0] != '(' || str[len - 1] != ')')
		return ERROR;
	(*substr) = (char *)malloc(sizeof(char)*(len - 1));
	if (!(*substr))
		return OVERFLOW;
	for (i = 1; i < len - 1; i++)(*substr)[i - 1] = str[i];
	(*substr)[i - 1] = '\0';
	return OK;
}
Status SplitStr(char ***arrstr, char *astr, int *len) {
	int i, k, num;
	int start;

	// 复制原字符串，可以用来修改，不会影响到原字符串
	char *str;
	str = (char*)malloc(sizeof(char)*(strlen(astr) + 1));
	if (!str)
		return OVERFLOW;
	strcpy(str, astr);

	(*arrstr) = (char **)malloc(sizeof(char*)*(strlen(str) + 1));
	if (!(*arrstr))
		return OVERFLOW;

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
				if (!(*arrstr)[num])
					return OVERFLOW;

				strcpy((*arrstr)[num], str + start);
				++num;
			}
			str[i] = ',';
			start = i + 1;
		}
	}
	if (strlen(str + start) != 0) {
		(*arrstr)[num] = (char*)malloc(sizeof(char)*(strlen(str + start) + 1));
		if (!(*arrstr)[num])
			return OVERFLOW;

		strcpy((*arrstr)[num], str + start);
		++num;
	}
	*len = num;

	(*arrstr) = (char **)realloc(*arrstr, sizeof(char*)*num);
	if (!(*arrstr))
		return OVERFLOW;
	free(str);
	return OK;
}
Status CreateGList(GLNode **glist, char *str) {
	InitGList(glist);
	if (strlen(str) == 1) {
		(*glist)->tag = ATOM;
		(*glist)->atom = *str;
	}
	else if (strcmp(str, "()")) {
		char *substr;
		char **splitstr;
		int n, i;
		GLNode *temp, *p;
		Status status;

		if ((status = RemBracket(&substr, str)) != OK)return status;
		if ((status = SplitStr(&splitstr, substr, &n)) != OK)return status;
		free(substr);

		for (i = 0, p = *glist; i < n; i++) {
			CreateGList(&temp, splitstr[i]);
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
	return OK;
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
	if (!glist || !*glist || !node)return ERROR;
	CopyGList(&head, node);
	head->next = (*glist)->hp;
	(*glist)->hp = head;
	return OK;
}
Status DeleteFirst_GL(GLNode **glist, GLNode **node) {
	if (!glist || !*glist || !(*glist)->hp)return ERROR;
	*node = (*glist)->hp;
	(*glist)->hp = (*glist)->hp->next;
	(*node)->next = NULL;
	return OK;
}
Status Add(GLNode *node) {
	if (!node || !node->tag == ATOM)return ERROR;
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
