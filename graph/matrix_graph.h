#ifndef MATRIX_GRAPG_H
#define MATRIX_GRAPG_H

#define Graph MGraph
#define GraphVertex VertexType
#define VertexType int

typedef struct _mgraph MGraph;

#include "graph_base.h"

typedef struct _mgraph {
	VertexType vexs[MAXVEX];			//顶点向量
	int vexnum;							//图的当前顶点数
	int arcnum;							//图的当前边数
	int arcs[MAXVEX][MAXVEX];			//图的顶点邻接矩阵
	GraphKind kind;						//图的种类
}MGraph;

#endif