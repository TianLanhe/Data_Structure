#ifndef "graph_adjmat_h"
#define "graph_adjmat_h"
#include <stdio.h>
#include <stdlib.h>
#define Status int
#define MAXINT 0x7fffffff
#define OK 0
#define ERROR -1
#define true 1
#define false 0
#define DG 1    		//有向图
#define DN 2			//有向网
#define UDG 3 			//无向图
#define UDN 4 			//无向网
#define MAXVEX 20		//最大顶点数

typedef int GraphKind;
typedef int TElemType;
typedef struct _cstree{					//孩子兄弟链表树
	TElemType data;
	struct _cstree *firstchild;			//左孩子
	struct _cstree *nextsibling;		//右孩子
}CSTNode;
typedef struct _mgraph {
	int vexnum;							//图的当前顶点数
	int arcnum;							//图的当前有向边数
	int arcs[MAXVEX][MAXVEX];			//图的顶点邻接矩阵
	GraphKind kind;						//图的种类
}MGraph;
Status CreateDG(MGraph *graph);
//创建有向图，提示用户输入并根据信息创建有向图邻接矩阵
Status CreateDN(MGraph *graph);
//创建有向网，提示用户输入并根据信息创建有向网邻接矩阵
Status CreateUDG(MGraph *graph);
//创建无向图，提示用户输入并根据信息创建无向图邻接矩阵
Status CreateUDN(MGraph *graph);
//创建无向网，提示用户输入并根据信息创建无向网邻接矩阵
Status CreateGraph(MGraph *graph);
//创建图，提示用户输入并创建相应类型的图
Status DestriyGraph(MGraph *graph);
//销毁图graph，将各项成员置0
int FirstAdjVex(MGraph graph,int v);
//返回顶点v的第一个邻接顶点，若graph不存在或v不是graph的顶点或v没有邻接顶点，则返回-1
int NextAdjVex(MGraph graph,int v,int w);
//返回顶点v相对于w的第一个邻接顶点，若graph不存在或v不是graph的顶点或w不是graph的顶点或者v相对于w之后没有邻接顶点，则返回-1
Status InsertVex(MGraph *graph,int v);
//在图graph中增添新顶点v，若graph不存在或已经达到MAXVEX，或v小于0大于等于MAXVEX，则返回ERROR
//这个方法不太好，容易打乱先前顶点的序号，有待改进
Status DeleteVex(MGraph *graph,int v);
//从图graph中删除顶点v，及其相关的弧。若图graph不存在或顶点v不存在，返回ERROR
Status DeleteArc(MGraph *graph,int v,int w);
//从图graph中删除弧<v,w>，若graph是无向的，则还需删除对称弧<w,v>。若图graph不存在或顶点v或w不存着，则返回ERROR
Status InsertArc(MGraph *graph,int v,int w,int adj);
//若图中没有弧<v,w>，则在图graph中增加该弧，若graph是无向的，则还需增加对称弧<w,v>。若图graph不存在或顶点v或w不存在或边<v,w>已存在，则返回ERROR
Status DFSTraverse(MGraph *graph,Status (*traverse)(int));
//对图进行深度优先遍历，对每个顶点调用一次traverse函数(顶点的应用函数)，若图不存在或其中一个顶点traverse失败，返回ERROR
Status DFSTraverse_sub(MGraph *graph,int start,Status (*traverse)(int),int *visit);
//深度优先遍历的子函数，递归实现深度优先遍历。
Status Print(int i);
//顶点的应用函数，打印顶点的序号
Status BFSTraverse(MGraph *graph,Status (*traverse)(int));
//对图进行广度优先遍历，对每个顶点调用一次traverse函数(顶点的应用函数)，若图不存在或其中一个顶点traverse失败，返回ERROR
Status DFSForest(MGraph graph,CSTNode **root);
//建立无向图graph的深度优先生成森林root
Status DFSTree(MGraph graph,int index,CSTNode *root,int visit[]);
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
Status MiniSpanTree_PRIM(MGraph graph,int start);
//普里姆法求从第start个顶点出发构造网graph的最小生成树，输出各条边。若start大于等于graph顶点数，返回ERROR
//说明：包含打印
int findparent(int *arr,int vertex);
//库鲁斯卡尔法的子函数，往上求vertex的根节点，若两个结点的根节点都相同，则表示会构成环
Status MiniSpanTree_Kruskal(MGraph graph);
//库鲁斯卡尔法构造网graph的最小生成树，输出各条边。说明：包含打印
Status TopologicalSort(MGraph oldgraph,int toposequ[]);
//若有向图(网)oldgraph中无回路，则将oldgraph的一个拓扑序列保存在toposequ中并返回OK。若oldgraph是无向图(网)或有环，返回ERROR
Status TopologicalOrder(MGraph graph,int toposequ[],int etv[]);
//求有向图(网)的拓扑序列和顶点最早开始时间，若图不是有向的，或者存在环，则返回ERROR
Status CriticalPath(MGraph graph);
//求图(网)的关键路径并输出，若图不是有向的，或者存在环则返回ERROR
Status CopyGraph(MGraph *newgraph,MGraph oldgraph);
//复制(克隆)oldgraph到newgraph中
Status hasLoop_un_sub(MGraph graph,int start,int visit[]);
//递归搜索无向图(网)graph,若图中存在回路，返回ERROR，否则返回OK
Status hasLoop_un(MGraph graph);
//若无向图(网)graph中无回路，则返回false，有回路返回true。若是有向图(网)，返回ERROR，
Status hasLoop(MGraph graph);
//判断图中是否存在，有返回true，否则返回false
Status DijShortPath(MGraph graph,int v,int path[][MAXVEX+2],int *dist);
//根据Dijkstra算法求图graph中v顶点到其他顶点的距离(到自身距离为0，无法到达距离为MAXINT)
//path[w][...]存储点v到w的最短路径，其中path[w][0]表示最短路径的顶点个数(包括起点与终点)，接下来n个元素为顶点。dist[w]表示顶点v到w的距离
Status FloShortPath(MGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]);
//根据Floyd算法求图graph中每个顶点到其余顶点的距离(到自身距离为0，无法到达距离为MAXINT)
//path[v][w][...]存储点v到w的最短路径，其中path[v][w][0]表示最短路径的顶点个数(包括起点与终点)，接下来n个元素为顶点。dist[v][w]表示顶点v到w的距离
#endif
