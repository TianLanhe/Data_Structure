Status FloShortPath(ALGraph graph,int path[MAXVEX][MAXVEX][MAXVEX+2],int dist[MAXVEX][MAXVEX]){
	int i,j,k;
	if(path == NULL || dist == NULL)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++){
			dist[i][j]=Distance(graph,graph.vertices[i].vexno,graph.vertices[j].vexno);
			path[i][j][0]=0;
			path[i][j][1]=MAXINT;
			if(dist[i][j] != MAXINT){
				path[i][j][0]+=2;
				path[i][j][1]=graph.vertices[i].vexno;
				path[i][j][2]=graph.vertices[j].vexno;
			}
		}
		path[i][i][0]++;
		path[i][i][1]=graph.vertices[i].vexno;
		dist[i][i]=0;
	}
	for(i=0;i<graph.vexnum;i++){
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
Status DijShortPath(ALGraph graph,int v,int path[][MAXVEX+2],int *dist){
	int index;
	int index2;
	int i,j,k;
	int mindist;
	int distance;
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	if(graph.vexnum == 0)return ERROR;
	if(path == NULL  || dist == NULL)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		dist[i]=Distance(graph,v,graph.vertices[i].vexno);
		path[i][0]=0;
		path[i][1]=MAXINT;
		if(dist[i] != MAXINT){
			path[i][0]++;
			path[i][1]=v;
		}
	}
	path[index][0]=1;						//path的存储结构为path[0]=length表示点的个数
	path[index][1]=v;						//接下来length个元素为顶点，第length+1个元素
	path[index][2]=0;						//暂存距离dist，数组dist用-1表示已并入S中，搜索结束后再赋值给dist
	dist[index]=-1;								//-1表示该点已并入S中
	for(i=1;i<graph.vexnum;i++){
		mindist=MAXINT;
		for(j=0;j<graph.vexnum;j++){
			if(dist[j] != -1 && dist[j] < mindist){
				mindist=dist[j];
				index2=j;
			}
		}
		if(mindist != MAXINT){
			path[index2][0]++;
			path[index2][path[index2][0]]=graph.vertices[index2].vexno;
			path[index2][path[index2][0]+1]=dist[index2];
			for(j=0;j<graph.vexnum;j++){
				if(dist[j] != -1 && (distance=Distance(graph,graph.vertices[index2].vexno,graph.vertices[j].vexno)) != MAXINT){
					if(dist[index2]+distance < dist[j]){
						dist[j]=dist[index2]+distance;
						for(k=0;k<path[index2][0]+1;k++){
							path[j][k]=path[index2][k];
						}
					}
				}
			}
			dist[index2]=-1;
		}else break;
	}
	for(i=0;i<graph.vexnum;i++){
		dist[i]=path[i][path[i][0]+1];
	}
	return OK;
}
Status hasLoop_un_sub(ALGraph *graph,int start,int visit[]){
	int nextvex;
	int index;
	if(visit[start] == true)return ERROR;
	visit[start]=true;
	while((nextvex=FirstAdjVex(*graph,graph->vertices[start].vexno)) >= 0){
		if(DeleteArc(graph,graph->vertices[start].vexno,nextvex) == ERROR)return ERROR;
		if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
		if(hasLoop_un_sub(graph,index,visit) == ERROR)return ERROR;
	}
	return OK;
}
Status CopyGraph(ALGraph *graph,ALGraph oldgraph){
	int i;
	int nextvex;
	ArcNode *node;
	if(graph == NULL || oldgraph.vexnum == 0)return ERROR;
	graph->vexnum=oldgraph.vexnum;
	graph->arcnum=oldgraph.arcnum;
	graph->kind=oldgraph.kind;
	for(i=0;i<oldgraph.vexnum;i++){
		graph->vertices[i].vexno=oldgraph.vertices[i].vexno;
		graph->vertices[i].firstarc=NULL;
	}
	for(i=0;i<oldgraph.vexnum;i++){
		for(node=oldgraph.vertices[i].firstarc;node;node=node->nextarc){
			if(InsertArc(graph,graph->vertices[i].vexno,node->adjvex,node->weight) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status hasLoop_un(ALGraph oldgraph){
	int visit[MAXVEX];
	int i;
	ALGraph graph;
	if(oldgraph.kind == DG || oldgraph.kind == DN)return ERROR;
	if(CopyGraph(&graph,oldgraph) == ERROR)return ERROR;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			if(hasLoop_un_sub(&graph,i,visit) == ERROR){
				DestroyGraph(&graph);
				return true;
			}
		}
	}
	DestroyGraph(&graph);
	return false;
}
Status hasLoop(ALGraph graph){
	int toposequ[MAXVEX];
	if(graph.kind == DG || graph.kind == DN)
		return TopologicalSort(graph,toposequ)==ERROR?true:false;
	else
		return hasLoop_un(graph);
}
Status TopologicalSort(ALGraph graph,int toposequ[]){
	int inarc[MAXVEX];
	int i;
	int vertex;
	int index;
	int count;
	if(graph.kind == UDG || graph.kind == UDN)return ERROR;
	for(i=0;i<graph.vexnum;i++)inarc[i]=0;
	for(i=0;i<graph.vexnum;i++){
		for(vertex=FirstAdjVex(graph,graph.vertices[i].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[i].vexno,vertex)){
			if((index=VexNo(graph,vertex)) == ERROR)return ERROR;
			inarc[index]++;
		}
	}
	count=0;
	while(count < graph.vexnum){
		for(i=0;i<graph.vexnum;i++){
			if(inarc[i] == 0){
				toposequ[count]=graph.vertices[i].vexno;
				inarc[i]=-1;
				count++;
				for(vertex=FirstAdjVex(graph,graph.vertices[i].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[i].vexno,vertex)){
					if((index=VexNo(graph,vertex)) == ERROR)return ERROR;
					inarc[index]--;
				}
				break;
			}
		}
		if(count < graph.vexnum && i == graph.vexnum)return ERROR;
	}
	for(i=0;i<graph.vexnum;i++)printf("%3d",toposequ[i]);
	return OK;
}
Status MiniSpanTree_PRIM(ALGraph graph,int v){
	int i,j;
	int index;
	int distance;
	struct {
		int vexno;
		int lowcost;
	}closedge[MAXVEX];
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	for(i=0;i<graph.vexnum;i++){
		closedge[i].vexno=v;
		if(i != index){
			closedge[i].lowcost=Distance(graph,v,graph.vertices[i].vexno);
			if(closedge[i].lowcost == ERROR)return ERROR;
		}else{
			closedge[i].lowcost=-1;
		}
	}
	for(i=1;i<graph.vexnum;i++){
		for(j=0;j<graph.vexnum;j++)
			if(closedge[j].lowcost != -1)
				break;
		index=j;
		for(j=j+1;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && closedge[j].lowcost < closedge[index].lowcost)
				index=j;
		}
		printf("<%d,%d>  ",closedge[index].vexno,graph.vertices[index].vexno);
		closedge[index].lowcost=-1;
		for(j=0;j<graph.vexnum;j++){
			if(closedge[j].lowcost != -1 && (distance=Distance(graph,graph.vertices[index].vexno,graph.vertices[j].vexno)) < closedge[j].lowcost){
				closedge[j].vexno=graph.vertices[index].vexno;
				if(closedge[j].vexno == ERROR)return ERROR;
				closedge[j].lowcost=distance;
			}
		}
	}
	printf("\n");
	return OK;
}
int Distance(ALGraph graph,int v,int w){
	int index;
	int index2;
	ArcNode *node;
	if((index=VexNo(graph,v)) == ERROR)return ERROR;
	if((index2=VexNo(graph,w)) == ERROR)return ERROR;
	for(node=graph.vertices[index].firstarc;node;node=node->nextarc){
		if(node->adjvex == w)
			return node->weight;
	}
	return MAXINT;
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
	for(tress=root;tress;tress=tress->nextsibling){
		if(PreOrderTraverseCSTress(tress,visit) == ERROR)return ERROR;
		printf("\n");
	}
	return OK;
}
Status PrintCSTree(CSTNode *node){
	printf("%3d",node->data);
	return OK;
}
Status DFSForest(ALGraph graph,CSTNode **root){
	int visit[MAXVEX];
	int i;
	CSTNode *pre,*node;
	*root=NULL;
	for(i=0;i<graph.vexnum;i++)visit[i]=false;
	for(i=0;i<graph.vexnum;i++){
		if(visit[i] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			node->data=graph.vertices[i].vexno;
			if(*root == NULL)*root=node;
			else pre->nextsibling=node;
			pre=node;
			if(DFSTree(graph,i,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTree(ALGraph graph,int start,CSTNode *root,int *visit){
	int vertex;
	int first;
	int index;
	CSTNode *node,*pre;
	if(start < 0)return ERROR;
	if(root == NULL)return ERROR;
	if(visit == NULL)return ERROR;
	visit[start]=true;
	first=true;
	for(vertex=FirstAdjVex(graph,graph.vertices[start].vexno);vertex>=0;vertex=NextAdjVex(graph,graph.vertices[start].vexno,vertex)){
		if((index=VexNo(graph,vertex)) == -1)return ERROR;
		if(visit[index] == false){
			node=(CSTNode*)malloc(sizeof(CSTNode));
			if(!node)return ERROR;
			node->data=vertex;
			node->firstchild=NULL;
			node->nextsibling=NULL;
			if(first){
				root->firstchild=node;
				first=false;
			}else{
				pre->nextsibling=node;
			}
			pre=node;
			if(DFSTree(graph,index,node,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse_sub(ALGraph *graph,int start,Status (*traverse)(VNode),int *visit){
	int index;
	int nextvex;
	if((index=VexNo(*graph,start)) == ERROR)return ERROR;
	if(traverse(graph->vertices[index]) == ERROR)return ERROR;
	visit[index]=true;
	for(nextvex=FirstAdjVex(*graph,start);nextvex>=0;nextvex=NextAdjVex(*graph,start,nextvex)){
		if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
		if(visit[index] == false){
			if(DFSTraverse_sub(graph,nextvex,traverse,visit) == ERROR)return ERROR;
		}
	}
	return OK;
}
Status DFSTraverse(ALGraph *graph,Status (*traverse)(VNode)){
	int visit[MAXVEX];
	int i;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	return DFSTraverse_sub(graph,graph->vertices[0].vexno,traverse,visit);
}
Status BFSTraverse(ALGraph *graph,Status (*traverse)(VNode)){
	int queue[MAXVEX];
	int top,buttom;
	int visit[MAXVEX];
	int vertex;
	int index;
	int i;
	int nextvex;
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	for(i=0;i<graph->vexnum;i++)visit[i]=false;
	top=buttom=0;				//初始化队列，队首等于队尾表示队列为空
	if(traverse(graph->vertices[0]) == ERROR)return ERROR;	//访问顶点
	visit[0]=true;
	queue[buttom]=graph->vertices[0].vexno;	
	buttom++;					//这两句模拟入队列，将顶点序号入队列，然后队尾向后一个	
	while(top != buttom){		//当队列不空时
		vertex=queue[top];
		top++;					//这两句模拟出队列，将顶点序号从队列中弹出，并使队首向后一个
		for(nextvex=FirstAdjVex(*graph,vertex);nextvex>=0;nextvex=NextAdjVex(*graph,vertex,nextvex)){
			if((index=VexNo(*graph,nextvex)) == ERROR)return ERROR;
			if(visit[index] == false){		//如果顶点还未访问过
				if(traverse(graph->vertices[index]) == ERROR)return ERROR;
				visit[index]=true;
				queue[buttom]=nextvex;		//则访问并入队列
				buttom++;
			}
		}
	}
	return OK;
}
Status Print(VNode vnode){
	printf("%2d",vnode.vexno);
	return OK;
}
Status InsertVex(ALGraph *graph,int v){
	if(graph == NULL || graph->vexnum >= MAXVEX)return ERROR;
	if(VexNo(*graph,v) != -1)return ERROR;			//判断参数合法性
	graph->vertices[graph->vexnum].firstarc=NULL;
	graph->vertices[graph->vexnum].vexno=v;
	graph->vexnum++;
	return OK;
}
Status DeleteVex(ALGraph *graph,int v){
	int index;
	ArcNode *node,*temp;
	int i;
	if(graph == NULL || graph->vexnum <= 0)return ERROR;
	if((index=VexNo(*graph,v)) == -1)return ERROR;			//判断参数合法性
	for(i=0;i<graph->vexnum;i++){					//先删除其他顶点到v的边
		if(DeleteArc(graph,graph->vertices[i].vexno,v) == ERROR)return ERROR;
	}
	node=graph->vertices[index].firstarc;			//再删除v到其他顶点的边
	while(node){									//如果是无向图，第一步已经将v到其他顶点的边删除了
		temp=node;
		node=node->nextarc;
		free(temp);
	}
	for(;index<graph->vexnum-1;index++){			//将数组中顶点v的下标index以下的顶点晚上移一行
		graph->vertices[index].vexno=graph->vertices[index+1].vexno;
		graph->vertices[index].firstarc=graph->vertices[index+1].firstarc;
	}
	graph->vexnum--;
	return OK;
}
Status DeleteArc(ALGraph *graph,int v,int w){
	int index;
	int index2;												//三种返回类型
	ArcNode *node,*pre;										//0:成功,-1:失败,-2:可忽略
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	if((index=VexNo(*graph,v)) == -1)return ERROR;
	if((index2=VexNo(*graph,w)) == -1)return ERROR;			//判断参数合法性
	node=graph->vertices[index].firstarc;
	pre=graph->vertices[index].firstarc;					//与删除无虚头结点的链表操作相同
	while(node){
		if(node->adjvex == w){
			if(node == graph->vertices[index].firstarc){
				graph->vertices[index].firstarc=node->nextarc;
				free(node);
			}else{
				pre->nextarc=node->nextarc;
				free(node);
			}
			if(graph->kind == UDG || graph->kind == UDN){	//若是无向图(网)，还要删除对称边
				node=graph->vertices[index2].firstarc;
				pre=graph->vertices[index2].firstarc;
				while(node){
					if(node->adjvex == v){
						if(node == graph->vertices[index2].firstarc){
							graph->vertices[index2].firstarc=node->nextarc;
							free(node);
						}else{
							pre->nextarc=node->nextarc;
							free(node);
						}
						return OK;
					}else{
						pre=node;
						node=node->nextarc;
					}
				}
			}
			graph->arcnum--;
			return OK;
		}else{
			pre=node;
			node=node->nextarc;
		}
	}
	return -2;
}
int FirstAdjVex(ALGraph graph,int v){
	int index;
	ArcNode *firnode;
	if(graph.vexnum == 0)return ERROR;
	index=VexNo(graph,v);
	if(index == -1)return ERROR;
	firnode=graph.vertices[index].firstarc;
	return firnode==NULL?ERROR:firnode->adjvex;
}
int NextAdjVex(ALGraph graph,int v,int w){
	int index;
	int index2;
	ArcNode *nextnode;
	if(graph.vexnum == 0)return ERROR;
	index=VexNo(graph,v);
	if(index == -1)return ERROR;
	index2=VexNo(graph,w);
	if(index2 == -1)return ERROR;
	for(nextnode=graph.vertices[index].firstarc;nextnode && nextnode->adjvex != w;nextnode=nextnode->nextarc);
	if(nextnode == NULL)return ERROR;
	else nextnode=nextnode->nextarc;
	return nextnode==NULL?ERROR:nextnode->adjvex;
}
Status DestroyGraph(ALGraph *graph){
	int i;
	ArcNode *temp,*arcnode;
	if(graph->vexnum == 0 && graph->arcnum == 0)return ERROR;
	graph->vexnum=0;
	graph->arcnum=0;
	graph->kind=0;
	for(i=0;i<graph->vexnum;i++){
		arcnode=graph->vertices[i].firstarc;
	    while(arcnode){
	    	temp=arcnode;
	    	arcnode=arcnode->nextarc;
	    	free(temp);
	    }
	    graph->vertices[i].firstarc=NULL;
	    graph->vertices[i].vexno=-1;
	}
	return OK;
}
Status CreateGraph(ALGraph *graph){
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
int VexNo(ALGraph graph,int vexnum){
	int i;
	for(i=0;i<graph.vexnum;i++)
		if(graph.vertices[i].vexno == vexnum)
			break;
	return i<graph.vexnum?i:-1;
}
Status InsertArc(ALGraph *graph,int v,int w,int adj){
	int start,end;
	ArcNode *arcnode,*temp;
	if(graph == NULL || graph->vexnum == 0)return ERROR;
	start=VexNo(*graph,v);
	end=VexNo(*graph,w);
	if(end == -1 || start == -1 || start == end)return ERROR;	//判断参数的合法性
	for(temp=graph->vertices[start].firstarc;temp;temp=temp->nextarc)	//如果已经有<v,w>弧了，不添加，返回-2
		if(temp->adjvex == w)return -2;							//三种返回类型
	arcnode=(ArcNode*)malloc(sizeof(ArcNode));					//0:成功,-1:失败,-2:可忽略
	if(!arcnode)return ERROR;
	arcnode->adjvex=w;
	if(graph->kind == DG || graph->kind == UDG)
		arcnode->weight=1;
	else arcnode->weight=adj;
	arcnode->nextarc=graph->vertices[start].firstarc;			//插入的位置是链表首部，即插入后成为v的第一条邻边，而不是最后一条
	graph->vertices[start].firstarc=arcnode;
	if(graph->kind == UDG || graph->kind == UDN){				//如果是无向图(网)，还要插入对称边
		temp=(ArcNode*)malloc(sizeof(ArcNode));
		if(!temp)return ERROR;
		temp->adjvex=v;
		temp->weight=arcnode->weight;
		temp->nextarc=graph->vertices[end].firstarc;
		graph->vertices[end].firstarc=temp;
	}
	return OK;
}
Status CreateDG(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
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
	printf("请依次输入顶点的编号(按默认编号输入-1)：");
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点和终点，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,1) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateDN(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	int adj;
	graph->kind=DN;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;
	printf("请依次输入顶点的编号(按默认编号输入-1)：");
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){
			printf("边权不合法！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,adj) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDG(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
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
	printf("请依次输入顶点的编号(按默认编号输入-1)：");
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点和终点，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,1) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
Status CreateUDN(ALGraph *graph){
	int vexnum;
	int arcnum;
	int i;
	int start;
	int end;
	int adj;
	graph->kind=UDN;
	printf("请输入顶点数：");
	scanf("%d",&vexnum);
	if(vexnum>MAXVEX || vexnum<1){				//判断顶点数是否合法
		printf("顶点数不合法！\n");
		return ERROR;
	}
	graph->vexnum=vexnum;							   //邻接矩阵中下标就是顶点的编号
	printf("请依次输入顶点的编号(按默认编号输入-1)：");//这里下标与编号分开，顶点编号可以任意，更加合理
	scanf("%d",&vexnum);
	if(vexnum == -1){
		for(i=0;i<graph->vexnum;i++){
			graph->vertices[i].vexno=i;
			graph->vertices[i].firstarc=NULL;
		}
	}else if(vexnum >-1){
		int count;
		count=0;
		while(count < graph->vexnum){
			if(vexnum <= -1){
				printf("请输入大于-1的整数！\n");
			}else{
				graph->vertices[count].vexno=vexnum;
				graph->vertices[count].firstarc=NULL;
				count++;
			}
			if(count < graph->vexnum)scanf("%d",&vexnum);
		}
	}else{
		printf("请输入大于等于-1的整数！\n");
		return ERROR;
	}
	printf("请输入边的始点、终点和边的权，输入-1结束:\n");
	arcnum=0;
	while(1){
		scanf("%d",&start);
		if(start == -1)break;
		else if(VexNo(*graph,start) == -1){
			printf("不存在编号为%d的顶点！\n",start);
			return ERROR;
		}
		scanf("%d",&end);
		if(VexNo(*graph,end) == -1){
			printf("不存在编号为%d的顶点！\n",end);
			return ERROR;
		}
		if(start == end){
			printf("不允许出现环！\n");
			return ERROR;
		}
		scanf("%d",&adj);
		if(adj<=0){
			printf("边权不合法！\n");
			return ERROR;
		}
		arcnum++;
		if(InsertArc(graph,start,end,adj) == ERROR)return ERROR;
	}
	graph->arcnum=arcnum;
	return OK;
}
