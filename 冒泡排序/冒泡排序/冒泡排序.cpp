// 冒泡排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std; 

void bubble_sort(int arr[], int len) {

	bool didSwap = false ;	// 加快  时间复杂度 O(n) 

	for (int i = 0; i < len - 1; i++) {
		didSwap = false;
		for (int j = 0; j < len -1 -i; j++) { 
			if (arr[j] > arr[j + 1]) { // 小--大 
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				didSwap = true;
			} 
		}
		if (!didSwap) {
			cout << "time = " << i << endl;
			break; // 过去一次遍历没有顺序调换
		}
	}
}

int main()
{
	int test[] = { 189,89,6,1,9,2,11,7,12,12 };
	
	bubble_sort(test, sizeof(test) / sizeof(test[0]));

	for (int i = 0; i < sizeof(test) / sizeof(test[0]); i++) {
		cout << test[i] << " ";
	}
	cout << endl; 

    return 0;
}

