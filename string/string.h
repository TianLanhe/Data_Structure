#ifndef STRING_H
#define STRING_H

#include "../DataStructureBase.h"

typedef struct {
	char *ch;		//储存字符串，使用动态分配
	int len;		//存储字符串长度
}HString;

Status InitStr(HString *str);
//初始化str为空串
Status DestroyStr(HString *str);
//销毁串str
Status StrAssign(HString *str1, char *str2);
//生成一个其值等于str2的串str1
Status StrCopy(HString *str1, HString str2);
//拷贝str2的副本到str1 
int StrCompare(HString str1, HString str2);
//按字典序比较两个串str1和str2，若相等返回0，若str1<str2，返回大于大于0的整数。若str1>str2，返回小于0的整数
int StrLength(HString str);
//返回S的元素个数，即串的长度
Status StrEmpty(HString str);
//判断串str是否是空串
Status ClearString(HString *str);
//将串str清为空串
Status Concat(HString *str3, HString str1, HString str2);
//用str3返回str1和str2连接而成的新串
Status SubString(HString *sub, HString str, int position, int length);
//0<=position<str.len,len>=0,返回串的第position个字符起长度为length的子串
Status StrInsert(HString *str1, HString str2, int pos);
//在串str1的pos位置插入串str2
Status StrDelete(HString *str1, int pos, int length);
//删除串str2中[pos,pos+length)位置的字符
Status StrReplace(HString *str1, HString str2, int pos, int length);
//替换串str1中[pos,length)位置的内容为str2
char At(HString str, int index);
//返回串str某位置的字符，位置非法返回'\0'
int Index(HString str, char c, int pos);
//返回c在pos后第一次出现的位置，找不到或pos非法返回-1
void PrintStr(HString str);
//打印串str的内容
void PrintStrWithLine(HString str);
//打印串str的内容并换行
Status Next(HString str, int *next);
//KMP模式匹配算法求改良版的next数组
int SubIndex(HString str, HString sub, int pos);
//返回串sub在str中的位置，位置非法或找不到返回-1，采用KMP模式匹配
Status StrReplaceFirst(HString *str, HString sub, HString new, int pos);
//替换串str第pos位置之后的第一个字符ch
Status StrReplaceAll(HString *str, HString sub, HString new, int pos);
//替换串str第pos位置之后的第一个字符ch
char *ToCString(HString *str);
//返回C语言风格的字符串

#endif