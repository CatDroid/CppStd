// 单链表中间节点和归并排序法.cpp : 定义控制台应用程序的入口点。
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
单链表的一个比较大的特点用一句广告语来说就是“不走回头路”，不能实现随机存取（random access）

如果我们想要找一个数组a的中间元素，直接a[len/2]就可以了
但是链表不行，因为只有a[len/2 - 1] 知道a[len/2]在哪儿，其他人不知道

因此，如果按照数组的做法依样画葫芦，
要找到链表的中点，我们需要做两步
（1）知道链表有多长
（2）从头结点开始顺序遍历到链表长度的一半的位置。
这就需要1.5n（n为链表的长度）的时间复杂度了。]

更好的办法：两个人赛跑，如果A的 速度是B的两倍的话，当A到终点的时候，B应该刚到中点。
这只需要遍历一遍链表就行了，还不用计算链表的长度。 时间复杂度 0.5n 

*/
bool middle(Node* head , int& value) {

	if (head == NULL || head->next == NULL) return false;

	Node* step2 = head->next;
	Node* step1 = head->next;

	while (step2->next != NULL && step2->next->next  != NULL) { // 如果是偶数个元素 这样中间那个是 (len-1)/2     (序号，从0开始)   
	//while (step2 != NULL && step2->next != NULL) {			// 如果是偶数个元素 这样中间那个是 (len-1)/2 + 1 

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

