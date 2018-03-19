/*

floyd算法求任意两点间的最短路径

*/

#include "MatrixGraph.cpp"

void Floyd(MatrixGraph G,int (*path)[VERTEX_MAX],int (*dis)[VERTEX_MAX])
{
    int i,j,k;
    for(i=0;i<G.VertexNum;i++)
        for(j=0;j<G.VertexNum;j++)
        {
            path[i][j]=-1;
            if(i!=j)
                dis[i][j]=G.Edges[i][j];
            else
                dis[i][j]=0;
        }
    for(k=0;k<G.VertexNum;k++)
        for(i=0;i<G.VertexNum;i++)
            for(j=0;j<G.VertexNum;j++)
                if(dis[i][j]>dis[i][k]+dis[k][j])
                {
                    path[i][j]=k;
                    dis[i][j]=dis[i][k]+dis[k][j];
                }
}

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

    int path[VERTEX_MAX][VERTEX_MAX];
    int dis[VERTEX_MAX][VERTEX_MAX];


    Floyd(G,path,dis);

    int t;
    printf("\n任意两个顶点的最短路径是(终点 < 源点):\n");
    for(i=0;i<G.VertexNum;i++)//输出结果
    {
        for(j=0;j<G.VertexNum;j++)
        {
            t=path[i][j];
            printf("长度：%d   %c < ",dis[i][j],G.Vertex[j]);
            while(t!=-1)
            {
                printf("%c < ",G.Vertex[t]);
                t=path[i][t];
            }
            printf("%c\n",G.Vertex[i]);
        }
    }
    return 0;
}
