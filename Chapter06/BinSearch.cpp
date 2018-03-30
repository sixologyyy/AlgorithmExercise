//二分查找

#include <stdio.h>
#define ARRAYLEN 10
int source[]={6,12,28,32,53,65,69,83,90,92};

//二分查找，数组从小到大排
int BinSearch(int s[],int n,int key)
{
	int low,high,mid;
	low=0;
	high=n-1;
    while(low<=high)        //查找范围含含至少一个元素 
    {
        mid=(low+high)/2;   //计算中间位置序号 
        if(s[mid]==key)      //中间元素与关键字相等 
            return mid;      //返回序号 
        else if(s[mid]>key)  //中间元素大于关键字 
            high=mid-1;     //重定义查找范围 
        else                 //中间元素小于关键字 
            low=mid+1;       //重定义查找范围 
    }
    return -1;               //返回查找失败 
}

//递归方法，s按从小到大排序
int BinSearchRecur (int *s,int low,int high,int num)
{
	int mid;
	mid = (low+high)/2;
	if ((low>=high)&&(s[mid]!=num))
		return -1;
	else 
	{
		if (s[mid]==num)
			return mid;
		else if (s[mid]>num)
			high = mid+1;//中间数字比要查的数还大，说明可能在中间段以前
		else 
			low = mid-1;//同上，可能在中间段以后
		return BinSearchRecur(s,low,high,num); //递归 
	}
}


int main()
{
	int key,i,pos;
	printf("请输入关键字:");
	scanf("%d",&key); 
	pos=BinSearch(source,ARRAYLEN,key);
	pos=BinSearchRecur(source,0,ARRAYLEN,key);
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
