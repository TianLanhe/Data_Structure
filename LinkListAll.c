#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <math.h>
// #define ERROR 0
// #define OVERFLOW -2
// #define true 1
// #define false 0
// #define OK 1
// #define Status int
// #define FreeNode(p) _FreeNode(&(p))	//传入一级指针即可
// typedef struct {						//节点数据域类型
// 	double coef;				   	//系数
// 	int expn;						//指数
// }*ElemType, term;
// typedef struct LNode {				//节点类型
// 	ElemType data;
// 	struct LNode *next;
// }Link;
// typedef struct _linklist {			//链表类型
// 	Link *head;
// 	Link *tail;
// 	int len;
// }LinkList;
// typedef LinkList polynomail;		//重定义链表类型为多项式类型
// typedef LinkList SqStack;			//重定义链表类型为栈类型
// typedef Link SElemType;				//重定义节点类型为栈节点类型
// typedef ElemType SData;				//重定义节点数据域类型为栈节点的数据域类型
// typedef LinkList LinkQueue;			//重定义链表类型为队列类型
// typedef Link QNode;					//重定义链表节点类型为队列节点类型
// typedef ElemType QData;				//重定义节点数据域类型为队列节点的数据域类型





// //链表基本操作：
// void _FreeNode(Link **p);
// //释放p所指节点
// Status MakeNode(Link **p, ElemType data);
// //分配由p指向的值为e的结点，并返回OK；若分配失败，则返回ERROR
// Status InitList(LinkList *linklist);
// //构造一个空的线性链表linklist
// Status DestroyList(LinkList *linklist);
// //销毁线性链表linklist，linklist不再存在
// Status ClearList(LinkList *linklist);
// //将线性链表linklist重置为空表，并释放原链表的结点空间
// Status InsFirst(Link *head, Link *p);
// //已知head指向线性链表的头结点，将p所指的一个(串)结点插入在第一个结点之前
// Status DelFirst(Link *head, Link **p);
// //已知head指向线性链表的头结点，删除链表中的第一个结点并以q返回
// Status Append(LinkList *linklist, Link *p);
// //将指针p所指（彼此以指针相链）的一串结点链接在线性链表linklist的最后一个节点
// //之后，并改变链表linklist的尾指针指向新的尾结点
// Status Remove(LinkList *linklist, Link **p);
// //删除线性链表的尾结点并以p返回，改变链表linklist的尾指针指向新的尾结点
// Status InsBefore(LinkList *linklist, Link **p, Link *h);
// //已知p指向线性链表中的一个结点，将h所指结点插入在p所指结点之前，
// //并修改指针p指向新插入的节点
// Status InsAfter(LinkList *linklist, Link **p, Link *h);
// //已知p指向线性链表中的一个结点，将s所指结点插入在p所指结点之后，
// //并修改指针p指向新插入的节点
// Status LinkListInsert(LinkList *linklist, int position, ElemType e);
// //在带结点的线性链表linklist的第i个元素之前插入元素e
// Status SetCurElem(Link *p, ElemType e);
// //已知p指向线性链表中的一个结点，用e更新p所指结点中数据元素的值
// ElemType GetCurElem(Link *p);
// //已知p指向线性链表中的一个结点，返回p所指结点中数据元素的值
// Status ListEmpty(LinkList linklist);
// //若线性链表为空表，则返回TRUE，否则返回FALSE
// int ListLength(LinkList linklist);
// //返回线性链表linklist的元素个数
// Link *GetHead(LinkList linklist);
// //返回线性链表linklist头结点
// Link *GetLast(LinkList linklist);
// //返回线性链表linklist尾结点
// Link *PriorPos(LinkList linklist, Link *p);
// //已知p指向线性链表的一个结点，返回p所指结点的直接前驱的位置
// //若无前驱，则返回NULL
// Link *NextPos(LinkList linklist, Link *p);
// //已知p指向线性链表的一个结点，返回p所指结点的直接后继的位置
// //若无后继，则返回NULL
// Status LocatePos(LinkList linklist, int i, Link **p);
// //返回p指示线性链表linklist中第i个结点的位置并返回OK，i值不合法时返回ERROR
// Status inverse(Link *p);
// //遍历函数用的功能函数，其功能是将结点p中数据域元素的coef(系数)取反
// Status PrintLinkList(Link *p);
// //遍历函数用的功能函数，其功能是打印节点p中的数据域各项成员
// Status ListTraverse(LinkList linklist, Status(*visit)(Link*));
// //依次对linklist的每个元素调用visit()，一旦调用失败，则操作失败





// //链表应用——多项式基本操作：
// Status SetPolyn(ElemType *e, double coef, int expn);
// //分配由e指向的元素的数据值，并设置其coef和expn成员，并返回OK，若分配失败，则返回ERROR
// Status CreatPolyn(polynomail *p, int m);
// //输入m项的系数和指数，建立表示一元多项式的有序链表p
// Status DestroyPolyn(polynomail *p);
// //销毁一元多项式p
// void PrintPolyn(polynomail p);
// //打印输出一元多项式
// int PolynLength(polynomail p);
// //返回一元多项式p中的项数
// void SortPolyn(polynomail *p);
// //对一元多项式进行排序、合并和删除处理，将一元多项式化为指数从低到高的系数不为0的形式
// void AddPolyn(polynomail *pa, polynomail *pb);
// //完成一元多项式的相加运算，即：pa=pa+pb，并销毁一元多项式pb
// void SubtractPolyn(polynomail *pa, polynomail *pb);
// //完成一元多项式的相减运算，即：pa=pa-pb，并销毁一元多项式pb
// Link *sub_MultiplyPolyn(Link *p, polynomail *pb);
// //完成单项式的相加运算，即：pc=a*pb，是一元多项式相乘的基础
// Status MultiplyPolyn(polynomail *pa, polynomail *pb);
// //完成一元多项式的相乘运算，即：pa=pa*pb，并销毁一元多项式pb





// //链栈的基本操作：
// Status InitStack(SqStack *stack);
// //构造一个空栈stack
// Status DestroyStack(SqStack *stack);
// //销毁栈stack，栈stack不再存在
// Status ClearStack(SqStack *stack);
// //将栈stack置为空栈，并释放原链表的结点空间
// Status StackEmpty(SqStack stack);
// //若栈stack为空栈，则返回TRUE，否则返回FALSE
// int StackLength(SqStack stack);
// //返回栈stack的节点个数，即栈的长度
// Status GetTop(SqStack stack, SElemType **e);
// //用e返回栈Stack的栈顶节点
// Status Pop(SqStack *stack, SElemType **e);
// //删除栈stack的栈顶节点，并用e返回其值
// Status Push(SqStack *stack, SElemType *e);
// //插入节点为e为新的栈顶节点
Status SetData(SData *e, double dou, int num);
//分配由e指向的元素的数据值，并设置其coef和expn成员，并返回OK。若分配失败，则返回ERROR
// void PrintStr(SElemType e);
// //遍历函数用的功能函数，其功能是打印结点e中数据域元素的expn(字符)
// void PrintNum(SElemType e);
// //遍历函数用的功能函数，其功能是打印结点e中数据域元素的expn(整数)
// void PrintNode(SElemType e);
// //遍历函数用的功能函数，其功能是打印结点e中数据域元素的coef和expn
// Status StackTraverse(SqStack stack, void(*visit)(SElemType));
// //从栈低到栈顶依次对S的每个数据元素调用函数visit(),一旦visit()调用失败，则操作失败





// //链栈应用——数制转换、括号匹配、行编辑、表达式求值、8皇后问题
// void Conversion(int num, int base);
// //数制转换，将十进制数num转化为base进制的整数
// Status BracketMatch(char *str);
// //括号匹配，实现左右小括号与中括号的匹配。成功匹配返回OK，匹配失败返回ERROR
// void LineEdit(char back, char clear);
// //行编辑函数，设定back为退格符，clear为清除符，实现退格删除一个字符，清除删除一行字符
// int Precede(char ch1, char ch2);
// //比较两个运算符的优先级，若ch1的优先级小于ch2，返回值小于0，以此类推
// Status GetNum(char **str, double *dou);
// //将字符串的连续数字字符转化为浮点数
// SElemType *Operate(SElemType *num1, SElemType *operator,SElemType *num2);
// //进行两个数的运算
// SElemType *Calculator(char *str);
//表达式求值
// typedef struct {
// 	int x, y;					//稀疏矩阵非零元素的坐标
// 	int value;					//稀疏矩阵非零元素的值
// }Triple;
// typedef struct {
// 	Triple data[8];				//储存稀疏矩阵非零元素的信息
// 	int row, column, num;			//稀疏矩阵的行数列数和非零元素个数
// }TSMatrix;
// Status CreateSMatrix(TSMatrix *matrix, SqStack stack);
// //根据栈的内容创建相应的稀疏矩阵matrix，表示棋盘上皇后的位置
// void PrintSMatrix(TSMatrix matrix);
// //打印稀疏矩阵
// void SortMatrix(TSMatrix *matrix);
// //将系数矩阵的非零元素的坐标重新排列，使其坐标从小到大排列
// Status sub_isEquel(TSMatrix matrix1, TSMatrix matrix2);
// //判断两个矩阵表示的棋盘是否能通过旋转得到，若能即是同一个，返回TRUE，否则返回FALSE
// Status isEquel(TSMatrix *matrix1, TSMatrix matrix2, int length);
// //判断矩阵matrix2是否能通过之前任意一个矩阵旋转获得，若能返回TRUE，否则返回FALSE
// int CompareMatrix(TSMatrix matrix1, TSMatrix matrix2);
// //比较两个矩阵是否相等
// Status LRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2);
// //求稀疏矩阵matrix2逆时针旋转90度的矩阵matrix1
// Status RRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2);
// //求稀疏矩阵matrix2顺时针旋转90度的矩阵matrix1
// Status TurnMatrix(TSMatrix *matrix1, TSMatrix matrix2);
// //求稀疏矩阵matrix2旋转180度的矩阵matrix1
// Status isPeace(SqStack stack, SData data);
// //检查栈顶元素的坐标是否与其他元素处于同一行或者同一列或者同一斜线，是返回ERROR，否返回OK
// //由于数据类型限制，规定coef为行(double型)，expn为列(int型)
// void EightQueen();
// //求解八皇后问题，即在8*8的国际象棋棋盘上摆放八个皇后，使其不在同一行或者同一列或者同一斜线上的所有摆法





// //队列的基本操作：
// Status InitQueue(LinkQueue *Q);
// //构造一个空队列Q
// Status DestroyQueue(LinkQueue *Q);
// //销毁队列Q，Q不再存在
// Status ClearQueue(LinkQueue *Q);
// //将Q清为空队列
// Status QueueEmpty(LinkQueue Q);
// //若队列Q为空队列，则返回TRUE，否则返回FALSE
// int QueueLength(LinkQueue Q);
// //返回Q的元素个数，即队列的长度
// Status GetQHead(LinkQueue Q, QData *e);
// //若队列不空，则用e返回Q的队头元素，并返回OK，否则返回ERROR
// Status EnQueue(LinkQueue *Q, QData e);
// //插入元素e为Q的队尾元素
// Status DeQueue(LinkQueue *Q, QData *e);
// //若队列不空，则删除Q的队头元素，用e返回其值，并返回OK，否则返回FALSE
// void PrintQueue(QData data);
// //队列遍历函数的功能函数，其功能是打印队列元素的数据值
// Status QueueTraverse(LinkQueue Q, void(*visit)(QData));
// //从队头到队尾依次对队列Q中每个元素调用函数visit(),一旦visit调用失败，则操作失败





//队列的终极应用：银行业务模拟
//功能：模拟银行一天中客户在银行逗留的平均时间（计算方法：平均逗留时间=总逗留时间/总人数）
//数据类型：链表与（链）队列
//分析：采用事件驱动模拟，用一张链表作为事件表记录客户的事件类型(到达还是离开)和到达时间。
//      用四个队列分别代表四个窗口，链表数据元素的内容包括用户到达的时间和事件类型，
//		队列的数据元素内容包括客户到达的时间和客户办理业务所需时间。
//过程：首先检查事件表第一个结点(需初始化第一个到达的客户为第一个结点)，生成一个
//		随机数为下一个客户到达的间隔时间，计算下一个客户到达的时间并生成一个结点(事件)
//		按时间先后顺序插入到线性表中，再生成一个随机数表示客户办理业务所需时间，
//		将客户安排到人数(元素)最少的窗口(队列)中，如果该客户是该窗口第一个(唯一的)客户，
//		则要在此时生成离开事件加入时间表(若队列还有其他客户，则新加入的客户离开时间取决于前面的人的办理时间与离开时间，故此时不能立即生成离开事件)
//		若是第一个客户，则并根据顾客到达时间与等候时间计算离开时间，与事件类型一起，
//		生成客户离开事件按时间顺序插入到事件表中。此事件处理完毕，从事件表中删除该事件。
//		接着检查事件的下一个结点，若还有事件，则判断事件类型，若是到达事件，则进行到达时间的处理：
//		生成间隔时间，计算下一个客户到达时间生成到达节点插入事件表中(注意到达时间需早于结束营业时间)
//		再生成业务办理时间安排到队列中，判断是否是第一个客户，若是，则生成离开事件加入事件表
//		若不是，则不生成离开事件加入事件表中。此事件处理完毕，从时间表删除该时间，接着处理下一事件
//		若还有事件，判断事件类型，若是离开时间，则进行离开事件的处理：计算逗留时间，
//		增加总人数和总逗留时间，为下一客户生成离开事件插入时间表中，删除队头元素，此事件处理完毕，
//		从时间表中删除该事件。
//说明：由于数据类型限制，规定事件表中coef为事件发生时间(double型)，expn为事件类型(int型)
//					      窗口(队列)中coef为客户到达时间(double型)，expn为业务处理时间(int型)
typedef struct _bankinformation {
	LinkQueue *eventlist;					//事件表
	LinkQueue *service[4];					//四个队列作为窗口
	int total_time;							//总等候时间
	int total_num;							//总人数
	int opentime;							//营业时间(分钟)
	int closetime;			  				//结束时间(分钟)
	int intertime_arr;						//到达最大间隔时间
	int intertime_work;						//业务等待最长时间
}BankInfor;
//将银行的所有信息封装在一个结构体中
int Minimum(BankInfor *infor);
//找出四个队列中元素(人数)最少的队列的下标
Status EventInsert(BankInfor *infor, int evtype, int arrivetime);
//将事件类型和事件发生时间封装成结构体加入事件表中
Status OpenForDay(BankInfor *infor, int opentime, int closetime, int intertime_arr, int intertime_work);
//初始化信息结构体里的事件表，队列和四个时间，并将第一个到达的人添加到事件表中
double CloseForDay(BankInfor *infor);
//销毁信息结构体里的各种结构体，计算并返回平均等候时间
void CustomerArrived(BankInfor *infor);
//处理到达事件，将客户添加到人数最少的队列中，从事件表中删除该时间
void CustomerDeparture(BankInfor *infor);
//处理离开时间，将客户等候时间加入总时间，将客户从队列中删除，将该事件从事件表中删除
void BankSimulation(int opentime, int closetime, int intertime_arr, int intertime_work, int isPrint);
//模拟银行业务，计算每天人均等候时间





Status EventInsert(BankInfor *infor, int evtype, int arrivetime) {
	QData data;
	QNode *node;
	QNode *p;
	if (!SetData(&data, arrivetime, evtype))return ERROR;
	if (!MakeNode(&node, data))return ERROR;
	p = infor->eventlist->head->next;
	for (; p != NULL&&p->data->coef < arrivetime; p = p->next);
	if (!p)Append(infor->eventlist, node);
	else InsBefore(infor->eventlist, &p, node);
	return OK;
}
Status OpenForDay(BankInfor *infor, int opentime, int closetime, int intertime_arr, int intertime_work) {
	int i;
	int arrtime;
	time_t t;
	time(&t);
	srand(t);
	infor->eventlist = (LinkQueue *)malloc(sizeof(LinkQueue));
	if (!infor->eventlist)return ERROR;
	if (!InitQueue(infor->eventlist))return ERROR;
	for (i = 0; i < 4; i++) {
		infor->service[i] = (LinkQueue *)malloc(sizeof(LinkQueue));
		if (!infor->service[i])return ERROR;
		if (!InitQueue(infor->service[i]))return ERROR;
	}
	infor->total_num = infor->total_time = 0;
	infor->opentime = opentime;
	infor->closetime = closetime;
	infor->intertime_work = intertime_work;
	infor->intertime_arr = intertime_arr;
	arrtime = rand() % infor->intertime_arr + infor->opentime;
	if (!EventInsert(infor, 0, arrtime))return ERROR;
	return OK;
}
double CloseForDay(BankInfor *infor) {
	double aver_time;
	int i;
	DestroyQueue(infor->eventlist);
	free(infor->eventlist);
	infor->eventlist = NULL;
	for (i = 0; i < 4; i++) {
		DestroyQueue(infor->service[i]);
		free(infor->service[i]);
		infor->service[i] = NULL;
	}
	aver_time = infor->total_time*1.0 / infor->total_num;
	infor->total_num = infor->total_time = 0;
	infor->opentime = infor->closetime = 0;
	infor->intertime_arr = infor->intertime_work = 0;
	return aver_time;
}
int Minimum(BankInfor *infor) {
	int len[4];
	int i, min;
	for (i = 0, min = 0; i < 4; i++) {
		len[i] = QueueLength(*infor->service[i]);
		if (len[i] < len[min])min = i;
	}
	return min;
}
void CustomerArrived(BankInfor *infor) {
	int duringtime;
	int arrivetime;
	int min;
	QData data;
	QData t;
	QNode *node;
	time_t T;
	time(&T);
	srand(T);
	DeQueue(infor->eventlist, &data);
	infor->total_num++;
	duringtime = rand() % infor->intertime_work;
	arrivetime = rand() % infor->intertime_arr + (int)data->coef;
	min = Minimum(infor);
	SetData(&t, data->coef, duringtime);
	EnQueue(infor->service[min], t);
	if (arrivetime < infor->closetime)EventInsert(infor, 0, arrivetime);
	if (QueueLength(*infor->service[min]) == 1)EventInsert(infor, min + 1, duringtime + data->coef);
}
void CustomerDeparture(BankInfor *infor) {
	QData data;
	QData customer;
	int i;
	DeQueue(infor->eventlist, &data);
	i = data->expn - 1;
	DeQueue(infor->service[i], &customer);
	infor->total_time += data->coef - customer->coef;
	if (!QueueEmpty(*infor->service[i])) {
		GetQHead(*infor->service[i], &customer);
		EventInsert(infor, i + 1, data->coef + customer->expn);
	}
}
void BankSimulation(int opentime, int closetime, int intertime_arr, int intertime_work, int isPrint) {
	BankInfor infor;
	int i;
	int j;
	OpenForDay(&infor, opentime, closetime, intertime_arr, intertime_work);
	if (isPrint) {
		ListTraverse(*infor.eventlist, PrintLinkList);
		printf("\n");
	}
	while (!QueueEmpty(*infor.eventlist)) {
		i = (infor.eventlist)->head->next->data->expn;
		if (!i) {
			CustomerArrived(&infor);
			if (isPrint) {
				ListTraverse(*infor.eventlist, PrintLinkList);
				printf("%d %d %d %d\n", QueueLength(*infor.service[0]), QueueLength(*infor.service[1]), QueueLength(*infor.service[2]), QueueLength(*infor.service[3]));
				for (j = 0; j < 4; j++) {
					printf("Queue%d:", j);
					QueueTraverse(*infor.service[j], PrintQueue);
					printf("\n");
				}
				printf("\n");
			}
		}
		else {
			CustomerDeparture(&infor);
			if (isPrint) {
				ListTraverse(*infor.eventlist, PrintLinkList);
				printf("%d %d %d %d\n", QueueLength(*infor.service[0]), QueueLength(*infor.service[1]), QueueLength(*infor.service[2]), QueueLength(*infor.service[3]));
				for (j = 0; j < 4; j++) {
					printf("Queue%d:", j);
					QueueTraverse(*infor.service[j], PrintQueue);
					printf("\n");
				}
				printf("\n");
			}
		}
		if (isPrint)getch();
	}
	i = infor.total_num;
	j = infor.total_time;
	printf("总人数：%d(人)\n总时间：%d(分钟)\n平均时间：%.2f(分钟)\n", i, j, CloseForDay(&infor));
}





// Status InitQueue(LinkQueue *Q) {
// 	if (InitList(Q) == ERROR)return ERROR;
// 	else return OK;
// }
// Status DestroyQueue(LinkQueue *Q) {
// 	if (DestroyList(Q) == ERROR)return ERROR;
// 	else return OK;
// }
// Status ClearQueue(LinkQueue *Q) {
// 	if (ClearList(Q) == ERROR)return ERROR;
// 	else return OK;
// }
// Status QueueEmpty(LinkQueue Q) {
// 	return ListEmpty(Q);
// }
// int QueueLength(LinkQueue Q) {
// 	return ListLength(Q);
// }
// Status EnQueue(LinkQueue *Q, QData e) {
// 	QNode *t;
// 	if (MakeNode(&t, e) == ERROR)return ERROR;
// 	if (Append(Q, t) == ERROR)return ERROR;		//在链表尾插入节点模拟入队列
// 	else return OK;
// }
// Status GetQHead(LinkQueue Q, QData *e) {
// 	QNode *t;
// 	if ((t = GetHead(Q)) == NULL)return ERROR;		//若链表(队列)为空，则GetHead返回NULL
// 	else {
// 		*e = t->data;
// 		return OK;
// 	}
// }
// Status DeQueue(LinkQueue *Q, QData *e) {
// 	QNode *t;									//删除链表第一个结点，模拟出队列
// 	t = Q->head->next;
// 	if (!t)return ERROR;					//队列为空，无法出队列，返回ERROR
// 	if (!t->next)Q->tail = Q->head;
// 	Q->head->next = t->next;
// 	*e = t->data;
// 	free(t);
// 	Q->len--;
// 	return OK;
// }
// void PrintQueue(QData data) {
// 	printf("%d %d  ", (int)data->coef, data->expn);
// }
// Status QueueTraverse(LinkQueue Q, void(*visit)(QData)) {
// 	QNode *p;
// 	for (p = (Q.head)->next; p; p = p->next)visit(p->data);
// 	return OK;
// }






// Status StackTraverse(SqStack stack, void(*visit)(SElemType)) {
// 	if (stack.len <= 0)return ERROR;
// 	SElemType *e;							//这里用了void的，应该用Status比较好
// 	for (e = (stack.head)->next; e; e = e->next)visit(*e);
// 	printf("\n");
// 	return OK;
// }
Status SetData(SData *e, double dou, int num) {
	if (SetPolyn(e, dou, num) == ERROR)return ERROR;
	else return OK;
}
// Status InitStack(SqStack *stack) {
// 	if (InitList(stack) == ERROR)return ERROR;
// 	else return OK;
// }
// void PrintStr(SElemType e) {
// 	printf("%c", (e.data)->expn);
// }
// void PrintNum(SElemType e) {
// 	printf("%d ", (e.data)->expn);
// }
// void PrintNode(SElemType e) {
// 	printf("%d   %d\n", (int)(e.data)->coef, (e.data)->expn);
// }
// Status DestroyStack(SqStack *stack) {
// 	if (DestroyList(stack) == ERROR)return ERROR;
// 	else return OK;
// }
// Status ClearStack(SqStack *stack) {
// 	if (ClearList(stack) == ERROR)return ERROR;
// 	else return OK;
// }
// Status StackEmpty(SqStack stack) {
// 	return ListEmpty(stack);
// }
// Status GetTop(SqStack stack, SElemType **e) {
// 	if ((*e = GetLast(stack)) == NULL)return ERROR;	//若空栈，即空链表，
// 	return OK;										//则GetLast返回NULL
// }
// int StackLength(SqStack stack) {
// 	return ListLength(stack);
// }
// Status Push(SqStack *stack, SElemType *e) {
// 	if (Append(stack, e) == ERROR)return ERROR;		//在链表插入一个结点，模拟入栈
// 	else return OK;
// }
// Status Pop(SqStack *stack, SElemType **e) {
// 	if (Remove(stack, e) == ERROR)return ERROR;		//在链表删除一个结点，模拟出栈
// 	else return OK;
// }





// void _FreeNode(Link **p) {
// 	if (p&&*p) {
// 		if ((*p)->data)
// 			free((*p)->data);
// 		(*p)->data = NULL;
// 		free(*p);
// 		*p = NULL;
// 	}
// }
// Status MakeNode(Link **node, ElemType data) {
// 	if (!node)
// 		return ERROR;
// 	*node = (Link*)malloc(sizeof(Link));
// 	if (!*node)
// 		return OVERFLOW;
// 	(*node)->data = data;
// 	(*node)->next = NULL;
// 	return OK;
// }
// Status InitList(LinkList *linklist) {
// 	if (!linklist)
// 		return ERROR;
// 	linklist->tail = linklist->head = (Link *)malloc(sizeof(Link));	//分配虚头节点，链表头和尾均指向头结点表示空链表
// 	if (!linklist->head)
// 		return OVERFLOW;
// 	linklist->head->data = NULL;
// 	linklist->head->next = NULL;
// 	linklist->len = 0;
// 	return OK;
// }
// Status DestroyList(LinkList *linklist) {
// 	if (!linklist)
// 		return ERROR;
// 	if (ClearList(linklist) == ERROR)
// 		return ERROR;
// 	free(linklist->head);
// 	linklist->len = 0;
// 	linklist->tail = NULL;
// 	linklist->head = NULL;
// 	return OK;
// }
// Status ClearList(LinkList *linklist) {
// 	if (!linklist)
// 		return ERROR;
// 	Link *pf, *pb;
// 	pb = linklist->head->next;			//将结点都释放了
// 	while (pb) {
// 		pf = pb->next;
// 		FreeNode(pb);
// 		pb = pf;
// 	}
// 	linklist->len = 0;					//修改长度
// 	linklist->head->next = NULL;			//修改虚头结点
// 	linklist->tail = linklist->head;		//修改链尾指针
// 	return OK;
// }
// Status InsFirst(Link *head, Link *p) {
// 	Link *tail;
// 	if (!p || !head)
// 		return ERROR;
// 	for (tail = p; tail->next; tail = tail->next);	//找到p的尾巴
// 	tail->next = head->next;					//连接
// 	head->next = p;
// 	return OK;
// }
// Status DelFirst(Link *head, Link **p) {
// 	if (!head || !head->next)
// 		return ERROR;					//如果是空链表，无法删除，返回ERROR
// 	*p = head->next;						//取出第一个结点
// 	head->next = (*p)->next;				//修改指向第二个结点
// 	(*p)->next = NULL;
// 	return OK;
// }
// Status Append(LinkList *linklist, Link *p) {
// 	Link *t;
// 	int i;
// 	if (!p || !linklist)
// 		return ERROR;
// 	for (i = 1, t = p; t->next; t = t->next, ++i);	//找到p的尾巴，同时统计结点个数
// 	linklist->tail->next = p;				//连接
// 	linklist->tail = t;
// 	linklist->len += i;
// 	return OK;
// }
// Status Remove(LinkList *linklist, Link **p) {
// 	Link *t;
// 	if (!linklist || linklist->len == 0)
// 		return ERROR;
// 	*p = linklist->tail;
// 	--linklist->len;
// 	for (t = linklist->head; t->next != linklist->tail; t = t->next);
// 	t->next = NULL;
// 	linklist->tail = t;
// 	return OK;
// }
// Status InsBefore(LinkList *linklist, Link **p, Link *h) {
// 	Link *t;
// 	if (!linklist || linklist->len == 0 || !h)
// 		return ERROR;
// 	for (t = linklist->head; t->next&&t->next != *p; t = t->next);
// 	if (!t->next)			// p不是链表中的节点
// 		return ERROR;
// 	if (InsFirst(t, h) == ERROR)
// 		return ERROR;
// 	++linklist->len;
// 	*p = h;
// 	return OK;
// }
// Status InsAfter(LinkList *linklist, Link **p, Link *h) {
// 	Link *t;
// 	if (!linklist || linklist->len == 0 || !h)
// 		return ERROR;
// 	for (t = linklist->head; t&&t != *p; t = t->next);
// 	if (!t)						// p不是链表中的节点
// 		return ERROR;
// 	++linklist->len;			// 修改长度
// 	h->next = t->next;			// 修改指针指向
// 	t->next = h;
// 	if (t == linklist->tail)		// 如果p是尾节点，还需要修改linklist.tail
// 		linklist->tail = h;
// 	return OK;
// }
// Status LinkListInsert(LinkList *linklist, int position, ElemType e) {
// 	Link *t;									//只能插入到[0,len)之间的位置，不会改变尾结点
// 	Link *newnode;
// 	if (LocatePos(*linklist, position - 1, &t) == ERROR)return ERROR;
// 	if (MakeNode(&newnode, e) == ERROR)return ERROR;
// 	if (InsFirst(t, newnode) == ERROR)return ERROR;
// 	linklist->len++;
// 	return OK;
// }
// Status SetCurElem(Link *p, ElemType e) {
// 	if (p == NULL)
// 		return ERROR;
// 	p->data = e;
// 	return OK;
// }
// ElemType GetCurElem(Link *p) {
// 	return p ? p->data : NULL;
// }
// Status ListEmpty(LinkList linklist) {
// 	return linklist.len ? false : true;
// }
// int ListLength(LinkList linklist) {
// 	Link *t;							//不根据linklist.len直接获得
// 	int i;								//遍历链表并计算节点个数
// 	for (t = linklist.head, i = 0; t->next; t = t->next, i++);
// 	return i;
// }
// Link *GetHead(LinkList linklist) {
// 	return (linklist.head)->next;		//根据linklist.head直接返回第一个
// }
// Link *GetLast(LinkList linklist) {
// 	Link *t; 							//不根据linklist.tail直接获得，通过遍历链表得到最后一个
// 	if (ListEmpty(linklist) == true)
// 		return NULL;					//如果是空表，则没有最后一个，返回ERROR
// 	for (t = linklist.head; t->next; t = t->next); //一直走到头，返回该节点
// 	return t;
// }
// Link *PriorPos(LinkList linklist, Link *p) {
// 	Link *t;
// 	if (p == linklist.head || p == NULL)return NULL;		//该节点已是首节点，无上一个结点，返回NULL
// 	for (t = linklist.head; t->next&&t->next != p; t = t->next);	//一直走到p的上一个
// 	if (!t->next)
// 		return NULL;						//若没找到下一个是p，即p不是链表中的结点，返回ERROR
// 	else
// 		return t;
// }
// Link *NextPos(LinkList linklist, Link *p) {
// 	Link *t;
// 	if (p == NULL)
// 		return NULL;
// 	for (t = linklist.head; t&&t != p; t = t->next);	//找到结点p
// 	if (!t)
// 		return NULL;						//若没找到结点p返回ERROR
// 	else
// 		return t->next;					//否则返回p的下一个节点
// }
// Status LocatePos(LinkList linklist, int i, Link **p) {
// 	int count;
// 	Link *t;
// 	if (i < 0 || i >= linklist.len)
// 		return ERROR;		//位置非法返回ERROR
// 	for (count = 0, t = (linklist.head)->next; count < i&&t; t = t->next, count++);
// 	if (!t)
// 		return ERROR;
// 	*p = t;
// 	return OK;
// }
// Status inverse(Link *p) {
// 	if (!p)
// 		return ERROR;
// 	p->data->coef *= -1;
// 	return OK;
// }
// Status PrintLinkList(Link *p) {
// 	if (!p)
// 		return ERROR;
// 	printf("%d  %f\n", p->data->expn, p->data->coef);
// 	return OK;
// }
// Status ListTraverse(LinkList linklist, Status(*visit)(Link*)) {
// 	Link *p;
// 	for (p = (linklist.head)->next; p; p = p->next)
// 		if (visit(p) == ERROR)
// 			return ERROR;
// 	return OK;
// }




// void Conversion(int num, int base) {
// 	SqStack stack;
// 	SData e;
// 	SElemType *t;
// 	int basenum[100], i;
// 	InitStack(&stack);
// 	if (!num)printf("0\n");
// 	for (i = 0; i < 100; i++) {				//因为超过十进制就要用ABCD了
// 		if (i < 10)basenum[i] = '0' + i;	//所以用一个数组储存一张表，该表是该进制所用的符号集合
// 		else basenum[i] = 'A' + i - 10;
// 	}
// 	while (num) {
// 		SetData(&e, 0, basenum[num%base]);	//把该进制所用的符号入栈，低数位先入栈，高位后入栈
// 		MakeNode(&t, e);
// 		Push(&stack, t);
// 		num /= base;
// 	}
// 	while (!StackEmpty(stack)) {
// 		Pop(&stack, &t);			//出栈并打印
// 		printf("%c", t->data->expn);
// 	}
// 	printf("\n");
// 	DestroyStack(&stack);
// }
// Status BracketMatch(char *str) {
// 	SqStack stack;
// 	InitStack(&stack);
// 	SElemType *t;
// 	SData e;
// 	for (; *str; str++) {
// 		if (*str == '[') {
// 			SetData(&e, 0, 1);	//用1表示'['
// 			MakeNode(&t, e);
// 			Push(&stack, t);
// 		}
// 		else if (*str == ']') {	//用2表示']'
// 			if (StackEmpty(stack))return ERROR;
// 			GetTop(stack, &t);
// 			if (t->data->expn == 1) {
// 				Pop(&stack, &t);
// 				FreeNode(t);
// 			}
// 			else return ERROR;
// 		}
// 		else if (*str == '(') {	//用3表示'('
// 			SetData(&e, 0, 2);
// 			MakeNode(&t, e);
// 			Push(&stack, t);
// 		}
// 		else if (*str == ')') {	//用4表示')'
// 			if (StackEmpty(stack))return ERROR;
// 			GetTop(stack, &t);
// 			if (t->data->expn == 2) {
// 				Pop(&stack, &t);
// 				free(t);
// 			}
// 			else return ERROR;
// 		}
// 	}
// 	if (StackEmpty(stack)) {
// 		DestroyStack(&stack);
// 		return OK;
// 	}
// 	else {
// 		DestroyStack(&stack);
// 		return ERROR;
// 	}
// }
// void LineEdit(char back, char clear) {
// 	SqStack stack;
// 	char ch;
// 	SElemType *e;
// 	SData data;
// 	InitStack(&stack);
// 	ch = getchar();
// 	while (ch != EOF&&ch != '\n') {
// 		if (ch == back) {
// 			Pop(&stack, &e);
// 			free(e);
// 		}
// 		else if (ch == clear)ClearStack(&stack);
// 		else {
// 			SetData(&data, 0, ch);
// 			MakeNode(&e, data);
// 			Push(&stack, e);
// 		}
// 		ch = getchar();
// 	}
// 	StackTraverse(stack, PrintStr);
// 	DestroyStack(&stack);
// }
// int Precede(char ch1, char ch2) {
// 	if (ch1 == '=') {
// 		if (ch2 == '=')return 0;
// 		else return -1;
// 	}
// 	else if (ch1 == ')') {
// 		return 1;
// 	}
// 	else if (ch1 == '(') {
// 		if (ch2 == ')')return 0;
// 		else return -1;
// 	}
// 	else if (ch1 == '*' || ch1 == '/') {
// 		if (ch2 == '(')return -1;
// 		else return 1;
// 	}
// 	else if (ch1 == '+' || ch1 == '-') {
// 		if (ch2 == '(' || ch2 == '*' || ch2 == '/')return -1;
// 		else return 1;
// 	}
// 	return -2;
// }
// Status GetNum(char **str, double *dou) {
// 	char s[11];
// 	int n = 0;
// 	for (; **str && (isdigit(**str) || **str == '.'); (*str)++) {
// 		s[n++] = **str;
// 	}
// 	s[n] = '\0';
// 	if (!**str)return ERROR;
// 	*dou = atof(s);
// 	(*str)--;
// 	return OK;
// }
// SElemType *Operate(SElemType *num1, SElemType *operator,SElemType *num2) {
// 	double result = 0;
// 	SData data;
// 	SElemType *e;
// 	switch (operator->data->expn) {
// 	case '+':result = num1->data->coef + num2->data->coef; break;
// 	case '-':result = num1->data->coef - num2->data->coef; break;
// 	case '*':result = num1->data->coef*num2->data->coef; break;
// 	case '/':result = num1->data->coef / num2->data->coef; break;
// 	}
// 	SetData(&data, result, 0);
// 	MakeNode(&e, data);
// 	return e;
// }
// SElemType *Calculator(char *str) {
// 	SqStack optr;
// 	SqStack opnd;
// 	SElemType *e;
// 	SData data;
// 	double dou = 0;
// 	if (BracketMatch(str) == ERROR)return ERROR;
// 	InitStack(&optr);
// 	InitStack(&opnd);
// 	SetData(&data, 0, '=');
// 	MakeNode(&e, data);
// 	Push(&optr, e);
// 	while (*str) {
// 		if (isdigit(*str)) {
// 			if (GetNum(&str, &dou) == ERROR)break;
// 			SetData(&data, dou, 0);
// 			MakeNode(&e, data);
// 			Push(&opnd, e);
// 			str++;
// 		}
// 		else {
// 			GetTop(optr, &e);
// 			if (Precede(e->data->expn, *str) < 0) {
// 				SetData(&data, 0, *str);
// 				MakeNode(&e, data);
// 				Push(&optr, e);
// 				str++;
// 			}
// 			else if (Precede(e->data->expn, *str) == 0) {
// 				Pop(&optr, &e);
// 				FreeNode(e);
// 				str++;
// 			}
// 			else if (Precede(e->data->expn, *str) > 0) {
// 				SElemType *num1, *num2, *result;
// 				SElemType *operator;
// 				Pop(&optr, &operator);
// 				Pop(&opnd, &num2);
// 				Pop(&opnd, &num1);
// 				result = Operate(num1, operator,num2);
// 				Push(&opnd, result);
// 				FreeNode(num1);
// 				FreeNode(num2);
// 			}
// 		}
// 	}
// 	DestroyStack(&optr);
// 	GetTop(opnd, &e);
// 	return e;
// }
// Status CreateSMatrix(TSMatrix *matrix, SqStack stack) {
// 	SqStack temp;
// 	SData data;
// 	SElemType *node;
// 	int i;
// 	if (StackEmpty(stack))return ERROR;
// 	matrix->column = matrix->row = 8;
// 	matrix->num = StackLength(stack);
// 	if (!InitStack(&temp))return ERROR;
// 	for (i = 0; i < StackLength(stack); i++) {
// 		LocatePos(stack, i, &node);
// 		SetData(&data, node->data->coef, node->data->expn);
// 		MakeNode(&node, data);
// 		Push(&temp, node);
// 	}
// 	for (i = matrix->num - 1; i >= 0; i--) {
// 		Pop(&temp, &node);
// 		matrix->data[i].x = (int)node->data->coef;
// 		matrix->data[i].y = node->data->expn;
// 		matrix->data[i].value = 1;
// 	}
// 	SortMatrix(matrix);
// 	DestroyStack(&temp);
// 	return OK;
// }
// void PrintSMatrix(TSMatrix matrix) {
// 	int i, j, n;
// 	for (i = 0, n = 0; i < matrix.row; i++) {
// 		for (j = 0; j < matrix.column; j++) {
// 			if (i == matrix.data[n].x&&j == matrix.data[n].y)printf("%d", matrix.data[n++].value);
// 			else printf("O");
// 			if (j != matrix.column - 1)printf(" ");
// 		}
// 		printf("\n");
// 	}
// }
// void SortMatrix(TSMatrix *matrix) {
// 	int i, j;
// 	int index;
// 	Triple temp;
// 	for (i = 0; i < matrix->num; i++) {
// 		index = i;
// 		for (j = i + 1; j < matrix->num; j++) {
// 			if (matrix->data[j].x < matrix->data[index].x || (matrix->data[j].x == matrix->data[index].x&&matrix->data[j].y < matrix->data[index].y)) {
// 				index = j;
// 			}
// 		}
// 		if (index != i) {
// 			temp = matrix->data[i];
// 			matrix->data[i] = matrix->data[index];
// 			matrix->data[index] = temp;
// 		}
// 	}
// }
// Status sub_isEquel(TSMatrix matrix1, TSMatrix matrix2) {
// 	TSMatrix temp;
// 	int i = 0;
// 	if (!CompareMatrix(matrix1, matrix2))i = 1;
// 	LRevolveMatrix(&temp, matrix1);
// 	if (!CompareMatrix(temp, matrix2))i = 1;
// 	RRevolveMatrix(&temp, matrix1);
// 	if (!CompareMatrix(temp, matrix2))i = 1;
// 	TurnMatrix(&temp, matrix1);
// 	if (!CompareMatrix(temp, matrix2))i = 1;
// 	return i;
// }
// Status isEquel(TSMatrix *matrix1, TSMatrix matrix2, int length) {
// 	int i;
// 	for (i = 0; i < length; i++) {
// 		if (sub_isEquel(matrix1[i], matrix2))return true;
// 	}
// 	return false;
// }
// int CompareMatrix(TSMatrix matrix1, TSMatrix matrix2) {
// 	int i;
// 	if (matrix1.column != matrix2.column&&matrix1.row != matrix2.row&&matrix1.num != matrix2.num)return -1;
// 	for (i = 0; i < matrix1.num; i++) {
// 		if (matrix1.data[i].x != matrix2.data[i].x || matrix1.data[i].y != matrix2.data[i].y || matrix1.data[i].value != matrix2.data[i].value)return -1;
// 	}
// 	return 0;
// }
// Status LRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2) {
// 	int i;
// 	matrix1->row = matrix2.column;
// 	matrix1->column = matrix2.row;
// 	matrix1->num = matrix2.num;
// 	for (i = 0; i < matrix1->num; i++) {
// 		matrix1->data[i].y = matrix2.data[i].x;
// 		matrix1->data[i].x = matrix2.row - 1 - matrix2.data[i].y;
// 		matrix1->data[i].value = matrix2.data[i].value;
// 	}
// 	SortMatrix(matrix1);
// 	return OK;
// }
// Status RRevolveMatrix(TSMatrix *matrix1, TSMatrix matrix2) {
// 	int i;
// 	matrix1->row = matrix2.column;
// 	matrix1->column = matrix2.row;
// 	matrix1->num = matrix2.num;
// 	for (i = 0; i < matrix1->num; i++) {
// 		matrix1->data[i].x = matrix2.data[i].y;
// 		matrix1->data[i].y = matrix2.row - 1 - matrix2.data[i].x;
// 		matrix1->data[i].value = matrix2.data[i].value;
// 	}
// 	SortMatrix(matrix1);
// 	return OK;
// }
// Status TurnMatrix(TSMatrix *matrix1, TSMatrix matrix2) {
// 	TSMatrix temp;
// 	if (RRevolveMatrix(&temp, matrix2) == ERROR)return ERROR;
// 	if (RRevolveMatrix(matrix1, temp) == ERROR)return ERROR;
// 	return OK;
// }
// Status isPeace(SqStack stack, SData data) {
// 	SElemType *t;
// 	if (StackEmpty(stack))return OK;
// 	for (t = (stack.head)->next; t; t = t->next) {
// 		if (t->data->coef == data->coef || t->data->expn == data->expn || abs(t->data->coef - data->coef) == abs(t->data->expn - data->expn))
// 			return ERROR;
// 	}
// 	return OK;
// }
// void EightQueen() {
// 	int x = 0, y = 0, n = 0, num = 0;
// 	SqStack stack;
// 	SElemType *node;
// 	SData data;
// 	TSMatrix matrix[100];
// 	InitStack(&stack);
// 	while (StackLength(stack) < 8) {
// 		SetData(&data, x, y);
// 		//printf("%d   %d   已放%d个\n",(int)data->coef,data->expn,StackLength(stack));
// 		if (!isPeace(stack, data)) {
// 			//printf("放不下\n");
// 			while (data->expn == 7) {
// 				if (!GetTop(stack, &node))return;
// 				if (node->data->coef != data->coef) {
// 					free(data);
// 					Pop(&stack, &node);
// 					data = node->data;
// 					x = data->coef;
// 					y = data->expn;
// 					free(data);
// 				}
// 			}
// 		}
// 		else {
// 			MakeNode(&node, data);
// 			Push(&stack, node);
// 			y = 7;
// 		}
// 		if (StackLength(stack) == 8) {
// 			TSMatrix temp;
// 			CreateSMatrix(&temp, stack);
// 			if (!isEquel(matrix, temp, n)) {
// 				matrix[n++] = temp;
// 				printf("第%d种摆法：\n", n);
// 				PrintSMatrix(temp);
// 			}
// 			do {
// 				Pop(&stack, &node);
// 				data = node->data;
// 				x = data->coef;
// 				y = data->expn;
// 				free(data);
// 			} while (y == 7);
// 		}
// 		//getch();
// 		if (y == 7) {
// 			y = 0;
// 			x++;
// 		}
// 		else y++;

// 	}
// 	DestroyStack(&stack);
// }





// Status SetPolyn(ElemType *e, double coef, int expn) {
// 	if(!e)return ERROR;
// 	*e = (ElemType)malloc(sizeof(term)); //注意这里ElemType本身就是一级指针类型
// 	if (!*e)return OVERFLOW; 				//所以ElemType*是个二级指针
// 	(*e)->coef = coef; 					//我也不知道当初为什么自己要这么设置
// 	(*e)->expn = expn;
// 	return OK;
// }
// void SortPolyn(polynomail *p) {
// 	Link *p1, *p2;						//采用直接插入排序
// 	for (p1 = p->head->next; p1; p1 = p1->next) {
// 		for (p2 = p->head->next; p2 != p1; p2 = p2->next) {
// 			if (p2->data->expn == p1->data->expn) {	//若后边待排序的节点的指数跟前面已排序
// 				Link *pri;						//节点的指数相同，则应该合并两项，即删除后者，并入前者
// 				p2->data->coef += p1->data->coef;
// 				pri = PriorPos(*p, p1);
// 				DelFirst(pri, &p1);
// 				FreeNode(p1);
// 				p->len--;
// 				if (abs(p2->data->coef) < 1e-6) {	//如果合并后系数为0，那也要把这个节点删除
// 					pri = PriorPos(*p, p2);		//佩服自己当初思维如此缜密
// 					DelFirst(pri, &p2);
// 					FreeNode(p2);
// 					p->len--;
// 				}
// 				p1 = pri;
// 				break;
// 			}
// 			else if (p1->data->expn < p2->data->expn) {
// 				Link *pri1, *pri2;
// 				pri1 = PriorPos(*p, p1);			//在学生管理系统自己想得半死的插入排序，这里用了5行就搞定了
// 				DelFirst(pri1, &p1);
// 				pri2 = PriorPos(*p, p2);
// 				InsFirst(pri2, p1);
// 				p1 = pri1;
// 				break;
// 			}
// 		}
// 	}
// 	p->tail = GetLast(*p);					//在设置一下尾结点，更佩服当初自己缜密的思维
// }
// Status CreatPolyn(polynomail *p, int m) {
// 	int i, expn;
// 	double coef;
// 	ElemType e;
// 	Link *s;
// 	if (InitList(p) == ERROR)return ERROR;
// 	for (i = 0; i < m; i++) {
// 		printf("请输入第%d项的系数和指数：", i + 1);
// 		scanf("%lf%d", &coef, &expn);
// 		if (SetPolyn(&e, coef, expn) == ERROR)return ERROR;	//输入数据，形成数据域
// 		if (MakeNode(&s, e) == ERROR)return ERROR;			//包装进一个结点
// 		if (Append(p, s) == ERROR)return ERROR;				//将结点插入链表尾
// 	}
// 	SortPolyn(p);											//再慢慢排序
// 	return OK;
// }
// Status DestroyPolyn(polynomail *p) {
// 	if (DestroyList(p) == ERROR)return ERROR;
// 	else return OK;
// }
// void PrintPolyn(polynomail p) {
// 	Link *pt;
// 	if (ListEmpty(p))return;
// 	printf("y=");
// 	for (pt = (p.head)->next; pt; pt = pt->next) {
// 		if (pt == (p.head)->next&&abs(pt->next->data->coef + 1) < 1e-6)printf("-");
// 		if (!(abs(pt->data->coef) - 1 < 1e-6))printf("%.2f", pt->data->coef);
// 		printf("x^%d", pt->data->expn);
// 		if (pt->next) {
// 			if (pt->next->data->coef > 0)printf("+");
// 			else if (abs(pt->next->data->coef + 1) < 1e-6)printf("-");
// 		}
// 	}
// 	printf("\n");
// }
// int PolynLength(polynomail p) {
// 	return ListLength(p);
// }
// void AddPolyn(polynomail *pa, polynomail *pb) {
// 	Link *ha, *hb, *hc;					//利用归并的方法，将两个多项式合并成一个
// 	ha = pa->head->next;
// 	hb = pb->head->next;
// 	hc = pa->head;
// 	while (ha&&hb) {
// 		if (ha->data->expn < hb->data->expn) {
// 			hc->next = ha;
// 			hc = hc->next;
// 			ha = ha->next;
// 		}
// 		else if (ha->data->expn == hb->data->expn) {
// 			Link *t;
// 			ha->data->coef += hb->data->coef;
// 			t = hb;
// 			hb = hb->next;
// 			FreeNode(t);
// 			if (abs(ha->data->coef) < 1e-6) {
// 				t = ha;
// 				ha = ha->next;
// 				FreeNode(t);
// 			}
// 			else {
// 				hc->next = ha;
// 				ha = ha->next;
// 				hc = hc->next;
// 			}
// 		}
// 		else {
// 			hc->next = hb;
// 			hc = hc->next;
// 			hb = hb->next;
// 		}
// 	}
// 	if (ha)hc->next = ha;
// 	if (hb)hc->next = hb;
// 	pb->head->next = NULL;
// 	DestroyPolyn(pb);
// 	pa->tail = GetLast(*pa);
// 	pa->len = ListLength(*pa);
// }
// void SubtractPolyn(polynomail *pa, polynomail *pb) {
// 	ListTraverse(*pb, inverse);
// 	AddPolyn(pa, pb);
// }
// Link *sub_MultiplyPolyn(Link *p, polynomail *pb) {
// 	Link *pt, *head = NULL, *newnode = NULL;
// 	Link *t;
// 	ElemType e = NULL;
// 	double coef, coef_ori = p->data->coef;
// 	int expn, expn_ori = p->data->expn;
// 	for (pt = pb->head->next; pt; pt = pt->next) {		//遍历pb的每个结点，分别于p相乘
// 		coef = coef_ori;							//得到的新数据包装成结点并链成新链表
// 		expn = expn_ori;							//然后返回这一串结点的首节点地址
// 		coef *= pt->data->coef;
// 		expn += pt->data->expn;
// 		if (SetPolyn(&e, coef, expn) == ERROR)return NULL;	//组成数据域
// 		if (MakeNode(&newnode, e) == ERROR)return NULL;	//包装成行指针域的节点
// 		if (pt == pb->head->next)head = t = newnode;			//将结点插入链表
// 		else {
// 			if (InsFirst(t, newnode) == ERROR)return NULL;
// 			t = t->next;
// 		}
// 	}
// 	return head;
// }
// Status MultiplyPolyn(polynomail *pa, polynomail *pb) {
// 	Link *ha;
// 	Link *t;
// 	ha = pa->head->next;
// 	pa->tail = pa->head;
// 	pa->head->next = NULL;
// 	pa->len = 0;
// 	while (ha) {								//将pa中每个结点分别于pb整个链表乘一遍
// 		t = sub_MultiplyPolyn(ha, pb);			//返回一串结点，将这一串节点插入pa中
// 		if (Append(pa, t) == ERROR)return ERROR;
// 		t = ha;
// 		ha = ha->next;
// 		FreeNode(t);
// 	}
// 	SortPolyn(pa);
// 	DestroyPolyn(pb);
// }





int main() {
	// polynomail p1,p2;
	// printf("请输入第一个多项式：\n");
	// CreatPolyn(&p1,2);
	// printf("请输入第二个多项式：\n");
	// CreatPolyn(&p2,4);
	// printf("\n这两个多项式分别是：\n");
	// PrintPolyn(p1);
	// PrintPolyn(p2);
	// MultiplyPolyn(&p1,&p2);
	// printf("\n相乘的结果是：\n");
	// PrintPolyn(p1);

	// char str[20];
	// SElemType *e;
	// printf("请输入算式：");
	// gets(str);
	// e=Calculator(str);
	// printf("结果为：%f\n",e->data->coef);

	// int opentime,closetime,intertime_arr,intertime_work;
	// printf("请输入开始营业时间：");
	// scanf("%d",&opentime);
	// printf("请输入结束营业时间：");
	// scanf("%d",&closetime);
	// printf("请输入每两人到达的最大时间间隔：");
	// scanf("%d",&intertime_arr);
	// printf("请输入客户业务最长处理时间：");
	// scanf("%d",&intertime_work);
	// BankSimulation(0,100,5,30,0);

	// EightQueen();

	// Conversion(100000000,16);

	// printf("%d\n",BracketMatch("([(]])])"));
	return 0;
}
