#include <stdio.h>
#include <stdlib.h>
#include "../DataStructureBase.h"

Status TopologicalSort(ALGraph oldgraph, int toposequ[]);
//若有向图(网)oldgraph中无回路，则将oldgraph的一个拓扑序列保存在toposequ中并返回OK。若oldgraph是无向图(网)或有环，返回ERROR
Status TopologicalOrder(ALGraph graph, int toposequ[], int etv[]);
//求有向图(网)的拓扑序列和顶点最早开始时间，若图不是有向的，或者存在环，则返回ERROR
Status CriticalPath(ALGraph graph);
//求图(网)的关键路径并输出，若图不是有向的，或者存在环则返回ERROR
Status CopyGraph(ALGraph *graph, ALGraph oldgraph);
//复制(克隆)oldgraph到graph中
Status hasLoop_un_sub(ALGraph *graph, int start, int visit[]);
//递归搜索无向图(网)graph,若图中存在回路，返回ERROR，否则返回OK
//要复制和删除所有边，而且边的遍历混乱。效率不高，有待改进
Status hasLoop_un(ALGraph oldgraph);
//若无向图(网)graph中无回路，则返回false，有回路返回true。若是有向图(网)，返回ERROR，
Status hasLoop(ALGraph graph);
//判断图中是否存在，有返回true，否则返回false

Status hasLoop_un_sub(ALGraph *graph, int start, int visit[]) {
	int nextvex;
	int index;
	if (visit[start] == true)return ERROR;
	visit[start] = true;
	while ((nextvex = FirstAdjVex(*graph, graph->vertices[start].vexno)) >= 0) {
		if (DeleteArc(graph, graph->vertices[start].vexno, nextvex) == ERROR)return ERROR;
		if ((index = LocateVex(*graph, nextvex)) == ERROR)return ERROR;
		if (hasLoop_un_sub(graph, index, visit) == ERROR)return ERROR;
	}
	return OK;
}
Status CopyGraph(ALGraph *graph, ALGraph oldgraph) {
	int i;
	int nextvex;
	ArcNode *node;
	if (graph == NULL || oldgraph.vexnum == 0)return ERROR;
	graph->vexnum = oldgraph.vexnum;
	graph->arcnum = oldgraph.arcnum;
	graph->kind = oldgraph.kind;
	for (i = 0; i < oldgraph.vexnum; i++) {
		graph->vertices[i].vexno = oldgraph.vertices[i].vexno;
		graph->vertices[i].firstarc = NULL;
	}
	for (i = 0; i < oldgraph.vexnum; i++) {
		for (node = oldgraph.vertices[i].firstarc; node; node = node->nextarc) {
			if (InsertArc(graph, graph->vertices[i].vexno, node->adjvex, node->weight) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status hasLoop_un(ALGraph oldgraph) {
	int visit[MAXVEX];
	int i;
	ALGraph graph;
	if (oldgraph.kind == DG || oldgraph.kind == DN)return ERROR;
	if (CopyGraph(&graph, oldgraph) == ERROR)return ERROR;	//邻接表中不能直接修改内容，会影响原图
	for (i = 0; i < graph.vexnum; i++)visit[i] = false;				//故复制了一个
	for (i = 0; i < graph.vexnum; i++) {
		if (visit[i] == false) {
			if (hasLoop_un_sub(&graph, i, visit) == ERROR) {
				DestroyGraph(&graph);
				return true;
			}
		}
	}
	DestroyGraph(&graph);
	return false;
}
Status hasLoop(ALGraph graph) {
	int toposequ[MAXVEX];
	if (graph.kind == DG || graph.kind == DN)
		return TopologicalSort(graph, toposequ) == ERROR ? true : false;
	else
		return hasLoop_un(graph);
}
Status TopologicalSort(ALGraph graph, int toposequ[]) {
	int inarc[MAXVEX];
	int i;
	int vertex;
	int index;
	int count;
	if (graph.kind == UDG || graph.kind == UDN)return ERROR;
	for (i = 0; i < graph.vexnum; i++)inarc[i] = 0;
	for (i = 0; i < graph.vexnum; i++) {
		for (vertex = FirstAdjVex(graph, graph.vertices[i].vexno); vertex >= 0; vertex = NextAdjVex(graph, graph.vertices[i].vexno, vertex)) {
			if ((index = LocateVex(graph, vertex)) == ERROR)return ERROR;
			inarc[index]++;
		}
	}
	count = 0;
	while (count < graph.vexnum) {
		for (i = 0; i < graph.vexnum; i++) {
			if (inarc[i] == 0) {
				toposequ[count] = graph.vertices[i].vexno;
				inarc[i] = -1;
				count++;
				for (vertex = FirstAdjVex(graph, graph.vertices[i].vexno); vertex >= 0; vertex = NextAdjVex(graph, graph.vertices[i].vexno, vertex)) {
					if ((index = LocateVex(graph, vertex)) == ERROR)return ERROR;
					inarc[index]--;
				}
				break;
			}
		}
		if (count < graph.vexnum && i == graph.vexnum)return ERROR;
	}
	for (i = 0; i < graph.vexnum; i++)printf("%3d", toposequ[i]);
	return OK;
}
Status TopologicalOrder(ALGraph graph, int toposequ[], int etv[]) {
	int count;
	int stack[MAXVEX];
	int top;
	int top_toposequ;
	int inarc[MAXVEX];
	int i, j, topvex;
	if (graph.vexnum == 0 || toposequ == NULL || etv == NULL)return ERROR;	//判断参数合法性
	if (graph.kind == UDG || graph.kind == UDN)return ERROR;		//只有有向的才能进行拓扑排序
	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;				//初始化入度数组
		etv[i] = 0;				//和顶点最早开始时间
	}
	for (i = 0; i < graph.vexnum; i++) {
		for (j = FirstAdjVex(graph, graph.vertices[i].vexno); j >= 0; j = NextAdjVex(graph, graph.vertices[i].vexno, j)) {
			if ((topvex = LocateVex(graph, j)) == ERROR)return ERROR;
			inarc[topvex]++;	//统计各顶点入度
		}
	}
	top = -1;
	for (i = 0; i < graph.vexnum; i++) {
		if (inarc[i] == 0) {
			top++;
			stack[top] = i;		//将入度为0的顶点下标入栈，注意是下标入栈
		}
	}
	top_toposequ = -1;
	count = 0;
	while (top != -1) {
		topvex = stack[top];
		top--;
		top_toposequ++;
		toposequ[top_toposequ] = topvex;	//将顶点下标存进拓扑序列中
		count++;
		for (i = FirstAdjVex(graph, graph.vertices[topvex].vexno); i >= 0; i = NextAdjVex(graph, graph.vertices[topvex].vexno, i)) {
			if ((j = LocateVex(graph, i)) == ERROR)return ERROR;
			inarc[j]--;
			if (inarc[j] == 0) {
				top++;
				stack[top] = j;
			}
			if (etv[j] < etv[topvex] + Distance(graph, graph.vertices[topvex].vexno, i))
				etv[j] = etv[topvex] + Distance(graph, graph.vertices[topvex].vexno, i);
		}
	}
	if (count < graph.vexnum)return ERROR;	//存在回路
	else return OK;
}
Status CriticalPath(ALGraph graph) {
	int etv[MAXVEX];
	int ltv[MAXVEX];
	int toposequ[MAXVEX];
	int ete, lte;
	int i, j, topvex;
	int top;
	if (TopologicalOrder(graph, toposequ, etv) == ERROR)return ERROR;
	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)ltv[i] = etv[top];
	while (top != -1) {
		topvex = toposequ[top];
		top--;
		for (i = FirstAdjVex(graph, graph.vertices[topvex].vexno); i >= 0; i = NextAdjVex(graph, graph.vertices[topvex].vexno, i)) {
			if ((j = LocateVex(graph, i)) == ERROR)return ERROR;
			if (ltv[topvex] > ltv[j] - Distance(graph, graph.vertices[topvex].vexno, i))
				ltv[topvex] = ltv[j] - Distance(graph, graph.vertices[topvex].vexno, i);
		}
	}
	for (i = 0; i < graph.vexnum; i++) {
		for (j = FirstAdjVex(graph, graph.vertices[i].vexno); j >= 0; j = NextAdjVex(graph, graph.vertices[i].vexno, j)) {
			if ((topvex = LocateVex(graph, j)) == ERROR)return ERROR;
			ete = etv[i];
			lte = ltv[topvex] - Distance(graph, graph.vertices[i].vexno, j);
			if (ete == lte) {
				printf("<%d,%d>  ", graph.vertices[i].vexno, j);
			}
		}
	}
	printf("\n");
	return OK;
}

int main() {
	ALGraph graph;
	int i, j;
	ArcNode *temp;
	if (CreateGraph(&graph) == ERROR)printf("error!\n");
	/*for (i = 0; i < graph.vexnum; i++) {
		printf("%-5d", graph.vertices[i].vexno);
		for (temp = graph.vertices[i].firstarc; temp; temp = temp->nextarc) {
			printf("adjvex=%d  weight=%d     ", temp->adjvex, temp->weight);
		}
		printf("\n");
	}
	if (CriticalPath(graph) == ERROR)return ERROR;*/
	return 0;
}
