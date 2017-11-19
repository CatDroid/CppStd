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

���õİ취�����������ܣ����A���ٶ���B�������Ļ�����A���յ��ʱ��BӦ�øյ��е㡣
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

/*

1. ���η���ʱ�临�Ӷ� O(nlogn)

2. �鲢�����㷨���ܹ鲢������һ�������㷨(Divide and Conquer)��һ������ʵ��
	�鲢�����˼·�ǡ����Ρ�

3. �����������ʹ�ù鲢�����㷨

	a. '�����򡢿�������'��Щ��'��������'ʱ���ܷǳ��õ��㷨,��'����'ֻ�ܡ�˳����ʡ���ħ�����޷�ʩչ����

	b. ���ǹ鲢����ȴ�����ˮ���ǵ���������O(nlogn)��ʱ�临�Ӷȣ�  logn �Ǹ߶�  n��ÿ����Ҫ�Ա�n��
		��������'��������'�й���ڸ����'�ռ临�Ӷ�����������'��Ҳ��O(n)������O(1)

4. �鲢�����������������ϵ��������ϳ�һ���µ������
		�ڲ������У�ͨ�����õ��� 2-·�鲢����Ҳ���ǣ�������λ�����ڵļ�¼���������й飬��Ϊһ����¼���������
*/

void mergeSort(Node* head) {

	int size = 1;

	while (1) {
		Node* first = head->next;
		Node* second = first;
		Node* current = head;
		int first_size = size;
		int second_size = size;

		while (second != NULL && first_size--) {
			second = second->next;
		}
		if (second == NULL) break; //  �������size�Ѿ����������ĳ���
								   //  ͬʱ secondҲָ�� ��size���г����� ��һ��'���ڶ��ж�'�ĵڶ������еĵ�һ��Ԫ��
		while (1) { // TODO
			first_size = size;
			second_size = size;

			while(first_size > 0   && second_size > 0  && first!= NULL && second !=NULL  ){
				if (first->data > second->data) {     // ��С 
				// if (first->data < second ->data) { // second���� δ���� size�Ĵ�С
					current->next = first;
					current = first;
					first = first->next;
					first_size--;
				}
				else {
					current->next = second ;
					current = second;
					second = second ->next;
					second_size--;
				}
			}

			while (first_size != 0 && first != NULL) {
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
			current->next = second; // ��������һ��Ԫ�ص�nextҪָ��second(second����һ�����ڶ��е�һ�����е�Ԫ��)
			if (current->next == NULL) break;
									// current ��һ��'���ڶ��ж�'�����һ��Ԫ�� 
			first = current->next;  // ��һ��'���ڶ��ж�' �Ŀ�ʼ
			second = first;  
			first_size = size;
			while (second && first_size--) { // ��һ��'���ڶ��ж�'�ĵڶ������еĿ�ʼ
				second = second->next;		 // ���� '���ڶ��ж�'�ĵ�һ������size������Ԫ��
			}
			if (second == NULL) break;
		 
		}
		size += size;

	}


}

int main()
{

	Node head(0);
#if 0
	for (int i = 0; i < 10 ; i++) {
		insert(&head , i );
	}
#else
	//int array[] = { 6,1,9,-10,2,20,-5,39};
	//int array[] = { 6,1,9,-10,2,20,-5  };
	int array[] = { -2,1 };
	int len = sizeof(array) / sizeof(array[0]);
	for (int i = 0; i < len ; i++) {
		insert(&head, array[i]);
	}
#endif 

	dump(&head);

	int midvalue = 0;

	bool success = middle(&head,midvalue);
	if (success) {
		cout << midvalue << endl;
	}
	else {
		cout << "Fail" << endl;
	}

	mergeSort(&head);

	dump(&head);

    return 0;
}

