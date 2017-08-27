#include "../list_graph.h"
#include "minimumSpanningTree.h"
#include <stdio.h>

Status MiniSpanTree_PRIM(ALGraph graph, int v) {
	int i, j;
	int index;
	int distance;
	struct {
		int pre_index;
		int lowcost;
	}closedge[MAXVEX];

	if (graph.vexnum == 0)
		return ERROR;
	if ((index = LocateVex(graph, v)) == -1)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {
		closedge[i].pre_index = index;
		closedge[i].lowcost = Distance(graph, index, i);
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

		graph.kind == UDN || graph.kind == DN
			? printf("<%d,%d>(%d)  ", graph.vertices[closedge[index].pre_index].vexno, graph.vertices[index].vexno, closedge[index].lowcost)
			: printf("<%d,%d>  ", graph.vertices[closedge[index].pre_index].vexno, graph.vertices[index].vexno);
		closedge[index].lowcost = -1;

		for (j = 0; j < graph.vexnum; j++) {
			if (closedge[j].lowcost != -1 && (distance = Distance(graph, index, j)) < closedge[j].lowcost) {
				closedge[j].pre_index = index;
				closedge[j].lowcost = distance;
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

Status MiniSpanTree_Kruskal(ALGraph graph) {
	int parent[MAXVEX];
	struct {
		int begin;			//起始顶点
		int end;			//终点
		int weight;			//权
	}edge[MAXVEX*(MAXVEX - 1)];
	int edgenum;
	int i, k, index;
	int parent_begin, parent_end;
	int begin, end;
	int weight;
	ArcNode *arc;

	if (graph.vexnum == 0)
		return ERROR;

	edgenum = 0;
	for (i = 0; i < graph.vexnum; i++) {				//提取边，边提取边排序
		for (arc = graph.vertices[i].firstarc; arc; arc = arc->nextarc) {
			weight = arc->weight;						//由于对于无向网，无法提前预知哪些边已经添加过了
			begin = i;									//因此采用边添加边排序，若遇到同样的边，则不用添加
			end = arc->adjvex;

			for (index = 0; index < edgenum; index++) {	//找到该插入的位置
				if (edge[index].weight > weight)break;	//在此处插入
				if (edge[index].end == begin && edge[index].begin == end)
					break;	//遇到同样的边，不插入
			}
			if (index == edgenum || edge[index].weight > weight) {	//采用直接插入排序
				for (k = edgenum - 1; k >= index; k--) 				//往后移一格
					edge[k + 1] = edge[k];

				edge[index].begin = begin;
				edge[index].end = end;
				edge[index].weight = weight;
				edgenum++;
			}			//else则遇到相同边，不用插入
		}
	}

	for (i = 0; i < graph.vexnum; i++)
		parent[i] = -1;

	edgenum = 0;
	for (i = 0; i < graph.arcnum; i++) {
		if (edgenum == graph.vexnum - 1)
			break;

		begin = edge[i].begin;
		end = edge[i].end;
		parent_begin = findparent(parent, begin);	//回溯到最上的parent
		parent_end = findparent(parent, end);

		if (parent_begin != parent_end) {			//若parent不同，说明在不同连通分量，不会构成回路
			parent[parent_end] = parent_begin;
			graph.kind == UDN || graph.kind == DN
				? printf("<%d,%d>(%d)  ", graph.vertices[begin].vexno, graph.vertices[end].vexno, edge[i].weight)
				: printf("<%d,%d>  ", graph.vertices[begin].vexno, graph.vertices[end].vexno);
			edgenum++;
		}
	}
	return OK;
}

int main() {
	ALGraph graph;
	ArcNode *temp;
	int i;
	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}

	if (MiniSpanTree_Kruskal(graph) != OK)return 1;
	return 0;
}
