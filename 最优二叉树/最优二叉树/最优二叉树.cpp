// 最优二叉树.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <windows.h>
#include <stdint.h>
#include <iostream>
#include <assert.h>
using namespace std;
 
/*
哈夫曼树(也称为最优二叉树) 

树的带权路径长度(WPL):树中所有叶子结点的带权路径长度之和

权值 可以是 概率 ， 可以实现 概率高的码元 对应编码的码字

解码时候查树


*/

/*
	template<class T>
	class LocalRef  {
		T* node;
		public:
		explicit LocalRef(T* ptr):node(ptr){
		}

		~LocalRef() {
			if (node != NULL) delete node;
		}
		LocalRef& operator=(const LocalRef&);
		LocalRef(const LocalRef&);
	};
*/

#define TARGET_FILE "text.txt" 
#define INIT_HEAP_SIZE	 8 
#define MAX_HUFFMAN_CODEC 100 

// 最小堆 作为优先队列使用  

struct MinHeapNode {
	int  weight;		 
	char data;
	MinHeapNode* left;
	MinHeapNode* right;
	MinHeapNode* next;
	MinHeapNode(char dat, int freq) :data(dat), weight(freq), left(NULL), right(NULL),next(NULL) {}
};

class MinHeap {
private:

	MinHeapNode** arrayHeap; // 指针数组
	int32_t size;
	int32_t capacity;

public:
	MinHeap() {
		arrayHeap = (MinHeapNode**)malloc( sizeof(MinHeapNode*) * INIT_HEAP_SIZE );
		size = 0;
		capacity = INIT_HEAP_SIZE;
	}
	
	~MinHeap() {
		free(arrayHeap);
	}

	MinHeap(int weights[], int size) {
		// TODO
		// last_index = (size - 1) ; 
		// start_index = (last_index - 1 )/2 ; start_index >= 0 ; start_index--
		// left  right  start_index 
		// 大的数 下沉
	}

	int32_t getSize() { return size;  }
	 
	struct MinHeapNode* pop() {

		if (size <= 0) {
			return NULL;
		}

		MinHeapNode* node = arrayHeap[0];

		arrayHeap[0] = arrayHeap[size - 1];// 最后一个前进
		int current = 0;
		while (current < size - 1) { // 现在只有[0, size-2] 总共size-1个

			int left_index = 2 * current + 1;
			int right_index = 2 * current + 2;
			int min_index = current ;
			if (left_index < size - 1 && arrayHeap[left_index]->weight < arrayHeap[min_index]->weight   ) {
				min_index = left_index;
			}
			if (right_index < size - 1 && arrayHeap[right_index]->weight < arrayHeap[min_index]->weight  ) {
				min_index = right_index;
			}

			if (min_index == current) break; // 比左右节点都比current要大
			
			MinHeapNode* temp = arrayHeap[min_index];
			arrayHeap[min_index] = arrayHeap[current];
			arrayHeap[current] = temp;
			current = min_index;
		}
		size--;
		return node ;
	}

	void push( MinHeapNode* node ) {

		if (size + 1 > capacity) { 
			capacity = capacity * 2; 
			arrayHeap = (MinHeapNode**)realloc(arrayHeap, sizeof(MinHeapNode*)* capacity);
		}

		int cur = size;
		int parent = 0 ;
		while (cur > 0) {  
			parent = (cur - 1) / 2;
			if (arrayHeap[parent]->weight > node->weight ) {
				arrayHeap[cur] = arrayHeap[parent];
				cur = parent;
			}
			else {
				break; 
			}
		}
		arrayHeap[cur] = node; 

		size++;
	}

public:
	MinHeap& operator=(const MinHeap& temp); // 禁止赋值 
	MinHeap(const MinHeap& other);			 // 禁止拷贝构造
};


 
void printCodes(MinHeapNode* current , uint8_t arr[] , int level )// level从0开始
{
	if ( current->left != NULL  ) {
		arr[level] = 0;
		printCodes(current->left, arr, level+1 );
	}

	if (current->right != NULL) {
		arr[level] = 1;
		printCodes(current->right, arr, level + 1);
	}

	if (current->right == NULL && current->left == NULL ) { // 叶子节点
		printf("char %c , freq %d , code : " , current->data, current->weight );
		for (int i = 0; i < level; i++) {
			printf("%c", arr[i]==0 ? '0':'1' );
		}
		printf("\n");
	}
}

/*
	根节点 一定不是  元组
	叶节点 一定是    元组

	如果没有左右子节点  就是叶节点  就是元组

	如果有节点 左右节点一定都同时存在

	level=0,1,2..
	    				  x				
	array[0]=0			/   \	
					   x     x
	array[1]=0		 /   \
					x      x
	array[2]=0    /  \   array[2]=1
				x      x
	 	
*/

int main()
{ 
	HANDLE dumpFileDescriptor = CreateFileA( TARGET_FILE ,
								GENERIC_READ | GENERIC_WRITE,
								FILE_SHARE_READ ,
								NULL,
								OPEN_EXISTING,
								FILE_ATTRIBUTE_NORMAL,
								NULL);

	DWORD dwHigh = 0;
	DWORD dwSize = ::GetFileSize(dumpFileDescriptor, &dwHigh);
	__int64 fileSize = ((__int64)dwHigh << 32) + dwSize;

	HANDLE fileMappingObject = CreateFileMapping(dumpFileDescriptor,
								NULL,
								PAGE_READONLY,// PAGE_READWRITE
		                        0,
								fileSize,
		                        NULL // "MySharedMem" 
								);
	uint8_t * mappedFileAddress = (uint8_t *)MapViewOfFile(fileMappingObject,
								FILE_MAP_READ,	// FILE_MAP_READ|FILE_MAP_WRITE 
		                        0,
		                        0,
								0);
	
 
	// Step 1. 统计 
	uint8_t statistic[256]; // ascii字符下标
	memset(statistic,0, sizeof(statistic) );
	uint8_t * current = mappedFileAddress;
	int heapSize = 0;
	for (int i = 0; i < fileSize; i++) {
		statistic[ 0xFF & *current]++;
		if (statistic[0xFF & *current] == 1) heapSize++;
		current++;
	}
	assert(heapSize > 1);// 元组必须大于1个，否则就没有必要  霍夫曼编码 

	// Step2. 建立最小堆 作为优先队列
	MinHeap* heap = new MinHeap();
	MinHeapNode* array = (MinHeapNode*)malloc( sizeof(MinHeapNode) *  heapSize );
	MinHeapNode* start = array;
	for (int i = 0 ; i < 256; i++) {
		if (statistic[i] != 0) {
			heap->push( new(start++) MinHeapNode( (uint8_t )i , statistic[i])  );
		}
	}

	//int32_t size = heap->getSize();
	//for (int32_t i = 0; i < size; i++) {
	//	MinHeapNode* node = heap->pop();
	//	printf("node %c %d\n", node->data, node->weight);
	//}

	// Step3. 建立哈夫曼树
	MinHeapNode* left = NULL;
	MinHeapNode* right = NULL;
	MinHeapNode head(-1, 0); head.next = NULL; 
	MinHeapNode* list_ptr = &head;
	MinHeapNode* temp = NULL;
	while ( heap->getSize() > 1 ) {
		left = heap->pop();
		right = heap->pop();
		temp = new MinHeapNode('$', left->weight + right->weight ); // ??? 一定偶数 ??? --> 只要不是1个
		temp->left = left;
		temp->right = right; // 二叉树 
		list_ptr->next = temp ;
		list_ptr = temp;
		heap->push(temp);
	} //  2(n-1) *  log(n)    2=left,right  n-1 循环次数   pop() logN

	// Step4. 打印霍夫曼编码  
	MinHeapNode* treeRoot = heap->pop();
	uint8_t codec_array[MAX_HUFFMAN_CODEC]; // 最大MAX_HUFFMAN_CODEC层
	memset(codec_array,0, sizeof(codec_array));
	printCodes( treeRoot, codec_array, 0 );


	// 释放节点 
	list_ptr = head.next ;
	while (list_ptr != NULL) {
		temp = list_ptr->next;
		delete list_ptr;
		list_ptr = temp;
	}
	// 释放最小堆
	delete heap;
	// 释放叶子节点
	free(array);

	UnmapViewOfFile(mappedFileAddress);
	CloseHandle(fileMappingObject);
	CloseHandle(dumpFileDescriptor);


 

    return 0;
}

