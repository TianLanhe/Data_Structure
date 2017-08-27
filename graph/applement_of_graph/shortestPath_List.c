#include "../list_graph.h"
#include "shortestPath.h"
#include <stdio.h>

Status FloShortPath(ALGraph graph, int path[MAXVEX][MAXVEX][MAXVEX + 1], int dist[MAXVEX][MAXVEX]) {
	int i, j, k;
	int w, count;
	if (path == NULL || dist == NULL)
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			dist[i][j] = Distance(graph, i, j);
			path[i][j][0] = 0;
			if (dist[i][j] != MAXINT) {
				path[i][j][0] += 2;
				path[i][j][1] = graph.vertices[i].vexno;
				path[i][j][2] = graph.vertices[j].vexno;
			}
		}
		path[i][i][0]++;
		path[i][i][1] = graph.vertices[i].vexno;
		dist[i][i] = 0;
	}

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			for (k = 0; k < graph.vexnum; k++) {
				if (dist[j][i] < MAXINT && dist[i][k] < MAXINT) {
					if (dist[j][i] + dist[i][k] < dist[j][k]) {
						dist[j][k] = dist[j][i] + dist[i][k];
						count = 0;
						for (w = 0; w < path[j][i][0] + 1; w++)
							path[j][k][count++] = path[j][i][w];
						for (w = 2; w < path[i][k][0] + 1; w++)
							path[j][k][count++] = path[i][k][w];
						path[j][k][0] += path[i][k][0] - 1;
					}
				}
			}
		}
	}
	return OK;
}

Status DijShortPath(ALGraph graph, int v, int path[][MAXVEX + 1], int *dist) {
	int index;
	int index2;
	int i, j, k;
	int mindist;
	int distance;
	int final[MAXVEX];

	if (graph.vexnum == 0)
		return ERROR;
	if ((index = LocateVex(graph, v)) == -1)
		return ERROR;
	if (path == NULL || dist == NULL)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {
		final[i] = false;
		dist[i] = Distance(graph, index, i);
		path[i][0] = 0;
		if (dist[i] != MAXINT) {
			path[i][0]++;
			path[i][1] = v;
		}
	}
	path[index][0] = 1;						//path的存储结构为path[0]=length表示点的个数
	path[index][1] = v;						//接下来length个元素为顶点
	final[index] = true;
	dist[index] = 0;

	for (i = 1; i < graph.vexnum; i++) {
		mindist = MAXINT;
		for (j = 0; j < graph.vexnum; j++) {
			if (!final[j] && dist[j] < mindist) {
				mindist = dist[j];
				index2 = j;
			}
		}

		if (mindist == MAXINT)
			break;

		final[index2] = true;
		path[index2][0]++;
		path[index2][path[index2][0]] = graph.vertices[index2].vexno;
		for (j = 0; j < graph.vexnum; j++) {
			if (!final[j] && (distance = Distance(graph, index2, j)) != MAXINT) {
				if (dist[index2] + distance < dist[j]) {
					dist[j] = dist[index2] + distance;
					for (k = 0; k < path[index2][0] + 1; k++) {
						path[j][k] = path[index2][k];
					}
				}
			}
		}
	}
	return OK;
}

int main() {
	ALGraph graph;
	ArcNode *temp;
	int i, j;
	if (CreateGraph(&graph) == ERROR)return ERROR;

	for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}

	int path[MAXVEX][MAXVEX + 1];
	int dist[MAXVEX];
	if (DijShortPath(graph, 0, path, dist) == ERROR)return 1;
	for (i = 0; i < graph.vexnum; ++i) {
		for (j = 1; j <= path[i][0]; ++j) {
			printf("%d ", path[i][j]);
		}
		printf("dist:%d\n", dist[i]);
	}
	// int path[MAXVEX][MAXVEX][MAXVEX + 1];
	// int dist[MAXVEX][MAXVEX];
	// if (FloShortPath(graph, path, dist) == ERROR)return 1;
	// for (i = 0; i < graph.vexnum; ++i) {
	// 	for (j = 0; j < graph.vexnum; ++j) {
	// 		printf("%d ", dist[i][j]);
	// 	}
	// 	printf("\n");
	// }
	return 0;
}
