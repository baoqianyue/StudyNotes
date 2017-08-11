//以下为不带头结点的单向链表的各项操作 
#include <stdio.h>
#include <stdlib.h>
typedef int datatype;
typedef struct link_node{
	datatype info;
	struct link_node *next;
}node;
typedef node *linklist;
//头插法创建链表
linklist creatbystack()
	{
		linklist head,s;
		datatype x;
		printf("请输入若干整数序列并以0结尾\n");
		scanf("%d",&x);
		while(x != 0)
		{
			s = (linklist)malloc(sizeof(node));
			s -> info = x;
			s -> next = head;
			head = s;
			scanf("%d",&x);
		}
	return head; 
	}

//尾插法创建链表
linklist creatbyqueue()
	{
		linklist head,r,s;
		datatype x;
		head = r = NULL;//创建一个一直指向尾结点的指针 
		printf("请输入若干整数序列并以0结束\n");
		scanf("%d",&x);
		while(x != 0)
		{
			s = (linklist)malloc(sizeof(node));
			s -> info = x;
			//将新结点插入到链表后端
			if(head == NULL)
			{
				head = s; 
			}
			else
				r -> next = s;
			r = s;//移动尾指针 
			scanf("%d",&x);
		}
		if (r) 
		r -> next = NULL;//最后将链表的结尾设置为NULL 
		return head;
	}
	
//输出链表
void print(linklist head)
	{
		linklist p;
		int i = 0;
		p = head;
		printf("表中有：\n");
		while(p)
		{
			printf("%d  ",p -> info);
			p = p -> next;
			i++;
			if(i == 10)
			{
				printf("\n");
			}
		}
		printf("\n");
	}
//删除链表中的某个值
linklist delx(linklist head,datatype x)
	{
		linklist p1,p2;
		if(head == NULL)
		{
			printf("链表是空的\n");
			return head;
		}
		p1 = head;
		while(x != p1 -> info && p1 -> next != NULL)
		//p1不是要找的结点，而且它后面还有结点 
		{ 
			p2 = p1;
			p1 = p1 -> next;//p1后移一个单位 	
		}
		if(p1 -> info == x)//找到了
		{
			if(p1 == head)
			{
				head = p1 -> next;
			}//如果p1指向首结点，把后一个结点地址赋给head
			else
			{
				p2 -> next = p1 -> next;	
			}//如果不是首结点，就把下一个结点地址赋给前一个结点地址
			free(p1); 
		} 
		else
		{
			printf("没有找到该结点\n");
		}
		return head;
		
	}
	
//反转链表     
//主要思路是将原来链表中各结点指针域反向，将原来表中最后一个结点作为新链表的头节点  
linklist reverse(linklist head)
	{
		//先判空 
		if(head == NULL || head -> next == NULL){
			return head;
		} 
		//创建三个辅助指针
		//pre指向前一个结点，now指向当前结点，next指向下一个结点
		linklist pre,now,next;
		//初始化指针
		pre = head;
		now = head -> next;
		pre -> next = NULL;
		//开始反转
		while(now){
			//先用next保存下一个结点
			next = now -> next;
			//将当前结点的指针方向反转
			now -> next = pre;
			//移动now,pre保持循环
			pre = now;
			now = next;
		} 
		head = pre;
		return head; 
	} 



//测试 
int main()
{
	datatype x;
	linklist head;
	head = creatbyqueue();//测试尾插法创建链表 
	print(head);
	reverse(head);
	printf("反转后的链表是\n");
	print(head);
	printf("请输入要删除的结点是：");
	scanf("%d",&x);
	head = delx(head,x);//测试删除结点 
	print(head);
	dellist(head); 
	return 0;
}
