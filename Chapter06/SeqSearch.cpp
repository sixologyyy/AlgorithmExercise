//线性查找
//优化，在0或者最后的位置设置监视哨，里面的值等于待查找值，这样for循环可以不需要i和n的比较

#include <stdio.h>
#define ARRAYLEN 8

int source[]={63,61,88,37,92,32,28,54};

int SeqSearch(int s[],int n,int key)
{
    int i;
    for(i=0;i<n && s[i]!=key;i++)
        ;
    if(i<n)
        return i;
    else
        return -1;
}

int SeqSearch2(int s[],int n,int key)
{
    int i;
    for(i=0;s[i]!=key;i++)
        ;
    if(i<n)
        return i;
    else
        return -1;
}   

int main()
{
    int key,i,pos;
    printf("输入关键字:");
    scanf("%d",&key);    
    pos=SeqSearch(source,ARRAYLEN,key);
    printf("原数据表:"); 
    for(i=0;i<ARRAYLEN;i++)
        printf("%d ",source[i]);
    printf("\n");
    if(pos>=0)
        printf("查找成功，该关键字位于数组的第%d个位置。\n",pos);
    else
        printf("查找失败!\n");
    return 0;
}
