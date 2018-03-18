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
int StackPush(Stack *S);
int StackPop(Stack *S);

//队列操作函数
void QueueInit(CycQueue *Q);
int QueueIsEmpty(CycQueue *Q);
int QueueIn(CycQueue *Q,int x);
int QueueOut(CycQueue *Q,int *x);

//图操作函数
void DFSRecur(MatrixGraph *G);
void DFSSub(MatrixGraph *G,int i);
void DFSNoRecurr(MatrixGraph *G);
void BFS(MatrixGraph *G);
void BFSsub(MatrixGraph *G,int i);

//--------栈--------
void StackInit(Stack *S)
{
	S->top=-1;
}

int StackPush(Stack *S,int x)
{
	if(S->top==QUEUE_MAX-1)
		return 0;
	S->data[S->++top]=x;
}

int StackPop(Stack *S,int *x)
{
	if(S->top==-1)
		return 0;
	*x=S->data[S->top];
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
//深度优先遍历
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

//子函数，递归深度优先遍历
void DFSSub(MatrixGraph *G,int v)
{
	int j;
	G->isTrav[v]=1;
	printf("->%c",G->Vertex[v]);

	for(j=0;j<G->VertexNum;j++)
		if(G->Edges[v][j]!=MAXVALUE && !G->isTrav[j])
			DFSSub(G,j);
}

//非递归深度优先遍历
void DFSNoRecurr(MatrixGraph *G)
{
	Stack S;
	StackInit(&S);
	
	int v=0;
	int near=0;   //邻接点的序号

	for(v=0;v<G->VertexNum;v++)
		G->isTrav[v]=0;
	printf("非递归深度优先遍历：\n");

	//第一个节点入栈
	StackPush(&S,G->Vertex[0]);
	while(S.top!=-1)   //栈不为空时循环处理
	{
		//取栈顶元素，不出栈
		v=S.data[S.top];
		//如果节点未访问，则访问
		if(G->isTrav[i]!=0)
		{
			G->isTrav[i]=1;
			printf("->%c",G->Vertex[i]);			
		}
		//寻找第一个邻接节点
		for(near=0;near<G->VertexNum;near++)
			if(G->Edges[i][near]!=MAXVALUE)
				break;
		i=G->Verted[near];
		while(i!=VertexNum)
		{
			if(isTrav[i]!=0)
				StackPush(&S,&G->Verted[i]);
			i=Nextadj
		}

	}
	printf("\n");
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
    return 0;
}