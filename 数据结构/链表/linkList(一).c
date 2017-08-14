//以下为不带头结点的单链表的各项操作
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
	linklist head,s;
	datatype x;
	head = NULL;
	printf("输入若干整数数列并以0结尾\n");
	scanf("%d",&x);
	while(x != 0)
	{
		s = (linklist) malloc(sizeof(node));
		s -> info = x;
		s -> next = head;
		head = s;
		scanf("%d",&x);
	}
	return head;
}


//尾插法创建单链表
linklist creatbyqueue()
{
	//r一直指向链表的结尾
	linklist head,r,s;
	datatype x;
	head = NULL;
	printf("输入若干整数数列并以0结尾\n");
	scanf("%d",&x);
	while(x != 0)
	{
		s = (linklist) malloc(sizeof(node));
		s -> info = x;
		if(head == NULL)
		{
			head = s;
		}
		else
		{
			r -> next = s;
		}
		r = s;
		scanf("%d",&x);
	}
	if(r)
	r -> next = NULL;
	return head;
}



//输出不带头结点的单链表
void print(linklist head)
{
	linklist p;
	int i = 0;
	p = head;
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


//释放不带头结点的单链表
//使用两个指针轮换指代，逐个释放
void delList(linklist head)
{
	linklist p;
	p = head;
	while(p)
	{
		head = p -> next;
		free(p);
		p = head;
	}
	p = NULL;
}


//删除不带头结点单链表中第一个值为x的结点
//在链表中删除一个结点必须要知道该结点的前一个结点的信息
linklist delx(linklist head, datatype x)
{
	linklist p,s;
	if(head == NULL)
	{
		printf("单链表为空\n");
		return head;
	}
	p = head;
	//按条件遍历单链表
	while(p -> info != x && p -> next != NULL)
	{
		//使用s保存前一个结点的信息
		s = p;
		p = p -> next;
	}
	if(p -> info == x)
	{
		//如果该结点恰好为首结点,直接将首结点覆盖为下一位
		if(p == head)
		{
			head = head -> next;
		}
		//如果该结点为普通结点，就借助该结点的前一结点进行删除
		else
		{
			s -> next = p -> next;
		}
		free(p);
	}
	else
	{
		printf("没有找到该结点\n");
	}
	return head;
}



//将不带头结点的单链表倒置(返回头指针)
linklist reverse1(linklist head)
{
	if(head == NULL || head -> next == NULL)
	{
		printf("单链表为空\n");
		return NULL;
	}
	linklist p,q;
	p = NULL;
	q = head;
	while(q)
	{
		head = head -> next;
		q -> next = p;
		p = q;
		q = head;
	}
	head = p;
	return head;
}


//将不带头结点的单链表倒置(返回值为空)
void reverse2(linklist *head)
{
	if(*head == NULL || (*head) -> next == NULL)
	{
		printf("单链表为空\n");
	}
	linklist p,q;
	p = NULL;
	q = *head;
	while(q)
	{
		*head = (*head) -> next;
		q -> next = p;
		p = q;
		q = *head;
	}
	*head = p;
}


//假设不带头结点的单链表是升序排列的，设计算法函数，将值为x的结点插入到链表中，并保持链表的有序性
linklist insert(linklist head, datatype x)
{
	linklist p,q;
	if(head == NULL || head -> next == NULL)
	{
		printf("单链表为空\n");
		return head;
	}
	for(q = head; q -> next != NULL; q = q -> next)
	{
		if((q -> next) -> info > x)
		break;
	}
	p = (linklist) malloc(sizeof(node));
	p -> info = x;
	p -> next = q -> next;
	q -> next = p;

	return head;

}


//删除不带头结点单链表中值为x的所有结点
linklist delallx(linklist head, datatype x)
{
	linklist p,q;
	if(head == NULL || head -> next == NULL)
	{
		printf("单链表为空\n");
		return head;
	}

	for(p = head; p -> next != NULL; p = p -> next)
	{
		if((p -> next) -> info == x)
		{
			q = p -> next;
			p -> next = q -> next;
			free(q);
		}
	}
	return head;
}

//测试
int main()
{
//	linklist p,s;
//	p = creatbystack();
//	print(p);
//	s = creatbyqueue();
//	print(s);
//	delList(p);
//	delList(s);
//	print(p);
//	print(s);
//  测试删除函数
//	linklist p;
//	datatype x;
//	p = creatbyqueue();
//	print(p);
//	printf("输入要删除的结点的值\n");
//	scanf("%d",&x);
//	p = delx(p,x);
//	print(p);
//  测试倒置函数
// 	linklist head;
// 	head = creatbystack();
// 	print(head);
// 	head = reverse1(head);
// 	print(head);
// 	reverse2(&head);
// 	print(head);
//	delList(head);
//  测试有序插入函数
//	datatype x;
//	linklist head;
//	printf("输入一组升序排列的整数:\n");
//	head = creatbyqueue();
//	print(head);
//	printf("输入要插入的值\n");
//	scanf("%d",&x);
//	head = insert(head,x);
//	print(head);
//	delList(head);
//  测试删除全部给定值函数
    datatype x;
	linklist head;
	head = creatbyqueue();
	print(head);
	printf("输入要删除的值\n");
	scanf("%d",&x);
	head = delallx(head,x);
	print(head);
	delList(head);
	return 0;
}
