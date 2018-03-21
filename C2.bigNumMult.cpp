//ģ����������˷�
/*
        123 * 456
		�ӵ�λ����456������123*6 , 123*5 , 123*4
		�õ��Ľ���ֱ���λ0,1,2��ӣ������λ
		result����ۼӽ����temp��Ÿ�λ���뱻�����Ļ�

		���ڴӵ�λ����λ�㣬��Ԥ��ȷ�������λ��ʱ�������ѣ���Ϊ���λ�Ľ�λ�п����ǴӺܵ͵�λ�ô�������
		����취�������㹻�Ŀռ䣬ȫ����'0'���׵�ַΪ resultStart
		                ���ʱ�������λ�Ľ�λ����tempCarryΪa*b[i]�Ľ����λ�Ƿ��λ��resultCarryΪ�ۼ����λ�Ƿ��λ
						ifCarry = tempCarry + resultCarry  (������ͬʱΪ1)����� resultStart+��1-ifCarry�� �����ַ�����������ǰ����ַ�
					    ��    11                  99 
						      *99                  99
						--------------------------------------
							   99                 891
							 99                 891
						--------------------------------------
					       1089               9801
						temp�޽�λ       temp��
						result�н�λ       result��
						result��temp������ͬʱ��λ����Ϊtemp���λ���������λ�����Ϊ99...*9=899...���ڶ���λ���Ҳ��899...
						                                             ��result���ۼӣ���Ϊ899...+089...�����99...�����ۼ���result�����λ����λ


					    ��ÿ��temp�Ĵ���ͬ�ϣ� ifCarry = tempCarry����ԭʼ��tempStart�������������tempStart+��1-ifCarry ��Ϊ��ʵ��temp��λ

		����취2�������㹻�Ŀռ䣬������ǰ����'0'�����Ա����ҵ���һ������'0'�ļ���        - -

		�ɰ汾�У�����tempʱ��������ifCarry��������ʵ��temp�ĵ�ַ��Ч����һ���ģ���Ҫ����׼ȷ�׵�ַ
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define length 1001

int howLong(char *a, char *b);        //�ѱ����ã���Ϊ�޷�����׼ȷ����Ƿ��λ�����޷�����λ��

int multOneDigit(char *dst, char *src, char ch);         //��λ��src * һλ��ch  �Ľ��������dst�У��������λ��λ���
int addResult(char *dst, char *src, int offset);    //��temp����result�У��ӵ�λ��ʼ����ʼƫ��offsetλ

int main(void)
{	
	//��ʼ������
	char *a = NULL;
	char *b = NULL;
	char *tempStart = NULL;
	char *resultStart = NULL;
	char *temp = NULL;
	char *result = NULL;
	a = (char*)malloc(length * sizeof(char));
	b = (char*)malloc(length * sizeof(char));

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
	
	//��ʼ��temp��result��ע�ⲻҪ��memset��Ҳ��Ҫ������0���򳤶ȼ������
	tempStart = (char*)malloc((lenA + 2) * sizeof(char));        //���ٿռ�ĳ���Ҫ���� ��λ��'\0'
	tempStart[lenA+1] = '\0';
	temp = tempStart;

	resultStart = (char*)malloc((lenResult + 1) * sizeof(char)); 
	for (i = 0; i < lenResult; i++)
		resultStart[i] = '0';
	resultStart[lenResult] = '\0';
	result = resultStart;

	//ģ��˷�
	for (i = lenB - 1; i >= 0 + signB; i--)                      //�ӵ�λ����b���ų�b��1λ���ܴ��ڵĸ���
	{
		ifTempCarry = multOneDigit(tempStart, a + signA , b[i]);                 //   a*b[i]�����ȫΪ������ַa+signA�ų���һλ�ĸ���
		temp = tempStart + (1 - ifTempCarry) + signA;
		ifResultCarry = addResult(resultStart, temp, lenB - 1 - i);                 //�ۼӽ������ԭʼresultStart��Ӧλ��
	}
	result = resultStart + (1 - (ifTempCarry + ifResultCarry));         //�����Ǹ��ŵ�����£����ݽ�λȷ����λ�ĵ�ַ
	                                                                                              //������������������
	if (signA&&signB)
		result = result + 2;                                                             //��������������λ����
	if ((signA + signB) % 2)                                                          //һ����������һλ�����ǽ����Ҫ��һ������λ������λ�����䣬�ѵ�0λ�ĳɸ���
		result[0] = '-';
		

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

int howLong(char *a, char *b)     //ע��ֻ�������ֳ��ȣ�����'\0'�ͷ���
{
	int lena = strlen(a);
	int lenb = strlen(b);
	int lenResult;
	if (a[0] == '-'&&b[0] == '-')
	{
		if ((a[1] - 48)*(b[1] - 48) < 10)      //��������������λ�����ֹ�  lena-1(ȥ����) + lenb-1(ȥ����)  -1(����λ)
			lenResult = lena + lenb - 3;
		else                                            //��λ
			lenResult = lena + lenb - 2;
	}
	else if (a[0] == '-')
	{
		if ((a[1] - 48)*(b[0] - 48) < 10)      //�����ø�������λ�����ֹ�  lena-1(ȥ����) + lenb  -1(����λ)
			lenResult = lena + lenb -2;
		else                                           //��λ
			lenResult = lena + lenb -1;
	}
	else if (b[0] == '-')
	{
		if ((a[0] - 48)*(b[1] - 48) < 10)      //�����ø�������λ��ͬ��
			lenResult = lena + lenb - 2;
		else
			lenResult = lena + lenb - 1;
	}
	else
	{
		if ((a[0] - 48)*(b[0] - 48) < 10)      //��������������λ�����ֹ�  lena + lenb  -1(����λ)
			lenResult = lena + lenb - 1;
		else
			lenResult = lena + lenb;
	}
	return lenResult;
}

int multOneDigit(char *dst, char *src, char ch)              //��λ��src * һλ��ch  �Ľ��������dst�У����ʱ+48
{
	int i, j, ifCarry = 0;
	int lenSrc = strlen(src);
	int lenDst = strlen(dst);
	char carry = 0;
	
	for (i = lenSrc - 1, j = lenDst - 1; i >= 0; i--, j--) //�ӵ�λ����������src
	{
		char tempResult = carry + (ch - 48)*(src[i] - 48);    //�˻��ͽ�λ
		dst[j] = tempResult % 10 + 48;                //�ӵ�λ����dst����+48
		carry = (char)tempResult / 10;
	}
	ifCarry = carry > 0 ? 1 : 0;
	if (ifCarry)
	{
		dst[j] = carry + 48;         //�����н�λ���������λ
	}
	return ifCarry;
}

int addResult(char *dst, char *src, int offset)          //��src����dst�У��ӵ�λ��ƫ��offset��ʼ���
{
	int i, j, ifCarry = 0;
	char carry = 0;
	int lenSrc = strlen(src);
	int lenDst = strlen(dst);

	for (i = lenSrc - 1, j = lenDst - 1; i >= 0; i--, j--)      //�ӵ�λ����src
	{
		//temp��result���Ѿ�����48
		char tempResult = carry + dst[j - offset] - 48 + src[i] - 48;
		dst[j - offset] = tempResult % 10 + 48;
		carry = (char)tempResult / 10;
	}
	ifCarry = carry > 0 ? 1 : 0;
	if (ifCarry)
	{
		dst[j - offset] = carry + 48;         //�����н�λ���������λ
	}
	return ifCarry;	
}