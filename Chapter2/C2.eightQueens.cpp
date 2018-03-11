//�˻ʺ����⣬8*8���̷�8���ʺ���������������ͬһ���л�б����

#define QUEEN 12
#include <stdio.h>

int solution[20];           //solution[i]��ʾ��i�е���һλ�Żʺ�
int count = 0;
int solves = 0;

int test(int row, int col)     //��row�У���col�зŻʺ�
{
	int j;
	for (j = 0; j < row; j++)
	{
		if (row - j == solution[row] - solution[j] || row + solution[row] == j + solution[j] || solution[row] == solution[j])
			//        ��һб��/                                   ��һб��\                                     ͬ�л�����
			//        �Ƚ� (row,solution(raw))���ѷ��õ�j���ʺ�
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
	printf("�ܹ�������%d\n", solves);
	return 1;
}