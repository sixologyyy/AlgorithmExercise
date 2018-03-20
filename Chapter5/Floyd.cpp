/*

floyd算法求任意两点间的最短路径
注意，外层变量k并不代表指遍历i,j的中间节点，否则它应该在最内层
对于点集V，其中有一条路(i,j)，我们考虑它经过点集V的情况，在其中寻找最短路径p
那么k和p的关系有两种：
（1）k不在p里，则经过{1,2...k-1}和经过{1,2...k}的p是一样的
（2）k在p里，则p里的点都是{1,2,..k}的点，那我们可以把p分为(i,k)和(k,j)，这两条分出来路径的只含{1,2,..k-1}，因为p是最短路径，而k又在p里，所以(i,k)和(k,j)都是相对于(i,j)的最短路径
以上可以得出动态规划的递推式，反映在初始化dis和核心代码的递推式上

（知乎）k是动态规划的阶段,而起点终点的i,j是状态。
第k次循环后，保证每个点到顶点k的距离，要么不可达，要么是最短距离，大前提是距离上除了起点和终点只有1~k-1这k-1个点。
当我们的k值从0枚举到n-1,那么我们获得的最短路径上允许出现的点的编号，就从0增加到n-1,当n-1被允许加入路径中，那么这个最短路径问题就得到解决。因为所有的顶点在最短路径的位置都被考虑了。


详见http://blog.csdn.net/u012469987/article/details/51319574#floyd-warshall

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
                (*(dis+i))[j]=G.Edges[i][j];
            else
                *(dis[i]+j)=0;
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
