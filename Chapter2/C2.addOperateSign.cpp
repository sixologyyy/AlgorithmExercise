// ����6�����֣�������ǰ5������֮������4�������(+-*/)��ʹ�ü��������ڵ�6����

#include <stdio.h>

int main(void)
{
	float num[6];
	char op[4];      //4���������ȡֵ1~4�ֱ����+-*/
	char opLib[] = { ' ','+','-','*','/' };
	float preResult, curNum;        //������Ϊ�ǵ�ǰ�������������ұ���
	int i, j, i1, i2, i3, i4;
	int sign, count = 0;
	float result;

	printf("����6������");
	scanf("%f %f %f %f %f %f", num, num + 1, num + 2, num + 3, num + 4, num + 5);

	for (i1 = 1; i1 <= 4; i1++)                                                   //������һ�������
	{
		op[0] = opLib[i1];
		if (op[0] != 4 || op[0] == 4 && num[1] != 0)           //��ֹ���ź�����0
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
									for (j = 0; j < 4; j++)                              //����          
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
	if (count == 0) printf("û�н��\n");

	return 1;
}
