#include "../matrix_graph.h"
#include "topologicalSort.h"
#include <stdio.h>

Status TopologicalSort(MGraph graph, int toposequ[]) {
	int count;
	int index;
	int column, row;

	int queue[MAXVEX];
	int top, bottom;
	int arcs_num[MAXVEX];

	if (graph.kind == UDG || graph.kind == UDN)//拓扑排序只针对有向图
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;
	if (toposequ == NULL)
		return ERROR;

	top = bottom = 0;
	for (row = 0; row < graph.vexnum; ++row)
		arcs_num[row] = 0;

	for (row = 0; row < graph.vexnum; ++row)
		for (column = 0; column < graph.vexnum; ++column)
			if (graph.arcs[row][column] != MAXINT)
				++arcs_num[column];

	for (row = 0; row < graph.vexnum; ++row)
		if (arcs_num[row] == 0)
			queue[bottom++] = row;

	count = 0;
	while (top != bottom) {
		index = queue[top++];
		toposequ[count++] = graph.vexs[index];
		for (column = 0; column < graph.vexnum; ++column) {
			if (graph.arcs[index][column] != MAXINT) {
				--arcs_num[column];
				if (arcs_num[column] == 0)
					queue[bottom++] = column;
			}
		}
	}

	if (count < graph.vexnum)
		return ERROR;
	return OK;
}

Status sub_DFSTopologicalSort(MGraph graph, int *count, int index, int toposequ[MAXVEX], int visited[MAXVEX], int path[MAXVEX]) {
	int nextvex;

	if (path[index])	//路径重复，表示有向图存在环
		return ERROR;

	if (!visited[index]) {
		path[index] = true;
		visited[index] = true;
		for (nextvex = FirstAdjVex(graph, index); nextvex != -1; nextvex = NextAdjVex(graph, index, nextvex)) {
			if (sub_DFSTopologicalSort(graph, count, nextvex, toposequ, visited, path) == ERROR)
				return ERROR;
		}
		toposequ[(*count)++] = graph.vexs[index];
		path[index] = false;
	}
	return OK;
}

Status DFSTopologicalSort(MGraph graph, int toposequ[MAXVEX]) {
	int visited[MAXVEX];
	int path[MAXVEX];
	int count;
	int i;

	if (graph.kind == UDG || graph.kind == UDN)//拓扑排序只针对有向图
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;
	if (!toposequ)
		return ERROR;

	for (i = 0; i < graph.vexnum; ++i) {
		visited[i] = false;
		path[i] = false;
	}

	count = 0;
	if (sub_DFSTopologicalSort(graph, &count, 0, toposequ, visited, path) == ERROR)
		return ERROR;

	if (count < graph.vexnum)
		return ERROR;

	for (i = 0; i < graph.vexnum / 2; ++i) {		//将逆拓扑序列倒置为拓扑序列
		count = toposequ[i];
		toposequ[i] = toposequ[graph.vexnum - 1 - i];
		toposequ[graph.vexnum - 1 - i] = count;
	}

	return OK;
}

int sub_undirected_hasLoop(MGraph graph, int index, int visited[MAXVEX]) {
	int nextvex;
	if (visited[index])
		return true;

	visited[index] = true;
	for (nextvex = FirstAdjVex(graph, index); nextvex != -1; nextvex = NextAdjVex(graph, index, nextvex)) {
		if (nextvex < index)
			continue;

		if (sub_undirected_hasLoop(graph, nextvex, visited))
			return true;
	}
	return false;
}

int undirected_hasLoop(MGraph graph) {
	int visited[MAXVEX];
	int index;
	for (index = 0; index < graph.vexnum; ++index)
		visited[index] = false;

	for (index = 0; index < graph.vexnum; ++index)
		if (visited[index] == false && sub_undirected_hasLoop(graph, index, visited))
			return true;
	return false;
}

int hasLoop(MGraph graph) {
	int topu[MAXVEX];
	if (graph.kind == UDG || graph.kind == UDN)
		return undirected_hasLoop(graph);
	else
		return TopologicalSort(graph, topu) == ERROR;
}

int main() {
	MGraph graph;
	int toqu[MAXVEX];
	int i, j;
	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("∞");
			else printf("%2d", graph.arcs[i][j]);
		}
		printf("\n");
	}

	if (DFSTopologicalSort(graph, toqu) != OK)return 1;
	for (i = 0; i < graph.vexnum; ++i)
		printf("%d ", toqu[i]);
	printf("\n");

	//printf("%d\n", hasLoop(graph));
	return 0;
}
