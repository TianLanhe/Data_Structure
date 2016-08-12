#include "mystring.h"
void strassign(char *p,char ch){				//字符赋值函数
	*p=ch;
	*(p+1)='\0';
}
int strempty(char *p){							//测试字符串是否为空
	return *p=='\0'?1:0;
}
void clearstring(char *p){						//字符串清空函数
	*p='\0';
}
void strdelete(char *p,int position,int length){//部分字符串删除函数
	char *t;
	for(t=p+position+length;*t;t++){
		*(t-length)=*t;
	}
	*(t-length)='\0';
}
int strlen(char *p){                             //测字符串长度
	int l=0;
	while(*p++!='\0')l++;
	return l;
}
void strlwr(char *p){                            //字符串转化为小写
	int i;
	for(i=0;*p!='\0';i++,p++){
		if(*p>='A'&&*p<='Z')*p+=32;
	}
}
void strupr(char *p){                            //字符串转化为大写
	int i;
	for(i=0;*p!='\0';i++,p++){
		if(*p>='a'&&*p<='z')*p-=32;
	}
}
void strcpy(char *p1,char *p2){                 //字符串复制函数
	while(*p1++=*p2++);
}
void strcat(char *p1,char *p2){                 //字符串连接函数
	p1+=strlen(p1);
	while(*p1++=*p2++);
}
int strcmp(char *p1,char *p2){                  //字符串比较函数
	while(1){
		if(*p1!=*p2)return *p1-*p2;
		if(*p1==*p2&&*p1==0)return 0;
		p1++;
		p2++;
	}
}
char *strchr(char *p,char ch){                  //字符搜索函数
	while(*p!='\0'){
		if(*p==ch)return p;
		p++;
	}
	return 0;
}
void strncat(char *p1,char *p2,int n){          //字符串部分连接函数
	int strlen(char *p);
	int l=0;
	p1+=strlen(p1);
	while((l++<n)&&(*p1++=*p2++));
	*p1='\0';
}
int strncmp(char *p1,char *p2,int n){          //字符串部分比较函数
	int l;
	for(l=0;*p1!='\0'&&*p2!='\0'&&l<n;p1++,p2++,l++){
		if(*p1>*p2)return 1;
		else if(*p1<*p2)return -1;
	}
	if(strlen(p1)>strlen(p2))return 1;
	else if(strlen(p1)<strlen(p2)) return -1;
	else return 0;
}
void strncpy(char *p1,char *p2,int n){         //字符串部分复制函数
	int l=0;
	while((l++<n)&&(*p1++=*p2++));
	*p1='\0';
}
char *strrchr(char *p,char ch){               //字符串倒数搜索函数
	int length=strlen(p);
	while(length>=0){
		if(*(p+length)==ch)return (p+length);
		length--;
	}
	return 0;
}
char *strstr(char *p1,char *p2){               //字符串匹配函数
	int length1=strlen(p1);
	int length2=strlen(p2);
	int n1,k,n2;
	if(length1<length2)return 0;
	for(n1=0;length1-n1>=length2;n1++){
		n2=0;
		k=n1;
		while(*(p1+k)==*(p2+n2)&&*(p2+n2)!='\0'){
			k++;
			n2++;
		}
		if(*(p2+n2)=='\0')return p1+n1;
	}
	return 0;
}
