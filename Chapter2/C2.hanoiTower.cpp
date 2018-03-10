//模拟汉诺塔
#include <stdio.h>

void move(int n, char x, char y, char z);      //n层的塔，把x上的堆借助y移动到z上

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

	move(n - 1, x, z, y);                  //先把前n-1个借助z移到y上
	printf("%c -> %c\n", x, z);       //再把最后一个移到z上
	move(n - 1, y, x, z);                  //最后把n-1个从y移到z上
	printf("\n");
}

