#include <stdio.h>
#include <ctype.h>
#include <string.h>
#define MAXWORD 1000			//最大单词数量
#define MAXLEN  21				//最大单词长度(留一个给'\0')
#define OK 0
#define ERROR -1
typedef struct _word{
	char wordname[MAXLEN];
	int count;
}Word;
typedef struct _wordcount{
	Word word[MAXWORD];
	int wordnum;
}WordCount;

void getword(FILE *fp,char str[]){
	char ch;
	int i;
	while((ch=fgetc(fp)) != EOF && !isalnum(ch));	//跳过之前的空格符号等
	if(ch==EOF)strcpy(str,"");						//读取第一个字母或数字
	else{
		i=0;
		do{
			str[i++]=ch;
		}while((ch=fgetc(fp)) != EOF && isalnum(ch));	//将接下来的字符或数字读取进去
		str[i]='\0';									//直至到文件末尾或不是英文或数字
	}
}
int wordcount(FILE *fp,WordCount *wc){
	char str[MAXLEN];
	int low,high,mid;
	int index;
	int i;
	int total;
	wc->wordnum=0;
	total=0;
	for(getword(fp,str);strcmp(str,"");getword(fp,str)){	//每读取一个单词
		total++;
		low=0;												//使用折半插入法
		high=wc->wordnum-1;
		while(low<=high){
			mid=(low+high)/2;
			if(strcmp(str,wc->word[mid].wordname) >= 0)low=mid+1;
			else high=mid-1;
		}
		index=high+1;										//根据折半查找法确定要插入的位置
		if(index && strcmp(str,wc->word[index-1].wordname) == 0){	//如果这个单词已经存在了，则count++即可
			wc->word[index-1].count++;
		}else{												//否则，记录往后移一个，把新单词添加进去
			for(i=wc->wordnum-1;i>=index;i--){
				strcpy(wc->word[i+1].wordname,wc->word[i].wordname);
				wc->word[i+1].count=wc->word[i].count;
			}
			strcpy(wc->word[index].wordname,str);
			wc->word[index].count=1;
			wc->wordnum++;
		}
	}
	return total;
}
void PrintWord(WordCount wc){
	int i;
	for(i=0;i<wc.wordnum;i++)
		printf("%4d%20s\n",wc.word[i].count,wc.word[i].wordname);
}
int main(int argc,char *argv[]){
	int i;
	int total;
	FILE *fp;
	WordCount wc;
	if(argc < 2){
		printf("Uage: program file1 file2 ...\n");
		return 0;
	}
	for(i=1;i<argc;i++){
		if((fp=fopen(argv[i],"r")) == NULL)return ERROR;
		total=wordcount(fp,&wc);
		PrintWord(wc);
		printf("单词个数：%d\n",wc.wordnum);
		printf("单词总数：%d\n",total);
	}
	return 0;
}
