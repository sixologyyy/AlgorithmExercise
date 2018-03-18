//图的深度优先遍历（递归和非递归），广度优先遍历（非递归）

#include "MatrixGraph.cpp"

#define QUEUE_MAX 40   //图的最大顶点数   

typedef struct
{
	int data[QUEUE_MAX];
	int top;
}Stack;

typedef struct
{
	int data[QUEUE_MAX];
	int head;
	int tail;
}CycQueue;

//栈操作函数
void StackInit(Stack *S);
int StackIsEmpty(Stack *S);
int StackPush(Stack *S,int x);
int StackPop(Stack *S,int *x);

//队列操作函数
void QueueInit(CycQueue *Q);
int QueueIsEmpty(CycQueue Q);
int QueueIn(CycQueue *Q,int x);
int QueueOut(CycQueue *Q,int *x);

//图操作函数
void DFSRecur(MatrixGraph *G);
void DFSSub(MatrixGraph *G,int i);
void DFSNoRecurr(MatrixGraph *G);
void BFS(MatrixGraph *G);
void BFSSub(MatrixGraph *G,int v);

//--------栈--------
void StackInit(Stack *S)
{
	S->top=-1;
}

int StackPush(Stack *S,int x)
{
	if(S->top==QUEUE_MAX-1)
	{
		printf("stackoverflow\n");
		return 0;
	}
	S->top++;
	S->data[S->top]=x;
	return 1;
}

int StackPop(Stack *S,int *x)
{
	if(S->top==-1)
	{
		printf("stackisempty\n");
		return 0;
	}
	*x=S->data[S->top];
	S->top--;
	return 1;
}


//--------队列--------
void QueueInit(CycQueue *Q)
{
	Q->head=Q->tail=0;
}

int QueueIsEmpty(CycQueue Q)
{
	return Q.head==Q.tail;
}

int QueueIn(CycQueue *Q,int x)
{
	if((Q->tail+1)%QUEUE_MAX==Q->head)
		return 0;
	Q->data[Q->tail]=x;
	Q->tail=(Q->tail+1)%QUEUE_MAX;
	return 1;
}

int QueueOut(CycQueue *Q,int *x)
{
	if(Q->head==Q->tail)
		return 0;
	*x=Q->data[Q->head];
	Q->head=(Q->head+1)%QUEUE_MAX;
	return 1;
}

//--------图遍历---------
//  1.深度优先遍历
void DFSRecur(MatrixGraph *G)
{
	int v;
	for(v=0;v<G->VertexNum;v++)
		G->isTrav[v]=0;
	printf("递归深度优先遍历：\n");
	for(v=0;v<G->VertexNum;v++)
		if(!G->isTrav[v])
			DFSSub(G,v);
	printf("\n");
}

//  1.5子函数，递归深度优先遍历
//寻找v的第一个未访问的邻接节点，递归调用
void DFSSub(MatrixGraph *G,int v)
{
	int j;
	G->isTrav[v]=1;
	printf("->%c",G->Vertex[v]);

	for(j=0;j<G->VertexNum;j++)
		if(G->Edges[v][j]!=MAXVALUE && !G->isTrav[j])
			DFSSub(G,j);
}

//  2.非递归深度优先遍历（思路类似非递归先序遍历二叉树）
/*  构造一个栈，起始点v先入栈，当栈不为空时进行如下循环
     (1)获取栈顶元素v，不出栈
     (2)寻找v的第一个未访问的邻接节点，访问并入栈
     (3)若v没有未访问节点，说明已到最深处，出栈进行回溯
*/
void DFSNoRecurr(MatrixGraph *G)
{
	Stack S;
	StackInit(&S);
	
	int v=0;
	int j=0;   //邻接点的序号

	for(v=0;v<G->VertexNum;v++)
		G->isTrav[v]=0;
	printf("非递归深度优先遍历：\n");

	//第一个节点入栈
	StackPush(&S,v);
	while(S.top!=-1)   //栈不为空时循环处理
	{
		//取栈顶元素，不出栈
		v=S.data[S.top];
		for(j=0;j<G->VertexNum;j++)   //遍历节点，寻找v的第一个未访问的邻接点，访问该节点，记录访问标志，入栈
			if(G->isTrav[j]!=1&&G->Edges[v][j]!=MAXVALUE)   
			{
				printf("->%c",G->Vertex[j]);
				G->isTrav[j]=1;
				StackPush(&S,j);
				break;
			}
		if(j==G->VertexNum)    //当前节点没有未访问的邻接点，说明已经到最深处，出栈进行回溯
			StackPop(&S,&j);

	}
	printf("\n");
}

//  2.广度优先遍历（递归法要在队列基础上改造，不够简洁，故舍弃）
void BFS(MatrixGraph *G)
{
	int v;
	for(v=0;v<G->VertexNum;v++)
		G->isTrav[v]=0;
	printf("广度优先遍历：\n");
	for(v=0;v<G->VertexNum;v++)
		if(G->isTrav[v]==0)
			BFSSub(G,v);
	printf("\n");
}

//  2.5子函数，队列实现广度优先遍历
/*
	第一个节点入队，当队列不为空时循环进行如下操作：
	（1）队首节点v出队
	（2）访问i的所有未访问的邻接节点，依次入队
*/
void BFSSub(MatrixGraph *G,int v)
{
	int i,j;
	CycQueue Q;
	QueueInit(&Q);

	G->isTrav[v]=1;
	printf("->%c",G->Vertex[v]);

	//第一个节点入队
	QueueIn(&Q,v);
	while(QueueIsEmpty(Q)==0)
	{
		QueueOut(&Q,&i);
		for(j=0;j<G->VertexNum;j++)
			if(G->isTrav[j]==0&&G->Edges[i][j]!=MAXVALUE)
			{
				QueueIn(&Q,j);
				printf("->%c",G->Vertex[j]);
				G->isTrav[j]=1;
			}
	}
}

//--------测试部分--------
int main()
{
    MatrixGraph G; //定义保存邻接矩阵结构的图 
    int i,j;
    printf("输入生成图的类型(0:无向图,1:有向图):");
    scanf("%d",&G.GraphType); //图的种类
    printf("输入图的顶点数量和边数量:");
    scanf("%d,%d",&G.VertexNum,&G.EdgeNum); //输入图顶点数和边数 
    for(i=0;i<G.VertexNum;i++)  //清空矩阵 
        for(j=0;j<G.VertexNum;j++)
            G.Edges[i][j]=MAXVALUE; //设置矩阵中各元素的值为最大值         
    CreateMGraph(&G); //创建用邻接表保存的图 
    printf("邻接矩阵数据如下:\n");
    PrintMGraph(&G);

    DFSRecur(&G);
    DFSNoRecurr(&G);
    BFS(&G);
    return 0;
}