#include "../list_graph.h"
#include "depthFirstSpanningTree.h"
#include <stdlib.h>
#include <stdio.h>

Status DFSForest(ALGraph graph, CSTNode **root) {
	int i;
	int visit[MAXVEX];
	CSTNode *node, *pre;
	Status status;

	for (i = 0; i < graph.vexnum; i++)
		visit[i] = false;

	*root = NULL;
	for (i = 0; i < graph.vexnum; i++) {
		if (visit[i] == false) {
			visit[i] = true;

			node = (CSTNode*)malloc(sizeof(CSTNode));
			if (!node)
				return OVERFLOW;

			node->firstchild = NULL;
			node->nextsibling = NULL;
			node->data = graph.vertices[i].vexno;

			if (*root == NULL)
				*root = node;
			else
				pre->nextsibling = node;
			pre = node;

			if ((status = DFSTree(graph, i, node, visit)) != OK)
				return status;
		}
	}
	return OK;
}

Status DFSTree(ALGraph graph, int start, CSTNode *root, int *visit) {
	int nextvex;
	int first;
	CSTNode *node, *pre;
	Status status;

	first = true;
	for (nextvex = FirstAdjVex(graph, start); nextvex >= 0; nextvex = NextAdjVex(graph, start, nextvex)) {
		if (visit[nextvex] == false) {
			visit[nextvex] = true;

			node = (CSTNode*)malloc(sizeof(CSTNode));
			if (!node)
				return OVERFLOW;

			node->data = graph.vertices[nextvex].vexno;
			node->firstchild = NULL;
			node->nextsibling = NULL;

			if (first) {
				root->firstchild = node;
				first = false;
			}
			else {
				pre->nextsibling = node;
			}
			pre = node;

			if ((status = DFSTree(graph, nextvex, node, visit)) != OK)
				return status;
		}
	}
	return OK;
}

int main() {
	Graph graph;
	ArcNode *temp;
	CSTNode *root;
	int i;
	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}

	if (DFSForest(graph, &root) != OK)return 1;
	PreOrderTraverseCSForest(root, PrintCSTree);
	InOrderTraverseCSForest(root, PrintCSTree);

	DestroyCSForest(&root);
	return 0;
}
