//ѭ�����ƣ�n�Ӳμӱ���������֮����һ��������n-1�죬ÿ��ÿ��ֻ����һ�����Ҳ����ֿ�

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX 256
int  a[MAX + 1][MAX + 1] = { 0 };
//��i�б�ʾ��i��ս�ӣ���j+1�б�ʾ��j��ö���Ķ��֣���1���Ǳ��

void getSchdule(int k, int n)
{
	int i, j;
	if (n == 2)
	{
		a[k][1] = k;                     //�������
		a[k][2] = k + 1;              //������
		a[k + 1][1] = k + 1;       //�������
		a[k + 1][2] = k;             //������
	}
	else
	{
		getSchdule(k, n / 2);
		getSchdule(k + n / 2, n / 2);

		for (i = k; i < k + n / 2; i++)   //�����Ͻ�
		{
			for (j = n / 2 + 1; j <= n; j++)
			{
				a[i][j] = a[i + n / 2][j - n / 2];
			}
		}
		for (i = k + n / 2; i < k + n; i++)  //�����½�
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

	printf("�������������������Ϊ2���ݣ�n��");
	scanf("%d", &n);
	m = log10(n) / log10(2);

	getSchdule(1, n);

	printf("\n���");
	for (i = 1; i < n; i++)
		printf("%4d��", i);
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