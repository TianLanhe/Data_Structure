#ifndef MINIMUM_SPANNING_TREE_H
#define MINIMUM_SPANNING_TREE_H

#include "../graph_base.h"

Status MiniSpanTree_PRIM(Graph graph, int start);
//普里姆法求从第start个顶点出发构造网graph的最小生成树，输出各条边。若graph中不存在编号为start的顶点，返回ERROR
//说明：包含打印
int findparent(int *arr, int vertex);
//库鲁斯卡尔法的子函数，往上求vertex的根节点，若两个结点的根节点都相同，则表示会构成环
Status MiniSpanTree_Kruskal(Graph graph);
//库鲁斯卡尔法构造网graph的最小生成树，输出各条边。
//说明：包含打印

#endif