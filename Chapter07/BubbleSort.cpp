//冒泡排序，升序

#include <stdio.h>

#define MAX 10

void BubbleSort(int *a,int n)
{
	int i,j,t,change;
	//比较n-1轮，第i轮把第i小的冒泡到第i位，若该轮没有交换，则排序完成
	for(i=0; change && i<n;i++)
	{
		change=0;
		for(j=n-1;j>i;j--)
		{
			if(a[j]<a[j-1])
				t=a[j],a[j]=a[j-1],a[j-1]=t,change=1;
		}

	}
	return;
}

int main(void)
{
	int i,a[MAX]={37,19,56,99,16,4,82,53,20,65};
	printf("原数组：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);
	BubbleSort(a,MAX);
	printf("排序后：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);

}