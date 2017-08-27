#include "../matrix_graph.h"
#include "shortestPath.h"
#include <stdio.h>

Status FloShortPath(MGraph graph, int path[MAXVEX][MAXVEX][MAXVEX + 1], int dist[MAXVEX][MAXVEX]) {
	int i, j, k;
	int w, count;

	if (path == NULL || dist == NULL)
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {		//以下是初始化部分
		for (j = 0; j < graph.vexnum; j++) {
			dist[i][j] = graph.arcs[i][j];
			path[i][j][0] = 0;
			if (dist[i][j] != MAXINT) {
				path[i][j][0] += 2;
				path[i][j][1] = graph.vexs[i];
				path[i][j][2] = graph.vexs[j];
			}
		}
		path[i][i][0]++;
		path[i][i][1] = graph.vexs[i];
		dist[i][i] = 0;
	}

	for (i = 0; i < graph.vexnum; i++) {		//以下是处理部分
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

Status DijShortPath(MGraph graph, int vertex, int path[][MAXVEX + 1], int *dist) {
	int i, j, k;
	int mindist;
	int index;
	int final[MAXVEX];

	if (graph.vexnum == 0)
		return ERROR;
	if (path == NULL || dist == NULL)
		return ERROR;
	if ((index = LocateVex(graph, vertex)) == -1)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {//以下是初始化部分
		final[i] = false;					//final数组表示顶点是否已经加入已选集合
		dist[i] = graph.arcs[index][i];		//dist[i]表示顶点v直接或经过中间节点间接到i的距离
		path[i][0] = 0;
		if (dist[i] != MAXINT) {
			++path[i][0];
			path[i][1] = graph.vexs[index];
		}
	}
	path[index][0] = 1;						//path的存储结构为path[0]=length表示点的个数
	path[index][1] = graph.vexs[index];		//接下来length个元素为顶点
	dist[index] = 0;
	final[index] = true;

	for (i = 1; i < graph.vexnum; i++) {		//以下是处理部分
		mindist = MAXINT;
		for (j = 0; j < graph.vexnum; j++) {	//选一个final为false且dist最小的顶点
			if (!final[j] && dist[j] < mindist) {
				mindist = dist[j];
				index = j;
			}
		}
		if (mindist == MAXINT)			//如果没选到，说明剩下的点要么都是-1要么都是MAXINT，后者无法到达，可以提前跳出
			break;

		path[index][0]++;
		path[index][path[index][0]] = graph.vexs[index];
		final[index] = true;
		for (j = 0; j < graph.vexnum; j++) {
			if (!final[j] && graph.arcs[index][j] != MAXINT) {
				if (dist[index] + graph.arcs[index][j] < dist[j]) {
					dist[j] = dist[index] + graph.arcs[index][j];
					for (k = 0; k < path[index][0] + 1; k++) {
						path[j][k] = path[index][k];
					}
				}
			}
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

	// int path[MAXVEX][MAXVEX + 1];
	// int dist[MAXVEX];
	// if (DijShortPath(graph, 0, path, dist) == ERROR)return 1;
	// for (i = 0; i < graph.vexnum; ++i) {
	// 	for (j = 1; j <= path[i][0]; ++j) {
	// 		printf("%d ", path[i][j]);
	// 	}
	// 	printf("dist:%d\n", dist[i]);
	// }
	int path[MAXVEX][MAXVEX][MAXVEX+1];
	int dist[MAXVEX][MAXVEX];
	if(FloShortPath(graph,path,dist) == ERROR)return 1;
	for(i=0;i<graph.vexnum;++i){
		for(j=0;j<graph.vexnum;++j){
			printf("%d ",dist[i][j]);
		}
		printf("\n");
	}
	return 0;
}
