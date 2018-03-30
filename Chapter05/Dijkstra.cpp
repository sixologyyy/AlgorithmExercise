/*

dijkstra算法求源点到各顶点的最短路径
weight[j]为源点到j点的权值
path[j]为源点到j点的中间节点，不断调用j=path[j]可以从j点回溯到源点
tempVertex[]记录该点是否访问
步骤：
（1）初始weight[]为源点v0到个点的边权，path[j]=v0为直连点，且所有点标记为未访问，源点v0记为已访问，权值赋0
（2）遍历所有节点，循环操作：
    在未访问节点中寻找到v0的最小权值，记录编号minIndex和权值
    以minIndex为中间点，更新v0到未访问节点的权值，如果经过minIndex点路径更短，记录path[j]=minIndex，即v0到j的路径经过minIndex

注意：和prim算法类似，两者有一个已访问集合U和未访问集合V-U，并且遍历所有节点，从V-U中寻找最小权值
区别是，prim是找到到U集合中最近的点，而dijk是找到离源点最近的点

*/

#include "MatrixGraph.cpp"

void Dijkstra(MatrixGraph G)
{
    int weight[VERTEX_MAX];     //某源点到各顶点的最短路径长度
    int path[VERTEX_MAX];       //某源点到终点经过的顶点集合的数组
    int tmpVertex[VERTEX_MAX];  //最短路径的终点集合，为1表示在路径中，0表示不在

    int i,j,minIndex,v0,minWeight;
    printf("\n入源点的编号:");
    scanf("%d",&v0);
 
    for(i=0;i<G.VertexNum;i++) //初始辅助数组 
    {
        weight[i]=G.Edges[v0][i]; //保存最小权值 
        if(weight[i]<MAXVALUE && weight[i]>0) //有效权值 
            path[i]=v0; //保存边
        tmpVertex[i]=0; //初始化顶点集合为空 
    }

    tmpVertex[v0]=1; //将顶点v0添加到集合U中 
    weight[v0]=0; //将源顶点的权值设为0 

    //外循环，遍历所有节点
    for(i=0;i<G.VertexNum;i++)
    {
        minWeight=MAXVALUE; //将min中保存一个最大值 
        minIndex=v0; //源顶点序号

        //内循环1，在U集合（未访问的）中查找顶点的最小权值 
        for(j=0;j<G.VertexNum;j++) 
            if(tmpVertex[j]==0 && weight[j]<minWeight)
            {
                minWeight=weight[j];
                minIndex=j;
            }
        tmpVertex[minIndex]=1;   //将顶点minIndex加入集合U

        //内循环2，以顶点minIndex为中间点，更新权值
        for(j=0;j<G.VertexNum;j++) 
            if(tmpVertex[j]==0 && weight[minIndex]+G.Edges[minIndex][j]<weight[j]) //有更小权值的路径 
            {
                weight[j]=weight[minIndex]+G.Edges[minIndex][j]; //更新权值 
                path[j]=minIndex;
            }
    }

    //输出源点到各点的最短路径
    printf("\n顶点%c到各顶点的最短路径是(终点 < 源点):\n",G.Vertex[v0]);
    for(i=0;i<G.VertexNum;i++)//输出结果
    {
        if(tmpVertex[i]==1)
        {
            minIndex=i;            
            while(minIndex!=v0)
            {
                j=minIndex;
                printf("%c < ",G.Vertex[minIndex]);
                minIndex=path[minIndex];
            }
            printf("%c\n",G.Vertex[minIndex]);
        }else
            printf("%c<-%c:无路径\n",G.Vertex[i],G.Vertex[v0]);
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

    printf("最短路径：\n");
    Dijkstra(G);
    return 0;
}
