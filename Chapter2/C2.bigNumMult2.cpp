//�����˷�
/*
123 * 456
�ӵ�λ�������������� i λ�͵� j λ�ĳ˻�����ڽ���ĵ� i+j λ 

ע���м�����ÿһλ��ֵ���ܷǳ������ų�����λ������Խ��Խ��
��  99...99 * 99...99  (100��9)
���м����У�i+j=0+99,1+98,...,99+0��100���������99λ���ܺ���100*81=8100
���� N λ�� a �� M λ�� b�������м����� min(M,N)*81
unsigned int ��� 2^31-1��/81�� 53024287��Ҳ���������������Ȳ�Ҫ��������ֵ

ע��sizeof������̬����Ŀռ�ĳ��ȣ�ֻ�������ָ��Ĵ�С��һ�㶼��4��

Ȼ�����λ

����ַ��������㹻�Ŀռ䣬��ǰ��'0'���ӵ�λ��ʼ���㣬���ʱѰ�ҵ�һ����'0'

*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length 1001


void multEveryDigit(unsigned int *dst, char *srcA, char *srcB, int lenDst);         //����ÿ����λ�ֱ���ˣ��˻�������>10������ i+j λ
                                                                                                  //ע��Ҫ����int����ĳ���������������֪����ĳ��ȣ�sizeof�޷����int���鳤��
void countCarry(char *dst,unsigned int* src, int lenSrc);           //�������Ͻ����ÿһλ�Ľ�λ

int main(void)
{
	//��ʼ������
	char *a = NULL;
	char *b = NULL;
	char *resultStart = NULL;
	char *result = NULL;
	a = (char*)malloc(length * sizeof(char));
	b = (char*)malloc(length * sizeof(char));

	unsigned int *tempStart = NULL;
	unsigned int *temp = NULL;

	//����
	printf("��������a,b��\n");
	gets_s(a, length);
	gets_s(b, length);

	//��������
	int i, j;
	int ifTempCarry = 0, ifResultCarry = 0;      //���λ��λ
	int lenA = strlen(a);
	int signA = a[0] == '-' ? 1 : 0;     //�и���ʱsign=1������0
	int lenB = strlen(b);
	int signB = b[0] == '-' ? 1 : 0;
	int lenResult = lenA + lenB;      //���ܵ���ĳ��ȣ��������źͽ�λ��������'\0'

    //��ʼ��temp��result    ����Ҫ��memset��
	tempStart = (unsigned int*)malloc((lenResult + 1) * sizeof(int));        //���ٿռ�ĳ���Ҫ���� ��λ
	for (i = 0; i < lenResult; i++)                 //��0
		tempStart[i] = 0;
	temp = tempStart;

	resultStart = (char*)malloc((lenResult + 1) * sizeof(char));
	for (i = 0; i < lenResult; i++)
		resultStart[i] = '0';
	resultStart[lenResult] = '\0';
	result = resultStart;

	//ģ��˷�
	multEveryDigit(tempStart, a + signA, b + signB, lenResult);
	countCarry(resultStart, tempStart, lenResult);
	for (i = 0; resultStart[i] == '0'; i++);         //Ѱ�����λ(��һ����Ϊ'0')��λ��
	if ((signA + signB) % 2)         //���Ϊ��
		result[i - 1] = '-', result += i - 1;
	else
		result += i;


	puts("\n�����");
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


void multEveryDigit(unsigned int *dst, char *srcA, char *srcB, int lenDst)              // srcA��srcB�� i , j λ������˴��� dst �� i + j λ��ע��dst������'0'
{
	int i, j;
	int lenA = strlen(srcA);
	int lenB = strlen(srcB);
	char carry = 0;

	for (i = 0; i <= lenA - 1; i++)
	{
		for (j = 0; j <= lenB - 1; j++)
		{
			dst[lenDst - 1 - (i + j)] += (srcA[lenA - 1 - i] - 48)*(srcB[lenB - 1 - j] - 48);     //�ӵ�λ������ע���±ꡣ���ڲ�ͬ i+j ���ܽ����ͬ������Ҫ�ۼ�(+=)
																															  //ע���ʱ��char���ܻ������ȡֵ-127~128���ڴ����λʱ����
		}
	}
}

void countCarry(char *dst, unsigned int* src, int lenSrc)        //����dst����ĳһλ����10���λ
{
	int i;
	unsigned int carry = 0;
	unsigned int tempResult = 0;            //��Ҫ��char�ͣ�������������99*99��ʱ�򣬵ڶ�λ�����Ϊ162+8=170����charΪ -128~127��
	int lenDst = strlen(dst);

	for (i = lenSrc - 1; i >= 0; i--)      //�ӵ�λ����
	{
		//src�д�������ͣ�����-48�����������dst[]����char
		tempResult = carry + src[i];		
		dst[i] = tempResult % 10 + 48;
		carry = tempResult / 10;
	}
	for (i = 0; dst[i] == '0'; i++);         //Ѱ�����λ(��һ����Ϊ'0')��λ��
	if(carry)
		dst[i] = carry + 48;                      //����н�λ������
}