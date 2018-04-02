//分治法大数乘法
/*           123
          *  456
第1次分治：
长度为3，二分得到2和1，即 12-3，45-6
计算12*45并左移2位，计算12*6并左移1位，计算45*3并左移1位，计算3*6不移位
移位数 = （如果乘数在前半段）对应的后半段元素个数 之和
第2次分治：
12、45分为1-2，4-5，同理

最后先填首段相乘的结果，再依次从次高段的低位开始填，即
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
int index = 1;                  //index 用于在结果中定位，从1开始

//当 a 只剩1位，即 ia=ja，计算当前分解的乘积
//其中a的下标从 ia 到 ja，b的下标从 ib 到 jb
//tbool=1 表示 a,b 的下标处在首段（即前1/2，1/4，1/8 ...），a 只剩最高位了
//move表示该分解相对于初始分解要移动多少位，移位数 = （如果乘数在前半段）对应的后半段元素个数 之和
//本函数是先从最高位开始填的，所以调用时要优先递归前半段
void getFill(char *a, char *b, int ia, int ja, int ib, int jb, int tbool, int move)
{
	int m, n, s, r, carry, t;     //m,n 记录 a,b 的数值
									    // s 从低位遍历 b
										// r 作为 stack 下标
										// carry 记录进位，注意由于待累加的段可能很多，它可能很大，要用int
										// t 也用于记录当前一位的进位
	char *stack;                  //stack[0]~stack[r] 栈存放从低到高位的两两乘积，包括进位

	m = a[ia] - 48;
	//都是首段
	if (tbool)             
	{
		//r = (jb - ib > ja - ia) ? (jb - ib) : (ja - ia);
		r = jb - ib;
		stack = (char*)malloc(r + 4);
		//乘积存入stack
		for (r = carry = 0, s = jb; s >= ib; r++, s--)
		{
			n = b[s] - 48;
			stack[r] = (m*n + carry) % 10;
			carry = (m*n + carry) / 10;
		}
		if (carry)                  //最高位的进位
		{
			stack[r] = carry;
			r++;
		}
		//stack写入result，从result高位开始，并移动全局变量index以定位，执行完后index 移动到了高位结果的后一位
		for (r--; r >= 0; r--, index++)         
			result[index] = stack[r];
		free(stack);
		//后面填0，相当于左移，执行完后 index 移动到了结果末尾后一位，即'\0'的位置
		for (move = move + index; index < move; index++)    
			result[index] = '\0';
	} 
	//不都是首段
	else           
	{
		//从最低位左移move位开始填，从b的低位开始算
		r = index - move - 1; 
		for (s = jb, carry = 0; s >= ib; r--, s--)
		{
			n = b[s] - 48;
			t = m*n + carry + result[r];
			result[r] = t % 10;
			carry = t / 10;
		}
		//b乘完了，填剩余的进位
		for (; carry; r--)
		{
			t = carry + result[r];
			result[r] = t % 10;
			carry = t / 10;
		}
	}
}

//计算字符串a，b的分解，其中a的下标从 ia 到 ja，b的下标从 ib 到 jb
//t = 1表示 a,b 的下标处在首段（即前1/2，1/4，1/8 ...）（因为只有都是前半段时，初始调用时的 t=1 才会被保留）
//move表示该分解相对于初始分解要移动多少位
//当其中一个字符串分解到1个元素时（即下标相等），调用getFill()
int get(char *a, char *b, int ia, int ja, int ib, int jb, int t, int move)
{
	int m, n, s, j;                                                     //m,n是 a,b 下标的中间点， s,j 是 a,b 后半段的元素个数，也就是该分解应该移位的位数
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
		//下面的调用要按顺序，最先处理两个前半段，在getFill()中也是最先填上最高位的
		get(a, b, ia, m, ib, n, t, s + j + move);                      //只有都是前半段时，第一次分解时的 t=1 才会被保留
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

	//输入
	printf("输入整数a,b：\n");
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

	puts("\n结果：");
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