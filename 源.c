#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<time.h>

typedef struct 
{
	int occurtime;
	int ntype;
}event;
//event en;
typedef struct node                     //事件有序链表
{
	event data;
	struct node *next;
}*eventlist;
//eventlist ev;
typedef struct
{
	int arrivetime;
	int duration;
}cus;
//cus inf;
typedef struct LN
{
	cus inf;
	struct LN *next;
}*queue;
//queue q;

typedef struct                         //银行队列
{
	queue front;
	queue rear;
}linkqueue;


int random(int n)
{
	srand(time(NULL));
	return rand() % n;
}
int cmp(event a, event b)
{
	if ((a.occurtime-b.occurtime)<0)
	     return -1;
	if ((a.occurtime - b.occurtime)==0)
		return 0;
	if ((a.occurtime - b.occurtime)>0)
		return 1;
}
eventlist init()                      //初始化有序链表
{
	eventlist head = (eventlist)malloc(sizeof(struct node));
	head->next = NULL;
	return head;
}              
void insert(eventlist ev, event en)         //插入有序链表
{
	eventlist p,q;
	q = (eventlist)malloc(sizeof(struct node));
	q->data = en;
	q->next = NULL;

	p = ev;
	if (p->next != NULL)
	{
		while (p->next&&p->next->data.occurtime < en.occurtime)
		{
			p = p->next;
		}
	}
	q->next = p->next;
	p->next = q;
	printf("insert = (%d %d) ", en.occurtime, en.ntype);
}
event deletelink(eventlist ev)          //删除有序链表头元素
{
	eventlist p;
	event en;
	p = ev->next;
	en = p->data;
	ev->next = p->next;
	printf("delete = (%d %d ) ", en.occurtime,en.ntype);
	return en;
}
event getheadlink(eventlist ev)
{
	eventlist p;
	event en;
	p = ev->next;
	en = p->data;
	return en;
}
int emptylink(eventlist ev)
{
	if (ev->next == NULL) return 1;
	else return 0;
}

linkqueue create()                        //初始化队列
{
	linkqueue lq;
	lq.front = lq.rear = (queue)malloc(sizeof(struct LN));
	if (!lq.front)
	{
		printf("error");
		exit(-1);
	}
	lq.front->next = NULL;
	return lq;
}
void insertlq(linkqueue lq, cus e)
{
	queue p;
	p = (queue)malloc(sizeof(struct LN));
	if (!p)
	{
		printf("overflow");
		exit(-1);
	}
	p->inf = e;
	p->next = NULL;
	lq.rear->next = p;
	lq.rear = p;
	printf("insertlq = (%d %d)", p->inf.arrivetime, p->inf.duration);
}
cus getheadlq(linkqueue lq)
{
	cus q;
	q = lq.front->next->inf;
	return q;
}
cus deletelq(linkqueue lq)
{
	cus q;
	queue pt;
	pt = lq.front->next;
	if (lq.rear == pt)
		lq.rear = lq.front;
	q = pt->inf;
	lq.front->next = pt->next;
	return q;
}
int emptylq(linkqueue lq)
{
	if (lq.front->next == NULL) return 1;
	else return 0;
}
int length(linkqueue lq)
{
	int x = 0;
	queue pt;
	pt = lq.front;
	while (pt->next != NULL)
	{
		x++;
		pt = pt->next;
	}
	//printf("length=%d ", x);
	return x;
}
int mini(linkqueue *lq)
{
	int min = length(lq[1]);
	int x = 1;
	for (int i = 2; i <= 4; i++)
	{
		if (length(lq[i]) < length(lq[1]))
		{
			min = length(lq[i]);
			x = i;
		}
	}
	printf("mini=%d ", x);
	return x;
}

int main()
{
	linkqueue ql[5]; cus inf;
	int cstnum = 0, durtime, intertime, j = 0;
	int closetime = 5;
	float totaltime = 0;
	srand(time(NULL));
	totaltime = 0; cstnum = 0;
	eventlist ev = init();
	event en, tn;
	en.ntype = 0; en.occurtime = 0;
	insert(ev, en);

	for (int i = 1; i <= 4; i++)
	{
		ql[i] = create();
	}
	printf("open ");
	while (!emptylink(ev))
	{
		en = deletelink(ev);
		
		if (en.ntype == 0)
		{
			durtime = rand() % 30;
			intertime = rand() % 5;
			//durtime = 12;
			//intertime = 3;
			++cstnum;
			int t = en.occurtime + intertime;
			printf("t=%d ", t);
			if (t < closetime)
			{
				tn.occurtime = t;
				tn.ntype = 0;
				insert(ev, tn);
				printf(" a ");
			}
			j = mini(ql);
			inf.arrivetime = en.occurtime;
			inf.duration = durtime;
			insertlq(ql[j], inf);
			if (length(ql[j]) == 1)
			{
				en.occurtime += durtime;
				en.ntype = j;
				insert(ev, en);
			}
		}
		else
		{
			
			j = en.ntype;
			inf = deletelq(ql[j]);
			totaltime += en.occurtime - inf.arrivetime;
			printf("total = %d ", totaltime);
			if (!emptylq(ql[j]))
			{
				inf = getheadlq(ql[j]);
				tn.occurtime = en.occurtime + inf.duration;
				tn.ntype = j;
				insert(ev, tn);
			}
		}
	}
	printf("The Average Time is %f\n", totaltime / cstnum);
	return 0;
}

