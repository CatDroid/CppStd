// 单链表逆转.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

struct Node {
	struct Node *next;
	int data; 
};


int main()
{
	Node *pHeadNode  = NULL;

	for (int i = 0; i < 10; i++) {
		Node* n = new Node();  n->data = i;
		n->next = pHeadNode;
		pHeadNode = n;
	}

	// 验证 
	Node* next = pHeadNode ;
	while (next != NULL) {
		printf("data = %d \n", next->data );
		next = next->next;
	}

	// 单链表反转
	Node* const header = pHeadNode ;
	while (header->next != NULL) {
		Node *move = header->next;
		header->next = move->next ;
		move->next = pHeadNode;
		pHeadNode = move;
	}

	// 验证 
	next = pHeadNode  ;
	while (next != NULL) {
		printf("data = %d \n", next->data);
		next = next->next;
	}
	

    return 0;
}

