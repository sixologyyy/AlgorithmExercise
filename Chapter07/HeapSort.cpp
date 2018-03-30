//堆排序，升序

#include <stdio.h>

#define MAX 10
 
void adjustHeap(int *a,int s,int j);
void HeapSort(int *a, int nums);     //nums是总的个数

//大根堆进行调整
void adjustHeap(int *a,int s, int j)
{
    int temp=a[s];
    for (int k=s*2+1;k<j;k=k*2+1)
    {
        //如果右边值大于左边值，指向右边
        if (k+1<j && a[k]< a[k+1])
        {
            k++;
        }
        //如果子节点大于父节点，将子节点值赋给父节点,并以新的子节点作为父节点（不用进行交换）
        if (a[k]>temp)
        {
            a[s]=a[k];
            s=k;
        }
        else
            break;
    }
    a[s]=temp;
}
//堆排序主要算法
void HeapSort(int *a,int nums)
{
    //1.构建大顶堆
    for (int i=nums/2-1;i>=0;i--)
    {
        adjustHeap(a,i,nums);
    }
    //2.调整堆结构+交换堆顶元素与末尾元素
    for (int j=nums-1;j>0;j--)
    {
        //堆顶元素和末尾元素进行交换
        int temp=a[0];
        a[0]=a[j];
        a[j]=temp;
 
        adjustHeap(a,0,j);//重新对堆进行调整
    }
}

int main(void)
{
	int i,a[MAX]={37,19,56,99,16,4,82,53,20,65};
	printf("原数组：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);
	HeapSort(a,MAX);
	printf("排序后：\n");
	for(i=0;i<MAX;i++)
		printf("%d\n",a[i]);

}