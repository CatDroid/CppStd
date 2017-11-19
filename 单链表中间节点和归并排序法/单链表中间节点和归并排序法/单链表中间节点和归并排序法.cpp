// �������м�ڵ�͹鲢����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;

struct Node {
	Node* next;
	int data;
	Node(int value):data(value),next(NULL) {
		
	}
};

void insert(Node* head, int value) {
	Node* next = new Node(value);
	next->next = head->next ;
	head->next = next;
}

void dump(Node* head) {
	Node* next = head->next;
	int i = 0;
	while (next != NULL) {
		cout << next->data << " ";
		if (++i % 4 == 0) cout << endl;
		next = next->next;
	}
	cout <<  endl;
}
/*
�������һ���Ƚϴ���ص���һ��������˵���ǡ����߻�ͷ·��������ʵ�������ȡ��random access��

���������Ҫ��һ������a���м�Ԫ�أ�ֱ��a[len/2]�Ϳ�����
���������У���Ϊֻ��a[len/2 - 1] ֪��a[len/2]���Ķ��������˲�֪��

��ˣ�������������������������«��
Ҫ�ҵ�������е㣬������Ҫ������
��1��֪�������ж೤
��2����ͷ��㿪ʼ˳������������ȵ�һ���λ�á�
�����Ҫ1.5n��nΪ����ĳ��ȣ���ʱ�临�Ӷ��ˡ�]

���õİ취�����������ܣ����A�� �ٶ���B�������Ļ�����A���յ��ʱ��BӦ�øյ��е㡣
��ֻ��Ҫ����һ����������ˣ������ü�������ĳ��ȡ� ʱ�临�Ӷ� 0.5n 

*/
bool middle(Node* head , int& value) {

	if (head == NULL || head->next == NULL) return false;

	Node* step2 = head->next;
	Node* step1 = head->next;

	while (step2->next != NULL && step2->next->next  != NULL) { // �����ż����Ԫ�� �����м��Ǹ��� (len-1)/2     (��ţ���0��ʼ)   
	//while (step2 != NULL && step2->next != NULL) {			// �����ż����Ԫ�� �����м��Ǹ��� (len-1)/2 + 1 

		step2 = step2->next->next;
		step1 = step1->next;
	}
	value = step1->data;
	return true ;

}

int main()
{
	Node head(0);
	for (int i = 0; i < 10 ; i++) {
		insert(&head , i );
	}

	dump(&head);

	int midvalue = 0;

	bool success = middle(&head,midvalue);
	if (success) {
		cout << midvalue << endl;
	}
	else {
		cout << "Fail" << endl;
	}

    return 0;
}

