#include "matrix_graph.h"
#include <stdio.h>

Status sub_CreateGraph(MGraph *graph, GraphKind kind) {
	int vexnum, arcnum;
	int i, j;
	int start, end;
	int idx_start, idx_end;
	int weight;

	if (!graph)
		return ERROR;

	graph->kind = kind;

	vexnum = 0;
	printf("请输入顶点数:");
	scanf("%d", &vexnum);
	if (vexnum > MAXVEX || vexnum < 1) {
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum = vexnum;

	vexnum = -2;
	printf("请依次输入顶点的编号(按默认编号输入-1):");
	scanf("%d", &vexnum);
	if (vexnum == -1) {
		for (i = 0; i < graph->vexnum; i++)
			graph->vexs[i] = i;
	}
	else if (vexnum > -1) {
		int count;
		count = 0;
		while (count < graph->vexnum) {
			if (vexnum <= -1) {
				printf("请输入大于-1的整数！\n");
				fflush(stdin);
			}
			else
				graph->vexs[count++] = vexnum;
			if (count < graph->vexnum) {
				vexnum = -2;
				scanf("%d", &vexnum);
			}
		}
	}
	else {
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}

	vexnum = graph->vexnum;
	for (i = 0; i < vexnum; i++)
		for (j = 0; j < vexnum; j++)
			graph->arcs[i][j] = MAXINT;

	kind == DG || kind == UDG ?
		printf("请输入边的始点和终点，输入-1结束:\n")
		: printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum = 0;
	while (1) {
		start = end = -2;
		scanf("%d", &start);
		if (start == -1)
			break;

		scanf("%d", &end);
		if (start < 0 || end < 0) {
			printf("边不合法！请重新输入！\n");
			continue;
		}
		if (start == end) {
			printf("不允许出现环！请重新输入！\n");
			continue;
		}

		idx_start = LocateVex(*graph, start);
		if (idx_start == -1) {
			printf("不存在编号为 %d 的顶点，请重新输入！\n", start);
			continue;
		}

		idx_end = LocateVex(*graph, end);
		if (idx_end == -1) {
			printf("不存在编号为 %d 的顶点，请重新输入！\n", end);
			continue;
		}

		if (kind == DN || kind == UDN) {
			weight = -1;
			scanf("%d", &weight);
			if (weight <= 0) {
				printf("边权不合法！请重新输入！\n");
				continue;
			}
		}
		else {
			weight = 1;
		}

		++arcnum;
		graph->arcs[idx_start][idx_end] = weight;
		if (kind == UDN || kind == UDG)
			graph->arcs[idx_end][idx_start] = weight;
	}
	graph->arcnum = arcnum;
	return OK;
}

Status CreateGraph(MGraph *graph) {
	int kind = -1;
	if (!graph)
		return ERROR;

	printf("1.有向图\n2.有向网\n3.无向图\n4.无向网\n");
	printf("请输入图的类型：");
	scanf("%d", &kind);
	if (kind >= 1 && kind <= 4) {
		return sub_CreateGraph(graph, (GraphKind)kind);
	}
	else {
		printf("请输入正确的图类型编号！\n");
		return ERROR;
	}
}

int LocateVex(MGraph graph, int vexnum) {
	int i;
	for (i = 0; i < graph.vexnum; ++i)
		if (graph.vexs[i] == vexnum)
			return i;
	return -1;
}

Status DestroyGraph(MGraph *graph) {
	int i, j;
	if (!graph)
		return ERROR;
	graph->arcnum = 0;
	graph->vexnum = 0;
	for (i = 0; i < MAXVEX; i++)
		for (j = 0; j < MAXVEX; j++)
			graph->arcs[i][j] = 0;
	graph->kind = 0;
	return OK;
}

int FirstAdjVex(MGraph graph, int v) {
	int w;
	if (v < 0 || v >= graph.vexnum)
		return -1;
	for (w = 0; w < graph.vexnum; w++)
		if (graph.arcs[v][w] != MAXINT)
			return w;
	return -1;
}

int NextAdjVex(MGraph graph, int v, int w) {
	int nexvex;
	if (v < 0 || v >= graph.vexnum)return -1;
	if (w < 0 || w >= graph.vexnum)return -1;
	for (nexvex = w + 1; nexvex < graph.vexnum; nexvex++)
		if (graph.arcs[v][nexvex] != MAXINT)
			return nexvex;
	return -1;
}

int Distance(MGraph graph, int index1, int index2) {
	if (index1 < 0 || index1 >= graph.vexnum)
		return MAXINT;
	if (index2 < 0 || index2 >= graph.vexnum)
		return MAXINT;
	
	return graph.arcs[index1][index2];
}

Status InsertVex(MGraph *graph, int vexnum) {
	int i;
	if (!graph)
		return ERROR;
	if (graph->vexnum == 0 || graph->vexnum == MAXVEX)
		return ERROR;
	if (vexnum < 0 || LocateVex(*graph, vexnum) != -1)	//存在编号为vexnum的顶点
		return ERROR;

	graph->vexs[graph->vexnum] = vexnum;
	++graph->vexnum;
	for (i = 0; i < graph->vexnum; ++i) {
		graph->arcs[graph->vexnum - 1][i] = MAXINT;
		graph->arcs[i][graph->vexnum - 1] = MAXINT;
	}

	return OK;
}

Status DeleteVex(MGraph *graph, int vexnum) {
	int i, j;
	int index;
	if (!graph || graph->vexnum == 0)
		return ERROR;
	if ((index = LocateVex(*graph, vexnum)) == -1)	//不存在编号为vexnum的顶点
		return ERROR;

	for (i = 0; i < graph->vexnum; i++)
		if (graph->arcs[index][i] != MAXINT)
			--graph->arcnum;					//减去以vexnum为尾的弧

	if (graph->kind == DG || graph->kind == DN) {	//若graph是有向图
		for (i = 0; i < graph->vexnum; i++)			//还需要减去以vexnum为头的弧
			if (graph->arcs[i][index] != MAXINT)
				--graph->arcnum;
	}

	for (i = index; i < graph->vexnum - 1; i++)	//将vexnum以下的行向上移动一行
		for (j = 0; j < graph->vexnum; j++)
			graph->arcs[i][j] = graph->arcs[i + 1][j];


	for (i = 0; i < graph->vexnum - 1; i++)		//将vexnum以右的列向左移动一列
		for (j = index; j < graph->vexnum - 1; j++)
			graph->arcs[i][j] = graph->arcs[i][j + 1];

	for (i = index; i < graph->vexnum - 1; ++i)	//将顶点数组往前移动一个
		graph->vexs[i] = graph->vexs[i + 1];

	--graph->vexnum;
	return OK;
}

Status InsertArc(MGraph *graph, int v, int w, int adj) {
	int idx_start, idx_end;
	int weight;
	if (!graph || graph->vexnum == 0)
		return ERROR;
	if (v == w)							//不能增加到自身的边
		return ERROR;
	if ((idx_start = LocateVex(*graph, v)) == -1)
		return ERROR;
	if ((idx_end = LocateVex(*graph, w)) == -1)
		return ERROR;
	if ((graph->kind == DN || graph->kind == UDN) && adj <= 0)	//如果是网，则对权值有要求，图则不需要这个参数
		return ERROR;
	if (graph->arcs[idx_start][idx_end] != MAXINT)	//已存在边
		return ERROR;

	if (graph->kind == DG || graph->kind == UDG)	//若是图，权为1
		weight = 1;									//若是网，权为adj
	else
		weight = adj;

	graph->arcs[v][w] = weight;
	if (graph->kind == UDG || graph->kind == UDN)	//若是无向的，还要添加对称边
		graph->arcs[w][v] = weight;

	++graph->arcnum;
	return OK;
}

Status DeleteArc(MGraph *graph, int v, int w) {
	int idx_start, idx_end;

	if (!graph || graph->vexnum == 0)
		return ERROR;
	if ((idx_start = LocateVex(*graph, v)) == -1)
		return ERROR;
	if ((idx_end = LocateVex(*graph, w)) == -1)
		return ERROR;

	if (graph->arcs[idx_start][idx_end] != MAXINT) {
		--graph->arcnum;
		graph->arcs[idx_start][idx_end] = MAXINT;
		if (graph->kind == UDG || graph->kind == UDN)	//若是无向的，还要删除对称边
			graph->arcs[idx_end][idx_start] = MAXINT;
	}
	return OK;
}

Status DFSTraverse(MGraph *graph, Status(*traverse)(VertexType)) {
	int visit[MAXVEX];
	int i;
	if (!graph || graph->vexnum == 0)
		return ERROR;

	for (i = 0; i < graph->vexnum; i++)
		visit[i] = false;

	for (i = 0; i < graph->vexnum; ++i)
		if (!visit[i])
			if (DFSTraverse_sub(graph, i, traverse, visit) == ERROR)return ERROR;
	return OK;
}

Status DFSTraverse_sub(MGraph *graph, int idx_start, Status(*traverse)(VertexType), int *visit) {
	int idx_nextvex;
	if (traverse(graph->vexs[idx_start]) == ERROR)return ERROR;
	visit[idx_start] = true;
	for (idx_nextvex = FirstAdjVex(*graph, idx_start); idx_nextvex >= 0; idx_nextvex = NextAdjVex(*graph, idx_start, idx_nextvex)) {
		if (!visit[idx_nextvex])
			if (DFSTraverse_sub(graph, idx_nextvex, traverse, visit) == ERROR)
				return ERROR;
	}
	return OK;
}

Status BFSTraverse(MGraph *graph, Status(*traverse)(VertexType)) {
	int queue[MAXVEX];			//借助辅助队列queue和访问标志数组visit
	int top, buttom;			//top表示队列队首，buttom表示队列队尾
	int vertex;
	int nextvex;
	int visit[MAXVEX];
	int i;
	if (!graph || graph->vexnum == 0)return ERROR;

	for (i = 0; i < graph->vexnum; i++)
		visit[i] = false;
	top = buttom = 0;			//初始化队列，队首等于队尾表示队列为空

	for (i = 0; i < graph->vexnum; ++i) {
		if (!visit[i]) {
			queue[buttom++] = i;	//模拟入队列，将顶点序号入队列，然后队尾向后一个
			visit[i] = true;
			while (top != buttom) {
				vertex = queue[top];
				top++;			//模拟出队列，将顶点序号从队列中弹出，并使队首向后一个
				if (traverse(graph->vexs[vertex]) == ERROR)return ERROR;	//访问顶点
				for (nextvex = FirstAdjVex(*graph, vertex); nextvex >= 0; nextvex = NextAdjVex(*graph, vertex, nextvex)) {
					if (!visit[nextvex]) {
						visit[nextvex] = true;
						queue[buttom++] = nextvex;
					}
				}
			}
		}
	}
	return OK;
}

Status Print(VertexType i) {
	printf("%2d", i);
	return OK;
}
