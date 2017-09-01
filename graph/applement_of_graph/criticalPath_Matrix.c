#include "../matrix_graph.h"
#include "criticalPath.h"

Status TopologicalOrder(MGraph graph, int toposequ[MAXVEX], int etv[MAXVEX]) {
	int queue[MAXVEX];
	int top, bottom;
	int inarc[MAXVEX];
	int i, j;
	int topvex;
	int count;

	if (graph.kind == UDG || graph.kind == UDN)
		return ERROR;
	if (graph.vexnum == 0)
		return ERROR;
	if (!toposequ || !etv)
		return ERROR;

	top = bottom = 0;						//初始化队列
	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;
		etv[i] = 0;							//事件(顶点)最早发生时间
	}

	for (i = 0; i < graph.vexnum; i++)
		for (j = 0; j < graph.vexnum; j++)
			if (graph.arcs[i][j] != MAXINT)
				inarc[j]++;					//统计各个顶点的入度

	for (i = 0; i < graph.vexnum; i++)		//循环一遍，把入度为0的顶点入栈
		if (inarc[i] == 0)
			queue[bottom++] = i;

	count = 0;								//统计顶点个数，如果最后拓扑序列中顶点个数少于
	while (top != bottom) {					//图的顶点个数，则表示存在回路，应返回ERROR
		topvex = queue[top++];
		toposequ[count++] = topvex;			//寻找以topvex为尾的边，然后删除终点的入度

		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			inarc[i]--;
			if (inarc[i] == 0)
				queue[bottom++] = i;

			if (etv[i] < etv[topvex] + graph.arcs[topvex][i])
				etv[i] = etv[topvex] + graph.arcs[topvex][i];
		}
	}

	if (count != graph.vexnum)	//存在回路
		return ERROR;
	return OK;
}

Status CriticalPath(MGraph graph, int criticalVex[MAXVEX + 1], Edge criticalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1]) {
	int etv[MAXVEX];			//顶点最早发生时间
	int ltv[MAXVEX];			//顶点最晚发生时间
	int ete, lte;				//边最早发生时间，边最晚发生时间
	int toposequ[MAXVEX];		//拓扑序列
	int top, topvex;			//top模仿栈顶，topvex表示取出的栈顶元素
	int i, j;

	if (TopologicalOrder(graph, toposequ, etv) == ERROR)	//进行拓扑排序并计算顶点最早发生时间
		return ERROR;

	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)
		ltv[i] = etv[top];

	while (top != -1) {			//对拓扑序列从尾开始倒序计算顶点最晚发生时间
		topvex = toposequ[top--];

		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			if (ltv[topvex] > ltv[i] - graph.arcs[topvex][i])	//更新顶点最晚发生时间
				ltv[topvex] = ltv[i] - graph.arcs[topvex][i];
		}
	}

	criticalVex[0] = 0;
	criticalEdge[0].start = criticalEdge[0].end = 0;
	for (i = 0; i < graph.vexnum; i++) {	//接下来根据顶点的时间计算每条边的最早发生时间与最晚发生时间
		for (j = FirstAdjVex(graph, i); j >= 0; j = NextAdjVex(graph, i, j)) {	//若相等，则证明其是关键边
			ete = etv[i];
			lte = ltv[j] - graph.arcs[i][j];
			if (ete == lte) {
				++criticalEdge[0].start;
				++criticalEdge[0].end;
				criticalEdge[criticalEdge[0].start].start = graph.vexs[i];
				criticalEdge[criticalEdge[0].end].end = graph.vexs[j];
			}
		}

		if (etv[i] == ltv[i]) {	//根据顶点最早时间和最晚时间判断是否是关键顶点
			++criticalVex[0];
			criticalVex[criticalVex[0]] = graph.vexs[i];
		}
	}
	return OK;
}

int main() {
	MGraph graph;
	int criticalVex[MAXVEX + 1];
	Edge critivalEdge[MAXVEX*(MAXVEX - 1) / 2 + 1];
	int i, j;

	if (CreateGraph(&graph) != OK)return 1;

	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("∞");
			else printf("%2d", graph.arcs[i][j]);
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
