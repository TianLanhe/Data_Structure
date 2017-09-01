#ifndef ARTICULATED_AND_BICONNECTED
#define ARTICULATED_AND_BICONNECTED

#include "../graph_base.h"

Status FindArticul(Graph graph, int articulated[MAXVEX + 1]);
//查找图graph上的全部关节点并储存在articulated中，其中articulated[0]存储长度，接下来的元素是关节点
//若图存在孤立点，则查找失败，返回ERROR
Status DFSArticul(Graph graph, int vex_index, int *count, int articulated[MAXVEX + 1], int visited_sequ[MAXVEX], int vex_can_arrived[MAXVEX]);
//从图graph的下标vex_index的顶点出发深度优先遍历并查找关节点
int isBiconnectedGraph(Graph graph);
//判断图graph是否为重连通图(没有关节点的重联通图)，若存在孤立点，则返回false

#endif