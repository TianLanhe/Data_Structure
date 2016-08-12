#include <stdio.h>
#include <math.h>
void PrintBoard(int board[][8]){
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++)printf("%d ",board[i][j]);
		printf("\n");
	}
	printf("\n");
}
int isPeace(int board[][8]){
	int i,j,k;				//确定没两颗棋子符合规则，不在同一行同一列同一对角线
	int row,column;
	for(i=0;i<8;i++){
		row=i;
		for(j=0;j<8;j++)
			if(board[i][j])
				column=j;	//确定一颗棋子，然后跟接下来的棋子比较
		for(j=i+1;j<8;j++){
			for(k=0;k<8;k++)	//扫描接下来棋盘的棋子，如果发现有棋子
				if(board[j][k])	//若在同一列，或在对角线上(利用等腰直角三角形两直角边比为1)
					if(k==column||abs(row-j)==abs(column-k))
						return 0;
		}
	}
	return 1;
}
void EightQueue(int board[][8],int i,int n){
	int j;
	if(i>=n)PrintBoard(board);
	else{
		for(j=0;j<n;j++){
			board[i][j]=1;
			if(isPeace(board))EightQueue(board,i+1,n);
			board[i][j]=0;
		}
	}
}
int main(){
	int board[8][8];
	int i,j;
	for(i=0;i<8;i++){
		for(j=0;j<8;j++)board[i][j]=0;
	}
	EightQueue(board,0,8);
	return 0;
}
