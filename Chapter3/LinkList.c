/*实现链表的基本操作，包括

1.初始化链表
2.创建链表
3.打印链表
4.清除链表
5.返回链表长度
6.检查链表是否为空
7.返回第pos处的元素
8.返回指定值的元素
9.插入元素
10.删除元素
11.向有序链表中插入元素
12.链表排序

main函数测试各项功能
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Node
{
	char name[10];
	int number;
	struct Node *next;
} Node;

//  1.初始化链表，置链表头指针为空
void initList(Node **pNode)
{
	*pNode=NULL;
	printf("初始化成功\n");
}

//  2.创建链表，输入number-999时终止输入，do while(1)比 while简洁，不过要记得跳出
Node *createList(Node *pHead)
{
	Node *p1;    //p1指向新读入的节点
	Node *p2;    //p2指向前一个p1，即表尾
	int number;

	do   //不断读入新节点
	{
		p1=(Node *)malloc(sizeof(Node));
		if(p1==NULL)
		{
			printf("内存分配失败\n");
			exit(0);
		}

		scanf("%d",&number);
		if(number==-999)  //结束，跳出
		{
			break;
		}
		else
		{
			p1->number=number;
			gets(p1->name);
			p1->next=NULL;

			if(pHead==NULL)  //空表
				pHead=p2=p1;
			else             //非空表
			{
				p2->next=p1;   //p2指向当前已加入的节点，即表尾
				p2=p1;
			}
		}
	}while(1);
	printf("创建链表成功\n");
	return pHead;
}

//  3.打印链表
void printList(Node *pHead)
{
	if(pHead==NULL)
		printf("打印：链表为空\n");
	else
	{
		printf("打印：\n");
		while(pHead!=NULL)
		{
			printf("序号：%d 姓名：%s\n",pHead->number,pHead->name);
			pHead=pHead->next;
		}
		printf("\n");
	}
}

//  4.清除链表，释放所有节点，使之成为一个空链表
Node *clearList(Node *pHead)
{
	Node *pNext;

	if(pHead==NULL)
	{
		printf("清除：链表为空\n");
		return pHead;
	}
	while(pHead->next!=NULL)
	{
		pNext=pHead->next;
		free(pHead);
		pHead=pNext;
	}
	free(pHead);
	pHead=NULL;     //free之后一定要让指针指向空
	printf("清除：成功了\n");
	return pHead;
}

//  5.返回链表长度
int lengthOfList(Node *pHead)
{
	int count=0;

	while(pHead!=NULL)
	{
		count++;
		pHead=pHead->next;
	}
	printf("链表长度：%d\n",count);
	return count;
}

//  6.检查链表是否为空
int isEmptyList(Node *pHead)
{
	if(pHead==NULL) 
	{
		printf("判断链表为空：是\n");
		return 1;
	}
	else
	{
		printf("判断链表为空：否\n"); 
		return 0;
	}
}

//  7.返回链表中第pos个元素的指针,pos从0开始
Node *getElementByPos(Node *pHead,int pos)
{
	if(pos<0)
	{
		printf("指定位置元素：pos值非法\n");
		return NULL;
	}
	if(pHead==NULL)
	{
		printf("指定位置元素：链表为空\n");
		return NULL;
	}
	while(pos>0)  //按位置寻找该节点
	{
		pos--;	
		if(pHead->next!=NULL)
			pHead=pHead->next;
		else
		{
			printf("指定位置元素：pos越界\n");
			return NULL;
		}
	}
	printf("指定位置元素：序号：%d 姓名：%s\n",pHead->number,pHead->name);
	return pHead;
}

//  8.指定元素值寻找在链表中的位置
Node *getElementByValue(Node *pHead,Node pValue)
{
	int count=0;
	if(pHead==NULL)
	{
		printf("查找元素：链表为空\n");
		return NULL;
	}
	while(pHead!=NULL)
	{
		if(pHead->number==pValue.number&&strcmp(pHead->name,pValue.name)==0)
		{
			printf("查找元素：序号：%d 姓名：%s 位置：%d\n",pValue.number,pValue.name,count);
			return pHead;
		}
		else
		{
			count++;
			pHead=pHead->next;
		}
	}
	printf("查找元素：没找到\n");
	return NULL;
}

//  9.向链表中插入一个元素，位置在pos的前面，pos从0开始，返回链表头
Node *insertElement(Node *pHead,Node pValue,int pos)   //pValue如果用指针会在多次插入时出错
{
	int pospos=pos;
	Node *p=(Node *)malloc(sizeof(Node));
	*p=pValue;     //p指向待插入元素
	Node *pf=pHead;    //pf记录插入位置的前一个节点，即pf->待插入>pos处

	if(pHead==NULL)
	{
		printf("插入元素：链表为空，已插入\n");
		pHead=p;
		pHead->next=NULL;
		return pHead;
	}
	if(pos<0)
	{
		printf("插入元素：pos值非法\n");
		return pHead;
	}

	if(pos==0)     //插入在最前面
	{
		printf("插入元素：成功插入在第%d个前面\n",pospos);
		p->next=pHead;
		return p;
	}

	while(pos>1)   //按位置寻找元素，注意，pos不能减到0，减到1是为了指向pos的前驱节点
	{
		pf=pf->next;
		if(pf->next==NULL)   //pf指向前驱，当while走完时指向pos前驱，且pf->next指向pos，此处提前判断是否越界
		{
			printf("插入元素：pos越界，已插入末尾\n");
			pf->next=p;
			p->next=NULL;
			return pHead;
		}
		pos--;
	}

	//此时pos=1，pf指向pos的前驱
	p->next=pf->next;
	pf->next=p;
	printf("插入元素：成功插入在第%d个前面\n",pospos);
	return pHead;
}

//  10.在链表中删除一个元素，位置在pos，pos从0开始，返回链表头
Node *deleteElement(Node *pHead,int pos)
{
	int pospos=pos;
	Node *pf=pHead;    //pf记录插入位置的前一个节点

	if(pHead==NULL)
	{
		printf("删除元素：链表为空\n");
		return pHead;
	}
	if(pos<0)
	{
		printf("删除元素：pos值非法\n");
		return pHead;
	}

	if(pos==0)     //删除最前面
	{
		printf("删除元素：成功删除第%d个元素\n",pospos);
		pHead=pHead->next;
		return pHead;
	}

	while(pos>1)   //按位置寻找元素，注意，pos不能减到0，减到1是为了指向pos的前驱节点
	{
		pf=pf->next;
		if(pf->next==NULL)   //pf指向前驱，当while走完时指向pos前驱，且pf->next指向pos，此处提前判断是否越界
		{
			printf("删除元素：pos越界，无操作\n");
			return pHead;
		}
		pos--;
	}

	//此时pos=1，pf指向pos的前驱
	Node *q=pf->next;
	pf->next=q->next;
	free(q);
	q=NULL;

	printf("删除元素：成功删除第%d个元素\n",pospos);
	return pHead;
}

//  11.假设链表为降序，按序号大小插入新元素
Node *insertSeq(Node *pHead,Node pValue)
{
	int pos=1;     //pos为第一个小于number的元素位置
	Node *p=(Node *)malloc(sizeof(Node));
	*p=pValue;       //p指向待插入元素
	Node *pf=pHead;    //pf记录插入位置的前一个节点，即pf->待插入>pos处

	if(pHead==NULL)
	{
		printf("顺序插入元素：链表为空，已插入\n");
		pHead=p;
		pHead->next=NULL;
		return pHead;
	}

	if(p->number>pHead->number)     //插入在最前面
	{
		printf("顺序插入元素：成功插入在第%d个前面\n",0);
		p->next=pHead;
		return p;
	}

	while(pf->next!=NULL&&p->number<pf->next->number)   //按number寻找元素,寻找第一个小于number的元素(pf->next)，位于pos，在它前面插入，所以要记录前驱pf
	{
		pf=pf->next;
		pos++;
	}

	if(pf->next==NULL)   //插在最后,此时pos已经移到了最后一个元素+1处
	{
		pf->next=p;
		p->next=NULL;
		printf("插入元素：成功插入在第%d个(最后)\n",pos);
		return pHead;
	}

	//此时pf->number > pValue.number > pf->next->number
	p->next=pf->next;
	pf->next=p;
	printf("插入元素：成功插入在第%d个前面\n",pos);
	return pHead;
}

//  12.对链表根据number进行降序排序，存在新的链表pSorted中
Node *sortLinkList(Node *pHead, Node *pSorted)
{
	pSorted=NULL;
	if(pHead==NULL)
	{
		printf("链表排序：链表为空\n");
		return pSorted;
	}
	while(pHead->next!=NULL)
	{
		pSorted=insertSeq(pSorted,*pHead);
		pHead=pHead->next;
	}
	pSorted=insertSeq(pSorted,*pHead);
	printf("链表排序：完成\n");
	return pSorted;
}

int main(void)
{
	Node *list=NULL;
	Node *listSorted=NULL;
	int length=0;

	Node node1={"sxy",10};
	Node node2={"yyy",0};
	Node node3={"rda",5};
	Node node4={"zpy",66};
	Node node5={"qaz",8};
	Node node6={"wsx",3};
	Node node7={"edc",-10};
	//printf("%d %s %d %s %d %s\n",node1.number,node1.name,node2.number,node2.name,node3.number,node3.name);

	initList(&list);
	printList(list);

	list=createList(list);
	printList(list);

	listSorted=sortLinkList(list,listSorted);
	printList(listSorted);

	length=lengthOfList(list);
	isEmptyList(list);

	getElementByPos(list,2);
	getElementByPos(list,-1);
	getElementByPos(list,4);

	getElementByValue(list,node1);
	getElementByValue(list,node2);
	getElementByValue(list,node3);

	list=insertElement(list,node4,-1);
	printList(list);
	list=insertElement(list,node4,0);
	printList(list);
	list=insertElement(list,node4,3);
	printList(list);
	list=insertElement(list,node4,10);
	printList(list);

	getElementByValue(list,node4);

	list=deleteElement(list,-1);
	printList(list);
	list=deleteElement(list,0);
	printList(list);
	getElementByValue(list,node4);
	list=deleteElement(list,2);
	printList(list);
	getElementByValue(list,node4);
	list=deleteElement(list,10);
	printList(list);
	list=deleteElement(list,3);
	printList(list);
	getElementByValue(list,node4);

	list=insertSeq(list,node4);
	printList(list);
	list=insertSeq(list,node5);
	printList(list);
	list=insertSeq(list,node6);
	printList(list);
	list=insertSeq(list,node7);
	printList(list);

	list=clearList(list);
	printList(list);
	isEmptyList(list);

	list=clearList(listSorted);

	return 0;
}
