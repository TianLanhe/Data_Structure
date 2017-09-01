#ifndef TOPOLOGICAL_SORT_H
#define TOPOLOGICAL_SORT_H

#include "../graph_base.h"

Status TopologicalSort(Graph graph, int toposequ[MAXVEX]);
//若graph是无向图(网)或有环，返回ERROR，否则将graph的一个拓扑序列保存在toposequ中并返回OK
Status sub_DFSTopologicalSort(Graph graph, int *count, int index, int toposequ[MAXVEX], int visited[MAXVEX], int path[MAXVEX]);
//深度优先搜索求有向无环图拓扑排序的子函数，深度优先遍历并记录拓扑逆序列，若存在环，则返回ERROR
Status DFSTopologicalSort(Graph graph,int toposequ[MAXVEX]);
//利用深度优先搜索求有向无环图的拓扑序列，保存在toposequ中并返回OK，若不是有向图或者有环，返回ERROR
//深度优先搜索求拓扑序列的局限性：
//	  要求指定从根节点出发进行遍历，且从根节点能遍历到其他所有的点，否则只会记录根节点所能到达的路径的拓扑排序
int sub_undirected_hasLoop(Graph graph, int index, int visited[MAXVEX]);
//判断无向图是否存在环的子函数，深度优先遍历，若遇到已经遍历的顶点则代表存在环，返回true
int undirected_hasLoop(Graph graph);
//判断无向图中是否存在环，有则返回true，否则返回false
int hasLoop(Graph graph);
//判断图中是否存在环，有返回true，否则返回false

#endif