#include <stdio.h>
#include <time.h>
#include <stdlib.h>
//#define MY_DEBUG			//用于调试的宏

typedef enum _type {
	ARRIVE,				//到达事件
	LEAVE				//离开事件
}Type;

typedef struct _event {
	Type type;			//事件类型
	int time;			//事件发生事件
	int arr_time;		//离开事件的额外信息，记录到达时的时间
}Event;

#define QElemType Event
#include "../PriorityQueue.h"

typedef struct _bankinformation {
	PriorityQueue *queue;			//事件表，用优先队列表示
	int *service;					//窗口数组，表示每个窗口服务需要到什么时候才能服务完该窗口的人
	int service_num;				//表示窗口数量
	int total_time;					//总等候时间
	int total_num;					//总人数
	int opentime;					//营业时间(分钟)
	int closetime;			  		//结束时间(分钟)
	int intertime_arr;				//到达最大间隔时间
	int intertime_work;				//业务等待最长时间
}BankInfo;

int comparator(QElemType* a, QElemType* b);
//优先队列用于比较的函数
Status Print(QElemType* e);
//遍历优先队列的应用函数，输出事件类型和事件发生事件
Status OpenForDay(BankInfo *info, int service_num, int opentime, int closetime, int intertime_arr, int intertime_work);
//开始营业，初始化信息结果题，设置窗口数量，营业、结束时间，顾客到达最大间隔，服务最长时间，并将第一个到达的人添加到事件表中
double CloseForDay(BankInfo *info);
//结束营业，销毁各种结构体，且计算并返回平均等候时间
int ShortestServiceWindow(BankInfo info);
//求出哪个窗口服务时间最短，安排客户到该窗口排队
int GetRandomNum(int start, int length);
//求随机数，rand()%n的方法不好，可能会使求得的数概率不同
int hasEvent(BankInfo info);
//判断事件表中是否还有事件
Status HandleEvent(BankInfo *info);
//处理事件
Status HandleArrive(BankInfo *info, Event event);
//处理到达事件，生成离开事件与下一个顾客到达事件
Status HandleLeave(BankInfo *info, Event event);
//处理离开事件，统计人数和事件
Status BankSimulation(int service_num, int opentime, int closetime, int intertime_arr, int intertime_work, double *ret);
//模拟银行业务，计算每天人均等候时间

int comparator(QElemType* a, QElemType* b) {
	return a->time - b->time;
}

Status Print(QElemType* e) {
	printf("%d %d\n", e->type, e->time);
	return OK;
}

Status OpenForDay(BankInfo *info, int service_num, int opentime, int closetime, int intertime_arr, int intertime_work) {
	CHECK_ERROR(info);
	CHECK_ERROR(opentime != closetime);
	CHECK_ERROR(opentime >= 0);
	CHECK_ERROR(closetime >= 0);
	CHECK_ERROR(service_num > 0);
	CHECK_ERROR(intertime_arr > 0);
	CHECK_ERROR(intertime_work > 0);

	srand(time(NULL));

	info->queue = (PriorityQueue*)malloc(sizeof(PriorityQueue));
	CHECK_OVERFLOW(info->queue);
	InitQueue(info->queue, sizeof(Event), comparator);

	info->service = (int*)malloc(sizeof(int) * service_num);
	CHECK_OVERFLOW(info->service);
	int i;
	for (i = 0; i < service_num; ++i)
		info->service[i] = opentime;

	info->service_num = service_num;
	info->opentime = opentime;
	info->closetime = closetime;
	info->intertime_arr = intertime_arr;
	info->intertime_work = intertime_work;

	info->total_num = info->total_time = 0;

	Event event;
	event.type = ARRIVE;
	event.arr_time = -1;	//到达事件不需要这个字段，随便设一个好了
	event.time = GetRandomNum(opentime, intertime_arr + 1);
	EnQueue(info->queue, &event);

	return OK;
}

double CloseForDay(BankInfo *info) {
	CHECK_ERROR(info);

	free(info->service);
	info->service = NULL;

	DestroyQueue(info->queue);
	free(info->queue);
	info->queue = NULL;

	info->service_num = 0;
	info->intertime_arr = info->intertime_work = 0;

	double ret;
	ret = info->total_time *1.0 / info->total_num;

	info->total_num = info->total_time = 0;

	return ret;
}

int ShortestServiceWindow(BankInfo info) {
	CHECK_ERROR(info.service_num != 0);
	CHECK_ERROR(info.service);
	int i;
	int min = 0;
	for (i = 1; i < info.service_num; ++i)
		if (info.service[i] < info.service[min])
			min = i;
	return min;
}

int GetRandomNum(int start, int length) {
	int rand_max = RAND_MAX / length * length;
	int ret;
	do {
		ret = rand();
	} while (ret >= rand_max);
	return ret % length + start;
}

int hasEvent(BankInfo info) {
	return !QueueEmpty(*(info.queue));
}

Status HandleEvent(BankInfo *info) {
	CHECK_ERROR(info);
	CHECK_ERROR(info->queue);
	CHECK_ERROR(info->service);
	CHECK_ERROR(info->service_num != 0);
	CHECK_ERROR(info->opentime != info->closetime);
	CHECK_ERROR(info->opentime >= 0);
	CHECK_ERROR(info->closetime >= 0);
	CHECK_ERROR(info->intertime_arr > 0);
	CHECK_ERROR(info->intertime_work > 0);

	CHECK_ERROR(!QueueEmpty(*(info->queue)));

	BEFORE_CHECK_RESULT();
	Event event;			//取出事件
	CHECK_RESULT(DeQueue(info->queue, &event));

	if (event.type == ARRIVE) {
		CHECK_RESULT(HandleArrive(info, event));
	}
	else if (event.type == LEAVE) {
		CHECK_RESULT(HandleLeave(info, event));
	}
	else {
		return ERROR;
	}

#ifdef MY_DEBUG		//调试状态下输出具体信息
	printf("\n");
	Print(&event);
	printf("\n");

	QueueTraverse(*info->queue, Print);
	printf("\n");

	for (int i = 0; i < info->service_num; ++i)
		printf("%d ", info->service[i]);
	printf("\n");

	printf("%2d %2d\n", info->total_num, info->total_time);
	getch();
#endif

	AFTER_CHECK_RESULT();
}

Status HandleArrive(BankInfo *info, Event event) {
	CHECK_ERROR(event.type == ARRIVE);

	int service_time = GetRandomNum(0, info->intertime_work + 1);
	int min_index = ShortestServiceWindow(*info);
	int max = info->service[min_index] > event.time ? info->service[min_index] : event.time;
	info->service[min_index] = max	+ service_time;

	Event e;					//生成离开事件，并插入事件表
	e.type = LEAVE;
	e.time = info->service[min_index];
	e.arr_time = event.time;
	EnQueue(info->queue, &e);

	int next_arr_time = GetRandomNum(event.time, info->intertime_arr + 1);
	if (next_arr_time < info->closetime) {	//生成下一客户到达时间
		e.type = ARRIVE;					//若在营业范围内，则生成
		e.time = next_arr_time;				//客户到达事件并插入事件表
		e.arr_time = -1;
		EnQueue(info->queue, &e);
	}
	return OK;
}

Status HandleLeave(BankInfo *info, Event event) {
	CHECK_ERROR(event.type == LEAVE);
	CHECK_ERROR(event.arr_time != -1);

	++info->total_num;
	info->total_time += event.time - event.arr_time;

	return OK;
}

Status BankSimulation(int service_num, int opentime, int closetime, int intertime_arr, int intertime_work, double *ret) {
	BankInfo info;
	BEFORE_CHECK_RESULT();

	CHECK_RESULT(OpenForDay(&info, service_num, opentime, closetime, intertime_arr, intertime_work));

	while (hasEvent(info))
		CHECK_RESULT(HandleEvent(&info));

	*ret = CloseForDay(&info);

	AFTER_CHECK_RESULT();
}

int main() {
	double ret;
	if (BankSimulation(250, 0, 36000, 20, 500, &ret) != OK)return 1;
	printf("%.2lf\n", ret);
	return 0;
}
