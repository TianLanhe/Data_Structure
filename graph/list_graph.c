#include <stdio.h>
#include <stdlib.h>
#include "list_graph.h"

Status sub_CreateGraph(ALGraph *graph, GraphKind kind) {
	int vexnum;
	int i;
	int start, end;
	int weight;
	Status status;

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
		for (i = 0; i < graph->vexnum; i++) {
			graph->vertices[i].vexno = i;
			graph->vertices[i].firstarc = NULL;
		}
	}
	else if (vexnum > -1) {
		int count;
		count = 0;
		while (count < graph->vexnum) {
			if (vexnum <= -1) {
				printf("请输入大于-1的整数！\n");
				fflush(stdin);
			}
			else {
				graph->vertices[count].vexno = vexnum;
				graph->vertices[count].firstarc = NULL;
				count++;
			}
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

	graph->arcnum = 0;
	kind == DG || kind == UDG ?
		printf("请输入边的始点和终点，输入-1结束:\n")
		: printf("请输入边的始点、终点和边的权，输入-1结束:\n");
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

		if (LocateVex(*graph, start) == -1) {
			printf("不存在编号为 %d 的顶点，请重新输入！\n", start);
			continue;
		}

		if (LocateVex(*graph, end) == -1) {
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

		if ((status = InsertArc(graph, start, end, weight)) != OK)return status;
	}
	return OK;
}

Status CreateGraph(ALGraph *graph) {
	int kind = -1;
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

int LocateVex(ALGraph graph, int vexnum) {
	int i;
	for (i = 0; i < graph.vexnum; i++)
		if (graph.vertices[i].vexno == vexnum)
			return i;
	return -1;
}

Status DestroyGraph(ALGraph *graph) {
	int i;
	ArcNode *temp, *arcnode;

	if (!graph || (graph->vexnum == 0 && graph->arcnum == 0))
		return ERROR;
	
	for (i = 0; i < graph->vexnum; i++) {				//释放边表
		arcnode = graph->vertices[i].firstarc;
		while (arcnode) {
			temp = arcnode;
			arcnode = arcnode->nextarc;
			free(temp);
		}
		graph->vertices[i].firstarc = NULL;
		graph->vertices[i].vexno = -1;
	}

	graph->vexnum = 0;
	graph->arcnum = 0;
	graph->kind = 0;
	return OK;
}

int FirstAdjVex(ALGraph graph, int index) {
	ArcNode *firnode;

	if (index < 0 || index >= graph.vexnum)
		return -1;

	firnode = graph.vertices[index].firstarc;
	return firnode == NULL ? -1 : firnode->adjvex;
}

int NextAdjVex(ALGraph graph, int v, int w) {
	ArcNode *nextnode;
	if (v < 0 || v >= graph.vexnum)
		return -1;
	if (w < 0 || w >= graph.vexnum)
		return -1;

	for (nextnode = graph.vertices[v].firstarc; nextnode && nextnode->adjvex != w; nextnode = nextnode->nextarc);
	if (nextnode == NULL)
		return -1;
	return nextnode->nextarc == NULL ? -1 : nextnode->nextarc->adjvex;
}

int Distance(ALGraph graph, int index1, int index2) {
	ArcNode *node;
	if (index1 < 0 || index1 >= graph.vexnum)
		return MAXINT;
	if (index2 < 0 || index2 >= graph.vexnum)
		return MAXINT;

	for (node = graph.vertices[index1].firstarc; node; node = node->nextarc)
		if (node->adjvex == index2)
			return node->weight;

	return MAXINT;
}

Status InsertVex(ALGraph *graph, int v) {
	if (!graph || graph->vexnum == 0)
		return ERROR;
	if (graph->vexnum >= MAXVEX)
		return ERROR;
	if (v < 0 || LocateVex(*graph, v) != -1)
		return ERROR;

	graph->vertices[graph->vexnum].firstarc = NULL;
	graph->vertices[graph->vexnum].vexno = v;
	++graph->vexnum;
	return OK;
}

Status DeleteVex(ALGraph *graph, int v) {
	int index;
	ArcNode *node, *temp;
	int i;

	if (!graph || graph->vexnum <= 0)
		return ERROR;
	if ((index = LocateVex(*graph, v)) == -1)
		return ERROR;

	for (i = 0; i < graph->vexnum; i++) {		//先删除其他顶点到v的边
		if (DeleteArc(graph, graph->vertices[i].vexno, v) == ERROR)return ERROR;
	}

	node = graph->vertices[index].firstarc;		//再删除v到其他顶点的边
	while (node) {								//如果是无向图，第一步已经将v到其他顶点的边删除了
		temp = node;
		node = node->nextarc;
		free(temp);
		--graph->arcnum;						//注意这里要手动减少边数
	}

	for (i = index; i < graph->vexnum - 1; ++i) {//将数组中顶点v的下标index以下的顶点往上移一行
		graph->vertices[i].vexno = graph->vertices[i + 1].vexno;
		graph->vertices[i].firstarc = graph->vertices[i + 1].firstarc;
	}

	--graph->vexnum;
	for (i = 0; i < graph->vexnum; ++i)			//移动数组顶点位置后，所有边的临界顶点均失效，要重新设置
		for (node = graph->vertices[i].firstarc; node; node = node->nextarc)
			if (node->adjvex > index)
				--node->adjvex;

	return OK;
}

Status InsertArc(ALGraph *graph, int v, int w, int adj) {
	int idx_start, idx_end;
	int weight;
	ArcNode *temp, *arcnode;
	if (!graph || graph->vexnum == 0)
		return ERROR;
	if (v == w)						//不能增加到自身的边
		return ERROR;
	if ((idx_start = LocateVex(*graph, v)) == -1)
		return ERROR;
	if ((idx_end = LocateVex(*graph, w)) == -1)
		return ERROR;
	if ((graph->kind == DN || graph->kind == UDN) && adj <= 0)	//如果是网，则对权值有要求，图则不需要这个参数
		return ERROR;
	//已存在边
	for (temp = graph->vertices[idx_start].firstarc; temp; temp = temp->nextarc)
		if (temp->adjvex == idx_end)
			return ERROR;

	if (graph->kind == DG || graph->kind == UDG)	//若是图，权为1
		weight = 1;									//若是网，权为adj
	else
		weight = adj;

	arcnode = (ArcNode*)malloc(sizeof(ArcNode));
	if (!arcnode)
		return OVERFLOW;

	arcnode->weight = weight;
	arcnode->adjvex = idx_end;		//采用头插法，插入的位置是链表首部，成为v的第一条邻边，而不是最后一条
	arcnode->nextarc = graph->vertices[idx_start].firstarc;
	graph->vertices[idx_start].firstarc = arcnode;

	if (graph->kind == UDG || graph->kind == UDN) {
		arcnode = (ArcNode*)malloc(sizeof(ArcNode));
		if (!arcnode)
			return OVERFLOW;

		arcnode->weight = weight;
		arcnode->adjvex = idx_start;
		arcnode->nextarc = graph->vertices[idx_end].firstarc;
		graph->vertices[idx_end].firstarc = arcnode;
	}

	++graph->arcnum;
	return OK;
}

Status DeleteArc(ALGraph *graph, int v, int w) {
	int index, index2;
	ArcNode *node, *pre;
	int flag;

	if (!graph || graph->vexnum == 0)
		return ERROR;
	if (v == w)
		return OK;
	if ((index = LocateVex(*graph, v)) == -1)
		return ERROR;
	if ((index2 = LocateVex(*graph, w)) == -1)
		return ERROR;

	node = graph->vertices[index].firstarc;
	pre = graph->vertices[index].firstarc;
	flag = false;
	while (node) {
		if (node->adjvex == index2) {
			if (node == graph->vertices[index].firstarc)
				graph->vertices[index].firstarc = node->nextarc;
			else
				pre->nextarc = node->nextarc;
			free(node);
			--graph->arcnum;
			flag = true;
			break;
		}
		else {
			pre = node;
			node = node->nextarc;
		}
	}

	if (flag && (graph->kind == UDG || graph->kind == UDN)) {
		node = graph->vertices[index2].firstarc;
		pre = graph->vertices[index2].firstarc;
		while (node) {
			if (node->adjvex == index) {
				if (node == graph->vertices[index2].firstarc)
					graph->vertices[index2].firstarc = node->nextarc;
				else
					pre->nextarc = node->nextarc;
				free(node);
				break;
			}
			else {
				pre = node;
				node = node->nextarc;
			}
		}
	}
	return OK;
}

Status DFSTraverse(ALGraph *graph, Status(*traverse)(VNode)) {
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

Status DFSTraverse_sub(ALGraph *graph, int idx_start, Status(*traverse)(VNode), int *visit) {
	int idx_nextvex;
	if (traverse(graph->vertices[idx_start]) == ERROR)return ERROR;
	visit[idx_start] = true;
	for (idx_nextvex = FirstAdjVex(*graph, idx_start); idx_nextvex >= 0; idx_nextvex = NextAdjVex(*graph, idx_start, idx_nextvex)) {
		if (!visit[idx_nextvex])
			if (DFSTraverse_sub(graph, idx_nextvex, traverse, visit) == ERROR)
				return ERROR;
	}
	return OK;
}

Status BFSTraverse(ALGraph *graph, Status(*traverse)(VNode)) {
	int queue[MAXVEX];
	int top, buttom;
	int visit[MAXVEX];
	int index;
	int i;
	int idx_nextvex;

	if (!graph || graph->vexnum == 0)
		return ERROR;

	for (i = 0; i < graph->vexnum; i++)
		visit[i] = false;
	top = buttom = 0;				//初始化队列，队首等于队尾表示队列为空

	for (i = 0; i < graph->vexnum; ++i) {
		if (!visit[i]) {
			visit[i] = true;
			queue[buttom++] = i;
			while (top != buttom) {
				index = queue[top++];
				if (traverse(graph->vertices[index]) == ERROR)return ERROR;
				for (idx_nextvex = FirstAdjVex(*graph, index); idx_nextvex >= 0; idx_nextvex = NextAdjVex(*graph, index, idx_nextvex)) {
					if (!visit[idx_nextvex]) {
						visit[idx_nextvex] = true;
						queue[buttom++] = idx_nextvex;
					}
				}
			}
		}
	}
	return OK;
}

Status Print(VNode vnode) {
	printf("%2d", vnode.vexno);
	return OK;
}
