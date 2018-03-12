#include <stdio.h>
#include <stdlib.h>

#define Stack_Max 5

typedef struct
{
	char name[15];
	int age;
}DATA;

typedef struct stack
{
	DATA data[Stack_Max+1];
	int top;
}SeqStack;


//  1.初始化
SeqStack *initSeqStack()
{
	SeqStack *p;
	p=(SeqStack *)malloc(sizeof(SeqStack));
	if(p!=NULL)
	{
		p->top=-1;
		printf("初始化：成功\n");
		return p;
	}
	else
	{
		printf("初始化：内存分配失败\n");
		return NULL;
	}
}

//  2.删除栈
void deleteSeqStack(SeqStack *s)
{
	if(s!=NULL)
	{
		free(s);
	}
	printf("删除栈：成功\n");
}


//  3.判断栈是否满
int isFullSeqStack(SeqStack *s)
{
	if(s!=NULL)
	{
		if(s->top==Stack_Max-1)
		{
			printf("栈已满\n");
			return 1;
		}
		return 0;
	}
	printf("栈不存在\n");
	return -1;
}

//  4.判断栈是否空
int isEmptySeqStack(SeqStack *s)
{
	if(s!=NULL)
	{
		if(s->top==-1)
		{
			printf("栈为空\n");
			return 1;
		}
		return 0;
	}
	printf("栈不存在\n");
	return -1;	
}

//  5.清除栈
void clearSeqStack(SeqStack *s)
{
	if(s!=NULL)
	{
		s->top=-1;
		printf("清理栈：成功\n");
		return;
	}
	printf("栈不存在\n");
	return;
}

//  6.入栈
int inSeqStack(SeqStack *s,DATA temp)
{
	printf("入栈：");
	if(!isFullSeqStack(s))
	{
		s->data[++s->top]=temp;
		printf("成功\n");
		return 1;
	}
	return 0;
}

//  7.出栈
DATA outSeqStack(SeqStack *s)
{
	printf("出栈：");
	DATA temp={"error",-1};
	if(!isEmptySeqStack(s))
	{
		temp=s->data[s->top--];
		printf("姓名：%s 年龄：%d\n",temp.name,temp.age);
		return temp;
	}
	return temp;
}

//  8.获取栈顶元素
DATA getTopOfSeqStack(SeqStack *s)
{
	DATA temp={"error",-1};
	if(!isEmptySeqStack(s))
	{
		temp=s->data[s->top];
		printf("获取栈顶：姓名：%s 年龄：%d\n",temp.name,temp.age);
		return temp;
	}
	return temp;
}


//  主函数，测试功能
int main(void)
{
	SeqStack *s;
	DATA data1={"sxy",20};
	DATA data2={"yyy",15};
	DATA data3={"zpy",25};
	DATA data4={"rda",30};

	s=initSeqStack();
	outSeqStack(s);
	inSeqStack(s,data1);
	inSeqStack(s,data2);
	outSeqStack(s);
	inSeqStack(s,data3);
	inSeqStack(s,data4);

	inSeqStack(s,data4);
	inSeqStack(s,data3);
	inSeqStack(s,data2);

	outSeqStack(s);
	outSeqStack(s);
	outSeqStack(s);
	outSeqStack(s);
	outSeqStack(s);
	outSeqStack(s);

	deleteSeqStack(s);

}






