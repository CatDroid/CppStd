// 快速排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

typedef int DATA;

// arr : [ 0 ,end ]  
void quick_sort(DATA* arr, int start, int end) {

	if (end <= start ) {
		return;  // 递归结束
	}

	int left = start+1;
	int right = end;
	DATA ref = arr[start];

	// 从小到大排序
	while (left != right) {
		
		while ( ref < arr[right] && right > left)  right--;

		while ( ref > arr[left] && right > left)  left++;

		if (left == right) break; 

		DATA temp = arr[left];
		arr[left] = arr[right];
		arr[right] = temp;
	}

	if (arr[left] < arr[start]) { // 避免只有两个元素时候
		arr[start] = arr[left];
		arr[left] = ref;
	}


	// 在 left == right 处 分开了两边 ，左边都小于参考ref  右边都大于参考ref 
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


// 快速排序的最差时间复杂度和冒泡排序是一样的都是O(N2)，它的平均时间复杂度为O(NlogN)

int main()
{
	DATA d[] = { 6,1,2,7,9,3,4,5,10,8 };
	//DATA d[] = { 6,10,2,7,9,3,4,10,10,8 }; // 注意快速排序不适宜解决有重复数据的排序 
	//DATA d[] = {1,2  };
	
	dump(d, sizeof(d) / sizeof(d[0]));
	quick_sort(d, 0, sizeof(d)/sizeof(d[0]) - 1 );
	cout << "---after sort---" << endl;
	dump(d, sizeof(d) / sizeof(d[0]));
	
    return 0;
}

