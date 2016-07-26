#include "graph_adjmat.h"
Status FloShortPath(MGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]){
	int i,j,k;
	if(path == NULL || dist == NULL)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	for(i=0;i<graph.vexnum;i++){		//以下是初始化部分
		for(j=0;j<graph.vexnum;j++){
			dist[i][j]=graph.arcs[i][j];
			path[i][j][0]=0;
			path[i][j][1]=MAXINT;
			if(dist[i][j] != MAXINT){
				path[i][j][0]+=2;
				path[i][j][1]=i;
				path[i][j][2]=j;
			}
		}
		path[i][i][0]++;
		path[i][i][1]=i;
		dist[i][i]=0;
	}
	for(i=0;i<graph.vexnum;i++){		//以下是处理部分
		for(j=0;j<graph.vexnum;j++){
			for(k=0;k<graph.vexnum;k++){
				if(dist[j][i]<MAXINT && dist[i][k]<MAXINT){
					if(dist[j][i]+dist[i][k] < dist[j][k]){
						int w,count;
						dist[j][k]=dist[j][i]+dist[i][k];
						count=0;
						for(w=0;w<path[j][i][0]+1;w++)
							path[j][k][count++]=path[j][i][w];
						for(w=2;w<path[i][k][0]+1;w++)
							path[j][k][count++]=path[i][k][w];
						path[j][k][0]+=path[i][k][0]-1;
					}
				}
			}
		}
	}
	return OK;
}
Status DijShortPath(MGraph graph,int v,int path[][MAXVEX+2],int *dist){
	int i,j,k;
	int mindist;
	int vexter;
	if(graph.vexnum == 0)return ERROR;
	if(path == NULL  || dist == NULL)return ERROR;
	if(v >= graph.vexnum)return ERROR;		//判断参数合法性
	for(i=0;i<graph.vexnum;i++){		//以下是初始化部分
		dist[i]=graph.arcs[v][i];		//dist[i]表示顶点v直接或经过中间节点间接到i的距离
		path[i][0]=0;
		path[i][1]=MAXINT;
		if(dist[i] != MAXINT){
			path[i][0]++;
			path[i][1]=v;
		}
	}
	path[v][0]=1;						//path的存储结构为path[0]=length表示点的个数
	path[v][1]=v;						//接下来length个元素为顶点，第length+1个元素
	path[v][2]=0;						//暂存距离dist，数组dist用-1表示已并入S中，搜索结束后再赋值给dist
	dist[v]=-1;								//-1表示该点已并入S中
	for(i=1;i<graph.vexnum;i++){		//以下是处理部分
		mindist=MAXINT;
		for(j=0;j<graph.vexnum;j++){	//选一个dist不为-1且最小的顶点
			if(dist[j] != -1 && dist[j] < mindist){
				mindist=dist[j];
				vexter=j;
			}
		}
		if(mindist != MAXINT){			//如果没选到，说明剩下的点要么都是-1要么都是MAXINT，后者无法到达，可以体检跳出
			path[vexter][0]++;
			path[vexter][path[vexter][0]]=vexter;
			path[vexter][path[vexter][0]+1]=dist[vexter];
			for(j=0;j<graph.vexnum;j++){
				if(dist[j] != -1 && graph.arcs[vexter][j] != MAXINT){
					if(dist[vexter]+graph.arcs[vexter][j] < dist[j]){
						dist[j]=dist[vexter]+graph.arcs[vexter][j];
						for(k=0;k<path[vexter][0]+1;k++){
							path[j][k]=path[vexter][k];
						}
					}
				}
			}
			dist[vexter]=-1;
		}else break;
	}
	for(i=0;i<graph.vexnum;i++){
		dist[i]=path[i][path[i][0]+1];
	}
	return OK;
}
Status hasLoop_un(MGraph graph){
	int visit[MAXVEX];
	int i;
	if(graph.kind == DG || graph.kind == DN)return ERROR;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++)
		if(visit[i] == false)
			if(hasLoop_un_sub(graph,i,visit) == ERROR)
				return true;
	return false;
}
Status hasLoop_un_sub(MGraph graph,int start,int visit[]){
	int nextvex;
	if(visit[start] == true)return ERROR;
	visit[start]=true;
	for(nextvex=FirstAdjVex(graph,start);nextvex>=0;nextvex=NextAdjVex(graph,start,nextvex)){
		if(DeleteArc(&graph,start,nextvex) == ERROR)return ERROR;
		if(hasLoop_un_sub(graph,nextvex,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status hasLoop(MGraph graph){
	int toposequ[MAXVEX];
	if(graph.kind == DG || graph.kind == DN)			//有向图(网)用拓扑排序判断是否有回路
		return TopologicalSort(graph,toposequ)==ERROR?true:false;
	else												//无向图(网)借助深度遍历判断是否有回路
		return hasLoop_un(graph);
}
Status CopyGraph(MGraph *newgraph,MGraph oldgraph){
	int i,j;
	if(newgraph == NULL)return ERROR;
	newgraph->kind=oldgraph.kind;
	newgraph->vexnum=oldgraph.vexnum;
	newgraph->arcnum=oldgraph.arcnum;
	for(i=0;i<oldgraph.vexnum;i++){
		for(j=0;j<oldgraph.vexnum;j++){
			newgraph->arcs[i][j]=oldgraph.arcs[i][j];
		}
	}
	return OK;
}
Status TopologicalSort(MGraph oldgraph,int toposequ[]){
	int count;
	int column,row;
	int flag;
	int visit[MAXVEX];					//拓扑排序只针对有向图
	MGraph graph;						//如果是无向图，返回ERROR
	if(oldgraph.kind == UDG || oldgraph.kind == UDN)return ERROR;
	if(toposequ == NULL)return ERROR;
	CopyGraph(&graph,oldgraph);			//由于选出一个顶点后要删除这个顶点及其关联的边，因此是破坏性的
	count=0;							//故copy了一个新的临时图来操作，可参考邻接表存储结构的图的另一个种更好的方法
	for(row=0;row<graph.vexnum;row++)visit[row]=false;
	while(count < graph.vexnum){
		for(column=0;column<graph.vexnum;column++){	//从头开始搜索，搜索第一个没访问过而且入度为0的顶点
			flag=true;
			for(row=0;row<graph.vexnum;row++){
				if(visit[column] == true || graph.arcs[row][column] != MAXINT)
					flag=false;
			}
			if(flag == true){						//若找到了，则设置visit已访问，加入拓扑序列
				visit[column]=true;
				toposequ[count]=column;
				count++;
				for(row=0;row<graph.vexnum;row++){
					graph.arcs[column][row]=MAXINT;	//将与该顶点关联的边全部去掉
				}
				break;								//跳出循环重新开始从头搜索
			}
		}											//如果找了一圈都没有找到入度为0的顶点
		if(flag == false && count<graph.vexnum){
			DestriyGraph(&graph);
			return ERROR;							//要么所有顶点都访问过了，要么无法找到拓扑序列
		}
	}
	DestriyGraph(&graph);							//记得使用完后销毁克隆的图，但其实并没有涉及到动态分配
	return OK;										//不会发生内存泄漏，销不销毁都无所谓啦
}
Status MiniSpanTree_PRIM(MGraph graph,int start){
	int i,j;
	int index;
	struct {
		int vexno;
		int lowcost;
	}closedge[MAXVEX];
	if(start >= graph.vexnum)return ERROR;		//判断参数合法性
	for(i=0;i<graph.vexnum;i++){
		closedge[i].vexno=start;
		if(i != start){
			closedge[i].lowcost=graph.arcs[start][i];
		}else{
			closedge[i].lowcost=-1;
		}
	}											//初始化closedge数组，lowcost=-1表示并入已选集合中
	for(i=1;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++)
			if(closedge[j].lowcost != -1)
				break;						//不直接用index=0的原因是有可能closedge[0].lowcost为-1
		index=j;
		for(j=j+1;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && closedge[j].lowcost < closedge[index].lowcost)
				index=j;
		}												//以上两个for选出closedge数组里第一个lowcost不为-1的最小的下标
		printf("<%d,%d>  ",closedge[index].vexno,index);
		closedge[index].lowcost=-1;
		for(j=0;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && graph.arcs[index][j] < closedge[j].lowcost){
				closedge[j].vexno=index;
				closedge[j].lowcost=graph.arcs[index][j];
			}
		}
	}
	printf("\n");
	return OK;
}
Status DFSForest(MGraph graph,CSTNode **root){
	int i;
	int visit[MAXVEX];
	CSTNode *node,*pre;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	*root=NULL;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=i;
			if(*root == NULL)*root=node;
			else pre->nextsibling=node;
			pre=node;
			if(DFSTree(graph,i,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTree(MGraph graph,int index,CSTNode *root,int visit[]){
	CSTNode *node,*pre;
	int nextvex;
	int first;
	visit[index]=true;
	first=true;										//深度优先遍历root的每一个邻接顶点，构造生成树
	for(nextvex=FirstAdjVex(graph,index);nextvex>=0;nextvex=NextAdjVex(graph,index,nextvex)){
		if(visit[nextvex] == false){				//如果没访问过，则将此顶点连接到root上并递归构建子树
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=nextvex;						//以上5行初始化一个树节点
			if(first){
				root->firstchild=node;
				first=false;						//孩子兄弟链表，第一个孩子连着父亲，第二个孩子连着第一个孩子
			}else{
				pre->nextsibling=node;
			}
			pre=node;
			if(DFSTree(graph,nextvex,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DestroyCSTree(CSTNode **root){
	CSTNode *node;
	CSTNode *temp;
	node=(*root)->firstchild;
	free(*root);
	*root=NULL;
	while(node){
		temp=node->nextsibling;
		if(DestroyCSTree(&node) == ERROR)return ERROR;
		node=temp;
	}
	return OK;
}
Status DestroyCSForest(CSTNode **root){
	CSTNode *tree,*temp;
	tree=*root;
	while(tree){
		temp=tree->nextsibling;
		if(DestroyCSTree(&tree) == ERROR)return ERROR;
		tree=temp;
	}
	(*root)=NULL;
	return OK;
}
Status PreOrderTraverseCSTress(CSTNode *root,Status (*visit)(CSTNode *)){
	CSTNode *node;
	if(visit(root) == ERROR)return ERROR;
	for(node=root->firstchild;node;node=node->nextsibling){
		if(PreOrderTraverseCSTress(node,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status PreOrderTraverseCSForest(CSTNode *root,Status (*visit)(CSTNode *)){
	CSTNode *tress;
	for(tress=root;tress;tress=tress->nextsibling){		//对森林root的每棵树都调用一次前序遍历
		if(PreOrderTraverseCSTress(tress,visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}
Status PrintCSTree(CSTNode *node){
	printf("%3d",node->data);
	return OK;
}
Status DFSTraverse_sub(MGraph *graph,int start,Status (*traverse)(int),int *visit){
	int nextvex;
	if(traverse(start) == ERROR)return ERROR;
	visit[start]=true;
	for(nextvex=FirstAdjVex(*graph,start);nextvex>=0;nextvex=NextAdjVex(*graph,start,nextvex)){
		if(visit[nextvex] == false){
			if(DFSTraverse_sub(graph,nextvex,traverse,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse(MGraph *graph,Status (*traverse)(int)){
	int visit[MAXVEX];
	int i;
	if(graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	if(DFSTraverse_sub(graph,0,traverse,visit) == ERROR)return ERROR;
	return OK;
}
Status Print(int i){
	printf("%2d",i);
	return OK;
}
Status BFSTraverse(MGraph *graph,Status (*traverse)(int)){
	int queue[MAXVEX];			//借助辅助队列queue和访问标志数组visit
	int top,buttom;				//top表示队列队首，buttom表示队列队尾
	int vexter;
	int nextvex;
	int visit[MAXVEX];
	int i;
	if(graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	top=buttom=0;				//初始化队列，队首等于队尾表示队列为空
	queue[buttom]=0;
	buttom++;					//这两句模拟入队列，将顶点序号入队列，然后队尾向后一个	
	visit[0]=true;
	while(top != buttom){		//当队列不空时
		vexter=queue[top];
		top++;					//这两句模拟出队列，将顶点序号从队列中弹出，并使队首向后一个
		if(traverse(vexter) == ERROR)return ERROR;	//访问顶点
		for(nextvex=FirstAdjVex(*graph,vexter);nextvex>=0;nextvex=NextAdjVex(*graph,vexter,nextvex)){
			if(visit[nextvex] == false){	//如果顶点还未访问过
				visit[nextvex]=true;
				queue[buttom]=nextvex;		//则入队列
				buttom++;
			}
		}
	}
	return OK;
}
Status DeleteArc(MGraph *graph,int v,int w){
	if(graph->vexnum == 0)return ERROR;
	if(v<0 || v>=graph->vexnum)return ERROR;
	if(w<0 || w>=graph->vexnum)return ERROR;
	if(graph->arcs[v][w] != MAXINT){
		graph->arcnum--;
		graph->arcs[v][w]=MAXINT;
		if(graph->kind == UDG || graph->kind == UDN)
			graph->arcs[w][v]=MAXINT;
	}
	return OK;
}
Status InsertArc(MGraph *graph,int v,int w,int adj){
	if(graph->vexnum == 0)return ERROR;
	if(v<0 || v>=graph->vexnum)return ERROR;
	if(w<0 || w>=graph->vexnum)return ERROR;
	if(adj <= 0)return ERROR;						//判断参数的合法性
	if(graph->arcs[v][w] != MAXINT)return ERROR;	//若已有边，返回error
	if(graph->kind == DG || graph->kind == UDG){	//添加边，若是无向图(网)，还有添加对称边
		graph->arcs[v][w]=1;
		if(graph->kind == UDG)graph->arcs[w][v]=1;
	}else{
		graph->arcs[v][w]=adj;
		if(graph->kind == UDN)graph->arcs[w][v]=adj;
	}												
	graph->arcnum++;
	return OK;
}
Status InsertVex(MGraph *graph,int v){
	int i,j;
	if(graph->vexnum == 0 || graph->vexnum == MAXVEX)return ERROR;
	if(v < 0 || v > graph->vexnum)return ERROR;			//判断图和顶点的合法性
	for(i=graph->vexnum-1;i>=v;i--){
		for(j=0;j<graph->vexnum;j++){				//将该行以后的顶点均往后移一行
			graph->arcs[i+1][j]=graph->arcs[i][j];
		}
	}
	for(j=0;j<graph->vexnum;j++)graph->arcs[v][j]=MAXINT;	//该行所有边置零
	for(i=0;i<graph->vexnum+1;i++){					//将该列以后的顶点均往后移一行
		for(j=graph->vexnum-1;j>=v;j--){
			graph->arcs[i][j+1]=graph->arcs[i][j];
		}
	}
	for(i=0;i<graph->vexnum+1;i++)graph->arcs[i][v]=MAXINT;	//该列所有边置零
	graph->vexnum++;
	return OK;
}
Status DeleteVex(MGraph *graph,int v){
	int i,j;
	if(graph->vexnum == 0)return ERROR;
	if(v < 0 || v >= graph->vexnum)return ERROR;	//判断图和顶点的合法性
	for(i=0;i<graph->vexnum;i++)
		if(graph->arcs[v][i] != MAXINT)
			graph->arcnum--;						//减去以v为尾的弧
	if(graph->kind == DG || graph->kind == DN){		//若graph是有向图
		for(i=0;i<graph->vexnum;i++)				//还需要减去以v为头的弧
			if(graph->arcs[i][v] != MAXINT)
				graph->arcnum--;
	}
	for(i=v;i<graph->vexnum;i++){					//将v以下的行向上移动一行
		for(j=0;j<graph->vexnum;j++){
			graph->arcs[i][j]=graph->arcs[i+1][j];
		}
	}
	for(i=0;i<graph->vexnum-1;i++){					//将v以右的列向左移动一列
		for(j=v;j<graph->vexnum;j++){
			graph->arcs[i][j]=graph->arcs[i][j+1];
		}
	}
	graph->vexnum--;
	return OK;
}
int FirstAdjVex(MGraph graph,int v){
	int w;
	if(v<0 || v>=graph.vexnum || graph.vexnum==0)return -1;
	for(w=0;w<graph.vexnum;w++)
		if(graph.arcs[v][w] != MAXINT)return w;
	return -1;
}
int NextAdjVex(MGraph graph,int v,int w){
	int nexvex;
	if(graph.vexnum == 0)return -1;
	if(v<0 || v>=graph.vexnum)return -1;
	if(w<0 || w>=graph.vexnum)return -1;
	for(nexvex=w+1;nexvex<graph.vexnum;nexvex++)
		if(graph.arcs[v][nexvex] != MAXINT)return nexvex;
	return -1;
}
Status DestriyGraph(MGraph *graph){
	int i,j;
	if(graph == NULL)return ERROR;
	graph->arcnum=0;
	graph->vexnum=0;
	for(i=0;i<MAXVEX;i++)
		for(j=0;j<MAXVEX;j++)
			graph->arcs[i][j]=0;
	graph->kind=0;
	return OK;
}
Status CreateDG(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
	int start;
	int end;
	graph->kind=DG;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	for(i=0;i<vexnum;i++){
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("请输入边的始点和终点，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("边不合法！\n");
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=1;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDG(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
	int start;
	int end;
	graph->kind=UDG;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	for(i=0;i<vexnum;i++){				//初始化所有边为MAXINT
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("请输入边的始点和终点，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("边不合法！\n");
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=graph->arcs[end][start]=1;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateDN(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
	int start;
	int end;
	int adj;
	graph->kind=DN;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){			//判断顶点数量是否合法
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	for(i=0;i<vexnum;i++){					//初始化所有边为MAXINT
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);					//判断起点和终点的合法性
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("边不合法！\n");
			return ERROR;
		}
		if(start == end){					//规定所有图均不能存在环
			printf("不允许出现环！\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){							//判断权的合法性
			printf("边权不合法！\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=adj;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDN(MGraph *graph){
	int vexnum;
	int arcnum;
	int i,j;
	int start;
	int end;
	int adj;
	graph->kind=UDN;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){			//判断顶点的数目是否合法
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	for(i=0;i<vexnum;i++){					//初始化所有边为MAXINT
		for(j=0;j<vexnum;j++){
			graph->arcs[i][j]=MAXINT;
		}
	}
	printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		scanf("%d",&end);					//判断起点和终点的合法性
		if(start<0 || start>=vexnum || end<0 || end>=vexnum){
			printf("边不合法！\n");
			return ERROR;
		}
		if(start == end){					//规定所有图均不能存在环
			printf("不允许出现环！\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){							//判断权的合法性
			printf("边权不合法！\n");
			return ERROR;
		}
		arcnum++;
		graph->arcs[start][end]=graph->arcs[end][start]=adj;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateGraph(MGraph *graph){
	int kind;
	printf("1.有向图\n2.有向网\n3.无向图\n4.无向网\n");
	printf("请输入图的类型：");
	scanf("%d",&kind);
	switch(kind){
		case 1:if(CreateDG(graph) == ERROR)return ERROR;break;
		case 2:if(CreateDN(graph) == ERROR)return ERROR;break;
		case 3:if(CreateUDG(graph) == ERROR)return ERROR;break;
		case 4:if(CreateUDN(graph) == ERROR)return ERROR;break;
		default:printf("请输入正确的图类型编号！\n");
				return ERROR;
	}
	return OK;
}
