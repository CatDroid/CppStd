// temp20171120.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

struct Node {
	Node* next;
	int data;
	Node(int value):data(value),next(NULL){}
};

void dump(Node* head){
	if (head == NULL) return;
	Node* next = head->next;
	int i = 0;
	while (next != NULL) {
		cout << next->data << "\t"; 
		next = next->next;
		if (++i % 4 == 0) cout << endl;
	}
	cout << endl;
}

bool mergeSort(Node* head) {

	if (head == NULL || head->next == NULL) return false;

	int size = 1;

	while (1) {

		Node* current = head ;

		int first_size = size;
		int second_size = size;
		Node* first = head->next;	// size大小下 第一个相邻队列对 的 第一个队列
		Node* second = first;	

		while (second_size != 0 &&  second != NULL ) {
			second = second->next;
			second_size--;
		}

		if (second == NULL) break; // 用来判断size是否超过整个队列

		while (1) {

			first_size = size;
			second_size = size;

			while (first != NULL && second != NULL && first_size != 0 && second_size != 0) {
				if (first->data < second->data) { // 小到大
					current->next = first;
					current = first;
					first = first->next;
					first_size--;
				}
				else {
					current->next = second;
					current = second;
					second = second->next;
					second_size--;
				}
			}

			while (first_size != 0 && first!=NULL ) {
				current->next = first;
				current = first;
				first = first->next;
				first_size--;
			}

			while (second_size != 0 && second != NULL ) {
				current->next = second;
				current = second;
				second = second->next;
				second_size--;
			}
			
			current->next = second; // 这时候 second应该指向 下一个相邻队列对 的第一个队列 的第一个元素
			
			// 下一对

			first = second;			// 下一对的第一个队列开始

			second_size = size;		// 下一对的第二个队列开始
			while (second_size != 0 && second != NULL ) {
				second = second->next;
				second_size--;
			}
			if (second == NULL) break;  // size大小 的 相邻队列对  已经遍历完毕  跳出内循环 去到下一次size+=size;
		}
		size += size;

	}
	return true;

}

int main()
{
	Node head(0);

	int array[] = { 9,-1,6,20,-10,-25,3,1,56,-2 };
	int len = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < len; i++){
		Node* node = new Node(array[i]);
		node->next = head.next;
		head.next = node;
	}
	
	dump(&head);

	mergeSort(&head);

	dump(&head);

    return 0;
}

