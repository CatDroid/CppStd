// ��������ת.cpp : �������̨Ӧ�ó������ڵ㡣
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

	// ��֤ 
	Node* next = pHeadNode ;
	while (next != NULL) {
		printf("data = %d \n", next->data );
		next = next->next;
	}

	// ������ת
	Node* const header = pHeadNode ;
	while (header->next != NULL) {
		Node *move = header->next;
		header->next = move->next ;
		move->next = pHeadNode;
		pHeadNode = move;
	}

	// ��֤ 
	next = pHeadNode  ;
	while (next != NULL) {
		printf("data = %d \n", next->data);
		next = next->next;
	}
	

    return 0;
}

