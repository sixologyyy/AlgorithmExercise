// 输入6个数字，程序在前5个数字之间填入4个运算符(+-*/)，使得计算结果等于第6个数

#include <stdio.h>

int main(void)
{
	float num[6];
	char op[4];      //4个运算符，取值1~4分别代表+-*/
	char opLib[] = { ' ','+','-','*','/' };
	float preResult, curNum;        //可以认为是当前计算的左边数和右边数
	int i, j, i1, i2, i3, i4;
	int sign, count = 0;
	float result;

	printf("输入6个数：");
	scanf("%f %f %f %f %f %f", num, num + 1, num + 2, num + 3, num + 4, num + 5);

	for (i1 = 1; i1 <= 4; i1++)                                                   //遍历第一个运算符
	{
		op[0] = opLib[i1];
		if (op[0] != 4 || op[0] == 4 && num[1] != 0)           //防止除号后面是0
		{
			for (i2 = 1; i2 <= 4; i2++)
			{
				op[1] = opLib[i2];
				if (op[1] != 4 || op[1] == 4 && num[2] != 0)
				{
					for (i3 = 1; i3 <= 4; i3++)
					{
						op[2] = opLib[i3];
						if (op[2] != 4 || op[2] == 4 && num[3] != 0)
						{
							for (i4 = 1; i4 <= 4; i4++)
							{
								op[3] = opLib[i4];
								if (op[3] != 4 || op[3] == 4 && num[4] != 0)
								{
									preResult = 0, curNum = num[0], sign = 1;
									for (j = 0; j < 4; j++)                              //计算          
									{
										switch (op[j])
										{
										case '+': preResult = preResult + sign*curNum; curNum = num[j + 1]; sign = 1; break;
										case '-': preResult = preResult + sign*curNum; curNum = num[j + 1]; sign = -1; break;
										case '*': curNum = curNum*num[j + 1]; break;
										case '/': curNum = curNum / num[j + 1]; break;
										}
									}
									result = preResult + sign*curNum;
									if (result == num[5])
									{
										count++;
										printf("%g %c %g %c %g %c %g %c %g = %g\n", num[0], op[0], num[1], op[1], num[2], op[2], num[3], op[3], num[4], num[5]);
									}
								}
							}
						}
					}
				}
			}
		}
	}
	if (count == 0) printf("没有结果\n");

	return 1;
}
