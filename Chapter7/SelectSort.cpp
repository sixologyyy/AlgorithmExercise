//选择排序，升序

#include <stdio.h>

#define MAX 10

void SelectSort(int *a,int n)
{
	int i,j,t;
	for(i=0;i<n-1;i++)
	{
		//从当前位置向后选择最小的和该位置交换
		t=i;  //最小下标
		for(j=i+1;j<n;j++)
		{
			if(a[j]<a[t])
				t=j;
		}
		//交换
		j=a[i];
		a[i]=a[t];
		a[t]=j;
	}
	return;
}

int main(void)
{
	int i,a[MAX]={37,19,56,99,16,4,82,53,20,65};
	printf("原数组：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);
	SelectSort(a,MAX);
	printf("排序后：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);

}