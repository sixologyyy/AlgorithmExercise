//归并排序求逆序对

#include <stdio.h>
#include <stdlib.h>

#define MAX 32767
#define LEN 6

int merge(int *array, int start,int mid,int end) { 
	//归并array[start...mid] 与 array[mid+1...end]

	int tempSum=0;
	int n1 = mid-start+1;
	int n2 = end-mid;
	int* left = NULL;
	int* right = NULL;
	int i,j,k;

	//最后多了个监视哨的位置
	left = ( int *)malloc(sizeof(int) * (n1+1));
	right = ( int *)malloc(sizeof(int) * (n2+1));
	
	for(i=0; i<n1; i++)
		left[i] = array[start+i];

	for(j=0; j<n2; j++)
		right[j] = array[mid+1+j];

	left[n1] = MAX; //监视哨，避免检查每一部分是否为空
	right[n2] = MAX;

	i=0;
	j=0;

	for(k=start; k<=end; k++) 
	{
		if( left[i] <= right[j]) 
		{
			array[k] = left[i];
			i++;
		}
		//每个左边大于右边，产生一个逆序对
		//若left[i] > right[j]，则left[i...n1-1]这n1-i个数都大于right[j]，所以产生了n1-i个逆序对
		else 
		{
			array[k] = right[j];
			j++;
			tempSum += n1 - i;
			printf("tempSum = %d\n", tempSum);
		}
	}
	//释放内存 
    free(left);
    free(right);
    left = NULL;
    right = NULL;
	return tempSum;

}

int mergeSort(int *array, int start, int end ) 
{
	int sum=0;
	if(start < end) 
	{
		int mid = (start + end) /2;
		sum += mergeSort(array, start, mid);
		sum += mergeSort(array, mid+1, end);
		sum += merge(array,start,mid,end);
	}
	return sum;
}

int main(void)
{
	int array[LEN] = {9,1,0,5,4,3};
	int inversePairNum;
	int i;

	inversePairNum = mergeSort(array,0,LEN-1);
	for( i=0; i<LEN; i++)
		printf("%d ", array[i]);
	printf("\n逆序对个数 = %d\n", inversePairNum);
    return 0;
}
