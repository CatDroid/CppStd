// ��ת������ֲ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
��֪��������a[N]�� 
���м�ĳ��λ��k��kδ֪��k=-1��ʾ�����������򣩷ֿ���Ȼ��ǰ�������ֻ�����
�õ��µ����飬�ڸ��������������Ԫ��x��

�磺a[]={1,2,5,7,9,10,15}��
��k=4�ֿ����õ�������a={9,10,15, 1,2,5,7}��


����ԭ��
// nΪ���鳤��, xΪ�����ҵ�Ԫ�أ���������򷵻�Ԫ����a�е��±꣨a�±��0��ʼ��������������򷵻�-1
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

		// �ж�mid��head����end�������� 

		if (a[head] < a[mid]  ) {	//	head .. mid ����������
			if ( a[head] < x  && x < a[mid]  ) { 
				 end = mid;			//	����������������
			}
			else {					//	������������������
				head = mid;
			}
		} else {					//  ������� mid end ���������� (��Ϊa[head]>a[mid] ˵��mid��������һ�� )
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

