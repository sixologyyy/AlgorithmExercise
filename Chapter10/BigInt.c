//大整数运算

#include <stdio.h>
#include <string.h>
typedef struct bigint
{
   char *num;					//指向长整数数组(序号0中保存着最低位)
   char zhengfu;					//符号(1表示正数,-1表示负数) 
   int digit;					//保存该数的位数(实际位数) 
}BIGINT, *pBIGINT;
void BigIntTrans(pBIGINT num);	//字符串转数字 
void BigIntMul(pBIGINT num1, pBIGINT num2, pBIGINT result);	//乘法函数 
void BigIntAdd1(pBIGINT num1, pBIGINT num2, pBIGINT result);	//同号数相加 
void BigIntAdd(pBIGINT num1, pBIGINT num2, pBIGINT result);	//加法函数 
void BigIntSub1(pBIGINT num1, pBIGINT num2, pBIGINT result);	//异号相减函数
void BigIntSub(pBIGINT num1, pBIGINT num2, pBIGINT result);	//减法函数 
void BigIntDiv(pBIGINT num1, pBIGINT num2, pBIGINT result, pBIGINT residue);	//除法函数 
void BigIntPrint(pBIGINT result);	//输出大整数
int BigIntEqual(pBIGINT num1, pBIGINT num2);	//两数大小比较

void BigIntTrim(pBIGINT num1) //整理大整数，去掉前面多余的0，并使调整其位数
{
   int i;
   for (i = num1->digit - 1; i >= 0; i--)
   {
	  if (num1->num[i] != 0)
		 break;
   }
   if (i < 0)	//若余数全部为0
   {
	  num1->digit = 1;	//设置余数位数为1
	  num1->num[0] = 0;
   } else
	  num1->digit = i + 1;	//余数位数     
}
void BigIntTrans(pBIGINT num1) //将字符串转为数字表示
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
   num1->zhengfu = 1;	//保存为正数 
   if (num1->num[0] == '-')	//判断是否为负数 
   {
	  num1->zhengfu = -1;	//保存为负数 
	  i++;
   }
   k = 0;	//数字位数计数器 
   while (num1->num[i] != '\0')	//字符串未结束 
   {
	  if (num1->num[i] >= '0' && num1->num[i] <= '9')	//为数字0~9 
	  {
		 temp[k] = num1->num[i] - '0';	//将ASCII码转换为对应数字 
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
}
void BigIntPrint(pBIGINT result) //输出大整数 
{
   int j;
   if (result->zhengfu == -1)	//是负数 
	  printf("-");	//输出负数 
   if (result->digit == 1 && result->num[0] == 0)	//若大整数为0
	  printf("0");
   else //不为0 
   {
	  for (j = result->digit - 1; j >= 0; j--) //从高位到低位输出 
		 printf("%d", result->num[j]);
   }
}
int BigIntEqual(pBIGINT num1, pBIGINT num2) //比较绝对值大小
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
void BigIntAdd(pBIGINT num1, pBIGINT num2, pBIGINT result)
{
   int i;
   i = BigIntEqual(num1, num2);	//比较两数绝对值大小
   if (i < 0)	//num1绝对值小于num2 
   {
     pBIGINT temp;
     temp = num1;	//交换两数 
     num1 = num2;
     num2 = temp;
   }
   if (num1->zhengfu * num2->zhengfu < 0)	//符号不同，则执减法 
   {	  
	  if (i == 0)	//两数相等
	  {
		 result->digit = 1;	//结果长度为一位数，就是数值0
		 result->num[0] = 0;	//结果值为0
		 result->zhengfu = 1;	//结果设为正号 
		 return;	//返回 
	  } 
	  BigIntSub1(num1, num2, result);	//调用相减函数完成异号相加的情况
   } else
	  BigIntAdd1(num1, num2, result);	//调用相加函数完成同号相加
}
void BigIntAdd1(pBIGINT num1, pBIGINT num2, pBIGINT result)
{
   int i, carry;
   carry = 0;
   result->zhengfu = num1->zhengfu;	//保存符号 
   for (i = 0; i < num1->digit; i++)	//将被加数复制到结果数组中 
	  result->num[i] = num1->num[i];
   for (i = 0; i < num2->digit; i++)	//num2中的数小，可能位数也小些
   {
	  result->num[i] = result->num[i] + num2->num[i] + carry;	//将对应位的数和进位数相加 
	  carry = result->num[i] / 10;	//计算进位数据
	  result->num[i] = result->num[i] % 10;	//保留一位     
   }
   if (carry)	//若最后还有进位 
	  result->num[i] = result->num[i] + carry;
   BigIntTrim(result);	//整理结果 
}
void BigIntSub1(pBIGINT num1, pBIGINT num2, pBIGINT result) //异号相减函数
{
   int i, borrow;
   result->zhengfu = num1->zhengfu;	//因num1绝对值比num2大，结果符号与num1相同 
   borrow = 0;
   for (i = 0; i < num1->digit; i++)	//将被减数的内容复制到结果中 
	  result->num[i] = num1->num[i];
   for (i = 0; i <= num2->digit; i++)
   {
	  result->num[i] = result->num[i] - num2->num[i] - borrow;	//num1减去num2，并减去低位的借位 
	  if (result->num[i] < 0)	//若为负数 
	  {
		 result->num[i] = 10 + result->num[i];	//向高位借位 
		 borrow = 1;	//设置借位值 
	  } else
		 borrow = 0;
   }
   if (borrow == 1)
	  result->num[i] = result->num[i] - borrow;
   BigIntTrim(result);
   /*i = num1->digit;
   while (i > 0)
   {
	  if (result->num[i] == 0)
		 i--;
	  else
		 break;
   }
   result->digit = i;	//保存结果位数*/
}
void BigIntSub(pBIGINT num1, pBIGINT num2, pBIGINT result) //减法函数 
{
   num2->zhengfu = -1 * num2->zhengfu;	//将减数的符号取反 
   BigIntAdd(num1, num2, result);	//调用加法函数 
}
void BigIntMul(pBIGINT num1, pBIGINT num2, pBIGINT result)
{
   char carry, temp;
   int i, j, pos;
   for (i = 0; i < num1->digit + num2->digit; i++)	//结果数组和中间数组清0 
	  result->num[i] = 0;
   for (i = 0; i < num2->digit; i++)	//用乘数的每1位乘以被乘数 
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
	  } else
		 result->digit = i + j;	//保存结果位数 
   }
   result->zhengfu = num1->zhengfu * num2->zhengfu;	//结果的符号 
}
void BigIntDiv(pBIGINT num1, pBIGINT num2, pBIGINT result, pBIGINT residue) //除法函数函数 》� 跞サ臀坏慕栉� 雗um1相同 数
{
   BIGINT quo1, residuo1, quo2;
   int i, j, k, m;				//k保存试商结果,m保存商的位数 
   char t;
   result->zhengfu = num1->zhengfu * num2->zhengfu;	//商的符号
   residue->num = (char *) malloc(sizeof(char) * num2->digit);	//分配余数的内存空间
   residue->digit = num2->digit+1;	//设置余数的初始位数与除数相同 
   for (i = 0; i < residue->digit; i++)	//将余数全部清0 
	  residue->num[i] = 0;
   m = 0;
   for (i = num1->digit - 1; i >= 0; i--)
   {
	  residue->digit=num2->digit+1; //重新设置余数的位数比除数多一位 
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
}
int main()
{
   BIGINT num1, num2, result, residue;	//参与运算的数、结果、余数 
   int i = 0, len;
   char op;
   printf("输入最大数的位数:");
   scanf("%d", &len);
   if (!(num1.num = (char *) malloc(sizeof(char) * (len + 1))))
   {
	  printf("内存分配失败!\n");
	  exit(0);
   }
   num1.digit = len + 1;
   if (!(num2.num = (char *) malloc(sizeof(char) * (len + 1))))
   {
	  printf("内存分配失败!\n");
	  exit(0);
   }
   num2.digit = len + 1;
   if (!(result.num = (char *) malloc(sizeof(char) * (2 * len + 1))))
   {
	  printf("内存分配失败!\n");
	  exit(0);
   }
   result.digit = 2 * len + 1;
   for (i = 0; i < result.digit; i++)	//清空结果集 
	  result.num[i] = 0;
   printf("选择大整数的运算(+、-、*、/):");
   fflush(stdin);
   scanf("%c", &op);
   switch (op)
   {
   case '+':
	  printf("\n输入被加数:");
	  scanf("%s", num1.num);
	  printf("\n输入加数:");
	  scanf("%s", num2.num);
	  BigIntTrans(&num1);
	  BigIntTrans(&num2);
	  BigIntAdd(&num1, &num2, &result);	//加法 
	  break;
   case '-':
	  printf("\n输入被减数:");
	  scanf("%s", num1.num);
	  printf("\n输入减数:");
	  scanf("%s", num2.num);
	  BigIntTrans(&num1);
	  BigIntTrans(&num2);
	  BigIntSub(&num1, &num2, &result);	//减法 
	  break;
   case '*':
	  printf("\n输入被乘数:");
	  scanf("%s", num1.num);
	  printf("\n输入乘数:");
	  scanf("%s", num2.num);
	  BigIntTrans(&num1);
	  BigIntTrans(&num2);
	  BigIntMul(&num1, &num2, &result);	//乘法 
	  break;
   case '/':
	  printf("\n输入被除数:");
	  scanf("%s", num1.num);
	  printf("\n输入除数:");
	  scanf("%s", num2.num);
	  BigIntTrans(&num1);
	  BigIntTrans(&num2);
	  if (num2.digit == 1 && num2.num[0] == 0)	//大整数为0
		 printf("除数不能为0!\n");
	  else
		 BigIntDiv(&num1, &num2, &result, &residue);	//除法法 
	  break;
   }
   if (op == '/')
   {
	  if (!(num2.digit == 1 && num2.num[0] == 0))	//为除法且除数不为0
	  {
		 printf("商:");
		 BigIntPrint(&result);
		 printf("\t余数:");
		 BigIntPrint(&residue);
	  }
   } else
   {
	  printf("\n结果:");
	  BigIntPrint(&result);
   }

   getch();
   return 0;
}
