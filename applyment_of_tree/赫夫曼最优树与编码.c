#include <stdio.h>
#include <stdlib.h>
#define OK 0
#define ERROR -1
#define Status int
typedef struct _htnode{		//使用顺序存储结构孩子双亲表示法表示二叉树
	int weight;				//权
	int parent;				//父亲结点
	int lchild;				//左孩子
	int rchild;				//右孩子
}HTnode;					//赫夫曼树的节点数据类型
Status HuffmanTreeMaking(HTnode **HT,int *w,int n);
//构造赫夫曼树，输入权重数组w与数组长度n，构造长度为(2n-1)的赫夫曼树HT
//由于数组w长度n意味着叶子数为n，则非叶子节点数为n-1，共(2n-1)个节点
Status SelectMin(HTnode *HT,int length,int *pos1,int *pos2);
//寻找两个权重最小，且parent==-1，即没有父亲结点的两个结点，返回到pos1和pos2中
Status HuffmanCoding(HTnode *HT,char ***HC);

Status HuffmanTreeMaking(HTnode **HT,int *w,int n){
	int i;
	int nodenum;
	int min1,min2;
	if(n<=1)return ERROR;
	nodenum=2*n-1;					//节点总数
	(*HT)=(HTnode *)malloc(sizeof(HTnode)*nodenum);
	if(!(*HT))return ERROR;
	for(i=0;i<nodenum;i++){				//初始化HT，输入前n个节点为叶子节点，修改权重
		if(i<n)(*HT)[i].weight=*(w+i);	//后(n-1)个节点权重为0
		else (*HT)[i].weight=0;			//所有结点的父亲及左右孩子均为-1，表示无
		(*HT)[i].parent=(*HT)[i].lchild=(*HT)[i].rchild=-1;
	}
	for(i=n;i<nodenum;i++){
		if(SelectMin(*HT,i,&min1,&min2) == ERROR)return ERROR;
		(*HT)[min1].parent=i;
		(*HT)[min2].parent=i;
		(*HT)[i].lchild=min1;
		(*HT)[i].rchild=min2;
		(*HT)[i].weight=(*HT)[min1].weight+(*HT)[min2].weight;
	}
	return OK;
}
Status SelectMin(HTnode *HT,int length,int *pos1,int *pos2){
	int i,j;
	int min1=0,min2=0;
	for(i=0;i<length&&HT[i].parent!=-1;i++);
	if(i >= length)return ERROR;
	min1=i;									//先找到第一个parent==1的作为min1
	for(;i<length;i++){						//寻找所有parent==1的并跟min1比较，找到weight最小的
		if(HT[i].parent==-1 && HT[i].weight<HT[min1].weight)
			min1=i;
	}
	for(i=0;i<length;i++){
		if(HT[i].parent==-1 && i!=min1)break;
	}
	min2=i;									//同样先找到第一个parent==1的作为min2
	for(;i<length;i++){						//注意这里要多加一个不等于min1的判定条件
		if(HT[i].parent==-1 && HT[i].weight<HT[min2].weight && i!=min1)
			min2=i;
	}
	*pos1=min1;
	*pos2=min2;
	return OK;
}
Status HuffmanCoding(HTnode *HT,char ***HC){
	int nodenum,leftnum;
	int i,n,start;
	int par,chi;
	char temp[100];
	if(!HT)return ERROR;
	for(i=0;HT[i].parent!=-1;i++);	//这里根据上述构建规则，HT的最后一个结点为根节点
	nodenum=i+1;					//最后一个节点的下标值加一即为结点总个数
	leftnum=(nodenum+1)/2;
	(*HC)=(char **)malloc(sizeof(char *)*leftnum);
	if(!(*HC))return ERROR;
	for(i=0;i<leftnum;i++){
		n=0;
		par=HT[i].parent;
		chi=i;
		while(par!=-1){
			if(HT[par].lchild==chi)temp[n++]='0';
			else if(HT[par].rchild==chi)temp[n++]='1';
			chi=par;
			par=HT[par].parent;
		}
		(*HC)[i]=(char *)malloc(sizeof(char)*n);
		if(!(*HC)[i])return ERROR;
		(*HC)[i][n]='\0';
		for(start=0,n--;n>=0;n--,start++)(*HC)[i][n]=temp[start];
	}
	return OK;
}
int main(){
	int weight[8]={5,29,7,8,14,23,3,11};
	int i;
	HTnode *HT;
	char **ch;
	HuffmanTreeMaking(&HT,weight,8);
	for(i=0;i<15;i++){
		printf("NO:%d  weight=%d  parent=%d  lchild=%d   rchild=%d\n",i,HT[i].weight,HT[i].parent,HT[i].lchild,HT[i].rchild);
	}
	printf("\n\n");
	HuffmanCoding(HT,&ch);
	for(i=0;i<8;i++)printf("%s\n",ch[i]);
	return 0;
}
