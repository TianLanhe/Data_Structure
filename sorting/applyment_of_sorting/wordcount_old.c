#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#define NUMBER 1000
typedef struct {
	char wordname[21];
	int num;
}WORD;
void Initialize(WORD *array, int length) {
	int i;
	for (i = 0; i < length; i++) {
		array[i].wordname[0] = 0;
		array[i].num = 1;
	}
}
int getWord(WORD *array, int length, FILE *fp) {
	char ch;
	int n;
	int i;
	while ((ch = fgetc(fp)) != EOF && !isalnum(ch));
	if (ch == EOF)return EOF;
	for (i = 0; i < length; i++) {
		n = 0;
		if (feof(fp)) {
			break;
		}
		do {
			array[i].wordname[n++] = ch;
		} while ((ch = fgetc(fp)) != EOF&&isalnum(ch));
		array[i].wordname[n] = '\0';
		while ((ch = fgetc(fp)) != EOF && !isalnum(ch));
	}
	return i - 1;
}
void Quick_sub(WORD *p, int start, int end) {       //字符串快速排序
	int i = start, j = end;
	char key[21];
	strcpy(key, p[start].wordname);
	while (i != j) {
		while (i != j&&strcmp(key, p[j].wordname) <= 0)j--;
		strcpy(p[i].wordname, p[j].wordname);
		while (i != j&&strcmp(key, p[i].wordname) >= 0)i++;
		strcpy(p[j].wordname, p[i].wordname);
	}
	strcpy(p[i].wordname, key);
	if (j - start > 1)Quick_sub(p, start, j - 1);
	if (end - i > 1)Quick_sub(p, i + 1, end);
}
void Quick(WORD *p, int length) {
	Quick_sub(p, 0, length - 1);
}
int Search2_sub(WORD *p, int start, int end, char *target) {    //递归法折半查找
	int mid = (start + end) / 2;
	if (strcmp(target, p[mid].wordname) == 0)return mid;
	else if (start == end)return -1;
	else if (strcmp(target, p[mid].wordname) < 0)return Search2_sub(p, start, mid - 1, target);
	else if (strcmp(target, p[mid].wordname) > 0)return Search2_sub(p, mid + 1, end, target);
}
int Search2(WORD *p, int length, char *target) {
	return Search2_sub(p, 0, length - 1, target);
}
WORD *Classify(FILE *fp, int *number) {
	WORD word[NUMBER];
	WORD *result;
	int n;
	int i;
	Initialize(word, NUMBER);
	getWord(word, NUMBER, fp);
	Quick(word, NUMBER);
	n = 0;
	for (i = 0; i < NUMBER - 1; i++) {
		if (strcmp(word[i].wordname, word[i + 1].wordname) == 0) {
			word[i].wordname[0] = '\0';
			word[i + 1].num += word[i].num;
		}
		if (word[i].wordname[0] != '\0')n++;
	}
	n++;
	result = (WORD *)malloc(sizeof(WORD)*n);
	n = 0;
	for (i = 0; i < NUMBER; i++) {
		if (word[i].wordname[0] != '\0') {
			strcpy(result[n].wordname, word[i].wordname);
			result[n].num = word[i].num;
			n++;
		}
	}
	*number = n;
	return result;
}
int main() {
	FILE *fp;
	WORD *result;
	int n;
	int i = 0;
	char ch[21];
	fp = fopen("String Fuction.c", "r");
	result = Classify(fp, &n);
	Quick(result, n);
	for (i = 0; i < n; i++)printf("%10s%2d\n", result[i].wordname, result[i].num);
	printf("请输入要搜索的单词：");
	scanf("%s", ch);
	i = Search2_sub(result, 0, n - 1, ch);
	if (i == -1)printf("没有找到%s这个单词！\n", ch);
	else printf("%s这个单词出现的次数是%d次！\n", ch, result[i].num);
	return 0;
}
