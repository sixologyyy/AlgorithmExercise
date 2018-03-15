//循环赛制，n队参加比赛，两两之间赛一场，比赛n-1天，每天每队只能赛一场，且不能轮空

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 256
int  a[MAX + 1][MAX + 1] = { 0 };
//第i行表示第i个战队，第j+1列表示第j天该队伍的对手，第1列是编号

void getSchdule(int k, int n)
{
	int i, j;
	if (n == 2)
	{
		a[k][1] = k;                     //参赛编号
		a[k][2] = k + 1;              //对阵编号
		a[k + 1][1] = k + 1;       //参赛编号
		a[k + 1][2] = k;             //对阵编号
	}
	else
	{
		getSchdule(k, n / 2);
		getSchdule(k + n / 2, n / 2);

		for (i = k; i < k + n / 2; i++)   //填右上角
		{
			for (j = n / 2 + 1; j <= n; j++)
			{
				a[i][j] = a[i + n / 2][j - n / 2];
			}
		}
		for (i = k + n / 2; i < k + n; i++)  //填左下角
		{
			for (j = n / 2 + 1; j <= n; j++)
			{
				a[i][j] = a[i - n / 2][j - n / 2];
			}
		}
	}
}

int main(void)
{
	int n, m, i, j;

	printf("输入参赛队伍数（必须为2的幂）n：");
	scanf("%d", &n);
	m = log10(n) / log10(2);

	getSchdule(1, n);

	printf("\n编号");
	for (i = 1; i < n; i++)
		printf("%4d天", i);
	printf("\n");
	for (i = 1; i <= n; i++)
	{
		for (j = 1; j <= n; j++)
		{
			if (j == 1)
				printf("%4d", a[i][j]);
			else
				printf("%5d ", a[i][j]);
		}
		printf("\n");
	}
	
	return 1;
}