/*

中序线索二叉树的基本操作
1.对二叉树中序线索化，生成一个头结点
  子函数，递归中序线索化
2.寻找后继节点
3.寻找前驱节点
4.中序遍历线索二叉树(调用后继函数)，逆序中序遍历线索二叉树(调用前驱函数)

*/
#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef enum    //枚举值：子树或者线索
{ subtree, thread } NodeFlag;

typedef struct ThreadBinTree
{
	char data;
	NodeFlag lflag;
	NodeFlag rflag;
	struct ThreadBinTree *left;
	struct ThreadBinTree *right;
}TBT;


//--------线索二叉树--------
void initLDRThreadBinTree(TBT *,TBT *&);
void buildLDRThreadBinTree(TBT *,TBT *&);
TBT *findNextOfThreadBinTree(TBT *);
TBT *findPreOfThreadBinTree(TBT *);
void checkLDRThreadBinTree(TBT *,void (*oper)(TBT *));

//  1.对二叉树进行中序线索化
//中序遍历二叉树bt，将其中序线索化，head指向头结点
void initLDRThreadBinTree(TBT *bt,TBT *&head)
{
	//初始化线索链表，为其建立头结点
	head =(TBT *)malloc(sizeof(TBT));

	head->lflag=subtree;
	head->rflag=thread;

	if(bt==NULL)
	{
		head->left=head;
		head->right=head;  //右指针回指
	}
	else
	{
		head->left=bt;
		TBT *previous=head;

		buildLDRThreadBinTree(bt,previous);

		//此时previous应该指向最后一个节点，将其回指到头节点
		previous->rflag=thread;
		previous->right=head;    //最后一个节点的右指针回指
		head->right=previous;    //头结点的右指针指向最后一个节点
	}
}

//子函数，递归中序线索化
//步骤：递归调用左子节点-->配置左子节点-->配置前驱的右子节点-->更新前驱-->递归调用右子节点
void buildLDRThreadBinTree(TBT *bt,TBT *&previous)
{
	if(bt)
	{
		buildLDRThreadBinTree(bt->left,previous);    //递归调用，将左子树线索化
		if(bt->left==NULL)          //若当前左子节点为空
		{
			bt->lflag=thread;       //设置左标志为线索，左子节点为前驱
			bt->left=previous;
		}
		else
			bt->lflag=subtree;      //若左子节点不为空，左标志为子树

		if(previous->right==NULL)   //若前驱的右子节点为空
		{
			previous->rflag=thread;  //设置前驱的右标志为线索，右子节点为当前节点
			previous->right=bt;
		}
		else
			previous->rflag=subtree;  //若前驱右子节点不为空，右标志为子树

		previous=bt;
		buildLDRThreadBinTree(bt->right,previous);   //递归调用，将右子树线索化
	}
}

//  2.查找后继节点
TBT *findNextOfThreadBinTree(TBT *bt)
{
	TBT *nextNode;
	if(!bt)
		return NULL;
	if(bt->rflag==thread)   //右子树为线索
		return bt->right;   //返回线索
	else
	{
		nextNode=bt->right;   //从当前节点的右子树开始查找
		while(nextNode->lflag==subtree)   //不断向左
			nextNode=nextNode->left;
		return nextNode;      //返回右子树最左下方的节点
	}
}

//  3.查找前驱节点
TBT *findPreOfThreadBinTree(TBT *bt)
{
	TBT *preNode;
	if(!bt)
		return NULL;
	if(bt->lflag==thread)    //左子树为线索
		return bt->left;
	else
	{
		preNode=bt->left;    //从当前节点的左子树开始查找，找到最右下的节点
		while(preNode->rflag==subtree)
			preNode=preNode->right;
		return preNode;
	}
}

//  4.遍历线索二叉树
void checkLDRThreadBinTree(TBT *head,void (*oper)(TBT *p))
{
	TBT *p=head->left;

	while(p!=head)
	{
		while(p->lflag==subtree)   //寻找最左下方节点，即第一个节点
			p=p->left;

		do
		{
			oper(p);
			p=findNextOfThreadBinTree(p);
		}while(p!=head);
	}
}

//  逆序的中序遍历，用findPre函数
void checkReverseLDRThreadBinTree(TBT *head,void (*oper)(TBT *p))
{
	TBT *p=head->right;

	while(p!=head)
	{
		while(p->rflag==subtree)   //寻找最右下方节点，即最后一个节点
			p=p->right;

		do
		{
			oper(p);
			p=findPreOfThreadBinTree(p);
		}while(p!=head);
	}
}

//  5.操作节点
void oper(TBT *p) //操作二叉树结点数据 
{
	printf("%c  ",p->data); //输出数据
	return;
}


//--------测试部分-------
//  先序建立二叉树，以#结束，递归
void createTreeByPreOrder(TBT *&bt)
{
	char ch;
	scanf("%c",&ch);

	if(ch!='#')
	{
		if(ch=='.')
		{
			bt=NULL;
		}
		else
		{
			bt=(TBT *)malloc(sizeof(TBT));
			bt->data=ch;

			createTreeByPreOrder(bt->left);
			createTreeByPreOrder(bt->right);
		}
	}
}


void levelOfLinkBinTree(TBT *bt,void (*oper)(TBT *p)) //按层遍历 
{
	TBT *p;
	TBT *q[MAX];  //定义一个循环队列，注意这是个指针数组，元素类型为（TBT *）

	int head=0,tail=0;//队首、队尾序号 
	if(bt)     
	{
		tail=(tail+1)%MAX;  //入队 
		q[tail] = bt;
	}
	while(head!=tail)  //队列不为空，进行循环 
	{
		head=(head+1)%MAX;  //出队，head指向队首元素前一个，所以先+1
		p=q[head];

		oper(p);//处理队首元素 

		if(p->left!=NULL) //左子节点先入队
		{
			tail=(tail+1)%MAX; 
			q[tail]=p->left;
		}

		if(p->right!=NULL) //右子节点后入队 
		{
			tail=(tail+1)%MAX;//计算循环队列的队尾序号 
			q[tail]=p->right;//将右子树指针进队 
		}
	}
	printf("\n");
	return; 
}

//主函数，测试功能
int main()
{
	TBT *bt=NULL;
	TBT *head=NULL;

	void (*oper1)(TBT *);   //指向函数的指针
	oper1=oper;

	//先序建立二叉树
	createTreeByPreOrder(bt);

	printf("层次遍历二叉树：\n");
	levelOfLinkBinTree(bt,oper1);

	initLDRThreadBinTree(bt,head);

	printf("中序遍历线索二叉树：\n");
	checkLDRThreadBinTree(head,oper1);
	printf("\n");

	printf("逆序的中序遍历线索二叉树：\n");
	checkReverseLDRThreadBinTree(head,oper1);
	printf("\n");

}
