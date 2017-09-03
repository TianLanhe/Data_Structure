#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define MY_DEBUG

#define BEFORE_CHECK_RESULT()	\
	Status __status;

#define CHECK_RESULT(func)		\
	if((__status = func)!=OK){	\
		return __status;		\
	}							\

#define AFTER_CHECK_RESULT()	\
	return OK

#define CHECK_OVERFLOW(var)		\
	if(!var){					\
		return OVERFLOW;		\
	}

#define CHECK_ERROR(exp)		\
	if(!(exp))					\
		return ERROR

typedef enum _type {
	ARRIVE,				//到达事件
	LEAVE				//离开事件
}Type;

typedef struct _event {
	Type type;			//事件类型
	int time;			//事件发生事件
}Event;

#define QElemType Event
#include "../PriorityQueue.h"

typedef struct _bankinformation {
	PriorityQueue *queue;			//事件队列
	int *service;					//窗口数组
	int service_num;				//表示窗口数量
	int total_time;					//总等候时间
	int total_num;					//总人数
	int opentime;					//营业时间(分钟)
	int closetime;			  		//结束时间(分钟)
	int intertime_arr;				//到达最大间隔时间
	int intertime_work;				//业务等待最长时间
}BankInfo;

int comparator(QElemType a, QElemType b) {
	return a.time < b.time;
}

Status OpenForDay(BankInfo *info, int service_num, int opentime, int closetime, int intertime_arr, int intertime_work);
double CloseForDay(BankInfo *info);
int ShortestServiceWindow(BankInfo info);
int GetRandomNum(int start, int length);
int hasEvent(BankInfo info);
Status HandleEvent(BankInfo *info);
Status HandleArrive(BankInfo *info,Event event);
Status HandleLeave(BankInfo *info,Event event);
double BankSimulation(int service_num, int opentime, int closetime, int intertime_arr, int intertime_work);

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
	InitQueue(info->queue, comparator);

	info->service = (int*)malloc(sizeof(int)*service_num);
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
	event.time = GetRandomNum(opentime, intertime_arr + 1);
	EnQueue(info->queue, event);

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
	int bucket_size = RAND_MAX / length;
	int ret;
	do {
		ret = rand() / bucket_size;
	} while (ret >= length);
	return ret + start;
}

int hasEvent(BankInfo info) {
	return !QueueEmpty(*(info.queue));
}

Status HandleEvent(BankInfo *info){
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
	Event event;
	CHECK_RESULT(DeQueue(info->queue,&event));

	if (event.type == ARRIVE){
		CHECK_RESULT(HandleArrive(info, event));
	}else if (event.type == LEAVE){
		CHECK_RESULT(HandleLeave(info,event));
	}else{
		return ERROR;
	}

	AFTER_CHECK_RESULT();
}

Status HandleArrive(BankInfo *info,Event event){
	int service_time = GetRandomNum(0,info->intertime_work+1);
	int min_index = ShortestServiceWindow(*info);
	return OK;
}

Status HandleLeave(BankInfo *info,Event event){
	return OK;
}

Status Print(QElemType e) {
	printf("%d %d\n", e.type, e.time);
}

double BankSimulation(int service_num, int opentime, int closetime, int intertime_arr, int intertime_work) {
	BankInfo info;
	BEFORE_CHECK_RESULT();

	CHECK_RESULT(OpenForDay(&info, service_num, opentime, closetime, intertime_arr, intertime_work));

	QueueTraverse(*info.queue, Print);
	while (hasEvent(info))
		CHECK_RESULT(HandleEvent(&info));

	return CloseForDay(&info);
}

int main() {
	BankSimulation(4, 0, 100, 5, 30);
	return 0;
}
