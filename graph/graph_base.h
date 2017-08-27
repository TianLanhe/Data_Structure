#ifndef GRAPH_BASE_H
#define GRAPH_BASE_H

#include "../DataStructureBase.h"

#define MAXINT 0x7fffffff

#ifndef MAXVEX
#define MAXVEX 20		//最大顶点数
#endif

#ifndef Graph
#define Graph void
#endif

#ifndef GraphVertex
#define GraphVertex int
#endif

typedef enum _graphkind {
	DG = 1, DN, UDG, UDN   	//有向图，有向网，无向图，无向网
} GraphKind;				//图的类型

Status sub_CreateGraph(Graph *graph, GraphKind kind);
//根据用户输入的类型创建图或网；若是网，需要提示输入权值；若是无向的，需要设置双向边
Status CreateGraph(Graph *graph);
//创建图，提示用户输入并创建相应类型的图
int LocateVex(Graph graph, int vexnum);
//根据顶点的编号确定其下标，若无此顶点则返回-1
Status DestroyGraph(Graph *graph);
//销毁图graph，将各项成员置0
int FirstAdjVex(Graph graph, int index);
//返回顶点v的第一个邻接顶点，若graph不存在或v不是graph的顶点或v没有邻接顶点，则返回-1
int NextAdjVex(Graph graph, int index1, int index2);
//返回顶点v相对于w的第一个邻接顶点，若graph不存在或v不是graph的顶点或w不是graph的顶点或者v相对于w之后没有邻接顶点，则返回-1
int Distance(Graph graph, int index1, int index2);
//计算两个顶点的距离，若无法直接到达，返回MAXINT，若下标不合法，返回MAXINT
Status InsertVex(Graph *graph, int vexnum);
//在图graph中增添编号为vexnum的新顶点，若graph不存在或已经达到MAXVEX，或vexnum小于0或已经有这个编号的顶点，则返回ERROR
Status DeleteVex(Graph *graph, int vexnum);
//从图graph中删除编号为vexnum的顶点，及其相关的弧。若图graph不存在或顶点v不存在，返回ERROR
Status InsertArc(Graph *graph, int v, int w, int adj);
//若图中没有弧<v,w>，则在图graph中增加该弧，若graph是无向的，则还需增加对称弧<w,v>。若图graph不存在或顶点v或w不存在或边<v,w>已存在，则返回ERROR
Status DeleteArc(Graph *graph, int v, int w);
//从图graph中删除弧<v,w>，若graph是无向的，则还需删除对称弧<w,v>。若图graph不存在或顶点v或w不存着，则返回ERROR
Status DFSTraverse(Graph *graph, Status(*traverse)(GraphVertex));
//对图进行深度优先遍历，对每个顶点调用一次traverse函数(顶点的应用函数)，若图不存在或其中一个顶点traverse失败，返回ERROR
Status DFSTraverse_sub(Graph *graph, int idx_start, Status(*traverse)(GraphVertex), int *visit);
//深度优先遍历的子函数，递归实现深度优先遍历。
Status BFSTraverse(Graph *graph, Status(*traverse)(GraphVertex));
//对图进行广度优先遍历，对每个顶点调用一次traverse函数(顶点的应用函数)，若图不存在或其中一个顶点traverse失败，返回ERROR
Status Print(GraphVertex i);
//顶点的应用函数，打印顶点的序号

#endif