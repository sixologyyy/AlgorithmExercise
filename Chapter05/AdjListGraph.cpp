//图的邻接表表示法

#include <stdio.h>
#include <stdlib.h>

#define VERTEX_MAX 20   //图的最大顶点数

typedef struct edgeNode   
{
    int Vertex; //顶点信息(序号或字母) 
    int weight; //权值
    struct edgeNode *next; //指向下一个顶点指针 (当前顶点和指向的下一顶点构成一条边) 
}EdgeNode; //邻接表边结构 

typedef struct   
{
    EdgeNode* AdjList[VERTEX_MAX]; //指针数组，指向每个顶点的指针
    int VextexNum,EdgeNum; //图的顶点的数量和边的数量  
    int GraphType; //图的类型(0:无向图，1:有向图)
}ALGraph;  //图的结构 

void CreateALGraph(ALGraph *G); //生成图的邻接表   
void PrintALGraph(ALGraph *G); //输出邻接表

void CreateALGraph(ALGraph *G)  //构造邻接表结构图
{
    int i,weight;
    int start,end;
    EdgeNode *s;
    for(i=1;i<=G->VextexNum;i++)//将图中各顶点指针清空 
        G->AdjList[i]=NULL;
    for(i=1;i<=G->EdgeNum;i++) //输入各边的两个顶点 
    {
        getchar();
        printf("第%d条边:",i); 
        scanf("%d,%d,%d",&start,&end,&weight); //输入边的起点和终点

        s=(EdgeNode *)malloc(sizeof(EdgeNode)); //申请保存一个顶点的内存 

        s->next=G->AdjList[start]; //插入到邻接表中，AdjList[start]为最新插入的start顶点开始的边
        s->Vertex=end; //保存终点编号
        s->weight=weight; //保存权值 
        G->AdjList[start]=s; //邻接表对应顶点存入最新插入的边

        if(G->GraphType==0) //若是无向图，再插入到终点的边链中
        {
            s=(EdgeNode *)malloc(sizeof(EdgeNode)); //申请保存一个顶点的内存 
            s->next=G->AdjList[end];
            s->Vertex=start;
            s->weight=weight;
            G->AdjList[end]=s;
        }
    }   
} 
void PrintALGraph(ALGraph *G)
{
    int i;
    EdgeNode *s;
    for(i=1;i<=G->VextexNum;i++)
    {
        printf("顶点%d",i); 
        s=G->AdjList[i];
        while(s)
        {
            printf("->%d(%d)",s->Vertex,s->weight); 
            s=s->next;
        }
        printf("\n");
    }
}


int main()
{
    ALGraph G; //定义保存邻接表结构的图 
    printf("输入生成图的类型(0:无向图,1:有向图):");
    scanf("%d",&G.GraphType); //图的种类
    printf("输入图的顶点数量和边数量:");
    scanf("%d,%d",&G.VextexNum,&G.EdgeNum); //输入图顶点数和边数 
    printf("输入构成各边的两个顶点及权值(用逗号分隔):\n"); 
    CreateALGraph(&G); //生成邻接表结构的图
    printf("输出图的邻接表:\n");
    PrintALGraph(&G); 
    return 0;
}
