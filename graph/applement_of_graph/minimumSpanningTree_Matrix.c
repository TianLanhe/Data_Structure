#include "../matrix_graph.h"
#include "minimumSpanningTree.h"
#include <stdio.h>

Status MiniSpanTree_PRIM(MGraph graph, int start) {
	int i, j;
	int index;
	struct {
		int pre_index;
		int lowcost;
	}closedge[MAXVEX];

	if ((index = LocateVex(graph, start)) == -1)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {	//初始化closedge数组，lowcost=-1表示并入已选集合中
		closedge[i].pre_index = index;
		closedge[i].lowcost = graph.arcs[index][i];
	}
	closedge[index].lowcost = -1;

	for (i = 1; i < graph.vexnum; i++) {
		index = -1;
		for (j = 0; j < graph.vexnum; j++) {
			if (closedge[j].lowcost != -1) {
				if (index == -1 || closedge[j].lowcost < closedge[index].lowcost)
					index = j;
			}
		}
		if (index == -1)
			return ERROR;

		graph.kind == UDG || graph.kind == DG
			? printf("<%d,%d>  ", graph.vexs[closedge[index].pre_index], graph.vexs[index])
			: printf("<%d,%d>(%d) ", graph.vexs[closedge[index].pre_index], graph.vexs[index], closedge[index].lowcost);
		closedge[index].lowcost = -1;

		for (j = 0; j < graph.vexnum; j++) {
			if (closedge[j].lowcost != -1 && graph.arcs[index][j] < closedge[j].lowcost) {
				closedge[j].pre_index = index;
				closedge[j].lowcost = graph.arcs[index][j];
			}
		}
	}
	printf("\n");
	return OK;
}

int findparent(int *arr, int index) {
	while (arr[index] != -1)
		index = arr[index];
	return index;
}

Status MiniSpanTree_Kruskal(MGraph graph) {
	struct _edge {
		int begin;			//起始顶点
		int end;			//终点
		int weight;			//权
	};
	struct _edge edges[MAXVEX*(MAXVEX - 1)];
	struct _edge edge;
	int parent[MAXVEX];
	int edgenum;
	int i, j;
	int parent_begin, parent_end;
	int begin, end;

	if (graph.vexnum == 0)
		return ERROR;

	edgenum = 0;								//将图中所有的边提取出来
	for (i = 0; i < graph.vexnum; i++) {		//注意无向图(网)的矩阵对称，只需要存储上三角的边即可
		j = graph.kind == UDN || graph.kind == UDG ? i + 1 : 0;
		while (j < graph.vexnum) {
			if (graph.arcs[i][j] != MAXINT) {
				edges[edgenum].begin = i;
				edges[edgenum].end = j;
				edges[edgenum].weight = graph.arcs[i][j];
				++edgenum;
			}
			++j;
		}
	}

	for (i = 1; i < edgenum; ++i) {				//直接插入排序
		if (edges[i].weight < edges[i - 1].weight) {
			edge = edges[i];
			for (j = i - 1; j >= 0 && edges[j].weight > edge.weight; --j)
				edges[j + 1] = edges[j];
			edges[j + 1] = edge;
		}
	}

	for (i = 0; i < graph.vexnum; i++)	//用一个parent数组判断是否会构成回路
		parent[i] = -1;

	edgenum = 0;
	for (i = 0; i < graph.arcnum; i++) {
		if (edgenum == graph.vexnum - 1)
			break;

		begin = edges[i].begin;
		end = edges[i].end;
		parent_begin = findparent(parent, begin);	//回溯到最上的parent
		parent_end = findparent(parent, end);

		if (parent_begin != parent_end) {			//若parent不同，说明在不同连通分量，不会构成回路
			parent[parent_end] = parent_begin;
			graph.kind == UDN || graph.kind == DN
				? printf("<%d,%d>(%d)  ", graph.vexs[begin], graph.vexs[end], edge[i].weight)
				: printf("<%d,%d>  ", graph.vexs[begin], graph.vexs[end]);
			++edgenum;
		}
	}
	return OK;
}

int main() {
	MGraph graph;
	int i, j;
	if (CreateGraph(&graph) == ERROR)return ERROR;

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("∞");
			else printf("%2d", graph.arcs[i][j]);
		}
		printf("\n");
	}
	
	if (MiniSpanTree_Kruskal(graph) == ERROR)return 1;
	return 0;
}
