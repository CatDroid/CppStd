// 最小堆与堆排序.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std ;

#define TYPE int 

//	我们在排序时，如果要排序后的顺序为从小到大，则需选择最大堆，反之，选择最小堆
//	最小堆 本质是 完全二叉树 + 子节点 必须比 父节点 要小 	
//	删除最小值 并新增一个数再求最小值    时间复杂度 O(log2N)简写为O(logN)
 
// current_root 上往下  当前值比左右节点要小的话，从小的节点 就下沉 
void sortDown(TYPE* heap, int len , int current_root) { 

	//if ( current_root > len - 1 ) return;

	int left = current_root * 2 + 1;
	int right = current_root * 2 + 2;
	int compare_index = -1;
	
	if (right <= len - 1) {			//	两个子节点都存在
		if (heap[left] > heap[right]) {
			compare_index = right;
		}
		else {
			compare_index = left;
		}
	} else if( left == len -1 ){	//	只存在 左子节点 
		compare_index = left;
	}
	else {							//	两个子节点都不存在 
		return;
	}


	if ( heap[compare_index] < heap[current_root]) {	//	当前值下沉
		TYPE temp = heap[compare_index];
		heap[compare_index] = heap[current_root];
		heap[current_root] = temp;						//	swap 
		sortDown(heap, len , compare_index );
	}
}

// current_root 下往上 当前值比父节点小的话 上浮
void sortUp(TYPE* heap, int len, int current_root) {	

	int next = current_root;
	while (next > 0) {
		int parent = (next - 1) / 2;  // 9/2 = 4.5 = 4 截断 
		if ( heap[parent] > heap[next] ) {
			TYPE temp = heap[parent];
			heap[parent] = heap[next];
			heap[next] = temp;
			next = parent;
		}
		else {
			break;
		}
	}
}


// 插入 
void HeapAdd(TYPE* heap_old, int len_old , TYPE* heap_new /*调用者申请 必须len_old+1*/ , TYPE new_value ) {

	memcpy(heap_new , heap_old , len_old * sizeof(TYPE) );
	heap_new[len_old] = new_value;
	sortUp(heap_new, len_old + 1 , len_old/*新加元素的index*/);
}

// 删除 (总是从buf[0]删除)  删除buf[0]之后把最后一个元素移到buf[0] 重新往下重排
TYPE HeapDel(TYPE* heap_old, int len_old, TYPE* heap_new /*调用者申请 必须len_old-1*/) {

	heap_new[0] = heap_old[ len_old - 1 ];
	memcpy(heap_new + 1 , heap_old + 1 , (len_old - 2)  * sizeof(TYPE));

	sortDown(heap_new, len_old - 1, 0 );

	return heap_old[0];
}


// 堆排序  大 到 小 
void HeapSort( TYPE* heap /* 已经建好的最小堆 */, int len) {
	int index = len - 1 ;
	while (index > 0) {
		// swap  当前开头的是最小的  移到堆的最后面
		TYPE temp = heap[index];
		heap[index] = heap[0];
		heap[0] = temp;
		sortDown(heap , index /*减少堆长度*/ , 0  /*从最顶的根节点开始重新调整 因为只有最顶的元素修改了*/ );
		index--;
	}
}

// 堆排序  小 到 大
void HeapSortIncrease(TYPE* heap /* 已经建好的最小堆 */, int len) {
	int index = len - 1;
	while (index > 0) {
		// swap  当前开头的是最小的  移到堆的最后面
		TYPE temp = heap[index];
		heap[index] = heap[0];
		heap[0] = temp;
		sortDown(heap, index /*减少堆长度*/, 0  /*从最顶的根节点开始重新调整 因为只有最顶的元素修改了*/);
		index--;
	}
	// 最小堆 适合  大 到 小
	// 最大堆 适合  小 到 大
	for (int i = 0 ; i < len / 2; i++) { //reverse 
		TYPE temp = heap[i];
		heap[i] = heap[len - 1 - i];
		heap[len - 1 - i] = temp;
	}
}

// 建堆 
void initHeap(TYPE* heap, int len) {
	int start_index = len / 2 - 1;
	do {
		cout << start_index << endl;
		sortDown(heap, len, start_index);
	} while (--start_index >= 0);
}


#define LENGTH 12 
int main()
{
	TYPE a[LENGTH] = { 8, 10, 2, 7, 24, 8, 19, 0, -13, 8 , 17,2 };
	initHeap(a, LENGTH);

	cout << "after build" << endl;
	for (TYPE thr : a) {
		cout << thr << " "; 
	}
	cout << endl;

	HeapSortIncrease(a, LENGTH); // 重复值 在排序也是可以的 见 8 
	cout << "after sort" << endl;
	for (TYPE thr : a) {
		cout << thr << " ";
	}
	cout << endl;

 
	 
	TYPE add[LENGTH + 1]; memset( add, 0, LENGTH + 1 );
	HeapAdd(a, LENGTH , add, -72); // 插入之后 原先排序好的会弄乱 但还是最小堆
	cout << "after add" << endl;
	for (TYPE thr : add) {
		cout << thr << " ";
	}
	cout << endl;
 

	
	TYPE del[LENGTH ]; memset(del, 0, LENGTH  );
	HeapDel(add, LENGTH + 1 , del);
	cout << "after del" << endl;
	for (TYPE thr : del ) {
		cout << thr << " ";
	}
	cout << endl;


	HeapSortIncrease(del, LENGTH);
	cout << "finally sorted " << endl;
	for (TYPE thr : del) {
		cout << thr << " ";
	}
	cout << endl;

    return 0;
}

