//堆排序，升序
/*
1.先将初始文件R[1..n]建成一个大根堆，此堆为初始的无序区
2.再将关键字最大的记录R[1]（即堆顶）和无序区的最后一个记录R[n]交换，由此得到新的无序区R[1..n-1]，和有序区R[n]，此时R[n]是所有元素最大的
3.由于交换后新的根R[1]可能违反堆性质，故应将当前无序区R[1..n-1]调整为堆。
  然后再次将R[1..n-1]中关键字最大的记录R[1]和该区间的最后一个记录R[n-1]交换，由此得到新的无序区R[1..n-2]和有序区R[n-1..n]，此时有序区存放最大的和次大的，同样要将R[1..n-2]调整为堆
4.直到无序区只有一个元素

类似选择排序，每次从堆中选出最大的放入有序区
*/

#include <stdio.h>

#define MAX 10
 
void adjustHeap(int *a,int s,int j);
void HeapSort(int *a, int nums);     //nums是总的个数

//大根堆进行调整，从最后一个非叶子节点，从下到上，从右至左
//s为待调整节点，j为调整范围内最后一个节点
void adjustHeap(int *a,int s, int j)
{
    int temp=a[s];
    //k用来遍历s的孩子
    for (int k=s*2+1;k<j;k=k*2+1)
    {
        //如果右边值大于左边值，指向右边
        if (k+1<j && a[k]< a[k+1])
        {
            k++;
        }
        //如果子节点大于父节点，将子节点值赋给父节点，并以新的子节点作为父节点（不用进行交换）
        //子树里面比父亲大的元素依次上浮，父亲沉到了比他大的元素下面
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
    //1.构建大顶堆，从最后一个非叶子节点开始
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