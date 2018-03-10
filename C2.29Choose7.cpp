//1~M中选N个数字，N个数字不能相同，输出所有可能结果
//深度优先搜索

//由于数字从小到大搜索，所以不需要test
#include <stdio.h>

#define M 10 //总共M个
#define N 5  //选N个

int a[N] = { 0 };
int solves = 0;
int count = 0;

//int test(int* a, int index)       //对于a里面新加入的元素，下标为index，验证是否重复
//{
//	if (index == 0)
//		return 1;
//	int i;
//	for (i = 0; i <= index - 1; i++)
//	{
//		if (a[i] == a[index])
//			return 0;
//	}
//	return 1;
//}

void dfs(int m, int n)      //总共m个，再选n个
{
	int i;

	if (n == 0)
	{
		solves++;
		for (i = 0; i < N; i++)
			printf("%2d  ", a[i]);
		printf("\n");		
	}
	else
	{
		count++;
		for (i = a[N-n-1]+1; i <= M; i++)
		{
			a[N - n] = i;
			dfs(m, n - 1);
		}		
	}
}

int main(void)
{
	dfs(M, N);
	printf("\n总共：%d个\n", solves);
}