#include "../list_graph.h"
#include "topologicalSort.h"
#include <stdio.h>

Status TopologicalSort(ALGraph graph, int toposequ[MAXVEX]) {
	int inarc[MAXVEX];
	int i;
	int vertex;
	int count;

	if (graph.kind == UDG || graph.kind == UDN)
		return ERROR;
	if (!toposequ)
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++)
		inarc[i] = 0;

	for (i = 0; i < graph.vexnum; i++)
		for (vertex = FirstAdjVex(graph, i); vertex >= 0; vertex = NextAdjVex(graph, i, vertex))
			inarc[vertex]++;

	count = 0;
	while (count < graph.vexnum) {
		for (i = 0; i < graph.vexnum; i++) {
			if (inarc[i] == 0) {
				toposequ[count++] = graph.vertices[i].vexno;
				inarc[i] = -1;
				for (vertex = FirstAdjVex(graph, i); vertex >= 0; vertex = NextAdjVex(graph, i, vertex)) {
					inarc[vertex]--;
				}
				break;
			}
		}
		if (count < graph.vexnum && i == graph.vexnum)
			return ERROR;
	}
	return OK;
}

Status sub_DFSTopologicalSort(Graph graph, int *count, int index, int toposequ[MAXVEX], int visited[MAXVEX], int path[MAXVEX]) {
	int nextvex;

	if (path[index])
		return ERROR;

	if (!visited[index]) {
		path[index] = true;
		visited[index] = true;
		for (nextvex = FirstAdjVex(graph, index); nextvex != -1; nextvex = NextAdjVex(graph, index, nextvex)) {
			if (sub_DFSTopologicalSort(graph, count, nextvex, toposequ, visited, path) == ERROR)
				return ERROR;
		}
		toposequ[(*count)++] = graph.vertices[index].vexno;
		path[index] = false;
	}
	return OK;
}

Status DFSTopologicalSort(Graph graph, int toposequ[MAXVEX]) {
	int visited[MAXVEX];
	int path[MAXVEX];
	int count;
	int i;

	if (graph.kind == UDG || graph.kind == UDN)
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

	for (i = 0; i < graph.vexnum / 2; ++i) {
		count = toposequ[i];
		toposequ[i] = toposequ[graph.vexnum - 1 - i];
		toposequ[graph.vexnum - 1 - i] = count;
	}

	return OK;
}

int sub_undirected_hasLoop(ALGraph graph, int index, int visited[MAXVEX]) {
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

int undirected_hasLoop(ALGraph graph) {
	int visited[MAXVEX];
	int index;
	for (index = 0; index < graph.vexnum; ++index)
		visited[index] = false;

	for (index = 0; index < graph.vexnum; ++index)
		if (visited[index] == false && sub_undirected_hasLoop(graph, index, visited))
			return true;
	return false;
}

int hasLoop(ALGraph graph) {
	int topu[MAXVEX];
	if (graph.kind == UDG || graph.kind == UDN)
		return undirected_hasLoop(graph);
	else
		return TopologicalSort(graph, topu) == ERROR;
}

int main() {
	ALGraph graph;
	ArcNode *temp;
	int toqu[MAXVEX];
	int i;
	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
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

