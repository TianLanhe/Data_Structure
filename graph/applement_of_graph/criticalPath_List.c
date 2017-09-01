#include "../list_graph.h"
#include "criticalPath.h"

Status TopologicalOrder(ALGraph graph, int toposequ[MAXVEX], int etv[MAXVEX]) {
	int inarc[MAXVEX];
	int i, j;
	ArcNode *nextarc;
	int count;

	if (graph.kind == UDG || graph.kind == UDN)
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;
	if (!toposequ || !etv)
		return ERROR;

	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;
		etv[i] = 0;							//事件(顶点)最早发生时间
	}

	for (i = 0; i < graph.vexnum; i++)
		for (j = FirstAdjVex(graph, i); j != -1; j = NextAdjVex(graph, i, j))
			inarc[j]++;					//统计各个顶点的入度

	count = 0;
	while (count < graph.vexnum) {
		for (i = 0; i < graph.vexnum; i++) {
			if (inarc[i] == 0) {
				toposequ[count++] = i;
				inarc[i] = -1;

				for (nextarc = graph.vertices[i].firstarc; nextarc; nextarc = nextarc->nextarc) {
					--inarc[nextarc->adjvex];

					if (etv[nextarc->adjvex] < etv[i] + nextarc->weight)
						etv[nextarc->adjvex] = etv[i] + nextarc->weight;
				}
				break;
			}
		}
		if (count < graph.vexnum && i == graph.vexnum)
			return ERROR;
	}
	return OK;
}

Status CriticalPath(ALGraph graph, int criticalVex[MAXVEX + 1], Edge criticalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1]) {
	int etv[MAXVEX];			//顶点最早发生时间
	int ltv[MAXVEX];			//顶点最晚发生时间
	int ete, lte;				//边最早发生时间，边最晚发生时间
	int toposequ[MAXVEX];		//拓扑序列
	int top, topvex;			//top模仿栈顶，topvex表示取出的栈顶元素
	ArcNode *nextarc;
	int i, j;

	if (TopologicalOrder(graph, toposequ, etv) == ERROR)	//进行拓扑排序并计算顶点最早发生时间
		return ERROR;

	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)
		ltv[i] = etv[top];

	while (top != -1) {			//对拓扑序列从尾开始倒序计算顶点最晚发生时间
		topvex = toposequ[top--];

		for (nextarc = graph.vertices[topvex].firstarc; nextarc; nextarc = nextarc->nextarc) {
			if (ltv[topvex] > ltv[nextarc->adjvex] - nextarc->weight)
				ltv[topvex] = ltv[nextarc->adjvex] - nextarc->weight;
		}
	}

	criticalVex[0] = 0;
	criticalEdge[0].start = criticalEdge[0].end = 0;
	for (i = 0; i < graph.vexnum; i++) {	//接下来根据顶点的时间计算每条边的最早发生时间与最晚发生时间
		for (nextarc = graph.vertices[i].firstarc; nextarc; nextarc = nextarc->nextarc) {	//若相等，则证明其是关键边
			j = nextarc->adjvex;
			ete = etv[i];
			lte = ltv[j] - nextarc->weight;
			if (ete == lte) {
				++criticalEdge[0].start;
				++criticalEdge[0].end;
				criticalEdge[criticalEdge[0].start].start = graph.vertices[i].vexno;
				criticalEdge[criticalEdge[0].end].end = graph.vertices[j].vexno;
			}
		}

		if (etv[i] == ltv[i]) {	//根据顶点最早时间和最晚时间判断是否是关键顶点
			++criticalVex[0];
			criticalVex[criticalVex[0]] = graph.vertices[i].vexno;
		}
	}
	return OK;
}

int main() {
	ALGraph graph;
	int criticalVex[MAXVEX + 1];
	Edge critivalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1];
	int i;
	ArcNode *temp;

	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}

	if (CriticalPath(graph, criticalVex, critivalEdge) != OK)return 1;

	for (i = 1; i <= criticalVex[0]; ++i)
		printf("%d ", criticalVex[i]);
	printf("\n");

	for (i = 1; i <= critivalEdge[0].start; ++i)
		printf("<%d,%d> ", critivalEdge[i].start, critivalEdge[i].end);
	printf("\n");
	return 0;
}
