// 单链表是有环的.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
如何判断一个单链表是有环的？ 判断一个单链表是否有环及环的链接点

（注意不能用标志位，最多只能用两个额外指针）

解法：
1、对于问题1，使用追赶的方法，设定两个指针slow、fast，从头指针开始，每次分别前进1步、2步。如存在环，则两者相遇；如不存在环，fast遇到NULL退出。
2、对于问题2，记录下问题1的碰撞点p，slow、fast从该点开始，再次碰撞所走过的操作数就是环的长度s。
3、问题3：有定理：碰撞点p到连接点的距离=头指针到连接点的距离，因此，分别从碰撞点、头指针开始走，相遇的那个点就是连接点。(证明在后面附注)
4、问题3中已经求出连接点距离头指针的长度，加上问题2中求出的环的长度，二者之和就是带环单链表的长度

*/

struct node { 
	char val; 
	node* next; 
};

//return false : 无环；true: 有环
// 一种O（n）的办法就是（搞两个指针，一个每次递增一步，一个每次递增两步，如果有环的话两者必然重合，反之亦然）：
bool check( node* const head)
{
	if (head == NULL) return false;
	node *low = head, *fast = head->next;
	if (low == fast) {
		printf("指向自己  环长度 = 0  \n" );
		return true;
	}

	while (fast != NULL && fast->next != NULL)
	{
		low = low->next;
		fast = fast->next->next;
		if (low == fast) {
			int i = 1; 
			low = low->next;
			//fast = fast->next->next;
			while (low != fast) {
				low = low->next;
				//fast = fast->next->next;
				i++;
			}
			printf("环长度 %d \n", i );
			return true;
		}
	}
	return false;
}

int main()
{
	{
		node nHead;
		nHead.next = &nHead;
		printf("check %s \n", check(&nHead) ? "true" : "false");
	}

	{
		node nHead;
		node n1; nHead.next = &n1; n1.next = NULL;
		node n2; n1.next = &n2; n2.next = NULL;
		node n3; n2.next = &n3; n3.next = NULL;
		node n4; n3.next = &n4; n4.next = NULL;
		node n5; n4.next = &n5; n5.next = NULL;
		node n6; n5.next = &n6; n6.next = NULL;
		node n7; n6.next = &n7; n7.next = NULL;
		node n8; n7.next = &n8; n8.next = NULL;
		node n9; n8.next = &n9; n9.next = &n5;

		printf("check %s \n", check(&nHead) ? "true" : "false");
	}

    return 0;
}

