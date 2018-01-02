#include <stdio.h>
#include <stdlib.h>
#include "../../DataStructureBase.h"

typedef struct _htnode {	//使用顺序存储结构孩子双亲表示法表示二叉树
	int weight;				//权
	int parent;				//父亲结点
	int lchild;				//左孩子
	int rchild;				//右孩子
}HTNode;					//赫夫曼树的节点数据类型

Status HuffmanTreeMaking(HTNode **HT, int *w, int n);
//构造赫夫曼树，输入权重数组w与数组长度n，构造长度为(2n-1)的赫夫曼树HT
//由于数组w长度n意味着叶子数为n，则非叶子节点数为n-1，共(2n-1)个节点
Status SelectMin(HTNode *HT, int length, int *pos1, int *pos2);
//寻找两个权重最小，且parent==-1，即没有父亲结点的两个结点，返回到pos1和pos2中
Status HuffmanCoding(HTNode *HT, char ***HC);
//根据赫夫曼树，求叶子结点的赫夫曼编码（字符串表示），将一系列字符串存储在二维数组HC中
Status HuffmanDeCoding(HTNode *HT, const char *str, const char *characters, char **decode);
//赫夫曼树译码，传入构造出的赫夫曼树，编码的01字符序列，以及赫夫曼树对应的字符，解码出原文字符串储存在decode中

Status HuffmanTreeMaking(HTNode **HT, int *w, int n) {
	int i;
	int nodenum;
	int min1, min2;

	if (n <= 1)
		return ERROR;

	nodenum = 2 * n - 1;					//节点总数
	(*HT) = (HTNode *)malloc(sizeof(HTNode)*nodenum);
	if (!(*HT))
		return OVERFLOW;

	for (i = 0; i < nodenum; i++) {				//初始化HT，输入前n个节点为叶子节点，修改权重
		if (i < n)(*HT)[i].weight = *(w + i);	//后(n-1)个节点权重为0
		else (*HT)[i].weight = 0;				//所有结点的父亲及左右孩子均为-1，表示无
		(*HT)[i].parent = (*HT)[i].lchild = (*HT)[i].rchild = -1;
	}

	for (i = n; i < nodenum; i++) {
		if (SelectMin(*HT, i, &min1, &min2) == ERROR)return ERROR;
		(*HT)[min1].parent = i;
		(*HT)[min2].parent = i;
		(*HT)[i].lchild = min1;
		(*HT)[i].rchild = min2;
		(*HT)[i].weight = (*HT)[min1].weight + (*HT)[min2].weight;
	}
	return OK;
}

Status SelectMin(HTNode *HT, int length, int *pos1, int *pos2) {
	int i;
	int min1 = -1;
	int min2 = -1;

	for (i = 0; i < length; ++i) {
		if (HT[i].parent == -1) {
			if (min1 == -1)
				min1 = i;
			else if (HT[i].weight < HT[min1].weight) {
				min2 = min1;
				min1 = i;
			}
			else if (min2 == -1 || HT[i].weight < HT[min2].weight)
				min2 = i;
		}
	}
	if (min1 == -1 || min2 == -1)
		return ERROR;

	*pos1 = min1;
	*pos2 = min2;
	return OK;
}

Status HuffmanCoding(HTNode *HT, char ***HC) {
	int nodenum, leave_num;
	int i, n, start;
	int par, chi;
	char temp[100];

	if (!HT || !HC)
		return ERROR;

	for (i = 0; HT[i].parent != -1; i++);	//这里根据上述构建规则，HT的最后一个结点为根节点
	nodenum = i + 1;						//最后一个节点的下标值加一即为结点总个数

	leave_num = (nodenum + 1) / 2;

	(*HC) = (char **)malloc(sizeof(char *)*leave_num);
	if (!(*HC))
		return OVERFLOW;

	for (i = 0; i < leave_num; i++) {
		n = 0;
		par = HT[i].parent;
		chi = i;
		while (par != -1) {
			if (HT[par].lchild == chi)temp[n++] = '0';
			else if (HT[par].rchild == chi)temp[n++] = '1';
			chi = par;
			par = HT[par].parent;
		}

		(*HC)[i] = (char *)malloc(sizeof(char)*(n + 1));
		if (!(*HC)[i])
			return OVERFLOW;

		(*HC)[i][n] = '\0';
		for (start = 0, n--; n >= 0; n--, start++)
			(*HC)[i][n] = temp[start];
	}
	return OK;
}

Status HuffmanDeCoding(HTNode *HT, const char *str, const char *characters, char **decode) {
	int nodenum, i, index;
	int size = 0;

	if (!HT || !str || !decode)
		return ERROR;

	*decode = (char*)malloc(sizeof(char) * (strlen(str) + 1));

	for (i = 0; HT[i].parent != -1; i++);	//这里根据上述构建规则，HT的最后一个结点为根节点
	nodenum = i + 1;						//最后一个节点的下标值加一即为结点总个数

	index = nodenum - 1;
	for (i = 0; str[i] != '\0'; ++i) {
		if (str[i] == '0') {
			index = HT[index].lchild;
		}
		else if (str[i] == '1') {
			index = HT[index].rchild;
		}
		else {
			printf("非01序列，解码失败！\n");
			return ERROR;
		}

		if (HT[index].lchild == -1 || HT[index].rchild == -1) {
			(*decode)[size++] = characters[index];
			index = nodenum - 1;
		}
	}
	(*decode)[size] = '\0';
	(*decode) = (char*)realloc(*decode, sizeof(char)*(strlen(*decode) + 1));
	return OK;
}

int main() {
	int weight[8] = { 5,29,7,8,14,23,3,11 };
	int i;
	HTNode *HT;
	char **ch;
	HuffmanTreeMaking(&HT, weight, 8);
	for (i = 0; i < 15; i++) {
		printf("NO:%2d  weight=%3d  parent=%2d  lchild=%2d   rchild=%2d\n", i, HT[i].weight, HT[i].parent, HT[i].lchild, HT[i].rchild);
	}
	printf("\n\n");
	HuffmanCoding(HT, &ch);
	for (i = 0; i < 8; i++)
		printf("%s\n", ch[i]);

	free(HT);
	for (i = 0; i < 8; ++i)
		free(ch[i]);
	free(ch);

	// FILE *file;
	// int ascii[129] = { 0 };
	// char filename[100];
	// char character;
	// int i,j,c,count;
	// int length;

	// int weight[128];
	// char characters[128];
	// int size;
	// char *codingline;
	// char *decodeline;

	// HTNode *HT;
	// char **ch;

	// printf("请输入读取的文件：");
	// scanf("%s", filename);

	// file = fopen(filename, "r");
	// if (file == NULL) {
	// 	printf("文件不存在或打开错误！\n");
	// 	return 1;
	// }

	// // 统计每个字母出现的次数
	// size = 0;	// 记录出现了多少个不同的字符
	// count = 0;	// 记录一共有多少个字符
	// while (!feof(file)) {
	// 	character = fgetc(file);
	// 	if (character > 0 && character < 128 && isprint(character)) {
	// 		++count;
	// 		if (ascii[character] == 0)
	// 			++size;
	// 		++ascii[character];
	// 	}
	// }

	// // 将字母和次数分开储存在数组中
	// c = 0;
	// for (i=0; i<129; ++i) {
	// 	if (ascii[i]) {
	// 		characters[c] = i;
	// 		weight[c++] = ascii[i];
	// 	}
	// }
	
	// // 传入权值那个数组，用于构造一棵哈夫曼树
	// HuffmanTreeMaking(&HT, weight, size);

	// // 根据哈夫曼树进行哈夫曼编码
	// HuffmanCoding(HT, &ch);

	// // 打印每个字符对应的编码规则
	// for (i = 0; i < size; ++i) {
	// 	printf("%c : %s\n", characters[i], ch[i]);
	// }

	// printf("未进行编码之前传输需要 %d 字节， %d 位\n", count, count * 8);	//	有多少字符就有多少字节，乘以8得位数

	// // 将编码后的字符进行拼接，组成编码字符串并输出
	// fseek(file, 0, 0);
	// codingline = (char*)malloc(sizeof(char) * 100000);
	// codingline[0] = '\0';
	// while (!feof(file)) {
	// 	character = fgetc(file);
	// 	if (character > 0 && character < 128 && isprint(character)) {
	// 		for (j = 0; j < size; ++j) {
	// 			if (characters[j] == character) {
	// 				strcat(codingline, ch[j]);
	// 				break;
	// 			}
	// 		}
	// 	}
	// }
	// printf("编码后的数据：%s\n", codingline);

	// length = strlen(codingline);

	// printf("编码后数据传输需要 %.2f 字节， %d 位\n", length*1.0 / 8, length);
	// printf("编码压缩比为:%.2f%%\n", length*100.0 / 8 / count);

	// HuffmanDeCoding(HT,codingline,characters,&decodeline);
	// printf("%s\n",decodeline);

	// free(codingline);
	// free(HT);
	// for (i = 0; i < size; ++i)
	// 	free(ch[i]);
	// free(ch);
	// free(decodeline);

	return 0;
}
