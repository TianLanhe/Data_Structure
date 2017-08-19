#ifndef POLYNOMAIL_H
#define POLYNOMAIL_H

#include "../LinkList.h"

typedef LinkList polynomail;		//重定义链表类型为多项式类型
typedef struct _elemtype term;				//重定义结点数据域别名

Status SetPolyn(ElemType *e, double coef, int expn);
//分配由e指向的元素的数据值，并设置其coef和expn成员，并返回OK，若分配失败，则返回ERROR
Status CreatPolyn(polynomail *p, int m);
//输入m项的系数和指数，建立表示一元多项式的有序链表p
Status DestroyPolyn(polynomail *p);
//销毁一元多项式p
void PrintPolyn(polynomail p);
//打印输出一元多项式
int PolynLength(polynomail p);
//返回一元多项式p中的项数
void SortPolyn(polynomail *p);
//对一元多项式进行排序、合并和删除处理，将一元多项式化为指数从低到高的系数不为0的形式
void AddPolyn(polynomail *pa, polynomail *pb);
//完成一元多项式的相加运算，即：pa=pa+pb，并销毁一元多项式pb
Status inverse(Link *p);
//遍历函数用的功能函数，其功能是将结点p中数据域元素的coef(系数)取反
void SubtractPolyn(polynomail *pa, polynomail *pb);
//完成一元多项式的相减运算，即：pa=pa-pb，并销毁一元多项式pb
Link *sub_MultiplyPolyn(Link *p, polynomail *pb);
//完成单项式的相加运算，即：pc=a*pb，是一元多项式相乘的基础
Status MultiplyPolyn(polynomail *pa, polynomail *pb);
//完成一元多项式的相乘运算，即：pa=pa*pb，并销毁一元多项式pb

#endif