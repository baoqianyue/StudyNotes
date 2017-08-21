//以下为顺序表的各项操作
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


//排序顺序表,将两个已排序好的顺序表，合并到另外的表中，仍保持数据的顺序
void merge(sequence_list *L1,sequence_list *L2,sequence_list *L3)
{
	int i,j,k;
	i = j = k = 0;
	//当L1和L2同时有元素时，对相同位置的元素进行比较并写入L3
	while(i < L1 -> size && j < L2 -> size)
	{
		if(L1 -> a[i] > L2 -> a[j])
		{
			L3 -> a[k] = L2 -> a[j];
			j++;
			k++;
		}
		else
		{
			L3 -> a[k] = L1 -> a[i];
			i++;
			k++;
		}
	}
	//当L2已空时
	while(i < L1 -> size)
	{
		L3 -> a[k] = L1 -> a[i];
		i++;
		k++;
	}
	//当L1空时
	while(j < L2 -> size)
	{
		L3 -> a[k] = L2 -> a[j];
		j++;
		k++;
	}
	//对L3的size赋值
	L3 -> size = k;

}

//求两个顺序表的交集
void inter(sequence_list *la, sequence_list *lb, sequence_list *lc)
{
	initseqlist(lc);
	int i,j;
	for(i = 0; i < la -> size; i++)
	{
		for(j = 0; j < lb -> size; j++)
		{
			if(la -> a[i] == lb -> a[j])
			{
				lc -> a[lc -> size++] = la -> a[i];
				break;
			}
		}
	}
}

//调整顺序表，将表中所有奇数移动到表的左端，将偶数移动到表的右端，并分析算法时间复杂度
void partion(sequence_list *L)
{
	//分别从表的两端开始遍历
	int i = 0,j = L -> size - 1;
	while(i < j)
	{
		//从表的左端开始，如果为奇数，继续遍历
		while(L -> a[i] % 2 != 0 && i < j)
		i++;
		//从表的右端开始，如果为偶数，继续遍历
		while(L -> a[j] % 2 == 0 && j > i)
		j--;
		//如果此时左端数据为偶数，右端为奇数，则交换位置
		if(L -> a[i] % 2 == 0 && L -> a[j] %2 != 0)
		{
			int temp;
			temp = L -> a[i];
			L -> a[i] = L -> a[j];
			L -> a[j] = temp;
		}
	}
	printf("算法时间复杂度为:O(n)\n");
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
//	sequence_list L1,L2,L3;
//	initseqlist(&L1);
//	initseqlist(&L2);
//	initseqlist(&L3);
//	input(&L1);
//	sprit(&L1,&L2,&L3);
//	print(&L1);
//	print(&L2);
//	print(&L3);
//	return 0;
//  测试合并排序函数
//	sequence_list L1,L2,L3;
//	input(&L1);
//	input(&L2);
//	merge(&L1,&L2,&L3);
//	print(&L3);
//	return 0;
//  测试求交集函数
//	sequence_list la,lb,lc;
//	input(&la);
//	input(&lb);
//	inter(&la,&lb,&lc);
//	print(&lc);
//	return 0;
//  测试调整函数
  	sequence_list L;
	input(&L);
	print(&L);
	partion(&L);
	print(&L);
	return 0;

}
