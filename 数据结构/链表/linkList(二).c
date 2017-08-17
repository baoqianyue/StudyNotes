//以下为带头结点的单链表的各项操作
#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
typedef struct link_node{
	datatype info;
	struct link_node *next;
}node;

//自定义指向node的指针
typedef node* linklist;


//头插法创建单链表(返回指向该链表的指针)
linklist creatbystack()
{
	linklist head,s,p;
	p = head -> next;
	datatype x;
	p = NULL;
	printf("输入若干整数数列并以0结尾\n");
	scanf("%d",&x);
	while(x != 0)
	{
		s = (linklist) malloc(sizeof(node));
		s -> info = x;
		//其实相当于在head和p之间插入结点，然后保持循环即可
		s -> next = p;
		head -> next = s;
		p = s;
		scanf("%d",&x);
	}
	return head;
}


//尾插法创建单链表
linklist creatbyqueue()
{
	//r一直指向链表的结尾
	linklist head,p,r,s;
	datatype x;
	//初始化时，r也应指向头结点
	r = head;
	printf("输入若干整数数列并以0结尾\n");
	scanf("%d",&x);
	while(x != 0)
	{
		s = (linklist) malloc(sizeof(node));
		s -> info = x;
		r -> next = s;
		r = s;
		scanf("%d",&x);
	}
	if(r)
	r -> next = NULL;
	return head;
}



//输出带头结点的单链表
void print(linklist head)
{
	linklist p;
	int i = 0;
	p = head -> next;
	printf("List is: \n");
	while(p)
	{
		printf("%5d ",p -> info);
		p  = p -> next;
		i++;
		if(i % 10 == 0)
		printf("\n");
	}
	printf("\n");
}


//删除带头结点单链表中第一个值为x的结点
void delx(linklist head, datatype x)
{
	linklist p,q;
	p = head -> next;
	q = p -> next;
	if(p -> info == x)
	{
		head -> next = p -> next;
	}
	else
	{
		while((q -> next) -> info != x)
		{
			q = q -> next;
		}
		q -> next = (q -> next) -> next;
	}
}



//倒置带头结点单链表
void reverse(linklist head)
{
	if(head -> next == NULL)
	{
		printf("单链表为空\n");
	}
	linklist p,q,s;
	p = head -> next;
	q = p -> next;
	while(q)
	{
		s = q;
		s -> next = head -> next;
		head -> next = s;
		s = p;
		q = q -> next;
	}
	p -> next = NULL;
}




//测试
int main()
{
//  测试创建和打印链表函数
//	linklist p,q;
//	p = creatbystack();
//	print(p);
//	q = creatbyqueue();
//	print(q);
//  测试删除首次出现元素函数
//	linklist p;
//	datatype x;
//	p = creatbyqueue();
//	print(p);
//	printf("输入要删除结点的值\n");
//	scanf("%d",&x);
//	delx(p,x);
//	print(p);
//  测试倒置函数
//	linklist head,head1;
//	head = creatbystack();
//	print(head);
//	reverse(head);
//	print(head);
	return 0;
}
