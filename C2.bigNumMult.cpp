//模拟手算大数乘法
/*
        123 * 456
		从低位遍历456，计算123*6 , 123*5 , 123*4
		得到的结果分别移位0,1,2相加，计算进位
		result存放累加结果，temp存放个位数与被乘数的积

		由于从低位往高位算，在预先确定结果总位数时出现困难，因为最高位的进位有可能是从很低的位置传递上来
		解决办法：开辟足够的空间，全部置'0'，首地址为 resultStart
		                输出时计算最高位的进位数，tempCarry为a*b[i]的结果高位是否进位，resultCarry为累加最高位是否进位
						ifCarry = tempCarry + resultCarry  (不可能同时为1)，输出 resultStart+（1-ifCarry） 处的字符串，无视再前面的字符
					    如    11                  99 
						      *99                  99
						--------------------------------------
							   99                 891
							 99                 891
						--------------------------------------
					       1089               9801
						temp无进位       temp有
						result有进位       result无
						result和temp不可能同时进位，因为temp最高位如果产生进位，最大为99...*9=899...，第二高位最多也是899...
						                                             在result中累加，即为899...+089...，最多99...，即累加在result中最高位不进位


					    对每个temp的处理同上， ifCarry = tempCarry，在原始的tempStart中填完计算结果后，tempStart+（1-ifCarry ）为真实的temp首位

		解决办法2：开辟足够的空间，由于提前置了'0'，所以遍历找到第一个不是'0'的即可        - -

		旧版本中，计算temp时返不返回ifCarry，返回真实的temp的地址，效果是一样的，但要计算准确首地址
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length 1001

int howLong(char *a, char *b);        //已被弃用，因为无法事先准确算出是否进位，故无法算总位数

int multOneDigit(char *dst, char *src, char ch);         //多位数src * 一位数ch  的结果，存在dst中，返回最高位进位结果
int addResult(char *dst, char *src, int offset);    //将temp放在result中，从低位开始，初始偏移offset位

int main(void)
{	
	//初始化数组
	char *a = NULL;
	char *b = NULL;
	char *tempStart = NULL;
	char *resultStart = NULL;
	char *temp = NULL;
	char *result = NULL;
	a = (char*)malloc(length * sizeof(char));
	b = (char*)malloc(length * sizeof(char));

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
	
	//初始化temp和result，注意不要用memset，也不要置数字0否则长度计算错误
	tempStart = (char*)malloc((lenA + 2) * sizeof(char));        //开辟空间的长度要包括 进位和'\0'
	tempStart[lenA+1] = '\0';
	temp = tempStart;

	resultStart = (char*)malloc((lenResult + 1) * sizeof(char)); 
	for (i = 0; i < lenResult; i++)
		resultStart[i] = '0';
	resultStart[lenResult] = '\0';
	result = resultStart;

	//模拟乘法
	for (i = lenB - 1; i >= 0 + signB; i--)                      //从低位遍历b，排除b第1位可能存在的负号
	{
		ifTempCarry = multOneDigit(tempStart, a + signA , b[i]);                 //   a*b[i]，输出全为正，地址a+signA排除第一位的负号
		temp = tempStart + (1 - ifTempCarry) + signA;
		ifResultCarry = addResult(resultStart, temp, lenB - 1 - i);                 //累加结果存入原始resultStart相应位置
	}
	result = resultStart + (1 - (ifTempCarry + ifResultCarry));         //不考虑负号的情况下，根据进位确定首位的地址
	                                                                                              //若是两个正数，不变
	if (signA&&signB)
		result = result + 2;                                                             //两个负数，少两位负号
	if ((signA + signB) % 2)                                                          //一个负数，少一位，但是结果中要留一个负号位，所以位数不变，把第0位改成负号
		result[0] = '-';
		

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

int howLong(char *a, char *b)     //注意只计算数字长度，不算'\0'和符号
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int lenResult;
	if (a[0] == '-'&&b[0] == '-')
	{
		if ((a[1] - 48)*(b[1] - 48) < 10)      //负负得正，不进位，数字共  lena-1(去负号) + lenb-1(去负号)  -1(不进位)
			lenResult = lena + lenb - 3;
		else                                            //进位
			lenResult = lena + lenb - 2;
	}
	else if (a[0] == '-')
	{
		if ((a[1] - 48)*(b[0] - 48) < 10)      //正负得负，不进位，数字共  lena-1(去负号) + lenb  -1(不进位)
			lenResult = lena + lenb -2;
		else                                           //进位
			lenResult = lena + lenb -1;
	}
	else if (b[0] == '-')
	{
		if ((a[0] - 48)*(b[1] - 48) < 10)      //正负得负，不进位，同上
			lenResult = lena + lenb - 2;
		else
			lenResult = lena + lenb - 1;
	}
	else
	{
		if ((a[0] - 48)*(b[0] - 48) < 10)      //正正得正，不进位，数字共  lena + lenb  -1(不进位)
			lenResult = lena + lenb - 1;
		else
			lenResult = lena + lenb;
	}
	return lenResult;
}

int multOneDigit(char *dst, char *src, char ch)              //多位数src * 一位数ch  的结果，存在dst中，输出时+48
{
	int i, j, ifCarry = 0;
	int lenSrc = strlen(src);
	int lenDst = strlen(dst);
	char carry = 0;
	
	for (i = lenSrc - 1, j = lenDst - 1; i >= 0; i--, j--) //从低位遍历被乘数src
	{
		char tempResult = carry + (ch - 48)*(src[i] - 48);    //乘积和进位
		dst[j] = tempResult % 10 + 48;                //从低位填入dst，并+48
		carry = (char)tempResult / 10;
	}
	ifCarry = carry > 0 ? 1 : 0;
	if (ifCarry)
	{
		dst[j] = carry + 48;         //若果有进位，填上最高位
	}
	return ifCarry;
}

int addResult(char *dst, char *src, int offset)          //把src加入dst中，从低位起偏移offset开始相加
{
	int i, j, ifCarry = 0;
	char carry = 0;
	int lenSrc = strlen(src);
	int lenDst = strlen(dst);

	for (i = lenSrc - 1, j = lenDst - 1; i >= 0; i--, j--)      //从低位遍历src
	{
		//temp，result都已经加了48
		char tempResult = carry + dst[j - offset] - 48 + src[i] - 48;
		dst[j - offset] = tempResult % 10 + 48;
		carry = (char)tempResult / 10;
	}
	ifCarry = carry > 0 ? 1 : 0;
	if (ifCarry)
	{
		dst[j - offset] = carry + 48;         //若果有进位，填上最高位
	}
	return ifCarry;	
}