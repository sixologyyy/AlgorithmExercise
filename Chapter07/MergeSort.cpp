//归并排序，升序

#include <stdio.h>

#define LEN 8
int a[LEN] = { 15, 9, 7, 1, 3, 11, 5, 13 };

void merge(int start, int mid, int end)
{
	//左半边 a[start...mid]
	int n1 = mid - start + 1;
	//右半边 a[mid+1...end]
	int n2 = end - mid;
	int left[n1], right[n2];
	int i, j, k;

	//复制
	for (i = 0; i < n1; i++)
		left[i] = a[start+i];
	for (j = 0; j < n2; j++)
		right[j] = a[mid+1+j];

	i = j = 0;
	k = start;
	while (i < n1 && j < n2)
		if (left[i] < right[j])
			a[k++] = left[i++];
		else
			a[k++] = right[j++];

	//多余的元素
	while (i < n1)
		a[k++] = left[i++];
	while (j < n2)
		a[k++] = right[j++];
}

void sort(int start, int end)
{
	int mid;
	if (start < end) 
	{
		mid = (start + end) / 2;
		printf("sort (%d-%d, %d-%d) %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);

		sort(start, mid);
		sort(mid+1, end);
		merge(start, mid, end);

		printf("merge (%d-%d, %d-%d) to %d %d %d %d %d %d %d %d\n", 
		       start, mid, mid+1, end, 
		       a[0], a[1], a[2], a[3], a[4], a[5], a[6], a[7]);
	}
}

int main(void)
{
	sort(0, LEN-1);
    return 0; 
}
