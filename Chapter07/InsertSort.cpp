//插入排序，升序

#include <stdio.h>

#define MAX 10

void InsertSort(int *a,int n)
{
	int i,j,t;
	for(i=1;i<n;i++)
	{
		t=a[i];
		//取出待插入数字，依次向前比较，如果比前面小就向后顺移
		for(j=i-1; t<a[j] && j>=0 ;j--)
		{
			a[j+1]=a[j];  //向后顺移
		}
		//插入
		a[j+1]=t;		
	}
	return;
}

int main(void)
{
	int i,a[MAX]={37,19,56,99,16,4,82,53,20,65};
	printf("原数组：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);
	InsertSort(a,MAX);
	printf("排序后：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);

}