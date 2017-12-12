
#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

 

struct Node {
	struct Node* next;
	int data;
};


void insert(Node* head, int value) {
	Node* node = new Node;
	node->data = value;
	node->next = head->next; // 单链表前插入
	head->next = node;
}


void reverse(Node* head) {
	if (head == NULL || head->next == NULL) return;
	Node* const first = head->next; 
 
	while (first->next != NULL) {
		Node* temp = first->next;
		first->next = first->next->next;
		temp->next = head->next;
		head->next = temp;
	}

}

void dump(Node* head) {
	int i = 0;
	Node* next = head->next ;
	while (next != NULL) {
		cout << next->data << " ";
		if ((++i) % 4 == 0) cout << endl;
		next = next->next;
	}
	cout << endl;
}

int main(int argc, char* argv[]) {


	struct Node head; head.next = NULL;

	for (int i = 0; i < 10; i++) {
		insert( &head, i );
	}
	dump(&head);

	cout  << "reverse : " << endl;
	reverse(&head);

	dump(&head);

	return 0;
}