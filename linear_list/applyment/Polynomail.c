#include "Polynomail.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

Status SetPolyn(ElemType *e, double coef, int expn) {
	if (!e)return ERROR;
	*e = (ElemType)malloc(sizeof(term)); //注意这里ElemType本身就是一级指针类型
	if (!*e)return OVERFLOW; 				//所以ElemType*是个二级指针
	(*e)->coef = coef; 					//我也不知道当初为什么自己要这么设置
	(*e)->expn = expn;
	return OK;
}
void SortPolyn(polynomail *p) {
	Link *p1, *p2;						//采用直接插入排序
	for (p1 = p->head->next; p1; p1 = p1->next) {
		for (p2 = p->head->next; p2 != p1; p2 = p2->next) {
			if (p2->data->expn == p1->data->expn) {	//若后边待排序的节点的指数跟前面已排序
				Link *pri;						//节点的指数相同，则应该合并两项，即删除后者，并入前者
				p2->data->coef += p1->data->coef;
				pri = PriorPos(*p, p1);
				DelFirst(pri, &p1);
				FreeNode(p1);
				--p->len;
				if (fabs(p2->data->coef) < 1e-6) {	//如果合并后系数为0，那也要把这个节点删除
					pri = PriorPos(*p, p2);
					DelFirst(pri, &p2);
					FreeNode(p2);
					--p->len;
				}
				p1 = pri;
				break;
			}
			else if (p1->data->expn < p2->data->expn) {
				Link *pri1, *pri2;
				pri1 = PriorPos(*p, p1);
				DelFirst(pri1, &p1);
				pri2 = PriorPos(*p, p2);
				InsFirst(pri2, p1);
				p1 = pri1;
				break;
			}
		}
	}
	p->tail = GetLast(*p);
}
Status CreatPolyn(polynomail *p, int m) {
	int i, expn;
	double coef;
	ElemType e;
	Link *s;
	if (InitList(p) == ERROR)return ERROR;
	for (i = 0; i < m; i++) {
		printf("请输入第%d项的系数和指数：", i + 1);
		scanf("%lf%d", &coef, &expn);
		if (SetPolyn(&e, coef, expn) == ERROR)return ERROR;	//输入数据，形成数据域
		if (MakeNode(&s, e) == ERROR)return ERROR;			//包装进一个结点
		if (Append(p, s) == ERROR)return ERROR;				//将结点插入链表尾
	}
	SortPolyn(p);											//再慢慢排序
	return OK;
}
Status DestroyPolyn(polynomail *p) {
	if (DestroyList(p) == ERROR)return ERROR;
	else return OK;
}
void PrintPolyn(polynomail p) {
	Link *pt;
	if (ListEmpty(p)){
		printf("y=0\n");
		return;
	}
	printf("y=");
	for (pt = (p.head)->next; pt; pt = pt->next) {
		if (pt != GetHead(p))
			printf("%c", pt->data->coef > 0 ? '+' : '-');
		if (fabs(pt->data->coef) > 1 || pt->data->expn == 0)
			printf("%.2f", pt->data->coef);

		if(pt->data->expn != 0){
			printf("x");
			if (pt->data->expn != 1)printf("^%d", pt->data->expn);
		}
	}
	printf("\n");
}
int PolynLength(polynomail p) {
	return ListLength(p);
}
void AddPolyn(polynomail *pa, polynomail *pb) {
	Link *ha, *hb, *hc;					//利用归并的方法，将两个多项式合并成一个
	ha = pa->head->next;
	hb = pb->head->next;
	hc = pa->head;
	while (ha&&hb) {
		if (ha->data->expn < hb->data->expn) {
			hc->next = ha;
			hc = hc->next;
			ha = ha->next;
		}
		else if (ha->data->expn == hb->data->expn) {
			Link *t;
			ha->data->coef += hb->data->coef;
			t = hb;
			hb = hb->next;
			FreeNode(t);
			if (fabs(ha->data->coef) < 1e-6) {
				t = ha;
				ha = ha->next;
				FreeNode(t);
			}
			else {
				hc->next = ha;
				ha = ha->next;
				hc = hc->next;
			}
		}
		else {
			hc->next = hb;
			hc = hc->next;
			hb = hb->next;
		}
	}
	if (ha)hc->next = ha;
	else if (hb)hc->next = hb;
	else hc->next = NULL;
	pb->head->next = NULL;
	DestroyPolyn(pb);
	pa->tail = GetLast(*pa);
	pa->len = ListLength(*pa);
}
Status inverse(Link *p) {
	if (!p)
		return ERROR;
	p->data->coef *= -1;
	return OK;
}
void SubtractPolyn(polynomail *pa, polynomail *pb) {
	ListTraverse(*pb, inverse);
	AddPolyn(pa, pb);
}
Link *sub_MultiplyPolyn(Link *p, polynomail *pb) {
	Link *pt, *head = NULL, *newnode = NULL;
	Link *t;
	ElemType e = NULL;
	double coef, coef_ori = p->data->coef;
	int expn, expn_ori = p->data->expn;
	for (pt = pb->head->next; pt; pt = pt->next) {		//遍历pb的每个结点，分别于p相乘
		coef = coef_ori;							//得到的新数据包装成结点并链成新链表
		expn = expn_ori;							//然后返回这一串结点的首节点地址
		coef *= pt->data->coef;
		expn += pt->data->expn;
		if (SetPolyn(&e, coef, expn) == ERROR)return NULL;	//组成数据域
		if (MakeNode(&newnode, e) == ERROR)return NULL;	//包装成行指针域的节点
		if (pt == GetHead(*pb))head = t = newnode;			//将结点插入链表
		else {
			if (InsFirst(t, newnode) == ERROR)return NULL;
			t = t->next;
		}
	}
	return head;
}
Status MultiplyPolyn(polynomail *pa, polynomail *pb) {
	Link *ha;
	Link *t;
	if (!pa || !pb)
		return ERROR;
	if (ListEmpty(*pa) || ListEmpty(*pb))
		return ERROR;
	ha = pa->head->next;
	pa->tail = pa->head;
	pa->head->next = NULL;
	pa->len = 0;
	while (ha) {								//将pa中每个结点分别于pb整个链表乘一遍
		t = sub_MultiplyPolyn(ha, pb);			//返回一串结点，将这一串节点插入pa中
		if (t == NULL)return ERROR;
		if (Append(pa, t) == ERROR)return ERROR;
		t = ha;
		ha = ha->next;
		FreeNode(t);
	}
	SortPolyn(pa);
	DestroyPolyn(pb);
	return OK;
}
