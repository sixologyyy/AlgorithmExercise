//快速排序，升序

#include <stdio.h>

#define MAX 10

//每一趟中，第一个数为key，先把从后往前第一个比key小的扔到key的位置，再把从前往后第一个比key大的扔到刚才后面空出的位置，两边互扔直到扔到中间，把key给最中间的值，此时key左边都是比它小的，右边都是比它大的
void QuickSort(int *a, int left, int right)
{
	//如果左边索引大于或者等于右边的索引就代表已经整理完成一个组了
	if(left >= right)
	{
		return;
	}
	int i = left;
	int j = right;
	int key = a[left];
	 
	//该趟的任务是，把大于key的扔到key右边，小于key的扔到key左边
	//循环结束条件是两个指针相遇
	while(i < j)
	{
		//右组，从最后向前寻找第一个小于key的数，给a[i]
		while(i < j && key <= a[j])
			j--;
		a[i] = a[j];
		
		//左组，从最前向后寻找第一个大于key的数，给a[j]	 
		while(i < j && key >= a[i])
			i++;
		a[j] = a[i];
	}
	
	//该趟完成后，把key放回中间位置
	a[i] = key;

	for(int t=0;t<MAX;t++)
		printf("%d ",a[t]);
	printf("\n");

	//递归排序左右组
	QuickSort(a, left, i - 1);
	QuickSort(a, i + 1, right);
}

int main(void)
{
	int i,a[MAX]={37,19,56,99,16,4,82,53,20,65};
	printf("原数组：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);
	QuickSort(a,0,MAX-1);
	printf("排序后：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);

}