#include "matrix_graph.h"
#include "../tree/ChildBroLinkTree.h"
#include <stdlib.h>
#include <stdio.h>

Status TopologicalSort(MGraph oldgraph, int toposequ[]);
//若有向图(网)oldgraph中无回路，则将oldgraph的一个拓扑序列保存在toposequ中并返回OK。若oldgraph是无向图(网)或有环，返回ERROR
Status TopologicalOrder(MGraph graph, int toposequ[], int etv[]);
//求有向图(网)的拓扑序列和顶点最早开始时间，若图不是有向的，或者存在环，则返回ERROR
Status CriticalPath(MGraph graph);
//求图(网)的关键路径并输出，若图不是有向的，或者存在环则返回ERROR
Status CopyGraph(MGraph *newgraph, MGraph oldgraph);
//复制(克隆)oldgraph到newgraph中
Status hasLoop_un_sub(MGraph graph, int start, int visit[]);
//递归搜索无向图(网)graph,若图中存在回路，返回ERROR，否则返回OK
Status hasLoop_un(MGraph graph);
//若无向图(网)graph中无回路，则返回false，有回路返回true。若是有向图(网)，返回ERROR，
Status hasLoop(MGraph graph);
//判断图中是否存在，有返回true，否则返回false

Status TopologicalOrder(MGraph graph, int toposequ[], int etv[]) {
	int stack[MAXVEX];
	int top;
	int inarc[MAXVEX];
	int top_toposequ;
	int i, j;
	int topvex;
	int count;
	if (graph.kind == UDN || graph.kind == UDG)return ERROR;	//如果是无向图，无法拓扑排序
	if (toposequ == NULL || etv == NULL || graph.vexnum == 0)return ERROR;	//判断参数合法性
	top = -1;						//初始化栈底
	top_toposequ = -1;			//初始化栈底
	for (i = 0; i < graph.vexnum; i++) {
		inarc[i] = 0;
		etv[i] = 0;				//事件(顶点)最早发生时间
	}
	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] != MAXINT) {
				inarc[j]++;					//统计各个顶点的入度
			}
		}
	}
	for (i = 0; i < graph.vexnum; i++) {			//循环一遍，把入度为0的顶点入栈
		if (inarc[i] == 0) {
			top++;
			stack[top] = i;
		}
	}
	count = 0;								//统计顶点个数，如果最后拓扑序列中顶点个数少于
	while (top != -1) {						//图的顶点个数，则表示存在回路，应返回ERROR
		topvex = stack[top];
		count++;					//栈顶元素出栈并推入toposequ中，
		top--;
		top_toposequ++;
		toposequ[top_toposequ] = topvex;	//寻找以topvex为尾的边，然后删除终点的入度
		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			inarc[i]--;
			if (inarc[i] == 0) {
				top++;
				stack[top] = i;
			}
			if (etv[i] < etv[topvex] + graph.arcs[topvex][i])
				etv[i] = etv[topvex] + graph.arcs[topvex][i];
		}
	}
	if (count != graph.vexnum)return ERROR;	//存在回路
	else return OK;
}
Status CriticalPath(MGraph graph) {
	int etv[MAXVEX];			//顶点最早发生时间
	int ltv[MAXVEX];			//顶点最晚发生时间
	int ete, lte;				//边最早发生时间，边最晚发生时间
	int toposequ[MAXVEX];		//拓扑序列
	int top, topvex;
	int i, j;							//进行拓扑排序并计算顶点最早发生时间
	if (TopologicalOrder(graph, toposequ, etv) == ERROR)return ERROR;
	top = graph.vexnum - 1;
	for (i = 0; i < graph.vexnum; i++)ltv[i] = etv[top];
	while (top != -1) {			//对拓扑序列从尾开始倒序计算顶点最晚发生时间
		topvex = toposequ[top];
		top--;
		for (i = FirstAdjVex(graph, topvex); i >= 0; i = NextAdjVex(graph, topvex, i)) {
			if (ltv[topvex] > ltv[i] - graph.arcs[topvex][i])	//更新顶点最晚发生时间
				ltv[topvex] = ltv[i] - graph.arcs[topvex][i];
		}
	}
	for (i = 0; i < graph.vexnum; i++) {			//接下来根据顶点的时间计算每条边的最早发生时间与最晚发生时间
		for (j = FirstAdjVex(graph, i); j >= 0; j = NextAdjVex(graph, i, j)) {//若相等，则证明其是关键边
			ete = etv[i];
			lte = ltv[j] - graph.arcs[i][j];
			if (ete == lte) {
				printf("<%d,%d>  ", i, j);
			}
		}
	}
	printf("\n");
	return OK;
}
Status hasLoop_un(MGraph graph) {
	int visit[MAXVEX];
	int i;
	if (graph.kind == DG || graph.kind == DN)return ERROR;
	for (i = 0; i < graph.vexnum; i++)visit[i] = false;
	for (i = 0; i < graph.vexnum; i++)
		if (visit[i] == false)
			if (hasLoop_un_sub(graph, i, visit) == ERROR)
				return true;
	return false;
}
Status hasLoop_un_sub(MGraph graph, int start, int visit[]) {
	int nextvex;
	if (visit[start] == true)return ERROR;
	visit[start] = true;
	for (nextvex = FirstAdjVex(graph, start); nextvex >= 0; nextvex = NextAdjVex(graph, start, nextvex)) {
		if (DeleteArc(&graph, start, nextvex) == ERROR)return ERROR;	//这里矩阵是副本，删除边无需担心影响到实参
		if (hasLoop_un_sub(graph, nextvex, visit) == ERROR)return ERROR;
	}
	return OK;
}
Status hasLoop(MGraph graph) {
	int toposequ[MAXVEX];
	if (graph.kind == DG || graph.kind == DN)			//有向图(网)用拓扑排序判断是否有回路
		return TopologicalSort(graph, toposequ) == ERROR ? true : false;
	else												//无向图(网)借助深度遍历判断是否有回路
		return hasLoop_un(graph);
}
Status CopyGraph(MGraph *newgraph, MGraph oldgraph) {
	int i, j;
	if (newgraph == NULL)return ERROR;
	newgraph->kind = oldgraph.kind;
	newgraph->vexnum = oldgraph.vexnum;
	newgraph->arcnum = oldgraph.arcnum;
	for (i = 0; i < oldgraph.vexnum; i++) {
		for (j = 0; j < oldgraph.vexnum; j++) {
			newgraph->arcs[i][j] = oldgraph.arcs[i][j];
		}
	}
	return OK;
}
Status TopologicalSort(MGraph oldgraph, int toposequ[]) {
	int count;
	int column, row;
	int flag;
	int visit[MAXVEX];					//拓扑排序只针对有向图
	MGraph graph;						//如果是无向图，返回ERROR
	if (oldgraph.kind == UDG || oldgraph.kind == UDN)return ERROR;
	if (toposequ == NULL)return ERROR;
	CopyGraph(&graph, oldgraph);			//由于选出一个顶点后要删除这个顶点及其关联的边，因此是破坏性的
	count = 0;							//故copy了一个新的临时图来操作，可参考邻接表存储结构的图的另一个种更好的方法
	for (row = 0; row < graph.vexnum; row++)visit[row] = false;
	while (count < graph.vexnum) {
		for (column = 0; column < graph.vexnum; column++) {	//从头开始搜索，搜索第一个没访问过而且入度为0的顶点
			flag = true;
			for (row = 0; row < graph.vexnum; row++) {
				if (visit[column] == true || graph.arcs[row][column] != MAXINT)
					flag = false;
			}
			if (flag == true) {						//若找到了，则设置visit已访问，加入拓扑序列
				visit[column] = true;
				toposequ[count] = column;
				count++;
				for (row = 0; row < graph.vexnum; row++) {
					graph.arcs[column][row] = MAXINT;	//将与该顶点关联的边全部去掉
				}
				break;								//跳出循环重新开始从头搜索
			}
		}											//如果找了一圈都没有找到入度为0的顶点
		if (flag == false && count < graph.vexnum) {
			DestroyGraph(&graph);
			return ERROR;							//要么所有顶点都访问过了，要么无法找到拓扑序列
		}
	}
	DestroyGraph(&graph);							//记得使用完后销毁克隆的图，但其实并没有涉及到动态分配
	return OK;										//不会发生内存泄漏，销不销毁都无所谓啦
}

int main() {
	MGraph graph;
	int etv[MAXVEX];
	int toposequ[MAXVEX];
	int i, j;
	if (CreateGraph(&graph) == ERROR)return ERROR;
	for (i = 0; i < graph.vexnum; i++) {
		for (j = 0; j < graph.vexnum; j++) {
			if (graph.arcs[i][j] == MAXINT)printf("∞");
			else printf("%2d", graph.arcs[i][j]);
		}
		printf("\n");
	}
	int path[MAXVEX][MAXVEX + 1];
	int dist[MAXVEX];
	if (DijShortPath(graph, 1, path, dist) == ERROR)return 1;
	for (i = 0; i < graph.vexnum; ++i) {
		for (j = 1; j <= path[i][0]; ++j) {
			printf("%d ", path[i][j]);
		}
		printf("dist:%d\n", dist[i]);
	}
	// CriticalPath(graph);
	return 0;
}
