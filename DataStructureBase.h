#ifndef DATA_STRUCTURE_BASE_H
#define DATA_STRUCTURE_BASE_H

#define OK 0
#define ERROR 1
#define OVERFLOW -2
#define INFEASIBLE -1
#define true 1
#define false 0

#ifndef ElemType
#define ElemType int
#endif

typedef int Status;

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

#endif
