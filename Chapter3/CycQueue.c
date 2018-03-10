//循环队列的操作与实例，实现初始化队列、删除队列、判断队列是否满，判断是否空，入队，出队，获取队列长度，获取第一个元素数据
//由于循环队列中head=rear可能有两种情况，满或者空，所以定义满状态为队列空出一个位置，令head指向队尾元素的前一个位置，所以满的条件为(rear+1)%MAX==head，空的条件为rear==head
//main函数实现简单的叫号系统

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define QUEUE_MAX 6

int num;   //顾客序号

typedef struct
{
	int num;
	long timeIn;
}DATA;

typedef struct
{
	DATA data[QUEUE_MAX];
	int head;
	int rear;
}CycQueue;


//  1.初始化队列
CycQueue *initCycQueue()
{
	CycQueue *q;
	q=(CycQueue *)malloc(sizeof(CycQueue));
	if(q!=NULL)
	{
		q->head=0;
		q->rear=0;
		printf("队列初始化：成功\n");
		return q;
	}
	else
	{
		printf("队列初始化：内存分配失败\n");
		return NULL;
	}
}

//  2.删除队列
void deleteCycQueue(CycQueue *q)
{
	if(q!=NULL)
	{
		free(q);
		printf("清除队列：成功\n");
	}
	else
	{
		printf("清除队列：队列不存在\n");
	}
	q=NULL;
	return;
}

//  3.判断队列是否满
int isFullCycQueue(CycQueue *q)
{
	if((q->rear+1)%QUEUE_MAX==q->head)
	{
		printf("队列已满\n");
		return 1;
	}
	else
		return 0;
}

//  4.判断队列是否空
int isEmptyQueue(CycQueue *q)
{
	if(q->head==q->rear)
	{
		printf("队列为空\n");
		return 1;
	}
	else
		return 0;
}

//  5.入队
int inCycQueue(CycQueue *q,DATA num)
{
	printf("入队：");
	if(isFullCycQueue(q))
		return 0;
	else
	{
		q->rear=(q->rear+1)%QUEUE_MAX;
		q->data[q->rear]=num;
		printf("成功\n");
		return 1;
	}
}

//  6.出队
DATA *outCycQueue(CycQueue *q)
{
	printf("出队：");
	if(isEmptyQueue(q))
		return NULL;
	else
	{
		q->head=(q->head+1)%QUEUE_MAX;    //head指向队首前一个位置，所以先+1再取出
		printf("成功\n");
		return &(q->data[q->head]);
	}
}

//  7.获取队列长度，负数+Queue_Max
int lengthOfCycQueue(CycQueue *q)
{
	printf("队列长度：%d\n",(q->rear-q->head+QUEUE_MAX)%QUEUE_MAX);
	return (q->rear-q->head+QUEUE_MAX)%QUEUE_MAX;
}

//  8.获取队首元素(不出队)
DATA *getPeek(CycQueue *q)
{
	printf("获取队首元素：");
	if(isEmptyQueue(q))
		return NULL;
	else
	{
		printf("成功\n");
		return &(q->data[(q->head+1)%QUEUE_MAX]);
	}
}

//  该函数测试队列的基本功能
int test(void)
{
	DATA *p;
	DATA data0={0,time(NULL)};
	DATA data1={1,time(NULL)};
	DATA data2={2,time(NULL)};
	DATA data3={3,time(NULL)};
	DATA data4={4,time(NULL)};


	CycQueue *q=initCycQueue();
	isEmptyQueue(q);

	p=outCycQueue(q);

	inCycQueue(q,data0);
	inCycQueue(q,data1);
	inCycQueue(q,data2);

	lengthOfCycQueue(q);
	isEmptyQueue(q);
	isFullCycQueue(q);

	inCycQueue(q,data3);
	p=outCycQueue(q);
	printf("序号：%d 时间：%ld\n",p->num,p->timeIn);

	inCycQueue(q,data4);
	isFullCycQueue(q);

	p=outCycQueue(q);
	printf("序号：%d 时间：%ld\n",p->num,p->timeIn);
	p=outCycQueue(q);
	printf("序号：%d 时间：%ld\n",p->num,p->timeIn);	
	p=outCycQueue(q);
	printf("序号：%d 时间：%ld\n",p->num,p->timeIn);
	p=outCycQueue(q);

	inCycQueue(q,data1);
	lengthOfCycQueue(q);
	deleteCycQueue(q);

	return 0;
}

//  新增排队顾客
void addCustomer(CycQueue *q)
{
	DATA data;
	if(isFullCycQueue(q))
		return;
	else
	{
		data.num=++num;
		data.timeIn=time(NULL);
		inCycQueue(q,data);
	}
}

//  通知下一位顾客准备
void nextCustomer(CycQueue *q)
{
	DATA *p;
	if(!isEmptyQueue(q))
	{
		p=outCycQueue(q);
		printf("请顾客办理业务：序号：%d 时间：%ld\n",p->num,p->timeIn);
	}
	if(!isEmptyQueue(q))
	{
		p=getPeek(q);
		printf("请下一位顾客做好准备：序号：%d 时间：%ld\n",p->num,p->timeIn);

	}
}


int main(void)
{
	CycQueue *q;
	int i,n;
	char select;
	num=0;

	q=initCycQueue();

	do{
		printf("\n请选择操作：\n");
		printf("1：新到顾客\n");
		printf("2：下一个顾客\n");
		printf("3：退出\n\n");

		fflush(stdin);
		select=getchar();
		switch(select)
		{
			case '1':
			addCustomer(q);
			printf("共有%d位顾客在等候\n",lengthOfCycQueue(q));
			break;
			case '2':
			nextCustomer(q);
			printf("共有%d位顾客在等候\n",lengthOfCycQueue(q));
			break;
			case '0':
			break;
		}
	}while(select!='0');
	deleteCycQueue(q);
	return 0;
}


