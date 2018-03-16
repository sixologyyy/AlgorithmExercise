/*
二叉树的基本操作
1.初始化根节点
2.添加新节点，链表存储形式
3.返回左子节点
4.返回右子节点
5.检查二叉树是否为空
6.递归求二叉树深度
7.递归查找值为data的节点
8.清空二叉树

*** 9.递归先序遍历，非递归先序遍历
*** 10.递归中序遍历，非递归中序遍历
*** 11.递归后序遍历，非递归后序遍历(2种)
*** 12.按层遍历

13.操作函数，通过指向函数的指针调用
14.根据父节点的值向二叉树添加节点
15.先序建立二叉树，参数为指针的引用

*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 50

typedef struct LinkBinTree
{
	char data;
	struct LinkBinTree *left;
	struct LinkBinTree *right;
}LBT;

//--------基础函数--------

//  1.初始化根节点
LBT *initLinkBinTree()
{
	printf("初始化：");
	LBT *bt;
	bt=(LBT *)malloc(sizeof(LBT));
	if(bt!=NULL)
	{
		printf("输入根节点数据：\n");
		fflush(stdin);
		scanf("%c",&bt->data);
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
	if(bt==NULL)
	{
		printf("添加节点：父节点不存在\n");	
		return -1;
	}
	switch(c)
	{
		case 'l':
		case 'L':
		if(bt->left!=NULL)
		{
			printf("添加节点：左子节点不为空\n");
			return -6;
		}
		else
			bt->left=node;
		break;

		case 'r':
		case 'R':
		if(bt->right!=NULL) 
		{
			printf("添加节点：右子结点不为空\n"); 
			return -9;
		}else
		bt->right=node;
		break;
		default:
		printf("添加节点：参数错误\n");
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
LBT *findNodeByValue(LBT *bt,char data)
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

//  9.先序遍历，递归，oper()为指向函数的指针，代表对某一节点的操作
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

/*  9.5非递归先序遍历

	访问根p，入栈
	若p的左子节点不为空，入栈，p指向p左，直到p为空，  注意，因为是先序，父节点先入栈，然后是左子节点，所以入栈的时候就进行操作
	若p的左子节点为空，出栈，p指向p右，返回上一步
	直到p和栈都为空
*/
void DLRNoRecur(LBT *bt,void (*oper)(LBT *p))
{
	LBT *p=bt;
	LBT *stack[MAX];
	int top=0;

	while(p!=NULL||top>0)   //指针和栈不为空
	{
		while(p!=NULL)     //左子节点不为空时，入栈
		{
			stack[++top]=p;    //入栈，注意，入栈时就打印
			oper(p);
			p=p->left;
		}
		if(top>0)    //左子节点为空，出栈，并转向栈顶的右子节点
		{
			p=stack[top--];
			p=p->right;
		}

	}

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

/*  10.5非递归中序遍历

	访问根p，入栈
	若p的左子节点不为空，入栈，p指向p左，直到p为空
	若p的左子节点为空，出栈，p指向p右，返回上一步，   注意，因为是中序，出栈的时候父节点在栈顶，左节点已入栈，所以在出栈的时候进行操作
	直到p和栈都为空
*/
void LDRNoRecur(LBT *bt,void (*oper)(LBT *p))
{
	LBT *p=bt;
	LBT *stack[MAX];
	int top=0;

	while(p!=NULL||top>0)   //指针和栈不为空
	{
		while(p!=NULL)     //左子节点不为空时，入栈
		{
			stack[++top]=p;
			p=p->left;
		}
		if(top>0)    //左子节点为空，出栈，并转向栈顶的右子节点
		{
			p=stack[top--];
			oper(p);     //入栈，注意，出栈时才打印
			p=p->right;
		}

	}

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

/*  11.3非递归后序遍历（1

	访问根p，入栈
	若p的左子节点不为空，入栈，p指向p左，直到p为空
	若p的左子节点为空，出栈，p指向p右，返回上一步

	注意，因为是后序，所以必须访问完左中右节点之后才能进行操作，但是出栈时右节点还没入栈，父节点在栈顶，左节点已入栈
	所以要记录每个节点入栈的次数，当其第2次出现在栈顶的时候才说明左中右都已访问，才能进行操作
	即入栈的时候增加一个入栈次数的记录，第1次出栈的时候立即入栈，第2次的时候操作
	
	直到p和栈都为空
*/
void LRDNoRecur1(LBT *bt,void (*oper)(LBT *p))
{
	LBT *p=bt;

	struct tempLBT   //带入栈次数的指针栈
	{
		LBT *pp;
		int firstOut;
	}stack[MAX];

	int top=0;

	while(p!=NULL||top>0)   //指针和栈不为空
	{
		while(p!=NULL)     //左子节点不为空时，入栈
		{
			top++;
			stack[top].pp=p;
			stack[top].firstOut=1;  //栈里面的位置可能重复用到，要重置firstOut
			p=p->left;
		}
		if(top>0)    //左子节点为空，出栈，并转向栈顶的右子节点
		{
			p=stack[top].pp;
			if(stack[top].firstOut==1)    //第一次出现在栈顶，入栈再出栈，本程序没有定义push()和pop()，直接不需要操作
			{
				stack[top].firstOut=2;
				p=p->right;
			}
			else if(stack[top].firstOut==2)     //第二次出现在栈顶，出栈并打印
			{
				stack[top].firstOut=1;  //栈里面的位置可能重复用到，要重置firstOut
				oper(p);
				top--;
				p=NULL;   //p指向NULL进行下一次出栈，少了这一句会死循环
			}
			else
				printf("栈错误\n");
		}

	}

}

/*  11.6非递归后序遍历（2

	注意到后续遍历其实和先序遍历有一定的镜像关系，即右斜子树向下依次遍历，最后所有输出逆序
	可以在非递归先序遍历的基础上，把优先遍历左子节点改为右子节点，其他相同，此时输出的结果是逆序的后序遍历
	再设立一个栈，在每次入栈进行操作的时候记录该指针，最后统一输出，就可以实现逆序输出，也就是正确结果了
*/
void LRDNoRecur2(LBT *bt,void (*oper)(LBT *p))
{
	LBT *p=bt;
	LBT *stack[MAX];
	LBT *stackReverse[MAX];
	int top=0,topR=0;

	while(p!=NULL||top>0)   //指针和栈不为空
	{
		while(p!=NULL)     //左子节点不为空时，入栈
		{
			stack[++top]=p;    //入栈
			stackReverse[++topR]=p;     //注意，最后输出完全相反，所以用另一个栈暂时记录输出
			p=p->right;
		}
		if(top>0)    //左子节点为空，出栈，并转向栈顶的右子节点
		{
			p=stack[top--];
			p=p->left;
		}
	}
	while(topR)   //输出反栈
		oper(stackReverse[topR--]);

}

//  12.按层遍历二叉树，用循环队列实现
//    根节点先进队，然后循环操作直到队列为空，操作为：出队->出队节点的左右子节点依次进队
void levelOfLinkBinTree(LBT *bt,void (*oper)(LBT *p)) //按层遍历 
{
	LBT *p;
	LBT *q[MAX];  //定义一个循环队列，注意这是个指针数组，元素类型为（LBT *）

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

//  13.操作节点
void oper(LBT *p) //操作二叉树结点数据 
{
	printf("%c  ",p->data); //输出数据
	return;
}


//--------测试部分-------
//  14.向二叉树指定值的节点添加子节点
void addTreeNodeByParentValue(LBT *bt)
{
	LBT *node,*parent;
	char data,parentData;
	char select;

	node=(LBT *)malloc(sizeof(LBT));
	if(node==NULL)
	{
		printf("添加节点：内存分配失败\n");
		return;
	}

	printf("输入父节点值，插入值，左/右：\n");
	//fflush(stdin);
	scanf("\n%c,%c,%c",&parentData,&data,&select);

	if(select!='l'&&select!='r'&&select!='L'&&select!='R')
	{
		printf("添加节点：左/右参数无效(%c)\n",select);
		free(node);
		return;
	}

	parent=findNodeByValue(bt,parentData);
	if(parent==NULL)
	{
		printf("添加节点：父节点无效(%c)\n",parentData);
		free(node);
		return;
	}

	node->data=data;
	node->left=NULL;
	node->right=NULL;
	int t=addTreeNode(parent,node,select);
	if(t==1)
		printf("添加节点：成功\n");
	else
		printf("添加节点：失败(%d)\n",t);

}

//  15.先序建立二叉树，以#结束，递归
//注意，如果传参数用LBT *p，则函数内形参p为一指针，先指向待操作的树bt，在函数中改变p指向的内容（比如指向malloc()或者NULL），并不会改变bt指向的内容，也就是说此时并没有创建树
//而如果把树bt声明为全局变量，在函数内递归调用的时候，要先把全局树指向其左右子节点，再调用函数本身，此时返回发生了困难，在第一次返回递归的时候就产生了segment fault 11错误，原因未知
//故采用引用的方法，即参数是待操作树的引用或别名，对引用的操作就是对原变量的操作，由于要新建存储空间和保存指针，所以传入指针的引用，即 (TBT *) &bt
void createTreeByPreOrder(LBT *&bt)
{
	char ch;
	scanf("%c",&ch);

	if(ch!='#')
	{
		if(ch=='.')
		{
			//printf("return %c\n",ch);
			bt=NULL;
		}
		else
		{
			bt=(LBT *)malloc(sizeof(LBT));
			bt->data=ch;
			//printf("go %c\n",ch);

			//printf("l  ");
			createTreeByPreOrder(bt->left);
			//printf("inserted left of %c\n",bt->data);
			//printf("r  ");
			createTreeByPreOrder(bt->right);
			//printf("inserted right of %c\n",bt->data);
		}
	}
}

//主函数，测试功能
int main()
{
	LBT *bt=NULL;
	void (*oper1)(LBT *);   //指向函数的指针
	oper1=oper;

	//初始化根节点
	//bt=initLinkBinTree();

	//按父节点值添加节点
	//for(int i=0;i<10;i++)
	//	addTreeNodeByParentValue(bt);

	//先序建立二叉树
	createTreeByPreOrder(bt);

	printf("二叉树深度为：%d\n",depthOfLinkBinTree(bt));

	printf("先序遍历(递归)：\n");
	DLRRecursion(bt,oper1);
	printf("\n");

	printf("先序遍历(非递归)：\n");
	DLRNoRecur(bt,oper1);
	printf("\n");

	printf("中序遍历(递归)：\n");
	LDRRecursion(bt,oper1);
	printf("\n");

	printf("中序遍历(非递归)：\n");
	LDRNoRecur(bt,oper1);
	printf("\n");	

	printf("后序遍历(递归)：\n");
	LRDRecursion(bt,oper1);
	printf("\n");

	printf("后序遍历1(非递归)：\n");
	LRDNoRecur1(bt,oper1);
	printf("\n");

	printf("后序遍历2(非递归)：\n");
	LRDNoRecur2(bt,oper1);
	printf("\n");

	printf("按层遍历：\n");
	levelOfLinkBinTree(bt,oper1);

	clearLinkBinTree(bt);
}
