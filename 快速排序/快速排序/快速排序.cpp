// ��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

using namespace std;

typedef int DATA;

// arr : [ 0 ,end ]  
void quick_sort(DATA* arr, int start, int end) {

	if (end <= start ) {
		return;  // �ݹ����
	}

	int left = start+1;
	int right = end;
	DATA ref = arr[start];

	// ��С��������
	while (left != right) {
		
		while ( ref < arr[right] && right > left)  right--;

		while ( ref > arr[left] && right > left)  left++;

		if (left == right) break; 

		DATA temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
	}

	if (arr[left] < arr[start]) { // ����ֻ������Ԫ��ʱ��
		arr[start] = arr[left];
		arr[left] = ref;
	}


	// �� left == right �� �ֿ������� ����߶�С�ڲο�ref  �ұ߶����ڲο�ref 
	quick_sort(arr, start , left-1);
	quick_sort(arr, left+1  , end );
}

void dump(DATA* dat , int length ) {
	cout << "dump begin " << endl;
	for (int i = 0; i < length; i++) {
		cout << dat[i] << " ";
		if ( (i+1) % 4 == 0 ) cout << endl; 
	}
	cout << endl;
	cout << "dump end   " << endl;
}


// ������������ʱ�临�ӶȺ�ð��������һ���Ķ���O(N2)������ƽ��ʱ�临�Ӷ�ΪO(NlogN)

int main()
{
	DATA d[] = { 6,1,2,7,9,3,4,5,10,8 };
	//DATA d[] = { 6,10,2,7,9,3,4,10,10,8 }; // ע������������˽�����ظ����ݵ����� 
	//DATA d[] = {1,2  };
	
	dump(d, sizeof(d) / sizeof(d[0]));
	quick_sort(d, 0, sizeof(d)/sizeof(d[0]) - 1 );
	cout << "---after sort---" << endl;
	dump(d, sizeof(d) / sizeof(d[0]));
	
    return 0;
}

