//装箱问题，有编号0~n-1的n个物品，体积分别为V0,V1...Vn-1，装入体积为V(V>Vi)的箱子，求最少的箱子数

#include <stdio.h>
#include <stdlib.h>

#define V 100

typedef struct box
{
	int no;
	int size;
	struct box* next;
}BOX;

void initList(BOX** H)            //H是链表头，每个结点的 no 是箱子的序号， size 是里面物品的总体积
{
	*H = (BOX*)malloc(sizeof(BOX));
	(*H)->no = 0;
	(*H)->size = 0;
	(*H)->next = NULL;
}

BOX* findNode(BOX* H, int volume, int v)       //寻找能放进去的物品，volume是当前已经装的体积，v是箱子的容积
{
	BOX *p = H->next;
	while (p != NULL)
	{
		if (p->size + volume <= v)
			break;
		p = p->next;
	}
	return p;
}

void addListTail(BOX *H, BOX *p)         //尾部添加节点
{
	BOX* tmp = H->next;
	BOX* q = H;

	while (tmp != NULL)
	{
		q = tmp;
		tmp = tmp->next;
	}
	q->next = p;
}

void printList(BOX *H)
{
	BOX* p = H->next;
	while (p != NULL)
	{
		printf("%d : %d\n", p->no, p->size);
		p = p->next;
	}
}

int putInBox(int volume[], int num, int v)            //装箱
{
	int count = 0;
	int i;
	BOX *H = NULL;

	initList(&H);

	for (i = 0; i < num; i++)
	{
		BOX *p = findNode(H, volume[i], v);
		if (p == NULL)
		{
			count++;
			p = (BOX*)malloc(sizeof(BOX));
			p->no = count;
			p->size = volume[i];
			p->next = NULL;
			addListTail(H, p);
		}
		else
		{
			p->size += volume[i];
		}
	}
	printList(H);
	return count;
}

int main(void)
{
	int count;
	int n, i;
	int volume[100];

	printf("输入物品个数：");
	scanf("%d", &n);
	printf("\n依次输入每个物品的体积：");
	for (i = 0; i < n; i++)
		scanf("%d", volume + i);

	printf("\n");
	count = putInBox(volume, n, V);
	printf("\n总共 %d 个箱子\n\n", count);

	return 1;
}