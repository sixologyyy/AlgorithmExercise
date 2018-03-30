//基数排序，低位优先LSD，升序

#include <math.h>
#include <stdio.h>

#define LEN 15

//获取数字的位数
int getLoopTimes(int num)
{
    int count = 1;
    int temp = num / 10;
    while(temp != 0)
    {
        count++;
        temp = temp / 10;
    }
    return count;
}
//查询数组中的最大数
int findMaxNum(int *p, int n)
{
    int i;
    int max = 0;
    for(i = 0; i < n; i++)
    {
        if(*(p + i) > max)
        {
            max = *(p + i);
        }
    }
    return max;
}

//将数字分配到各自的桶中，然后按照桶的顺序输出排序结果
void distribute(int *p, int n, int loop)
{
    //建立一组桶
    int buckets[10][LEN] = {0};
    //记录每个桶中新元素插入的位置
    int colIndex[10]={0};

    //求桶的index的除数
    //如798个位桶index=(798/1)%10=8
    //十位桶index=(798/10)%10=9
    //百位桶index=(798/100)%10=7
    //tempNum为上式中的1、10、100
    int tempNum = (int)pow(10, loop - 1);
    int i, j;
    for(i = 0; i < n; i++)
    {
        int rowIndex = (p[i] / tempNum) % 10;
        buckets[rowIndex][colIndex[rowIndex]] = p[i];
        colIndex[rowIndex]++;
    }
    //将桶中的数，倒回到原有数组中
    int k = 0;
    for(i = 0; i < 10; i++)
    {
        printf("桶 %d: ",i);

        for(j = 0; j < colIndex[i]; j++)
        {
            p[k] = buckets[i][j];
            printf("%d  ",p[k]);
            k++;
        }
        printf("\n");
    }
}

//基数排序
void RadixSort(int *p, int n)
{
    //获取数组中的最大数
    int maxNum = findMaxNum(p, n);
    //获取最大数的位数，次数也是再分配的次数。
    int loopTimes = getLoopTimes(maxNum);
    int i;
    //对每一位进行桶分配
    for(i = 1; i <= loopTimes; i++)
    {
        printf("\n第%d位：\n",i);
        distribute(p, n, i);
    }
}

int main(void)
{
    int a[LEN] = {27, 343, 342, 1, 126, 43, 4346, 435, 687, 654, 3, 9, 129, 38, 57};

    //基数排序
    RadixSort(a, LEN);

    int i;
    for(i = 0; i < LEN; i++)
    {
        printf("%d\n", a[i]);
    }
}