//װ�����⣬�б��0~n-1��n����Ʒ������ֱ�ΪV0,V1...Vn-1��װ�����ΪV(V>Vi)�����ӣ������ٵ�������

#include <stdio.h>
#include <stdlib.h>

#define V 100

typedef struct box
{
	int no;
	int size;
	struct box* next;
}BOX;

void initList(BOX** H)            //H������ͷ��ÿ������ no �����ӵ���ţ� size ��������Ʒ�������
{
	*H = (BOX*)malloc(sizeof(BOX));
	(*H)->no = 0;
	(*H)->size = 0;
	(*H)->next = NULL;
}

BOX* findNode(BOX* H, int volume, int v)       //Ѱ���ܷŽ�ȥ����Ʒ��volume�ǵ�ǰ�Ѿ�װ�������v�����ӵ��ݻ�
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

void addListTail(BOX *H, BOX *p)         //β����ӽڵ�
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

int putInBox(int volume[], int num, int v)            //װ��
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

	printf("������Ʒ������");
	scanf("%d", &n);
	printf("\n��������ÿ����Ʒ�������");
	for (i = 0; i < n; i++)
		scanf("%d", volume + i);

	printf("\n");
	count = putInBox(volume, n, V);
	printf("\n�ܹ� %d ������\n\n", count);

	return 1;
}