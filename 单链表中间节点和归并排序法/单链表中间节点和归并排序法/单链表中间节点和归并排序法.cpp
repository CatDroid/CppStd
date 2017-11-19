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

更好的办法：两个人赛跑，如果A的速度是B的两倍的话，当A到终点的时候，B应该刚到中点。
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

/*

1. 分治法的时间复杂度 O(nlogn)

2. 归并排序算法介绍归并排序是一个分治算法(Divide and Conquer)的一个典型实例
	归并排序的思路是‘分治’

3. 链表排序最好使用归并排序算法

	a. '堆排序、快速排序'这些在'数组排序'时性能非常好的算法,在'链表'只能“顺序访问”的魔咒下无法施展能力

	b. 但是归并排序却如鱼得水，非但保持了它O(nlogn)的时间复杂度，  logn 是高度  n是每次需要对比n次
		而且它在'数组排序'中广受诟病的'空间复杂度在链表排序'中也从O(n)降到了O(1)

4. 归并：将两个或两个以上的有序表组合成一个新的有序表。
		内部排序中，通常采用的是 2-路归并排序，也就是：将两个位置相邻的记录有序子序列归，并为一个记录有序的序列
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
		if (second == NULL) break; //  代表这次size已经超过单链的长度
								   //  同时 second也指向 在size队列长度下 第一个'相邻队列对'的第二个队列的第一个元素
		while (1) { // TODO
			first_size = size;
			second_size = size;

			while(first_size > 0   && second_size > 0  && first!= NULL && second !=NULL  ){
				if (first->data > second->data) {     // 大到小 
				// if (first->data < second ->data) { // second队列 未必有 size的大小
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
			current->next = second; // 排序后最后一个元素的next要指向second(second是下一个相邻队列第一个队列的元素)
			if (current->next == NULL) break;
									// current 上一个'相邻队列对'的最后一个元素 
			first = current->next;  // 下一个'相邻队列对' 的开始
			second = first;  
			first_size = size;
			while (second && first_size--) { // 下一个'相邻队列对'的第二个队列的开始
				second = second->next;		 // 跳过 '相邻队列对'的第一个队列size个链表元素
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

