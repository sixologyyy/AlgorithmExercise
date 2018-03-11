//八皇后问题，8*8棋盘放8个皇后，任意两个不能在同一行列或斜线上

#define QUEEN 12
#include <stdio.h>

int solution[20];           //solution[i]表示第i行的哪一位放皇后
int count = 0;
int solves = 0;

int test(int row, int col)     //第row行，第col列放皇后
{
	int j;
	for (j = 0; j < row; j++)
	{
		if (row - j == solution[row] - solution[j] || row + solution[row] == j + solution[j] || solution[row] == solution[j])
			//        任一斜线/                                   任一斜线\                                     同行或者列
			//        比较 (row,solution(raw))和已放置的j个皇后
			return 0;
	}
	return 1;
}

void dfs(int row)
{
	count++;
	int k;

	if (row == QUEEN)
	{
		solves++;
		/*for (k = 0; k < QUEEN; k++)
			printf("%d\t", solution[k]);
		printf("\n\n");*/
	}
	else
	{
		int i;
		for (i = 0; i < QUEEN; i++)
		{
			solution[row] = i;
			if (test(row, i))
				dfs(row + 1);
		}
	}
}

int main(void)
{
	dfs(0);
	printf("总共方案：%d\n", solves);
	return 1;
}