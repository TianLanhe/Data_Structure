#include <stdio.h>
#include <stdlib.h>
#define ERROR -1
#define OK 0
#define Status int
typedef struct {
	char *ch;		//储存字符串，使用动态分配
	int len;		//存储字符串长度
}HString;
Status InitStr(HString *str);
//初始化str，将各项赋值为0
Status StrAssign(HString *str1,char *str2);
//生成一个其值等于str2的串str1
int StrCompare(HString str1,HString str2);
//按字典序比较两个串str1和str2，若相等返回0，若str1<str2，返回大于大于0的整数。若str1>str2，返回小于0的整数
int StrLength(HString str);
//返回S的元素个数，即串的长度
Status ClearString(HString *str);
//将串str清为空串，并释放str所占空间
Status Concat(HString *str3,HString str1,HString str2);
//用str3返回str1和str2连接而成的新串
Status SubString(HString *sub,HString str,int position,int length);
//0<=position<str.len,len>=0,返回串的第position个字符起长度为length的子串
Status PrintStr(HString str);
//打印串str的内容
Status InitStr(HString *str){
	str->ch=NULL;
	str->len=0;
	return OK;
}
Status StrAssign(HString *str1,char *str2){
	int i;
	char *p;
	if(str1->ch){
		free(str1->ch);
		str1->ch=NULL;
		str1->len=0;
	}
	if(*str2){
		for(i=0;str2[i];i++);
		str1->len=i;
		str1->ch=(char*)malloc(sizeof(char)*i);
		if(!str1->ch)return ERROR;
		for(p=str1->ch;*p++=*str2++;);
		return OK;
	}else return ERROR;
}
int StrCompare(HString str1,HString str2){
	char *p1,*p2;
	for(p1=str1.ch,p2=str2.ch;p1&&p2;p1++,p2++){
		if(*p1!=*p2)return *p1-*p2;
	}
	return *p1-*p2;
}
int StrLength(HString str){
	int i;
	if(!str.ch)return 0;
	else{
		for(i=0;str.ch[i];i++);
		return i;
	}
}
Status ClearString(HString *str){
	if(str->ch){
		free(str->ch);
		str->ch=NULL;
	}
	str->len=0;
	return OK;
}
Status Concat(HString *str3,HString str1,HString str2){
	int i,j;
	char *p,*p1,*p2;
	if(str3->ch){
		free(str3->ch);
		str3->ch=NULL;
		str3->len=0;
	}
	for(i=0;str1.ch[i];i++);
	for(j=0;str2.ch[j];j++);
	if(i+j){
		str3->len=i+j;
		str3->ch=(char*)malloc(sizeof(char)*(i+j+1));
		if(!str3->ch)return ERROR;
		for(p=str3->ch,p1=str1.ch;*p++=*p1++;);
		for(p--,p2=str2.ch;*p++=*p2++;);
		return OK;
	}else return ERROR;
}
Status SubString(HString *sub,HString str,int position,int length){
	int i;
	char *p;
	if(position<0||position>=str.len||length<0)return ERROR;
	if(sub->ch){
		free(sub->ch);
		sub->ch=NULL;
	}
	sub->ch=(char*)malloc(sizeof(char)*(length+1));
	for(i=0,p=str.ch+position;i<length&&*p;i++,p++){
		sub->ch[i]=*p;
	}
	sub->ch[i]='\0';
	if(i!=length)sub->ch=(char*)realloc(sub->ch,sizeof(char)*(i+1));
	sub->len=i; 
	return OK;
}
Status PrintStr(HString str){
	if(!str.ch)return ERROR;
	printf("%s\n",str.ch);
}
int main(){
	HString str1,str2;
	InitStr(&str1);
	InitStr(&str2);
	StrAssign(&str1,"hello ");
	StrAssign(&str2,"world!");
	PrintStr(str2);
	SubString(&str1,str2,1,3);
	PrintStr(str1);
	printf("%d\n",str1.len);
	return 0;
}
