#include <stdio.h>
#include <stdlib.h>

#define QUEUE_MAX 50

typedef struct LinkBinTree
{
	int data;
	struct LinkBinTree *left;
	struct LinkBinTree *right;
}LBT;

//--------基础函数--------

//  1.初始化
LBT *initLinkBinTree()
{
	printf("初始化：");
	LBT *bt;
	bt=(LBT *)malloc(sizeof(LBT));
	if(bt!=NULL)
	{
		printf("输入根节点数据：\n");
		scanf("%d",&bt->data);
		bt->left=NULL;
		bt->right=NULL;

		printf("成功\n");
		return bt;
	}
	printf("内存分配失败\n");
	return NULL;
}

//  2.添加新节点,bt为父节点，node为子节点，n=l为添加左节点，r为右节点
int addTreeNode(LBT *bt,LBT *node,char c) 
{
	printf("添加节点：");
	if(bt==NULL)
	{
		printf("父节点不存在\n");	
		return -1;
	}
	switch(c)
	{
		case 'l':
		case 'L':
		if(bt->left!=NULL)
		{
			printf("左子节点不为空\n");
			return -6;
		}
		else
			bt->left=node;
		break;

		case 'r':
		case 'R':
		if(bt->right!=NULL) 
		{
			printf("右子结点不为空\n"); 
			return -9;
		}else
		bt->right=node;
		break;
		default:
		printf("参数错误\n");
		return -10;		
	}
	return 1;
}

//  3.返回左子节点
LBT *leftSonNode(LBT *bt)
{
	if(bt)
		return bt->left;
	else
		return NULL;
}

//  4.返回右子结点 
LBT *rightSonNode(LBT *bt)
{
	if(bt)
		return bt->right;
	else
		return NULL;
}

//  5.检查二叉树是否为空，为空则返回1,否则返回0 
int isEmptyLinkBinTree(LBT *bt)
{
	if(bt)
		return 0;
	else
		return 1;
}

//  6.求二叉树的深度，递归方法
int depthOfLinkBinTree(LBT *bt)
{
	int dep1,dep2;
	if(bt==NULL)
		return 0; //对于空树，深度为0
	else
	{
		dep1 = depthOfLinkBinTree(bt->left); //左子树深度 (递归调用)
		dep2 = depthOfLinkBinTree(bt->right); //右子树深度 (递归调用)
		if(dep1>dep2)
			return dep1 + 1; 
	else
		return dep2 + 1; 
	} 
} 

//  7.在二叉树中查找值为data的结点,递归查找
LBT *findNodeByValue(LBT *bt,int data)
{
	LBT *p;
	if(bt==NULL)
		return NULL;
	else
	{
		if(bt->data==data)
			return bt;
		// 分别向左右子树递归查找 
		else
		{
			if(p=findNodeByValue(bt->left,data))
				return p;
			else if(p=findNodeByValue(bt->right, data)) 
				return p;
			else
				return NULL; 
		} 
	} 
} 

//  8.清空二叉树
void clearLinkBinTree(LBT *bt)
{
	if(bt)
	{
		clearLinkBinTree(bt->left); //清空左子树 
		clearLinkBinTree(bt->right);//清空右子树 
		free(bt);//释放当前结点所占内存 
		bt=NULL;
	}
	return; 
}

//  9.先序遍历二叉树，递归方法，oper()为指向函数的指针，代表对某一节点的操作
//左斜子树向下依次遍历
void DLRRecursion(LBT *bt,void (*oper)(LBT *p))
{     
	if(bt)
	{
		oper(bt); //处理结点的数据 
		DLRRecursion(bt->left,oper);
		DLRRecursion(bt->right,oper);
	}
	return; 
}

//  10.中序遍历，递归
//下方投影
void LDRRecursion(LBT *bt,void(*oper)(LBT *p)) 
{
	if(bt) 
	{
		LDRRecursion(bt->left,oper);
		oper(bt);
		LDRRecursion(bt->right,oper);
	}
	return; 
}

//  11.后续遍历，递归
//逆序的(右斜子树向下依次遍历)
void LRDRecursion(LBT *bt,void (*oper)(LBT *p))
{
	if(bt)
	{
		LRDRecursion(bt->left,oper);
		LRDRecursion(bt->right,oper);
		oper(bt);
	}
	return;
}

//  12.操作节点
void oper(LBT *p) //操作二叉树结点数据 
{
	printf("%d  ",p->data); //输出数据
	return;
}

//  13.按层遍历二叉树，用循环队列实现
//    根节点先进队，然后循环操作直到队列为空，操作为：出队->出队节点的左右子节点依次进队
void levelOfLinkBinTree(LBT *bt,void (*oper)(LBT *p)) //按层遍历 
{
	LBT *p;
	LBT *q[QUEUE_MAX];  //定义一个循环队列，注意这是个指针数组，元素类型为（LBT *）

	int head=0,tail=0;//队首、队尾序号 
	if(bt)     
	{
		tail=(tail+1)%QUEUE_MAX;  //入队 
		q[tail] = bt;
	}
	while(head!=tail)  //队列不为空，进行循环 
	{
		head=(head+1)%QUEUE_MAX;  //出队，head指向队首元素前一个，所以先+1
		p=q[head];

		oper(p);//处理队首元素 

		if(p->left!=NULL) //左子节点先入队
		{
			tail=(tail+1)%QUEUE_MAX; 
			q[tail]=p->left;
		}

		if(p->right!=NULL) //右子节点后入队 
		{
			tail=(tail+1)%QUEUE_MAX;//计算循环队列的队尾序号 
			q[tail]=p->right;//将右子树指针进队 
		}
	}
	printf("\n");
	return; 
}

//--------测试部分-------
//  向二叉树指定值的节点添加子节点
void addTreeNodeByParentValue(LBT *bt)
{
	LBT *node,*parent;
	int data,parentData;
	char select;

	node=(LBT *)malloc(sizeof(LBT));
	if(node==NULL)
	{
		printf("添加节点：内存分配失败\n");
		return;
	}

	printf("输入父节点值，插入值，左/右：\n");
	fflush(stdin);
	scanf("%d,%d,%c",&parentData,&data,&select);

	if(select!='l'&&select!='r'&&select!='L'&&select!='R')
	{
		printf("添加节点：左/右参数无效\n");
		free(node);
		return;
	}

	parent=findNodeByValue(bt,parentData);
	if(parent==NULL)
	{
		printf("添加节点：父节点无效\n");
		free(node);
		return;
	}

	node->data=data;
	node->left=NULL;
	node->right=NULL;
	data=addTreeNode(parent,node,select);
	if(data==1)
		printf("添加节点：成功\n");
	else
		printf("添加节点：失败(%d)\n",data);

}

//主函数，测试功能
int main()
{
	LBT *bt=NULL;
	void (*oper1)();   //指向函数的指针
	oper1=oper;

	bt=initLinkBinTree();
	for(int i=0;i<10;i++)
		addTreeNodeByParentValue(bt);

	printf("二叉树深度为：%d\n",depthOfLinkBinTree(bt));

	printf("先序遍历：\n");
	DLRRecursion(bt,oper1);
	printf("\n");
	printf("中序遍历：\n");
	LDRRecursion(bt,oper1);
	printf("\n");
	printf("后序遍历：\n");
	LRDRecursion(bt,oper1);
	printf("\n");

	printf("按层遍历：\n");
	levelOfLinkBinTree(bt,oper1);

	clearLinkBinTree(bt);
}
