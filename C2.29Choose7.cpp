//1~M��ѡN�����֣�N�����ֲ�����ͬ��������п��ܽ��
//�����������

//�������ִ�С�������������Բ���Ҫtest
#include <stdio.h>

#define M 10 //�ܹ�M��
#define N 5  //ѡN��

int a[N] = { 0 };
int solves = 0;
int count = 0;

//int test(int* a, int index)       //����a�����¼����Ԫ�أ��±�Ϊindex����֤�Ƿ��ظ�
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

void dfs(int m, int n)      //�ܹ�m������ѡn��
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
	printf("\n�ܹ���%d��\n", solves);
}