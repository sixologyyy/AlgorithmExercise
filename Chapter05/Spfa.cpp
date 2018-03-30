#include "MatrixGraph.cpp"
#include <queue>

using namespace std;

//dis[i]为源点s到i的距离，path[i]为s到i经过的节点编号，vis[]表示是否在队中
void Spfa(MatrixGraph G,int s,int *dis,int *path)
{
    int i,v;
    int vis[VERTEX_MAX];

    //初始化每个点到s的距离
    for(i=0;i<G.VertexNum;i++)
    {
        dis[i]=MAXVALUE;
        path[i]=-1;
        vis[i]=0;
    }
    dis[s]=0;
    vis[s]=1;

    //源点s入队
    std::queue<int> q;
    q.push(s);

    while (!q.empty())
    {
        //队首v出队
        v = q.front();
        q.pop();
        vis[v] = 0;

        //遍历所有节点i，如果s到i经过队首v更短，则用v对i进行松弛操作
        for (i=0;i<G.VertexNum;i++)
        {
            if (dis[i] > dis[v] + G.Edges[v][i])
            {
                dis[i] = dis[v] + G.Edges[v][i];
                path[i]=v;
                //若被松弛的i不在队里
                if (!vis[i])
                {
                    vis[i] = 1;
                    q.push(i);
                }
            }
        }
    }

     //输出源点到各点的最短路径
    printf("\n顶点%c到任一顶点(终点 < 源点):\n",G.Vertex[s]);
    for(i=0;i<G.VertexNum;i++)//输出结果
    {            
        int t=path[i];
        printf("长度：%d   %c < ",dis[i],G.Vertex[i]);
        while(t!=-1)
        {
            printf("%c < ",G.Vertex[t]);
            t=path[t];
        }
        printf("\n");
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

    printf("最短路径：");
    int dis[VERTEX_MAX],path[VERTEX_MAX];
    Spfa(G,0,dis,path);

    return 0;
}