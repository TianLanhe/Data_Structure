#ifndef CRITICAL_PATH_H
#define CRITICAL_PATH_H

#include "../graph_base.h"

typedef struct _edge {
	int start;
	int end;
}Edge;

Status TopologicalOrder(Graph graph, int toposequ[MAXVEX], int etv[MAXVEX]);
//求有向图(网)的拓扑序列和顶点最早开始时间，若图不是有向的，或者存在环，则返回ERROR
Status CriticalPath(Graph graph, int criticalVex[MAXVEX + 1], Edge criticalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1]);
//求图(网)的关键顶点和关键路径，若图不是拓扑有序的，返回ERROR

#endif
