#ifndef SHORTEST_PATH_H
#define SHORTEST_PATH_H

#include "../graph_base.h"

Status DijShortPath(Graph graph, int v, int path[][MAXVEX + 1], int *dist);
//根据Dijkstra算法求图graph中v顶点到其他顶点的距离(到自身距离为0，无法到达距离为MAXINT)
//path[w][...]存储点v到w的最短路径，其中path[w][0]表示最短路径的顶点个数(包括起点与终点)，接下来n个元素为顶点。dist[w]表示顶点v到w的距离
Status FloShortPath(Graph graph, int path[MAXVEX][MAXVEX][MAXVEX + 1], int dist[MAXVEX][MAXVEX]);
//根据Floyd算法求图graph中每个顶点到其余顶点的距离(到自身距离为0，无法到达距离为MAXINT)
//path[v][w][...]存储点v到w的最短路径，其中path[v][w][0]表示最短路径的顶点个数(包括起点与终点)，接下来n个元素为顶点。dist[v][w]表示顶点v到w的距离

#endif
