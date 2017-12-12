// ����Ĺ鲢����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// ����������й鲢 
void sort(int array[], int left , int mid , int right) {
	
	// [left , mid], [mid+1, right]
	int i = left;
	int j = mid + 1;
	int k = 0;
	int* temp = new int[ right - left + 1 ];

	while (i <= mid && j <= right) {
		if (array[i] < array[j]) {
			temp[k++] = array[i];
			i++;
		}
		else {
			temp[k++] = array[j];
			j++;
		}
	}

	while (i <= mid) {  // ��ʣ��� ֱ�ӿ����� ����õ����� ����
		temp[k++] = array[i];
		i++;
	}
 
	while (j <= right) {
		temp[k++] = array[j];
		j++;
	}

	for (i = left, k = 0; i <= right; i++, k++) { // ������ԭ�������� 
		array[i] = temp[k];
	}

	delete temp;
	return;
}

/*

��·�鲢�����㷨����

ÿ�˹鲢��ʱ�临�Ӷ�ΪO(n)  ������� log2 n �� 

��·�鲢�����ʱ�临�Ӷ� = �鲢������ÿһ��ʱ�临�Ӷȵĳ˻� ʱ�临�Ӷ�Ϊ   O(nlog2n) 

��Ҫ�����������������ͬ�ĸ���������'��ʱ��Ԫ'���ʸ����򷽷��Ŀռ临�Ӷ�Ϊ O(n)

'�ȶ�':
	���ֱ�������������г�������ͬ�����룬���ʹǰһ�����������ͬ�������ȸ��ƣ���һ���������ͬ��������ƣ��Ӷ��������ǵ���Դ��򲻻�ı�


ͼ�⣺
http://blog.csdn.net/yinjiabin/article/details/8265827/
��һ��ͼ�� �ݹ�ʵ�� ��˼·
�ڶ���ͼ�� �ǵݹ��ʵ�� ��˼· 
http://www.cnblogs.com/kubixuesheng/p/4355865.html
��·�鲢������ �ȶ���
*/
// ��·�鲢���� 
void merge_sort (int array[], int length) {

	int size = 1;

	int left = 0;
	int mid = 0;
	int right = 0;

	while (size < length) {
		left = 0;
		while (left + size  <= length - 1 ) { // left + size �ǵڶ������еĿ�ʼԪ��(���)
			mid = left + size - 1 ;   // ��һ�����е����һ��Ԫ��
			right = left + size*2 - 1;// �ڶ������е����һ��Ԫ��
			if (right > length - 1) right = length - 1;
			sort(array, left, mid, right);
			left += size*2 ;		 // ��һ��Ŀ�ʼԪ��
		} 
		size *= 2;  // 1 , 2 , 4, 8 , 16 ..... 
				    // size = 1 �����������е�Ԫ�ظ���Ϊ1  [array[0]] �� [array[1]] ..   left+=2*size 
					// size = 2 �����������е�Ԫ�ظ���Ϊ2  [array[0],array[1]] �� [array[2],array[3]] .. left+=2*size
					
	}
}



int main()
{

	//int array[] = { 6, 1, 4 , 9, 3, 2, 12, -1, 19 , -100, 67 };
	int array[] = { 6, 1, 4 , 9, 3, -1 };
	//int array[] = { 6, 1 };
	//int array[] = {1, 2 };
	//int array[] = { 1 };

	int length = sizeof(array) / sizeof(array[0]);
	merge_sort(array, length);

	for (int i = 0; i < length; i++) {
		cout << array[i] << endl;
	}

    return 0;
}

