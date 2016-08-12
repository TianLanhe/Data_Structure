#ifndef mystring_h
#define mystring_h
#include <stdio.h>
void strassign(char *p,char ch);
//字符赋值函数
int strempty(char *p);
//测试字符串是否为空
void clearstring(char *p);
//字符串清空函数
void strdelete(char *p,int position,int length);
//部分字符串删除函数
int strlen(char *p);
//测字符串长度
void strlwr(char *p);
//字符串转化为小写
void strupr(char *p);
//字符串转化为大写
void strcpy(char *p1,char *p2);
//字符串复制函数
void strcat(char *p1,char *p2);
//字符串连接函数
int strcmp(char *p1,char *p2);
//字符串比较函数
char *strchr(char *p,char ch);
//字符搜索函数
void strncat(char *p1,char *p2,int n);
//字符串部分连接函数
int strncmp(char *p1,char *p2,int n);
//字符串部分比较函数
void strncpy(char *p1,char *p2,int n);
//字符串部分复制函数
char *strrchr(char *p,char ch);
//字符串倒数搜索函数
char *strstr(char *p1,char *p2);
//字符串匹配函数
#endif
