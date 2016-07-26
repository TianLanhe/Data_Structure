#ifndef graph_adjlist_h
#define graph_adjlist_h
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
Status TopologicalSort(ALGraph oldgraph,int toposequ[]);
//若有向图(网)oldgraph中无回路，则将oldgraph的一个拓扑序列保存在toposequ中并返回OK。若oldgraph是无向图(网)或有环，返回ERROR
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
#endif

