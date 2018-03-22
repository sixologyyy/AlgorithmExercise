//大数乘法
/*
123 * 456
从低位遍历两个数，第 i 位和第 j 位的乘积存放在结果的第 i+j 位 

注意中间结果的每一位的值可能非常大，随着乘数的位数增长越来越大
如  99...99 * 99...99  (100个9)
则中间结果中，i+j=0+99,1+98,...,99+0这100个结果都在99位，总和是100*81=8100
对于 N 位的 a 和 M 位的 b，最大的中间结果是 min(M,N)*81
unsigned int 最大 2^31-1，/81得 53024287，也就是两个乘数长度不要都超过该值

注意sizeof不能求动态分配的空间的长度，只能求这个指针的大小（一般都是4）

然后处理进位

结果字符串开辟足够的空间，提前置'0'，从低位开始计算，输出时寻找第一个非'0'

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length 1001


void multEveryDigit(unsigned int *dst, char *srcA, char *srcB, int lenDst);         //遍历每个数位分别相乘，乘积（可能>10）存在 i+j 位
                                                                                                  //注意要输入int数组的长度作参数，否则不知道其的长度，sizeof无法获得int数组长度
void countCarry(char *dst,unsigned int* src, int lenSrc);           //计算以上结果的每一位的进位

int main(void)
{
	//初始化数组
	char *a = NULL;
	char *b = NULL;
	char *resultStart = NULL;
	char *result = NULL;
	a = (char*)malloc(length * sizeof(char));
	b = (char*)malloc(length * sizeof(char));

	unsigned int *tempStart = NULL;
	unsigned int *temp = NULL;

	//输入
	printf("输入整数a,b：\n");
	gets_s(a, length);
	gets_s(b, length);

	//变量声明
	int i, j;
	int ifTempCarry = 0, ifResultCarry = 0;      //最高位进位
	int lenA = strlen(a);
	int signA = a[0] == '-' ? 1 : 0;     //有负号时sign=1，否则0
	int lenB = strlen(b);
	int signB = b[0] == '-' ? 1 : 0;
	int lenResult = lenA + lenB;      //可能的最长的长度，包括负号和进位，不包括'\0'

    //初始化temp和result    （不要用memset）
	tempStart = (unsigned int*)malloc((lenResult + 1) * sizeof(int));        //开辟空间的长度要包括 进位
	for (i = 0; i < lenResult; i++)                 //置0
		tempStart[i] = 0;
	temp = tempStart;

	resultStart = (char*)malloc((lenResult + 1) * sizeof(char));
	for (i = 0; i < lenResult; i++)
		resultStart[i] = '0';
	resultStart[lenResult] = '\0';
	result = resultStart;

	//模拟乘法
	multEveryDigit(tempStart, a + signA, b + signB, lenResult);
	countCarry(resultStart, tempStart, lenResult);
	for (i = 0; resultStart[i] == '0'; i++);         //寻找最高位(第一个不为'0')的位置
	if ((signA + signB) % 2)         //结果为负
		result[i - 1] = '-', result += i - 1;
	else
		result += i;


	puts("\n结果：");
	puts(a);
	puts("*");
	puts(b);
	puts("=");
	puts(result);
	puts("\n");

	free(a);
	free(b);
	free(tempStart);
	free(resultStart);
	return 1;
}


void multEveryDigit(unsigned int *dst, char *srcA, char *srcB, int lenDst)              // srcA，srcB的 i , j 位两两相乘存在 dst 的 i + j 位，注意dst事先置'0'
{
	int i, j;
	int lenA = strlen(srcA);
	int lenB = strlen(srcB);
	char carry = 0;

	for (i = 0; i <= lenA - 1; i++)
	{
		for (j = 0; j <= lenB - 1; j++)
		{
			dst[lenDst - 1 - (i + j)] += (srcA[lenA - 1 - i] - 48)*(srcB[lenB - 1 - j] - 48);     //从低位遍历，注意下标。由于不同 i+j 可能结果相同，所以要累加(+=)
																															  //注意此时的char可能会溢出，取值-127~128，在处理进位时会解决
		}
	}
}

void countCarry(char *dst, unsigned int* src, int lenSrc)        //遍历dst，若某一位大于10则进位
{
	int i;
	unsigned int carry = 0;
	unsigned int tempResult = 0;            //不要用char型，否则会溢出（如99*99的时候，第二位算出来为162+8=170，而char为 -128~127）
	int lenDst = strlen(dst);

	for (i = lenSrc - 1; i >= 0; i--)      //从低位遍历
	{
		//src中存的是整型，不用-48，但是输出到dst[]里是char
		tempResult = carry + src[i];		
		dst[i] = tempResult % 10 + 48;
		carry = tempResult / 10;
	}
	for (i = 0; dst[i] == '0'; i++);         //寻找最高位(第一个不为'0')的位置
	if(carry)
		dst[i] = carry + 48;                      //如果有进位，填上
}