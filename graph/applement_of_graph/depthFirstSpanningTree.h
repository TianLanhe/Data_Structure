#ifndef DEPTH_FIRST_SPANNING_TREE_H
#define DEPTH_FIRST_SPANNING_TREE_H

#include "../graph_base.h"
#include "../../tree/ChildBroLinkTree.h"

Status DFSForest(Graph graph, CSTNode **root);
//建立无向图graph的深度优先生成森林root
Status DFSTree(Graph graph, int index, CSTNode *root, int visit[]);
//从第index个顶点出发深度优先遍历图graph，建立以root为根的生成树

#endif
