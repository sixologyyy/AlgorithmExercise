//大整数运算,加减乘除

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define LEN 100

typedef struct bigint
{
   char *num;					//指向长整数数组(序号0中保存着最低位)
   char sign;					//符号(1表示正数,-1表示负数) 
   int digit;					//保存该数的位数(实际位数) 
}BIGINT, *pBIGINT;

void BigIntTrim(pBIGINT num1);        //整理大整数，去掉前面多余的0
pBIGINT BigIntTrans(pBIGINT num);	   //字符串转数字 

pBIGINT BigIntAdd(const pBIGINT num1,const pBIGINT num2, pBIGINT result);     //加法函数
pBIGINT BigIntAdd1(const pBIGINT num1,const pBIGINT num2, pBIGINT result);	   //子函数，同号相加 
 
pBIGINT BigIntSub(const pBIGINT num1,const pBIGINT num2, pBIGINT result);	   //减法函数
pBIGINT BigIntSub1(const pBIGINT num1,const pBIGINT num2, pBIGINT result);    //子函数，异号相加（即相减）

pBIGINT BigIntMul(const pBIGINT num1,const pBIGINT num2, pBIGINT result);     //乘法函数 

pBIGINT BigIntDiv(const pBIGINT num1,const pBIGINT num2, pBIGINT result, pBIGINT residue);	//除法函数

void BigIntPrint(const pBIGINT result);	//输出大整数
int BigIntEqual(const pBIGINT num1,const pBIGINT num2);	//两数大小比较

//  1.整理大整数，去掉前面多余的0，并使调整其位数（大整数里面的数码是倒着存的）
void BigIntTrim(pBIGINT num1)
{
	int i;
	for (i = num1->digit - 1; i >= 0; i--)
	{
		if (num1->num[i] != 0)
			break;
	}
	if (i < 0)	//若num1全部为0
	{
		num1->digit = 1;	//设置位数为1
		num1->num[0] = 0;
	} 
	else
	  num1->digit = i + 1;	//实际位数     
}

//  2.将字符串转为数字表示，倒着存入结构体的数组中（即从低位开始）
pBIGINT BigIntTrans(pBIGINT num1)
{
	char *temp;					//临时数组 
	int i, k, len;
	len = strlen(num1->num);	//字符串长度 
	if (!(temp = (char *) malloc(sizeof(char) * len)))	//分配内存 
	{
		printf("内存分配失败!\n");
		exit(0);
	}

	i = 0;
	num1->sign = 1;	//保存为正数 
	if (num1->num[0] == '-')	//判断是否为负数 
	{
		num1->sign = -1;	//保存为负数 
		i++;
	}

	k = 0;	//数字位数计数器 
	while (num1->num[i] != '\0')	//字符串未结束 
	{
		if (num1->num[i] >= '0' && num1->num[i] <= '9')	//为数字0~9 
		{
			temp[k] = num1->num[i] - '0';	       //将ASCII码转换为对应数字 
			k++;
		}
		i++;
	}

	for (i = 0; i < num1->digit; i++)	//清空数组各元素 
	num1->num[i] = 0;
	num1->digit = k;	//转换后的数据位数 
	for (i = 0, k--; k >= 0; k--, i++)	//将临时数组各位反置保存到数组num中 
		num1->num[i] = temp[k];
	BigIntTrim(num1); //整理输入的大整数

	return num1;
}

//  3.输出大整数
void BigIntPrint(const pBIGINT result)
{
	int j;
	if(result->digit==1 && result->num[0]==0)
	{
		printf("0\n");
		return;
	}
	if (result->sign == -1)	//是负数 
		printf("-");	//输出负数 

	for (j = result->digit - 1; j >= 0; j--) //从高位到低位输出 
		printf("%d", result->num[j]);

	printf("\n");
}

//  4.比较绝对值大小，前者大返回1，相等0，否则-1
int BigIntEqual(const pBIGINT num1,const pBIGINT num2)
{
	int i;
	if (num1->digit > num2->digit)	//num1的位数大于num2 
		return 1;
	else if (num1->digit < num2->digit)	//num1的位数小于num2
		return -1;
	else	//两数位数相等 
	{
		i = num1->digit - 1;	//num1的数据位数 
		while (i >= 0)	//从高位向低位比
		{
			if (num1->num[i] > num2->num[i])	//num1对应位大于num2
				return 1;
			else if (num1->num[i] < num2->num[i])	//num1对应位小于num2
				return -1;
			else
				i--; //比较下一位 
		}
	}
   return 0;	//相等 
}

//  5.大整数相加
pBIGINT BigIntAdd(const pBIGINT num1,const pBIGINT num2, pBIGINT result)
{
	int i;
	//重置result的内容和位数
	for (i = 0; i < result->digit; i++)
		result->num[i] = 0;
	result->digit=2*LEN+1;

	i = BigIntEqual(num1, num2);	//比较两数绝对值大小

	if (num1->sign * num2->sign == 1)
	{
		if(i>0)
			BigIntAdd1(num1, num2, result);	//调用相加函数完成同号相加
		else
			BigIntAdd1(num2, num1, result);
	}
	//符号不同，则执减法
	else
	{
		//两数相等
		if (i == 0)
		{
			result->digit = 1;	//结果长度为一位数，就是数值0
			result->num[0] = 0;	//结果值为0
			result->sign = 1;	//结果设为正号 
			return result;	//返回 
		}
		if(i>0)
			BigIntSub1(num1, num2, result);	//调用相减函数完成异号相加
		else
			BigIntSub1(num2, num1, result);	
	} 

	return result;
}

//  5.5 子函数，同号相加，其中要求前者绝对值大
pBIGINT BigIntAdd1(const pBIGINT num1,const pBIGINT num2, pBIGINT result)
{
	int i, carry;
	carry = 0;
	result->sign = num1->sign;	//保存符号 

	for (i = 0; i < num1->digit; i++)	//将被加数复制到结果数组中 
		result->num[i] = num1->num[i];

	for (i = 0; i < num2->digit; i++)	//num2中的数小，位数不大于num1
	{
		result->num[i] = result->num[i] + num2->num[i] + carry;	//将对应位的数和进位数相加 
		carry = result->num[i] / 10;	//计算进位数据
		result->num[i] = result->num[i] % 10;	//保留一位     
	}
	while (carry==1)	//若最后还有进位 
	{
		result->num[i] = result->num[i] + carry;
		carry = result->num[i] / 10;	//计算进位数据
		result->num[i] = result->num[i] % 10;	//保留一位
		i++;
	}

	BigIntTrim(result);	//整理结果
	return result;
}

//  6.大整数相减
//相减相当于+ (-num2)，可以直接num2取反，调用加法。
//但为了不改变num2的值，也不增加存储空间，所以分类讨论。当遇到调用函数中num2在前面的时候，由于当做是-num2，所以要在调用完后单独修改result的符号
pBIGINT BigIntSub(const pBIGINT num1,const pBIGINT num2, pBIGINT result)
{
	int i;
	//重置result的内容和位数
	for (i = 0; i < result->digit; i++)
		result->num[i] = 0;
	result->digit=2*LEN+1;

	i=BigIntEqual(num1, num2);

	//同号相减
	if(num1->sign * num2->sign ==1)
	{
		if(i==1)
			BigIntSub1(num1, num2, result);
		else if(i==-1)
		{
			BigIntSub1(num2, num1, result);
			//此时符号跟随num2，需要调整
			result->sign=-1*num2->sign;
		}
		else
		{
			result->sign=-1*num2->sign;
			result->digit = 1;	//结果长度为一位数，就是数值0
			result->num[0] = 0;	//结果值为0
			result->sign = 1;	//结果设为正号 
			return result;	//返回 
		}
	}
	//异号相减
	else
	{
		if(i==1)
		{
			BigIntAdd1(num1, num2, result);
		}
		else if(i==-1)
		{
			BigIntAdd1(num2, num1, result);
			result->sign=-1*num2->sign;
		}
		else
		{
			result->sign=-1*num2->sign;
			result->digit = 1;	//结果长度为一位数，就是数值0
			result->num[0] = 0;	//结果值为0
			result->sign = 1;	//结果设为正号 
			return result;	//返回			
		}
	}
	return result;
}

//  6.5 子函数，异号相加（即相减），其中要求前者绝对值大
pBIGINT BigIntSub1(const pBIGINT num1,const pBIGINT num2, pBIGINT result)
{
	int i, borrow;
	result->sign = num1->sign;	//结果符号与绝对值大的num1相同

	borrow = 0;   //借位

	//将被减数的内容复制到结果中 
	for (i = 0; i < num1->digit; i++)
		result->num[i] = num1->num[i];

	//num1减去num2，并减去低位的借位 
	for (i = 0; i <= num2->digit; i++)
	{
		result->num[i] = result->num[i] - num2->num[i] - borrow;
		if (result->num[i] < 0)	//若为负数 
		{
			result->num[i] = 10 + result->num[i];	//向高位借位 
			borrow = 1;	 //设置借位值 
		}
		else
			borrow = 0;
	}
	while(borrow == 1)
	{
		result->num[i] = result->num[i] - borrow;
		if (result->num[i] < 0)	//若为负数 
		{
			result->num[i] = 10 + result->num[i];	//向高位借位 
			borrow = 1;	 //设置借位值 
		}
		else
			borrow=0;
		i++;
	}

	BigIntTrim(result);
	return result;
}

//  7.大整数相乘
pBIGINT BigIntMul(const pBIGINT num1,const pBIGINT num2, pBIGINT result)
{
	char carry, temp;
	int i, j, pos;

	//重置result的内容和位数
	for (i = 0; i < num1->digit + num2->digit; i++)
		result->num[i] = 0;
	result->digit=2*LEN+1;

	//用乘数的每1位乘以被乘数
	for (i = 0; i < num2->digit; i++) 
	{
		carry = 0;	//清除进位
		for (j = 0; j < num1->digit; j++)	//被乘数的每1位 
		{
			temp = num2->num[i] * num1->num[j] + carry;	//相乘并加上进位
			carry = temp / 10;	//计算进位carry
			temp = temp % 10;	//计算当前位的值
			pos = i + j;
			result->num[pos] += temp;	//计算结果累加到临时数组中 
			carry = carry + result->num[pos] / 10;	//计算进位 
			result->num[pos] = result->num[pos] % 10;
		}
		if (carry > 0)
		{
			result->num[i + j] = carry;	//加上最高位进位
			result->digit = i + j + 1;	//保存结果位数 
		}
		else
			result->digit = i + j;	//保存结果位数 
	}
	result->sign = num1->sign * num2->sign;	//结果的符号
	return result;
}

//  8.大整数相除，余数在residue中
pBIGINT BigIntDiv(const pBIGINT num1,const pBIGINT num2, pBIGINT result, pBIGINT residue)
{
	int i, j, k, m;				//k保存试商结果,m保存商的位数 
	char t;

	result->sign = num1->sign * num2->sign;	//商的符号
	residue->sign = num1->sign;       //余数符号跟随被除数

	//重置result的内容和位数
	for (i = 0; i < result->digit; i++)	//将result全部清0 
		result->num[i] = 0;
	result->digit=2*LEN+1;
	for (i = 0; i < residue->digit; i++)
		residue->num[i] = 0;
	residue->digit=num2->digit+1;


	m = 0;
	for (i = num1->digit - 1; i >= 0; i--)
	{
		//暂时设置余数的位数比除数多一位，最高位要放被除数中新来的数字
		residue->digit=num2->digit+1;
		for (j = residue->digit - 1; j > 0; j--)	//移余数 
			residue->num[j] = residue->num[j - 1];	//将序号低位的数据移向高位(实际是将余数中的最高位去除) 

		residue->num[0] = num1->num[i];	//复制被除数中的一位到余数的最低位中
		BigIntTrim(residue);//整理余数

		k = 0;	//试商
		while (BigIntEqual(residue, num2) >= 0)	//比较余数与除数的大小
		{
			BigIntSub1(residue, num2, residue);	//用余数减去除数，差值保存在余数中
			k++;	//试商加1 
		}
		result->num[m++] = k;	//保存商    
	}

	result->digit = m;	//保存商的位数
	for (i = 0; i < m / 2; i++)	//将商各位反转(在计算过程中序号0保存的是商的高位) 
	{
		t = result->num[i];
		result->num[i] = result->num[m - 1 - i];
		result->num[m - 1 - i] = t;
	}
	BigIntTrim(result);	//整理商 
	BigIntTrim(residue);	//整理余数 
	return result;
}

int main()
{
	BIGINT num1, num2, result, residue;	//参与运算的数、结果、余数 
	int i = 0;

	if (!(num1.num = (char *) malloc(sizeof(char) * (LEN + 1))))
	{
		printf("内存分配失败!\n");
		exit(0);
	}
	num1.digit = LEN + 1;
	if (!(num2.num = (char *) malloc(sizeof(char) * (LEN + 1))))
	{
		printf("内存分配失败!\n");
		exit(0);
	}
	num2.digit = LEN + 1;
	if (!(result.num = (char *) malloc(sizeof(char) * (2 * LEN + 1))))
	{
		printf("内存分配失败!\n");
		exit(0);
	}
	result.digit = 2 * LEN + 1;
	if (!(residue.num = (char *) malloc(sizeof(char) * (LEN + 1))))
	{
		printf("内存分配失败!\n");
		exit(0);
	}
	residue.digit = LEN + 1;

	//清空结果集 
	for (i = 0; i < result.digit; i++)
		result.num[i] = 0;

	printf("\n输入数1:");
	scanf("%s", num1.num);
	printf("输入数2:");
	scanf("%s", num2.num);
	BigIntTrans(&num1);
	BigIntTrans(&num2);
	 
	BigIntAdd(&num1, &num2, &result);
	printf("和：");
	BigIntPrint(&result);

	BigIntSub(&num1, &num2, &result);
	printf("差：");
	BigIntPrint(&result);

	BigIntMul(&num1, &num2, &result);
	printf("积：");
	BigIntPrint(&result);

	BigIntDiv(&num1, &num2, &result, &residue);
	printf("商:");
	BigIntPrint(&result);
	printf("余:");
	BigIntPrint(&residue);

	BIGINT result2,result3,result4;
	result2.num = (char *) malloc(sizeof(char) * (2 * LEN + 1));
	result3.num = (char *) malloc(sizeof(char) * (2 * LEN + 1));
	result4.num = (char *) malloc(sizeof(char) * (2 * LEN + 1));


	BigIntSub(BigIntDiv(BigIntMul(BigIntAdd(&num1,&num2,&result),&num2,&result2),&num1,&result3,&residue),&num1,&result4);
	printf("连续运算 (num1 + num2) * num2 / num1 - num1\n");
	BigIntPrint(&result4);
	 
	return 0;
}
