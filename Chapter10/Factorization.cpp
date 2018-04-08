/*
分解质因数
输入n
再输入n个数
输出每个数的因式分解结果
*/


#include<math.h>
#include<stdio.h>
#include<time.h>
#include<vector>
#include<stdlib.h>
using namespace std;

#define PRIME_RANGE 1000000
#define NUM_MAX 100000

struct standard_factor_struct
{
	char power;
	int factor;
};    //分解结果(因子和它的幂次)

//vector<vector<standard_factor_struct>> standard_factor_array(NUM_MAX);   //vector的每一项对应一个数的所有因子
vector<standard_factor_struct> standard_factor_array[NUM_MAX];
vector<standard_factor_struct>::iterator factor_it;     //一个数的因子的序号

typedef vector<standard_factor_struct> new_factor;

//vector<vector<standard_factor_struct>>::iterator index;


int num_of_nums, prime_index = 0;
long prime_array[PRIME_RANGE / 10];      //质数序列
long number[NUM_MAX];              //待分解的数
//int factor_array[NUM_MAX][35];    //分解结果(乘积形式的因子序列,因子以在指数序列中的序号表示)




char isPrime(long num)   //判断质数
{
	if (num <= 1) return 0;
	if (num == 2 || num == 3 || num == 5) return 1;
	if (num % 2 == 0) return 0;
	long i;
	for (i = 3; i <= sqrt((double)num); i += 2)
	{
		if (num%i == 0) return 0;
	}
	return 1;
}

void setPrimeArray(void)   //生成质数序列
{
	long op, ed;
	op = clock();

	long n = PRIME_RANGE;
	long i;
	for (i = 0; i <= n; i++)
	{
		if (isPrime(i)) prime_array[prime_index] = i, prime_index++;
	}

	ed = clock();
	printf("已生成质数序列，用时%ldms...\n", ed - op);
}

void inputData(void)       //输入待分解的n个数
{
	/*
	int i;
	printf("被分解的个数n:");
	scanf("%d", &num_of_nums);
	printf("输入%d个数:\n", num_of_nums);
	for (i = 0; i < num_of_nums; i++) scanf("%ld", number + i);
	*/
	long op, ed;
	op = clock();

	num_of_nums = NUM_MAX;
	int i;
	for (i = 0; i < NUM_MAX; i++)
	{
		number[i] = i;
	}

	ed = clock();
	printf("数据读入完成，用时%ldms...\n", ed - op);
}

void factorize(void)    //分解
{
	long op, ed;
	op = clock();

	int index;      //第index个待分解数
	long temp, i;
	for (index = 0; index < num_of_nums; index++)
	{
		if (number[index] >= 0) temp = number[index];
		else temp = -number[index];
		if (temp == 1 || temp == 0)    //特殊的01
		{
			new_factor standard_factor(1);
			standard_factor[0].factor = -(temp + 10);
			standard_factor[0].power = 1;
			standard_factor_array[index] = standard_factor;
			continue;
		}
		//int factor_index = 0;    //因子的序号
		new_factor standard_factor;
		for (i = 0; i < prime_index; i++)   //对于质数表里的每一个质数，都进行整除测试和幂次累加
		{
			int count = 0;      //用于累计幂次
			while (temp >= prime_array[i] || count > 0)
			{
				
				if (temp%prime_array[i] == 0)    //每发现一个因子，记录并累加幂次
				{
					count++;
					temp = temp / prime_array[i];
				}
				else
				{
					if (count > 0)
					{
						standard_factor_struct new_struct;
						new_struct.factor = prime_array[i];
						new_struct.power = count;
						standard_factor.push_back(new_struct);
						//factor_index++;
					}
					//次数为0的因子不增加序号
					break;        //跳出当前整除环节，检测下一个质数
				}
			}
		}
		standard_factor_array[index] = standard_factor;
		//printf("分解进度 %d/%d  %.2f%c\n", index, NUM_MAX, (double)100.0*index / NUM_MAX, 37);
		/*
		new_factor standard_factor(1);
		standard_factor[0].factor = 10000;
		standard_factor_array[factor_index] = standard_factor;
	    */
	}

	ed = clock();
	printf("分解完成，用时%ldms...\n", ed - op);
	
}

/*
void factorStandarlize(void)
{
	int i, j;
	for (j = 0; j < num_of_nums; j++)
	{
		int index = 0;
		int temp = factor_array[j][0];
		standard_factor[j][0].factor = factor_array[j][0];    //第j个数，第index个因子，的因子值
		standard_factor[j][0].power = 1;                     //第j个数，第index个因子，的计数值
		for (i = 1; factor_array[j][i] != 10000; i++)
		{
			if (temp == factor_array[j][i])
			{
				standard_factor[j][index].power++;
			}
			else
			{
				index++;
				standard_factor[j][index].factor = factor_array[j][i];
				standard_factor[j][index].power = 1;
				temp = factor_array[j][i];
			}
		}
		standard_factor[j][index + 1].factor= 10000;
	}
}
*/

void output(void)
{
	long op, ed;
	op = clock();

	FILE *fp;
	fp = fopen("out.txt", "w");


	//printf("分解结果:\n");
	fprintf(fp,"分解结果:\n");
	int i, j;
	for (j = 0; j < num_of_nums; j++)    //第j个数
	{
		if (number[j] >= 0) fprintf(fp,"%ld = ", number[j]);   //printf("%ld = ", number[j]);
		else fprintf(fp,"%ld = - ", number[j]);   //printf("%ld = - ", number[j]);
		for (factor_it = standard_factor_array[j].begin(); factor_it < standard_factor_array[j].end() - 1; factor_it++)
		{    //factor_it依次指向每个数的从小到大的因子
			 //standard_factor_array[j]指向第j行的vector<struct>， .begin()指向其中第一个struct
			if ((*factor_it).power != 1)
			{
				fprintf(fp,"%d^%d * ", (*factor_it).factor, (*factor_it).power);
				//printf("%d^%d * ", (*factor_it).factor, (*factor_it).power);
			}
			else
			{
				fprintf(fp,"%d * ", (*factor_it).factor);
				//printf("%d * ", (*factor_it).factor);
			}
		}
		if ((*factor_it).power != 1)
		{
			fprintf(fp,"%ld^%ld ", (*factor_it).factor, (*factor_it).power);
			//printf("%ld^%ld ", (*factor_it).factor, (*factor_it).power);
		}
		else
		{
			if ((*factor_it).factor == -11) fprintf(fp,"%d", 1);  //printf("%d", 1);
			else if ((*factor_it).factor == -10) fprintf(fp,"%d", 0);  //printf("%d", 0);
			else fprintf(fp,"%ld", (*factor_it).factor);  //printf("%ld", (*factor_it).factor);
		}
		fprintf(fp,"\n");
		//printf("\n");
	}

	fclose(fp);

	ed = clock();
	printf("输出完成，用时%ldms...\n", ed - op);
}

void main()
{
	//printf("standard_factor %d\nprime_array %d\nnumber %d \n", sizeof(standard_factor), sizeof(prime_array), sizeof(number));
	long op, ed;
	op = clock();

	setPrimeArray();
	inputData();
	factorize();
	output();

	ed = clock();
	printf("程序运行完毕，用时%ldms...\n", ed - op);

	scanf("%d", &num_of_nums);

}


