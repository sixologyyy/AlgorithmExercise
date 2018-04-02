//���η������˷�
/*           123
          *  456
��1�η��Σ�
����Ϊ3�����ֵõ�2��1���� 12-3��45-6
����12*45������2λ������12*6������1λ������45*3������1λ������3*6����λ
��λ�� = �����������ǰ��Σ���Ӧ�ĺ���Ԫ�ظ��� ֮��
��2�η��Σ�
12��45��Ϊ1-2��4-5��ͬ��

��������׶���˵Ľ���������δӴθ߶εĵ�λ��ʼ���
xxx
  xxx
  xxx
     xxx
	 xxx
	 xxx
	    
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define length 1001

char *result = '\0';
int index = 1;                  //index �����ڽ���ж�λ����1��ʼ

//�� a ֻʣ1λ���� ia=ja�����㵱ǰ�ֽ�ĳ˻�
//����a���±�� ia �� ja��b���±�� ib �� jb
//tbool=1 ��ʾ a,b ���±괦���׶Σ���ǰ1/2��1/4��1/8 ...����a ֻʣ���λ��
//move��ʾ�÷ֽ�����ڳ�ʼ�ֽ�Ҫ�ƶ�����λ����λ�� = �����������ǰ��Σ���Ӧ�ĺ���Ԫ�ظ��� ֮��
//���������ȴ����λ��ʼ��ģ����Ե���ʱҪ���ȵݹ�ǰ���
void getFill(char *a, char *b, int ia, int ja, int ib, int jb, int tbool, int move)
{
	int m, n, s, r, carry, t;     //m,n ��¼ a,b ����ֵ
									    // s �ӵ�λ���� b
										// r ��Ϊ stack �±�
										// carry ��¼��λ��ע�����ڴ��ۼӵĶο��ܺܶ࣬�����ܴܺ�Ҫ��int
										// t Ҳ���ڼ�¼��ǰһλ�Ľ�λ
	char *stack;                  //stack[0]~stack[r] ջ��Ŵӵ͵���λ�������˻���������λ

	m = a[ia] - 48;
	//�����׶�
	if (tbool)             
	{
		//r = (jb - ib > ja - ia) ? (jb - ib) : (ja - ia);
		r = jb - ib;
		stack = (char*)malloc(r + 4);
		//�˻�����stack
		for (r = carry = 0, s = jb; s >= ib; r++, s--)
		{
			n = b[s] - 48;
			stack[r] = (m*n + carry) % 10;
			carry = (m*n + carry) / 10;
		}
		if (carry)                  //���λ�Ľ�λ
		{
			stack[r] = carry;
			r++;
		}
		//stackд��result����result��λ��ʼ�����ƶ�ȫ�ֱ���index�Զ�λ��ִ�����index �ƶ����˸�λ����ĺ�һλ
		for (r--; r >= 0; r--, index++)         
			result[index] = stack[r];
		free(stack);
		//������0���൱�����ƣ�ִ����� index �ƶ����˽��ĩβ��һλ����'\0'��λ��
		for (move = move + index; index < move; index++)    
			result[index] = '\0';
	} 
	//�������׶�
	else           
	{
		//�����λ����moveλ��ʼ���b�ĵ�λ��ʼ��
		r = index - move - 1; 
		for (s = jb, carry = 0; s >= ib; r--, s--)
		{
			n = b[s] - 48;
			t = m*n + carry + result[r];
			result[r] = t % 10;
			carry = t / 10;
		}
		//b�����ˣ���ʣ��Ľ�λ
		for (; carry; r--)
		{
			t = carry + result[r];
			result[r] = t % 10;
			carry = t / 10;
		}
	}
}

//�����ַ���a��b�ķֽ⣬����a���±�� ia �� ja��b���±�� ib �� jb
//t = 1��ʾ a,b ���±괦���׶Σ���ǰ1/2��1/4��1/8 ...������Ϊֻ�ж���ǰ���ʱ����ʼ����ʱ�� t=1 �Żᱻ������
//move��ʾ�÷ֽ�����ڳ�ʼ�ֽ�Ҫ�ƶ�����λ
//������һ���ַ����ֽ⵽1��Ԫ��ʱ�����±���ȣ�������getFill()
int get(char *a, char *b, int ia, int ja, int ib, int jb, int t, int move)
{
	int m, n, s, j;                                                     //m,n�� a,b �±���м�㣬 s,j �� a,b ���ε�Ԫ�ظ�����Ҳ���Ǹ÷ֽ�Ӧ����λ��λ��
	if (ia == ja)
	{
		getFill(a, b, ia, ja, ib, jb, t, move);
		return 1;
	}
	else if (ib == jb)
	{
		getFill(b, a, ib, jb, ia, ja, t, move);
		return 1;
	}
	else
	{
		m = (ja + ia) / 2;
		n = (jb + ib) / 2;
		s = ja - m;
		j = jb - n;
		//����ĵ���Ҫ��˳�����ȴ�������ǰ��Σ���getFill()��Ҳ�������������λ��
		get(a, b, ia, m, ib, n, t, s + j + move);                      //ֻ�ж���ǰ���ʱ����һ�ηֽ�ʱ�� t=1 �Żᱻ����
		get(a, b, ia, m, n + 1, jb, 0, s + move);
		get(a, b, m + 1, ja, ib, n, 0, j + move);
		get(a, b, m + 1, ja, n + 1, jb, 0, 0 + move); 

	}
	return 0;
}

int main()
{
	char *a, *b;
	int n, flag;

	a = (char*)malloc(length);
	b = (char*)malloc(length);

	//����
	printf("��������a,b��\n");
	gets_s(a, length);
	gets_s(b, length);

	int lenA = strlen(a);
	int lenB = strlen(b);

	result = (char*)malloc(strlen(a) + strlen(b) + 2);
	flag = index = 1;
	result[0] = '\0';
	if (a[0] == '-'&&b[0] == '-')
		get(a, b, 1, lenA - 1, 1, lenB - 1, 1, 0);
	if (a[0] == '-'&&b[0] != '-')
		get(a, b, 1, lenA - 1, 0, lenB - 1, 1, 0), flag = 0;
	if (a[0] != '-'&&b[0] == '-')
		get(a, b, 0, lenA - 1, 1, lenB - 1, 1, 0), flag = 0;
	if (a[0] != '-'&&b[0] != '-')
		get(a, b, 0, lenA - 1, 0, lenB - 1, 1, 0);

	puts("\n�����");
	if (!flag)
		printf("-");
	if (result[0])
		printf("%d", result[0]);
	for (n = 1; n < index; n++)
		printf("%d", result[n]);
	printf("\n\n");

	free(a);
	free(b);
	free(result);

	return 0;
}