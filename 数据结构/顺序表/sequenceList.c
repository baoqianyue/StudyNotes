//一下为顺序表的各项操作
#include <stdio.h>
#include <stdlib.h>
#define MAXSIZE 100
typedef int datatype;
typedef struct{
	datatype a[MAXSIZE];
	int size;
} sequence_list;

//初始化顺序表
void initseqlist(sequence_list *L)
{
	L -> size = 0;
}

//输入顺序表
void input(sequence_list *L)
{
	initseqlist(L);
	datatype x;
	printf("输入顺序表,并以0结尾:\n");
	scanf("%d",&x);
	while(x)
	{
		L -> a[L -> size++] = x;
		scanf("%d",&x);
	}
}

//从文件输入顺序表
void inputfromfile(sequence_list *L, char *filename)
{
	initseqlist(L);
	int i,x;
	//读取文件("r"表示只读)
	FILE *fp = fopen(filename,"r");
	if(fp)
	{
		while(! feof(fp))
		{
			fscanf(fp,"%d",&L -> a[L -> size++]);
		}
		fclose(fp);
	}

}

//输出顺序表
void print(sequence_list *L)
{
	int i;
	printf("顺序表为:\n");
	for(i = 0; i < L -> size; i++)
	{
		printf("%5d ",L -> a[i]);
		if((i + 1) % 10 == 0)
		printf("\n");
	}
	printf("\n");
}

//倒置顺序表
void reverse(sequence_list *L)
{
	int i,temp;
	if(L -> size == 0)
	{
		printf("顺序表为空\n");
	}
	else
	{
		for(i = 0; i < (L -> size) / 2; i++)
		{
			temp = L -> a[i];
			L -> a[i] = L -> a[L-> size - 1 - i];
			L -> a[L -> size - 1 - i] = temp;
		}
	}
}

//分类顺序表，将元素按照奇偶数分类
void sprit(sequence_list *L1, sequence_list *L2, sequence_list *L3)
{
	int i,j,k;
	j = k = 0;
	if(L1 -> size == 0)
	{
		printf("顺序表为空:\n");
	}
	else
	{
		for(i = 0; i < L1 -> size; i++)
		{
			if((L1 -> a[i])% 2 != 0)
			{
				L2 -> a[j] = L1 -> a[i];
				//保证新表的正确赋值
				++j;
				L2 -> size = j;
			}
			else
			{
				L3 -> a[k] = L1 -> a[i];
				++k;
				L3 -> size = k;
			}
		}
	}
}

//测试
int main()
{
//	sequence_list seq;
//	initseqlist(&seq);
//	input(&seq);
//	print(&seq);
//	reverse(&seq);
//	print(&seq);
//  测试分类函数
	sequence_list L1,L2,L3;
	initseqlist(&L1);
	initseqlist(&L2);
	initseqlist(&L3);
	input(&L1);
	sprit(&L1,&L2,&L3);
	print(&L1);
	print(&L2);
	print(&L3);
	return 0;
}
