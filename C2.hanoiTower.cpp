//ģ�⺺ŵ��
#include <stdio.h>

void move(int n, char x, char y, char z);      //n���������x�ϵĶѽ���y�ƶ���z��

int main(void)
{
	move(5, 'a', 'b', 'c');
	
	return 1;
}

void move(int n, char x, char y, char z)
{
	if (n == 1)
	{
		printf("%c -> %c\n", x, z); 
		return;
	}

	move(n - 1, x, z, y);                  //�Ȱ�ǰn-1������z�Ƶ�y��
	printf("%c -> %c\n", x, z);       //�ٰ����һ���Ƶ�z��
	move(n - 1, y, x, z);                  //����n-1����y�Ƶ�z��
	printf("\n");
}

