// 数组的归并排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

// 两个有序队列归并 
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

	while (i <= mid) {  // 把剩余的 直接拷贝到 排序好的数组 后面
		temp[k++] = array[i];
		i++;
	}
 
	while (j <= right) {
		temp[k++] = array[j];
		j++;
	}

	for (i = left, k = 0; i <= right; i++, k++) { // 拷贝会原来的数组 
		array[i] = temp[k];
	}

	delete temp;
	return;
}

/*

二路归并排序算法分析

每趟归并的时间复杂度为O(n)  共需进行 log2 n 趟 

二路归并排序的时间复杂度 = 归并趟数与每一趟时间复杂度的乘积 时间复杂度为   O(nlog2n) 

需要利用与待排序数组相同的辅助数组作'临时单元'，故该排序方法的空间复杂度为 O(n)

'稳定':
	若分别在两个有序表中出现有相同排序码，则会使前一个有序表中相同排序码先复制，后一有序表中相同排序码后复制，从而保持它们的相对次序不会改变


图解：
http://blog.csdn.net/yinjiabin/article/details/8265827/
第一个图是 递归实现 的思路
第二个图是 非递归的实现 的思路 
http://www.cnblogs.com/kubixuesheng/p/4355865.html
二路归并排序是 稳定的
*/
// 二路归并排序 
void merge_sort (int array[], int length) {

	int size = 1;

	int left = 0;
	int mid = 0;
	int right = 0;

	while (size < length) {
		left = 0;
		while (left + size  <= length - 1 ) { // left + size 是第二个队列的开始元素(序号)
			mid = left + size - 1 ;   // 第一个队列的最后一个元素
			right = left + size*2 - 1;// 第二个队列的最后一个元素
			if (right > length - 1) right = length - 1;
			sort(array, left, mid, right);
			left += size*2 ;		 // 下一组的开始元素
		} 
		size *= 2;  // 1 , 2 , 4, 8 , 16 ..... 
				    // size = 1 代表两个队列的元素个数为1  [array[0]] 与 [array[1]] ..   left+=2*size 
					// size = 2 代表两个队列的元素个数为2  [array[0],array[1]] 与 [array[2],array[3]] .. left+=2*size
					
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

