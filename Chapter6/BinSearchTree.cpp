/*
二叉查找树的创建、添加、查找、删除
左子节点 < 父节点 <右子节点，且左右子树也是二叉查找树
二叉查找树的中序遍历是一个递增序列
*/

#include <stdio.h>
#include <stdlib.h>
#define ARRAYLEN 10

int source[]={55,94,6,65,11,38,91,29,67,82};

typedef struct BinSearchNode
{
	int data;
	struct BinSearchNode *left;
	struct BinSearchNode * right;
}BST;

//  1.插入节点
void InsertNodeOfBST(BST *t,int key)   //在二叉排序树中插入查找关键字key
{
	BST *p,*parent,*head;

	if(!(p=(BST *)malloc(sizeof(BST)))) //申请内存空间 
	{
		printf("申请内存出错!\n");
		exit(0); 
	}
	p->data=key;
	p->left=p->right=NULL;

	head=t;
	while(head)    //查找需要添加的父结点 
	{
		parent=head;
		if(key<head->data)
			head=head->left;
		else
			head=head->right;
	}

	//判断添加到左子树还是右子树 
	if(key<parent->data)
		parent->left=p;
	else
		parent->right=p;
}

//  2.查找，递归方法
BST *SearchBSTRecurr(BST *t,int key)
{
	if(t!=NULL || t->data==key) //结点为空，或关键字相等 
		return t;          //返回结点指针
	else if(key>t->data) //关键字大于结点数据
		return(SearchBSTRecurr(t->right,key));
	else
		return(SearchBSTRecurr(t->left,key));
}

//  2.5查找，非递归方法
BST *SearchBST(BST *t,int key)
{
	BST *p=t;
	while(p)
	{
		if(key==p->data)
			return p;
		if(key<p->data)
			p=p->left;
		else
			p=p->right;
	}
	return NULL;
}

//  3.创建
void CreateBST(BST *t,int data[],int n)//n个数据在数组d中，tree为二叉排序树根
{
	int i;
	t->data=data[0];
	t->left=t->right=NULL;
	for(i=1;i<n;i++)
	{
		InsertNodeOfBST(t,data[i]);
	}
}

//  4.中序遍历
void LDRTraverse(BST *t)
{
	 if(t)//树不为空，则执行如下操作 
	 {
		 LDRTraverse(t->left); //中序遍历左子树
		 printf("%d ",t->data); //输出结点数据 
		 LDRTraverse(t->right); //中序遍历右子树/
	 }
	 return; 
 } 

//  5.删除节点
/*
删除一个节点p，并且保留二叉查找树的性质。分三种情况：
（1）叶子节点，直接删除
（2）只有左子节点或者右子节点，连接后面的子树再删除
（3）左右子节点都存在，那么需要找到p的中序遍历前驱节点s，即p的左子树的最右下（前驱还有可能不在p的子树上，但这种情况与p有左子树矛盾）

	有两种删除方法，连接法和代替法
	1）连接法：父亲f断掉的地方连p左，前驱s连p右
	   f->left（或right） = p->left   s->right = p->right   free(p)
	2）替代法：s的值代替p的值，s的父亲q右边连s左，最后删除s，特殊考虑q==p的情况
	   因为s在最右下，所以s没有右孩子
	   q->right = s->left  p->data = s->data     free(s)
*/
 void DeleteNodeOfBST(BST *t,int key)
 {
	BST *p,*parent;   //记录当前节点和其父亲
	BST *l,*l1;
	int child=0;       //记录p是父亲的左还是右，0表示左子树，1表示右子树 
	if(!t) return;     //二叉排序树为空，则退出

	p=t;
	parent=p;
	while(p)           //二叉排序树有效 
	{        
		if(p->data==key)
		{
			//叶节点
			if(p->left==NULL && p->right==NULL) 
			{
				if(p==t) //被删除的是根结点 
				{
					free(p);
					t=NULL;
				}
				else if(child==0) //父结点为左子树 
				{
					parent->left=NULL; 
					free(p); 
				}
				else //父结点为右子树 
				{
					parent->right=NULL;
					free(p); 
				}
			}
			//左子树为空，右子树不为空
			else if(p->left==NULL)
			{
				if(child==0) //是父结点的左子树
					parent->left=p->right;
				else         //是父结点的右子树             
					parent->right=p->right;
				free(p);
			}
			//右子树为空，左子树不为空
			else if(!p->right)
			{
				 if(child==0) //是父结点的左子树
					parent->left=p->left;
				else          //是父结点的右子树             
					parent->right=p->left;
				free(p);    
			}
			else  //左右子树都不为空 
			{
				l1=p; //保存左子树的父结点 
				l=p->right; //从当前结点的右子树进行查找 
				while(l->left) //左子树不为空 
				{
					l1=l;
					l=l->left; //查找左子树 
				}
				p->data=l->data; //将左子树的数据保存到被删除结点
				l1->left=NULL; //设置父结点的左子树指针为空 
				free(l1); //释放左子树占的内存空间
			}
			p=NULL;
		}
		//左子树继续遍历
		else if(key<p->data) 
		{
			child=0;
			parent=p;
			p=p->left;
		}
		//右子树继续遍历
		else    
		{
			child=1;
			parent=p;
			p=p->right;
		}    
	} 
}
int main()
{
	int i,key;
	BST bst,*pos;
	printf("原数据:"); 
	for(i=0;i<ARRAYLEN;i++)
		printf("%d ",source[i]);
	printf("\n");

	CreateBST(&bst,source,ARRAYLEN);

	printf("遍历二叉排序树:"); 
	LDRTraverse(&bst);

	do
	{
		printf("\n输入待删除关键字：\n");
		scanf("%d",&key);
		DeleteNodeOfBST(&bst,key);
		printf("删除结点值为%d后:",key); 
		LDRTraverse(&bst);

	}while(key!=-1);


	printf("\n请输入查找关键字:");
	scanf("%d",&key); 
	pos=SearchBST(&bst,key);
	if(pos)
		printf("查找成功，该结点的地址：%x\n",pos);
	else
		printf("查找失败!\n");
	return 0;
}
