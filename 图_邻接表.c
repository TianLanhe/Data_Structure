#include <stdio.h>
#include <stdlib.h>
#define Status int
#define MAXINT 0x7fffffff
#define OK 0
#define ERROR -1
#define true 1
#define false 0
#define DG 1    //有向图
#define DN 2	//有向网
#define UDG 3 	//无向图
#define UDN 4 	//无向网
#define MAXVEX 20		//最大顶点数

typedef int GraphKind;
typedef int TElemType;
typedef struct _cstree{					//孩子兄弟链表
	TElemType data;
	struct _cstree *firstchild;			//左孩子
	struct _cstree *nextsibling;		//右孩子
}CSTNode;
typedef struct _arcnode{
	int adjvex;					//该弧指向的顶点的位置
	int weight;					//权(规定只能正权)
	struct _arcnode *nextarc;	//指向下一条边
}ArcNode;
typedef struct _vnode{
	int vexno;					//顶点序号(编号)
	ArcNode *firstarc;			//指向第一条边
}VNode;
typedef struct _algraph{
	int vexnum;					//图的当前顶点数
	int arcnum;					//图的当前有向边数
	VNode vertices[MAXVEX];		//图的顶点邻接表(顺序存储)
	GraphKind kind;				//图的种类
}ALGraph;
Status CreateDG(ALGraph *graph);
//创建有向图，提示用户输入并根据信息创建有向图邻接矩阵
Status CreateDN(ALGraph *graph);
//创建有向网，提示用户输入并根据信息创建有向网邻接矩阵
Status CreateUDG(ALGraph *graph);
//创建无向图，提示用户输入并根据信息创建无向图邻接矩阵
Status CreateUDN(ALGraph *graph);
//创建无向网，提示用户输入并根据信息创建无向网邻接矩阵
Status CreateGraph(ALGraph *graph);
//创建图，提示用户输入并创建相应类型的图
Status DestroyGraph(ALGraph *graph);
//销毁图graph，将各项成员置0
int FirstAdjVex(ALGraph graph,int v);
//返回顶点v的第一个邻接顶点，若graph不存在或v不是graph的顶点或v没有邻接顶点，则返回-1
int NextAdjVex(ALGraph graph,int v,int w);
//返回顶点v相对于w的下一个邻接顶点，若graph不存在或v不是graph的顶点或w不是graph的顶点或者v相对于w之后没有邻接顶点，则返回-1
Status InsertVex(ALGraph *graph,int v);
//在图graph中增添新顶点v，若graph不存在或已有顶点已经达到MAXVEX或v小于0或v已存在graph中，则返回ERROR
Status DeleteVex(ALGraph *graph,int v);
//从图graph中删除顶点v，及其相关的弧。若图graph不存在或顶点v不存在，返回ERROR
Status DeleteArc(ALGraph *graph,int v,int w);
//从图graph中删除弧<v,w>，若graph是无向的，则还需删除对称弧<w,v>。若图graph不存在或顶点v或w不存着，则返回ERROR
Status InsertArc(ALGraph *graph,int v,int w,int adj);
//若图中没有弧<v,w>，则在图graph中增加该弧，若graph是无向的，则还需增加对称弧<w,v>。若图graph不存在或顶点v或w不存在或边<v,w>已存在，则返回ERROR
Status DFSTraverse(ALGraph *graph,Status (*traverse)(VNode));
//对图进行深度优先遍历，对每个顶点调用一次traverse函数(顶点的应用函数)，若图不存在或其中一个顶点traverse失败，返回ERROR
Status DFSTraverse_sub(ALGraph *graph,int start,Status (*traverse)(VNode),int *visit);
//深度优先遍历的子函数，递归实现深度优先遍历。
Status Print(VNode vnode);
//顶点的应用函数，打印顶点的序号
Status BFSTraverse(ALGraph *graph,Status (*traverse)(VNode));
//对图进行广度优先遍历，对每个顶点调用一次traverse函数(顶点的应用函数)，若图不存在或其中一个顶点traverse失败，返回ERROR
int VexNo(ALGraph graph,int vexnum);
//判断点vexnum是否是图graph的顶点，若是则返回下标，否则返回-1
Status DFSForest(ALGraph graph,CSTNode **root);
//建立无向图graph的深度优先生成森林root
Status DFSTree(ALGraph graph,int index,CSTNode *root,int visit[]);
//从第index个顶点出发深度优先遍历图graph，建立以root为根的生成树
Status DestroyCSTree(CSTNode **root);
//销毁树root，使其为空树
Status DestroyCSForest(CSTNode **root);
//销毁森林root，循环删除root及其后续的nextsibling.使其成为空森林
Status PreOrderTraverseCSTress(CSTNode *root,Status (*visit)(CSTNode *));
//先序遍历(递归法)树root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PreOrderTraverseCSForest(CSTNode *root,Status (*visit)(CSTNode *));
//先序遍历(递归法)森林root，对每个结点调用函数visit一次且仅一次，一旦调用失败，操作失败
Status PrintCSTree(CSTNode *node);
//遍历函数的功能函数，打印节点的数据值
int Distance(ALGraph graph,int v,int w);
//计算两个顶点的距离，若无法直接到达，返回MAXINT，若v或w不是graph中的顶点，返回error
Status MiniSpanTree_PRIM(ALGraph graph,int v);
//普里姆法求从第start个顶点出发构造网graph的最小生成树，输出各条边
Status MiniSpanTree_Kruskal(ALGraph graph);
//库鲁斯卡尔法构造网graph的最小生成树，输出各条边。说明：包含打印
int findparent(int *arr,int vertex);
//库鲁斯卡尔法的子函数，往上求vertex的根节点，若两个结点的根节点都相同，则表示会构成环
Status TopologicalSort(ALGraph oldgraph,int toposequ[]);
//若有向图(网)oldgraph中无回路，则将oldgraph的一个拓扑序列保存在toposequ中并返回OK。若oldgraph是无向图(网)或有环，返回ERROR
Status TopologicalOrder(ALGraph graph,int toposequ[],int etv[]);
//求有向图(网)的拓扑序列和顶点最早开始时间，若图不是有向的，或者存在环，则返回ERROR
Status CriticalPath(ALGraph graph);
//求图(网)的关键路径并输出，若图不是有向的，或者存在环则返回ERROR
Status CopyGraph(ALGraph *graph,ALGraph oldgraph);
//复制(克隆)oldgraph到graph中
Status hasLoop_un_sub(ALGraph *graph,int start,int visit[]);
//递归搜索无向图(网)graph,若图中存在回路，返回ERROR，否则返回OK
//要复制和删除所有边，而且边的遍历混乱。效率不高，有待改进
Status hasLoop_un(ALGraph oldgraph);
//若无向图(网)graph中无回路，则返回false，有回路返回true。若是有向图(网)，返回ERROR，
Status hasLoop(ALGraph graph);
//判断图中是否存在，有返回true，否则返回false
Status DijShortPath(ALGraph graph,int v,int path[][MAXVEX+2],int *dist);
//根据Dijkstra算法求图graph中v顶点到其他顶点的距离(到自身距离为0，无法到达距离为MAXINT)
//path[w][...]存储路径，其中path[w][0]表示顶点个数，接下来n个元素为顶点。dist[w]表示顶点v到w的距离
Status FloShortPath(ALGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]);
//根据Floyd算法求图graph中每个顶点到其余顶点的距离(到自身距离为0，无法到达距离为MAXINT)
//path[v][w][...]存储点v到w的最短路径，其中path[v][w][0]表示最短路径的顶点个数(包括起点与终点)，接下来n个元素为顶点。dist[v][w]表示顶点v到w的距离

Status FloShortPath(ALGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]){
	int i,j,k;
	if(path == NULL || dist == NULL)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			dist[i][j]=Distance(graph,graph.vertices[i].vexno,graph.vertices[j].vexno);
			path[i][j][0]=0;
			path[i][j][1]=MAXINT;
			if(dist[i][j] != MAXINT){
				path[i][j][0]+=2;
				path[i][j][1]=graph.vertices[i].vexno;
				path[i][j][2]=graph.vertices[j].vexno;
			}
		}
		path[i][i][0]++;
		path[i][i][1]=graph.vertices[i].vexno;
		dist[i][i]=0;
	}
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			for(k=0;k<graph.vexnum;k++){
				if(dist[j][i]<MAXINT && dist[i][k]<MAXINT){
					if(dist[j][i]+dist[i][k] < dist[j][k]){
						int w,count;
						dist[j][k]=dist[j][i]+dist[i][k];
						count=0;
						for(w=0;w<path[j][i][0]+1;w++)
							path[j][k][count++]=path[j][i][w];
						for(w=2;w<path[i][k][0]+1;w++)
							path[j][k][count++]=path[i][k][w];
						path[j][k][0]+=path[i][k][0]-1;
					}
				}
			}
		}
	}
	return OK;
}
Status DijShortPath(ALGraph graph,int v,int path[][MAXVEX+2],int *dist){
	int index;
	int index2;
	int i,j,k;
	int mindist;
	int distance;
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	if(path == NULL  || dist == NULL)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		dist[i]=Distance(graph,v,graph.vertices[i].vexno);
		path[i][0]=0;
		path[i][1]=MAXINT;
		if(dist[i] != MAXINT){
			path[i][0]++;
			path[i][1]=v;
		}
	}
	path[index][0]=1;						//path的存储结构为path[0]=length表示点的个数
	path[index][1]=v;						//接下来length个元素为顶点，第length+1个元素
	path[index][2]=0;						//暂存距离dist，数组dist用-1表示已并入S中，搜索结束后再赋值给dist
	dist[index]=-1;								//-1表示该点已并入S中
	for(i=1;i<graph.vexnum;i++){
		mindist=MAXINT;
		for(j=0;j<graph.vexnum;j++){
			if(dist[j] != -1 && dist[j] < mindist){
				mindist=dist[j];
				index2=j;
			}
		}
		if(mindist != MAXINT){
			path[index2][0]++;
			path[index2][path[index2][0]]=graph.vertices[index2].vexno;
			path[index2][path[index2][0]+1]=dist[index2];
			for(j=0;j<graph.vexnum;j++){
				if(dist[j] != -1 && (distance=Distance(graph,graph.vertices[index2].vexno,graph.vertices[j].vexno)) != MAXINT){
					if(dist[index2]+distance < dist[j]){
						dist[j]=dist[index2]+distance;
						for(k=0;k<path[index2][0]+1;k++){
							path[j][k]=path[index2][k];
						}
					}
				}
			}
			dist[index2]=-1;
		}else break;
	}
	for(i=0;i<graph.vexnum;i++){
		dist[i]=path[i][path[i][0]+1];
	}
	return OK;
}
Status hasLoop_un_sub(ALGraph *graph,int start,int visit[]){
	int nextvex;
	int index;
	if(visit[start] == true)return ERROR;
	visit[start]=true;
	while((nextvex=FirstAdjVex(*graph,graph->vertices[start].vexno)) >= 0){
		if(DeleteArc(graph,graph->vertices[start].vexno,nextvex) == ERROR)return ERROR;
		if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
		if(hasLoop_un_sub(graph,index,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status CopyGraph(ALGraph *graph,ALGraph oldgraph){
	int i;
	int nextvex;
	ArcNode *node;
	if(graph == NULL || oldgraph.vexnum == 0)return ERROR;
	graph->vexnum=oldgraph.vexnum;
	graph->arcnum=oldgraph.arcnum;
	graph->kind=oldgraph.kind;
	for(i=0;i<oldgraph.vexnum;i++){
		graph->vertices[i].vexno=oldgraph.vertices[i].vexno;
		graph->vertices[i].firstarc=NULL;
	}
	for(i=0;i<oldgraph.vexnum;i++){
		for(node=oldgraph.vertices[i].firstarc;node;node=node->nextarc){
			if(InsertArc(graph,graph->vertices[i].vexno,node->adjvex,node->weight) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status hasLoop_un(ALGraph oldgraph){
	int visit[MAXVEX];
	int i;
	ALGraph graph;
	if(oldgraph.kind == DG || oldgraph.kind == DN)return ERROR;
	if(CopyGraph(&graph,oldgraph) == ERROR)return ERROR;	//邻接表中不能直接修改内容，会影响原图
	for(i=0;i<graph.vexnum;i++)visit[i]=false;				//故复制了一个
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			if(hasLoop_un_sub(&graph,i,visit) == ERROR){
				DestroyGraph(&graph);
				return true;
			}
		}
	}
	DestroyGraph(&graph);
	return false;
}
Status hasLoop(ALGraph graph){
	int toposequ[MAXVEX];
	if(graph.kind == DG || graph.kind == DN)
		return TopologicalSort(graph,toposequ)==ERROR?true:false;
	else
		return hasLoop_un(graph);
}
Status TopologicalSort(ALGraph graph,int toposequ[]){
	int inarc[MAXVEX];
	int i;
	int vertex;
	int index;
	int count;
	if(graph.kind == UDG || graph.kind == UDN)return ERROR;
	for(i=0;i<graph.vexnum;i++)inarc[i]=0;
	for(i=0;i<graph.vexnum;i++){
		for(vertex=FirstAdjVex(graph,graph.vertices[i].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[i].vexno,vertex)){
			if((index=VexNo(graph,vertex)) == ERROR)return ERROR;
			inarc[index]++;
		}
	}
	count=0;
	while(count < graph.vexnum){
		for(i=0;i<graph.vexnum;i++){
			if(inarc[i] == 0){
				toposequ[count]=graph.vertices[i].vexno;
				inarc[i]=-1;
				count++;
				for(vertex=FirstAdjVex(graph,graph.vertices[i].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[i].vexno,vertex)){
					if((index=VexNo(graph,vertex)) == ERROR)return ERROR;
					inarc[index]--;
				}
				break;
			}
		}
		if(count < graph.vexnum && i == graph.vexnum)return ERROR;
	}
	for(i=0;i<graph.vexnum;i++)printf("%3d",toposequ[i]);
	return OK;
}
Status TopologicalOrder(ALGraph graph,int toposequ[],int etv[]){
	int count;
	int stack[MAXVEX];
	int top;
	int top_toposequ;
	int inarc[MAXVEX];
	int i,j,topvex;
	if(graph.vexnum==0 || toposequ==NULL || etv==NULL)return ERROR;	//判断参数合法性
	if(graph.kind == UDG || graph.kind == UDN)return ERROR;		//只有有向的才能进行拓扑排序
	for(i=0;i<graph.vexnum;i++){
		inarc[i]=0;				//初始化入度数组
		etv[i]=0;				//和顶点最早开始时间
	}
	for(i=0;i<graph.vexnum;i++){
		for(j=FirstAdjVex(graph,graph.vertices[i].vexno);j>=0;j=NextAdjVex(graph,graph.vertices[i].vexno,j)){
			if((topvex=VexNo(graph,j)) == ERROR)return ERROR;
			inarc[topvex]++;	//统计各顶点入度
		}
	}
	top=-1;
	for(i=0;i<graph.vexnum;i++){
		if(inarc[i] == 0){
			top++;
			stack[top]=i;		//将入度为0的顶点下标入栈，注意是下标入栈
		}
	}
	top_toposequ=-1;
	count=0;
	while(top != -1){
		topvex=stack[top];
		top--;
		top_toposequ++;
		toposequ[top_toposequ]=topvex;	//将顶点下标存进拓扑序列中
		count++;
		for(i=FirstAdjVex(graph,graph.vertices[topvex].vexno);i>=0;i=NextAdjVex(graph,graph.vertices[topvex].vexno,i)){
			if((j=VexNo(graph,i)) == ERROR)return ERROR;
			inarc[j]--;
			if(inarc[j] == 0){
				top++;
				stack[top]=j;
			}
			if(etv[j] < etv[topvex]+Distance(graph,graph.vertices[topvex].vexno,i))
				etv[j]=etv[topvex]+Distance(graph,graph.vertices[topvex].vexno,i);
		}
	}
	if(count < graph.vexnum)return ERROR;	//存在回路
	else return OK;
}
Status CriticalPath(ALGraph graph){
	int etv[MAXVEX];
	int ltv[MAXVEX];
	int toposequ[MAXVEX];
	int ete,lte;
	int i,j,topvex;
	int top;
	if(TopologicalOrder(graph,toposequ,etv) == ERROR)return ERROR;
	top=graph.vexnum-1;
	for(i=0;i<graph.vexnum;i++)ltv[i]=etv[top];
	while(top != -1){
		topvex=toposequ[top];
		top--;
		for(i=FirstAdjVex(graph,graph.vertices[topvex].vexno);i>=0;i=NextAdjVex(graph,graph.vertices[topvex].vexno,i)){
			if((j=VexNo(graph,i)) == ERROR)return ERROR;
			if(ltv[topvex] > ltv[j]-Distance(graph,graph.vertices[topvex].vexno,i))
				ltv[topvex]=ltv[j]-Distance(graph,graph.vertices[topvex].vexno,i);
		}
	}
	for(i=0;i<graph.vexnum;i++){
		for(j=FirstAdjVex(graph,graph.vertices[i].vexno);j>=0;j=NextAdjVex(graph,graph.vertices[i].vexno,j)){
			if((topvex=VexNo(graph,j)) == ERROR)return ERROR;
			ete=etv[i];
			lte=ltv[topvex]-Distance(graph,graph.vertices[i].vexno,j);
			if(ete == lte){
				printf("<%d,%d>  ",graph.vertices[i].vexno,j);
			}
		}
	}
	printf("\n");
	return OK;
}
Status MiniSpanTree_PRIM(ALGraph graph,int v){
	int i,j;
	int index;
	int distance;
	struct {
		int vexno;
		int lowcost;
	}closedge[MAXVEX];
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		closedge[i].vexno=v;
		if(i != index){
			closedge[i].lowcost=Distance(graph,v,graph.vertices[i].vexno);
			if(closedge[i].lowcost == ERROR)return ERROR;
		}else{
			closedge[i].lowcost=-1;
		}
	}
	for(i=1;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++)
			if(closedge[j].lowcost != -1)
				break;
		index=j;
		for(j=j+1;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && closedge[j].lowcost < closedge[index].lowcost)
				index=j;
		}
		printf("<%d,%d>  ",closedge[index].vexno,graph.vertices[index].vexno);
		closedge[index].lowcost=-1;
		for(j=0;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && (distance=Distance(graph,graph.vertices[index].vexno,graph.vertices[j].vexno)) < closedge[j].lowcost){
				closedge[j].vexno=graph.vertices[index].vexno;
				if(closedge[j].vexno == ERROR)return ERROR;
				closedge[j].lowcost=distance;
			}
		}
	}
	printf("\n");
	return OK;
}
Status MiniSpanTree_Kruskal(ALGraph graph){
	int parent[MAXVEX];
	struct {
		int begin;			//起始顶点
		int end;			//终点
		int weight;			//权
	}edge[100];				//无法确定边最大多少条，暂且用100吧
	int edgenum;
	int i,j,k,index;
	int parent_begin,parent_end;
	int begin,end;
	int weight;
	ArcNode *arc;
	if(graph.vexnum == 0)return ERROR;
	edgenum=0;
	for(i=0;i<graph.vexnum;i++){		
		for(arc=graph.vertices[i].firstarc;arc;arc=arc->nextarc){//由于对于无向网，无法提前预知哪些边已经添加过了
			weight=arc->weight;									//因此采用边添加边排序，若遇到同样的边，则不用添加
			begin=graph.vertices[i].vexno;
			end=arc->adjvex;
			for(index=0;index<edgenum;index++){				//找到该插入的位置
				if(edge[index].weight > weight)break;		//在此处插入
				if(edge[index].end==begin && edge[index].begin==end)break;	//遇到同样的边
			}
			if(index==edgenum || edge[index].weight > weight){	//采用直接插入排序
				for(k=edgenum-1;k>=index;k--){				//往后移一格
					edge[k+1].begin=edge[k].begin;
					edge[k+1].end=edge[k].end;
					edge[k+1].weight=edge[k].weight;
				}
				edge[index].begin=begin;					//插入
				edge[index].end=end;
				edge[index].weight=weight;
				edgenum++;
			}			//else则遇到相同边，不用插入
		}
	}
	for(i=0;i<graph.vexnum;i++)parent[i]=-1;
	edgenum=0;
	for(i=0;i<graph.arcnum;i++){
		if(edgenum == graph.vexnum-1)break;
		begin=edge[i].begin;
		end=edge[i].end;
		parent_begin=findparent(parent,VexNo(graph,begin));
		parent_end=findparent(parent,VexNo(graph,end));
		if(parent_begin != parent_end){
			parent[parent_end]=parent_begin;
			printf("<%d,%d>  ",begin,end);
			edgenum++;
		}
	}
	return OK;
}
int findparent(int *arr,int vertex){
	while(arr[vertex] != -1)
		vertex=arr[vertex];
	return vertex;
}
int Distance(ALGraph graph,int v,int w){
	int index;
	int index2;
	ArcNode *node;
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	if((index2=VexNo(graph,w)) == ERROR)return ERROR;
	for(node=graph.vertices[index].firstarc;node;node=node->nextarc){
		if(node->adjvex == w)				//找到边<v,w>，返回其权
			return node->weight;
	}
	return MAXINT;							//若没有找到边，返回无限大
}
Status DestroyCSTree(CSTNode **root){
	CSTNode *node;
	CSTNode *temp;
	node=(*root)->firstchild;
	free(*root);
	*root=NULL;
	while(node){
		temp=node->nextsibling;
		if(DestroyCSTree(&node) == ERROR)return ERROR;
		node=temp;
	}
	return OK;
}
Status DestroyCSForest(CSTNode **root){
	CSTNode *tree,*temp;
	tree=*root;
	while(tree){
		temp=tree->nextsibling;
		if(DestroyCSTree(&tree) == ERROR)return ERROR;
		tree=temp;
	}
	(*root)=NULL;
	return OK;
}
Status PreOrderTraverseCSTress(CSTNode *root,Status (*visit)(CSTNode *)){
	CSTNode *node;
	if(visit(root) == ERROR)return ERROR;
	for(node=root->firstchild;node;node=node->nextsibling){
		if(PreOrderTraverseCSTress(node,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status PreOrderTraverseCSForest(CSTNode *root,Status (*visit)(CSTNode *)){
	CSTNode *tress;
	for(tress=root;tress;tress=tress->nextsibling){
		if(PreOrderTraverseCSTress(tress,visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}
Status PrintCSTree(CSTNode *node){
	printf("%3d",node->data);
	return OK;
}
Status DFSForest(ALGraph graph,CSTNode **root){
	int visit[MAXVEX];
	int i;
	CSTNode *pre,*node;
	*root=NULL;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=graph.vertices[i].vexno;
			if(*root == NULL)*root=node;
			else pre->nextsibling=node;
			pre=node;
			if(DFSTree(graph,i,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTree(ALGraph graph,int start,CSTNode *root,int *visit){
	int vertex;
	int first;
	int index;
	CSTNode *node,*pre;
	if(start < 0)return ERROR;
	if(root == NULL)return ERROR;
	if(visit == NULL)return ERROR;
	visit[start]=true;
	first=true;
	for(vertex=FirstAdjVex(graph,graph.vertices[start].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[start].vexno,vertex)){
		if((index=VexNo(graph,vertex)) == -1)return ERROR;
		if(visit[index] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->data=vertex;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			if(first){
				root->firstchild=node;
				first=false;
			}else{
				pre->nextsibling=node;
			}
			pre=node;
			if(DFSTree(graph,index,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse_sub(ALGraph *graph,int start,Status (*traverse)(VNode),int *visit){
	int index;
	int nextvex;
	if((index=VexNo(*graph,start)) == ERROR)return ERROR;
	if(traverse(graph->vertices[index]) == ERROR)return ERROR;
	visit[index]=true;
	for(nextvex=FirstAdjVex(*graph,start);nextvex>=0;nextvex=NextAdjVex(*graph,start,nextvex)){
		if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
		if(visit[index] == false){
			if(DFSTraverse_sub(graph,nextvex,traverse,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse(ALGraph *graph,Status (*traverse)(VNode)){
	int visit[MAXVEX];
	int i;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	return DFSTraverse_sub(graph,graph->vertices[0].vexno,traverse,visit);
}
Status BFSTraverse(ALGraph *graph,Status (*traverse)(VNode)){
	int queue[MAXVEX];
	int top,buttom;
	int visit[MAXVEX];
	int vertex;
	int index;
	int i;
	int nextvex;
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	top=buttom=0;				//初始化队列，队首等于队尾表示队列为空
	if(traverse(graph->vertices[0]) == ERROR)return ERROR;	//访问顶点
	visit[0]=true;
	queue[buttom]=graph->vertices[0].vexno;	
	buttom++;					//这两句模拟入队列，将顶点序号入队列，然后队尾向后一个	
	while(top != buttom){		//当队列不空时
		vertex=queue[top];
		top++;					//这两句模拟出队列，将顶点序号从队列中弹出，并使队首向后一个
		for(nextvex=FirstAdjVex(*graph,vertex);nextvex>=0;nextvex=NextAdjVex(*graph,vertex,nextvex)){
			if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
			if(visit[index] == false){		//如果顶点还未访问过
				if(traverse(graph->vertices[index]) == ERROR)return ERROR;
				visit[index]=true;
				queue[buttom]=nextvex;		//则访问并入队列
				buttom++;
			}
		}
	}
	return OK;
}
Status Print(VNode vnode){
	printf("%2d",vnode.vexno);
	return OK;
}
Status InsertVex(ALGraph *graph,int v){
	if(graph == NULL || graph->vexnum >= MAXVEX)return ERROR;
	if(VexNo(*graph,v) != -1)return ERROR;			//判断参数合法性
	graph->vertices[graph->vexnum].firstarc=NULL;
	graph->vertices[graph->vexnum].vexno=v;
	graph->vexnum++;
	return OK;
}
Status DeleteVex(ALGraph *graph,int v){
	int index;
	ArcNode *node,*temp;
	int i;
	if(graph == NULL || graph->vexnum <= 0)return ERROR;
	if((index=VexNo(*graph,v)) == -1)return ERROR;			//判断参数合法性
	for(i=0;i<graph->vexnum;i++){					//先删除其他顶点到v的边
		if(DeleteArc(graph,graph->vertices[i].vexno,v) == ERROR)return ERROR;
	}
	node=graph->vertices[index].firstarc;			//再删除v到其他顶点的边
	while(node){									//如果是无向图，第一步已经将v到其他顶点的边删除了
		temp=node;
		node=node->nextarc;
		free(temp);
		graph->arcnum--;							//注意这里要手动减少边数
	}
	for(;index<graph->vexnum-1;index++){			//将数组中顶点v的下标index以下的顶点晚上移一行
		graph->vertices[index].vexno=graph->vertices[index+1].vexno;
		graph->vertices[index].firstarc=graph->vertices[index+1].firstarc;
	}
	graph->vexnum--;								//最后还要记得减少顶点数
	return OK;
}
Status DeleteArc(ALGraph *graph,int v,int w){
	int index;
	int index2;												//三种返回类型
	ArcNode *node,*pre;										//0:成功,-1:失败,-2:可忽略
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	if((index=VexNo(*graph,v)) == -1)return ERROR;
	if((index2=VexNo(*graph,w)) == -1)return ERROR;			//判断参数合法性
	node=graph->vertices[index].firstarc;
	pre=graph->vertices[index].firstarc;					//与删除无虚头结点的链表操作相同
	while(node){
		if(node->adjvex == w){
			if(node == graph->vertices[index].firstarc){
				graph->vertices[index].firstarc=node->nextarc;
				free(node);
			}else{
				pre->nextarc=node->nextarc;
				free(node);
			}
			if(graph->kind == UDG || graph->kind == UDN){	//若是无向图(网)，还要删除对称边
				node=graph->vertices[index2].firstarc;
				pre=graph->vertices[index2].firstarc;
				while(node){
					if(node->adjvex == v){
						if(node == graph->vertices[index2].firstarc){
							graph->vertices[index2].firstarc=node->nextarc;
							free(node);
						}else{
							pre->nextarc=node->nextarc;
							free(node);
						}
						return OK;
					}else{
						pre=node;
						node=node->nextarc;
					}
				}
			}
			graph->arcnum--;		//注意不要忘了减少边数
			return OK;
		}else{
			pre=node;
			node=node->nextarc;
		}
	}
	return -2;
}
int FirstAdjVex(ALGraph graph,int v){
	int index;
	ArcNode *firnode;
	if(graph.vexnum == 0)return ERROR;
	if((index=VexNo(graph,v)) == -1)return ERROR;
	firnode=graph.vertices[index].firstarc;
	return firnode==NULL?ERROR:firnode->adjvex;
}
int NextAdjVex(ALGraph graph,int v,int w){
	int index;
	int index2;
	ArcNode *nextnode;
	if(graph.vexnum == 0)return ERROR;
	if((index=VexNo(graph,v)) == -1)return ERROR;
	if((index2=VexNo(graph,w)) == -1)return ERROR;
	for(nextnode=graph.vertices[index].firstarc;nextnode && nextnode->adjvex != w;nextnode=nextnode->nextarc);
	if(nextnode == NULL)return ERROR;
	else nextnode=nextnode->nextarc;
	return nextnode==NULL?ERROR:nextnode->adjvex;
}
Status DestroyGraph(ALGraph *graph){
	int i;
	ArcNode *temp,*arcnode;
	if(graph->vexnum == 0 && graph->arcnum == 0)return ERROR;
	graph->vexnum=0;
	graph->arcnum=0;
	graph->kind=0;
	for(i=0;i<graph->vexnum;i++){				//释放边表
		arcnode=graph->vertices[i].firstarc;
	    while(arcnode){
	    	temp=arcnode;
	    	arcnode=arcnode->nextarc;
	    	free(temp);
	    }
	    graph->vertices[i].firstarc=NULL;
	    graph->vertices[i].vexno=-1;
	}
	return OK;
}
Status CreateGraph(ALGraph *graph){
	int kind;
	printf("1.有向图\n2.有向网\n3.无向图\n4.无向网\n");
	printf("请输入图的类型：");
	scanf("%d",&kind);
	switch(kind){
		case 1:if(CreateDG(graph) == ERROR)return ERROR;break;
		case 2:if(CreateDN(graph) == ERROR)return ERROR;break;
		case 3:if(CreateUDG(graph) == ERROR)return ERROR;break;
		case 4:if(CreateUDN(graph) == ERROR)return ERROR;break;
		default:printf("请输入正确的图类型编号！\n");
				return ERROR;
	}
	return OK;
}
int VexNo(ALGraph graph,int vexnum){
	int i;
	for(i=0;i<graph.vexnum;i++)
		if(graph.vertices[i].vexno == vexnum)
			break;
	return i<graph.vexnum?i:-1;
}
Status InsertArc(ALGraph *graph,int v,int w,int adj){
	int start,end;
	ArcNode *arcnode,*temp;
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	start=VexNo(*graph,v);
	end=VexNo(*graph,w);
	if(end == -1 || start == -1 || start == end)return ERROR;	//判断参数的合法性
	for(temp=graph->vertices[start].firstarc;temp;temp=temp->nextarc)	//如果已经有<v,w>弧了，不添加，返回-2
		if(temp->adjvex == w)return -2;							//三种返回类型
	arcnode=(ArcNode*)malloc(sizeof(ArcNode));					//0:成功,-1:失败,-2:可忽略
	if(!arcnode)return ERROR;
	arcnode->adjvex=w;
	if(graph->kind == DG || graph->kind == UDG)
		arcnode->weight=1;
	else arcnode->weight=adj;
	arcnode->nextarc=graph->vertices[start].firstarc;			//采用头插法，插入的位置是链表首部，即插入后成为v的第一条邻边，而不是最后一条
	graph->vertices[start].firstarc=arcnode;
	if(graph->kind == UDG || graph->kind == UDN){				//如果是无向图(网)，还要插入对称边
		temp=(ArcNode*)malloc(sizeof(ArcNode));
		if(!temp)return ERROR;
		temp->adjvex=v;
		temp->weight=arcnode->weight;
		temp->nextarc=graph->vertices[end].firstarc;
		graph->vertices[end].firstarc=temp;
	}
	return OK;
}
Status CreateDG(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	graph->kind=DG;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;							   //邻接矩阵中下标就是顶点的编号
	printf("请依次输入顶点的编号(按默认编号输入-1)：");//这里下标与编号分开，顶点编号可以任意，更加合理
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点和终点，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,1) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateDN(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	int adj;
	graph->kind=DN;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;							   //邻接矩阵中下标就是顶点的编号
	printf("请依次输入顶点的编号(按默认编号输入-1)：");//这里下标与编号分开，顶点编号可以任意，更加合理
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){
			printf("边权不合法！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,adj) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDG(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	graph->kind=UDG;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;							   //邻接矩阵中下标就是顶点的编号
	printf("请依次输入顶点的编号(按默认编号输入-1)：");//这里下标与编号分开，顶点编号可以任意，更加合理
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点和终点，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,1) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDN(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	int adj;
	graph->kind=UDN;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){				//判断顶点数是否合法
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;							   //邻接矩阵中下标就是顶点的编号
	printf("请依次输入顶点的编号(按默认编号输入-1)：");//这里下标与编号分开，顶点编号可以任意，更加合理
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){
			printf("边权不合法！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,adj) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
int main(){
	ALGraph graph;
	int i,j;
	ArcNode *temp;
	if(CreateGraph(&graph) == ERROR)printf("error!\n");
	for(i=0;i<graph.vexnum;i++){
		printf("%-5d",graph.vertices[i].vexno);
		for(temp=graph.vertices[i].firstarc;temp;temp=temp->nextarc){
			printf("adjvex=%d  weight=%d     ",temp->adjvex,temp->weight);
		}
		printf("\n");
	}
	if(CriticalPath(graph) == ERROR)return ERROR;
	return 0;
}
