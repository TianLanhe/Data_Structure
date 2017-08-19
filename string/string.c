#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "String.h"

Status InitStr(HString *str) {
	if (!str)return ERROR;
	str->ch = (char*)malloc(sizeof(char));
	str->ch[0] = '\0';
	str->len = 0;
	return OK;
}
Status DestroyStr(HString *str) {
	if (!str)
		return ERROR;
	if (str->ch) {
		free(str->ch);
		str->ch = NULL;
		str->len = 0;
	}
	return OK;
}
Status StrAssign(HString *str1, char *str2) {
	if (!str1 || !str2)
		return ERROR;
	if (str1->ch)
		free(str1->ch);
	str1->ch = (char*)malloc(sizeof(char)*(strlen(str2) + 1));
	if (!str1->ch)
		return OVERFLOW;
	str1->len = strlen(str2);
	strcpy(str1->ch, str2);
	return OK;
}
Status StrCopy(HString *str1, HString str2) {
	return StrAssign(str1, str2.ch);
}
int StrCompare(HString str1, HString str2) {
	return strcmp(str1.ch, str2.ch);
}
int StrLength(HString str) {
	return str.len;
}
Status ClearString(HString *str) {
	if (!str)
		return ERROR;
	free(str->ch);
	return InitStr(str);
}
Status StrEmpty(HString str) {
	return str.len == 0 ? true : false;
}
Status Concat(HString *str3, HString str1, HString str2) {
	Status status;
	if (!str3)
		return ERROR;
	status = StrCopy(str3, str1);
	if (status != OK)
		return status;
	str3->ch = (char*)realloc(str3->ch, sizeof(char)*(str1.len + str2.len + 1));
	if (!str3->ch)
		return OVERFLOW;
	str3->len = str2.len + str1.len;
	strcat(str3->ch, str2.ch);
	return OK;
}
Status SubString(HString *sub, HString str, int position, int length) {
	int i, n;
	char *p;
	Status status;
	if (position < 0 || position >= str.len || length < 0)
		return ERROR;
	if (!sub)
		return ERROR;
	p = (char*)malloc(sizeof(char)*length + 1);
	if (!p)
		return OVERFLOW;
	n = 0;
	for (i = position; i < position + length; ++i) {
		p[n++] = str.ch[i];
	}
	p[n] = '\0';
	status = StrAssign(sub, p);
	if (status != OK)
		return status;
	free(p);
	return OK;
}
Status StrInsert(HString *str1, HString str2, int pos) {
	int i;
	if (!str1)
		return ERROR;
	if (pos <0 || pos > str1->len)
		return ERROR;
	str1->ch = (char*)realloc(str1->ch, sizeof(char)*(str1->len + str2.len + 1));
	if (!str1->ch)
		return OVERFLOW;
	for (i = str1->len; i >= pos; --i) {
		str1->ch[i + str2.len] = str1->ch[i];
	}
	for (i = 0; i < str2.len; ++i) {
		str1->ch[i + pos] = str2.ch[i];
	}
	str1->len += str2.len;
	return OK;
}
Status StrDelete(HString *str, int pos, int length) {
	int i;
	if (!str)
		return ERROR;
	if (length < 0 || pos < 0 || pos >= str->len)
		return ERROR;
	if (pos + length > str->len)
		length = str->len - pos;
	for (i = pos + length; i < str->len + 1; ++i)
		str->ch[i - length] = str->ch[i];
	str->len = strlen(str->ch);
	str->ch = (char*)realloc(str->ch, sizeof(char)*(str->len + 1));
	if (!str->ch)
		return OVERFLOW;
	return OK;
}
Status StrReplace(HString *str1, HString str2, int pos, int length) {
	Status status;
	status = StrDelete(str1, pos, length);
	if (status != OK)
		return status;
	return StrInsert(str1, str2, pos);
}
char At(HString str, int index) {
	if (index < 0 || index >= str.len)
		return '\0';
	return str.ch[index];
}
int Index(HString str, char c, int pos) {
	if (pos < 0)
		pos = 0;
	for (; pos < str.len; ++pos) {
		if (str.ch[pos] == c)
			return pos;
	}
	return -1;
}
void PrintStr(HString str) {
	printf("%s", str.ch);
}
void PrintStrWithLine(HString str) {
	PrintStr(str);
	printf("\n");
}
Status Next(HString str, int *next) {
	int i, j;
	if (!str.ch || !next || str.len == 0)
		return ERROR;
	i = 0;
	j = -1;
	next[0] = -1;
	while (i < str.len) {
		if (j == -1 || str.ch[i] == str.ch[j]) {
			i++;
			if (i >= str.len)return OK;
			j++;
			if (str.ch[i] != str.ch[j])
				next[i] = j;
			else
				next[i] = next[j];
		}
		else {
			j = next[j];
		}
	}
	return OK;
}
int SubIndex(HString str, HString sub, int pos) {
	int i, j;
	Status status;
	int *next;
	if (pos < 0 || pos >= str.len)
		return ERROR;

	next = (int*)malloc(sizeof(int)*sub.len);
	if (!next)
		return OVERFLOW;

	status = Next(sub, next);
	if (status != OK)
		return status;

	for (i = pos, j = 0; i < str.len&&j < sub.len; i++, j++) {
		while (str.ch[i] != sub.ch[j] && j != -1) {
			j = next[j];
		}
	}
	free(next);

	return j >= sub.len ? i - sub.len : -1;
}
Status StrReplaceFirst(HString *str, HString sub, HString new, int pos) {
	int index;
	if ((index = SubIndex(*str, sub, pos)) == -1)
		return OK;
	return StrReplace(str, new, index, sub.len);
}
Status StrReplaceAll(HString *str, HString sub, HString new, int pos) {
	int index;
	while ((index = SubIndex(*str, sub, pos)) != -1)
		StrReplace(str, new, index, sub.len);
	return OK;
}
