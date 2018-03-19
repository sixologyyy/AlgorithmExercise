/*

求连通网的最小生成树的prim算法
原理：MST性质：设G=(V,E)是一个连通网，U是顶点V的非空子集，点u属于U，点v属于V-U，且(u,v)是一条最小权值的边，则存在一棵包含(u,v)的最小生成树
步骤：
（1）初始化U={u0}，M=空，M为最小生成树边集
（2）在所有u属于U，v属于V-U中选择一条最小权值的边(u0,v0)并入集合M，将v0并入U
（3）重复直到U=V

weight[j]记录U集合到j的最小权值
tempVertex[j]为-1(NOADJ)表示是非邻接点，为0(USED)表示已经访问过，放入了U集合，否则为U集合中到j点权值最小的点
*/


#include "MatrixGraph.cpp"

#define USED 0      //已使用，加入U集合
#define NOADJ -1    //非邻接节点

void Prim(MatrixGraph G)
{
	int i,j,minIndex,minWeight,sum=0;
	int weight[VERTEX_MAX];        //weight[j]记录U集合中的点到j点权值最小的那个
	int tempVertex[VERTEX_MAX];    //tempVertex[j]记录U集合中到j点权值最小的节点，以及标记已使用的节点，USED为在U集合中

	//初始化权值和临时顶点
	for(i=1;i<G.VertexNum;i++)
	{
		weight[i]=G.Edges[0][i];
		if(weight[i]==MAXVALUE)
			tempVertex[i]=NOADJ;
		else
			tempVertex[i]=G.Vertex[0];
	}
	tempVertex[0]=USED;
	weight[0]=MAXVALUE;

	//外循环，遍历所有节点
	for(i=1;i<G.VertexNum;i++)
	{
		minWeight=weight[0];
		minIndex=i;    //记录当前最小权值的节点

		//内循环1，在U集合（未访问的）中寻找最小权重的点
		for(j=1;j<G.VertexNum;j++)
			if(weight[j]<minWeight && tempVertex[j]>0)
			{
				minWeight=weight[j];
				minIndex=j;
			}
		sum+=minWeight;

		printf("<%c,%c>,",tempVertex[minIndex],G.Vertex[minIndex]);
		//标记为已加入U
		tempVertex[minIndex]=USED;
		weight[minIndex]=MAXVALUE;

		//内循环2，对新加入U的节点minIndex，更新权值数组
		for(j=0;j<G.VertexNum;j++)
			if(G.Edges[minIndex][j]<weight[j] && tempVertex[j]!=USED)   //注意，只排除USED节点，原来的NOADJ有可能是新加入的节点的邻接点
			{
				weight[j]=G.Edges[minIndex][j];
				tempVertex[j]=G.Vertex[minIndex];
			}
	}
	printf("\n最小生成树的总权值为：%d\n",sum);
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

    printf("最小生成树的边为：\n");
    Prim(G);
    return 0;
}