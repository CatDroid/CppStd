// ð������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

using namespace std; 

void bubble_sort(int arr[], int len) {

	bool didSwap = false ;	// �ӿ�  ʱ�临�Ӷ� O(n) 

	for (int i = 0; i < len - 1; i++) {
		didSwap = false;
		for (int j = 0; j < len -1 -i; j++) { 
			if (arr[j] > arr[j + 1]) { // С--�� 
				int temp = arr[j];
				arr[j] = arr[j + 1];
				arr[j + 1] = temp;
				didSwap = true;
			} 
		}
		if (!didSwap) {
			cout << "time = " << i << endl;
			break; // ��ȥһ�α���û��˳�����
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

