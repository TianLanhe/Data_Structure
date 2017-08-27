#ifndef LIST_GRAPG_H
#define LIST_GRAPG_H

#define Graph ALGraph
#define GraphVertex VNode

typedef struct _algraph ALGraph;
typedef struct _vnode VNode;

#include "graph_base.h"

typedef struct _arcnode {
	int adjvex;					//该弧指向的顶点的位置
	int weight;					//权(规定只能正权)
	struct _arcnode *nextarc;	//指向下一条边
}ArcNode;

typedef struct _vnode {
	int vexno;					//顶点序号(编号)
	ArcNode *firstarc;			//指向第一条边
}VNode;

typedef struct _algraph {
	int vexnum;					//图的当前顶点数
	int arcnum;					//图的当前有向边数
	VNode vertices[MAXVEX];		//图的顶点邻接表(顺序存储)
	GraphKind kind;				//图的种类
}ALGraph;

#endif