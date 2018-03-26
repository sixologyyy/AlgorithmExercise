//希尔排序，升序

#include <stdio.h>

#define MAX 10

//整个数组按增量delta分成若干段，每段里面采用插入排序，然后逐渐减小增量，直至增量为1
//实现的时候，不必对每一段数据独立排序，只要从每段的第二个元素开始，顺序扫描原数组，每一段的数据会轮流出现，此时将一个数据和它段内的其它数进行插入操作
void ShellSort(int a[],int n)//希尔排序 
{
    int delta,i,j,t;
    delta=n/2;
    while(delta>=1)     //循环至增量为1时结束 
    {
        for(i=delta;i<n;i++)
        {
            t=a[i];       //获取该段当前数据 
            j=i-delta;    //该段前一个数据的序号 
            while(j>=0 && a[j]>t)   //当前数大于前一个数 
            {
                a[j+delta]=a[j];   //向后顺移
                j=j-delta;         //修改序号，继续向前比较 
            }
            a[j+delta]=t;          //保存数据 
        }
        delta/=2;      //缩小增量 
    }
}

int main(void)
{
    int i,a[MAX]={37,19,56,99,16,4,82,53,20,65};
    printf("原数组：\n");
    for(i=0;i<MAX;i++)
        printf("%d\n",a[i]);
    ShellSort(a,MAX);
    printf("排序后：\n");
    for(i=0;i<MAX;i++)
        printf("%d\n",a[i]);

}