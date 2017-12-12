// 旋转数组二分查找.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
已知有序数组a[N]， 
从中间某个位置k（k未知，k=-1表示整个数组有序）分开，然后将前后两部分互换，
得到新的数组，在该新数组里面查找元素x。

如：a[]={1,2,5,7,9,10,15}，
从k=4分开，得到新数组a={9,10,15, 1,2,5,7}。


函数原型
// n为数组长度, x为待查找的元素，如果存在则返回元素在a中的下标（a下标从0开始），如果不存在则返回-1
int binary_search_rotate_array(int* a, int n, int x);
*/

#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
int binary_search_rotate_array(int* a, int n, int x) {

	int head = 0;
	int end = n - 1;
	int mid = 0; 

	while (head < end) {
 
		//printf("head %d end %d\n" , head ,end );
		mid = (head + end) / 2;
		//printf("mid = %d a[mid] =%d \n", mid , a[mid] );

		if (a[mid] == x) return mid;
		if (a[head] == x) return head;
		if (a[end] == x) return end;

		// 判断mid跟head还是end是连续的 

		if (a[head] < a[mid]  ) {	//	head .. mid 是连续变大的
			if ( a[head] < x  && x < a[mid]  ) { 
				 end = mid;			//	在连续变大的区域中
			}
			else {					//	不在连续变大的区域中
				head = mid;
			}
		} else {					//  否则就是 mid end 是连续变大的 (因为a[head]>a[mid] 说明mid是在另外一段 )
			if (   a[mid] < x  && x < a[end] ) {
				head = mid;
			}
			else {
				end = mid;
			}
		}
	}
	return -1 ;
}

int main()
{ 
	{
		int arr[] = { 4,5,1,2,3 };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 3);
		printf("index = %d\n", index);
	}

	{
		int arr[] = { 4,5,1,2,3 };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 6);
		printf("index = %d\n", index);
	}

	{
		int arr[] = { 4,5,6,7,8,9,1,2,3 };
		int index = binary_search_rotate_array(arr, sizeof(arr)/sizeof(arr[0]) , 6);
		printf("index = %d\n", index);
	}

	{
		int arr[] = { 6,9,11,25,29,45,-3,2,4 };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 2);
		printf("index = %d\n", index);
	}

	{
		int arr[] = { 6,9,11,25,29,45,-3,1,1 };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 2);
		printf("index = %d\n", index);
	}

	{
		int arr[] = { 1,1,1,0,1 };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 0);
		printf("{ 1,1,1,0,1 } index = %d\n", index);
	}

	{
		int arr[] = { 1,0,1,1,1,1  };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 0);
		printf("index = %d\n", index);
	}

	{
		int arr[] = { 1,0,1,1,1 };
		int index = binary_search_rotate_array(arr, sizeof(arr) / sizeof(arr[0]), 0);
		printf("index = %d\n", index);

	}

	//system("pause");
    return 0;
}

