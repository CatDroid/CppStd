// ���Ŷ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <windows.h>
#include <stdint.h>
#include <iostream>
#include <assert.h>
using namespace std;
 
/*
��������(Ҳ��Ϊ���Ŷ�����) 

���Ĵ�Ȩ·������(WPL):��������Ҷ�ӽ��Ĵ�Ȩ·������֮��

Ȩֵ ������ ���� �� ����ʵ�� ���ʸߵ���Ԫ ��Ӧ���������

����ʱ�����


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

// ��С�� ��Ϊ���ȶ���ʹ��  

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

	MinHeapNode** arrayHeap; // ָ������
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
		// ����� �³�
	}

	int32_t getSize() { return size;  }
	 
	struct MinHeapNode* pop() {

		if (size <= 0) {
			return NULL;
		}

		MinHeapNode* node = arrayHeap[0];

		arrayHeap[0] = arrayHeap[size - 1];// ���һ��ǰ��
		int current = 0;
		while (current < size - 1) { // ����ֻ��[0, size-2] �ܹ�size-1��

			int left_index = 2 * current + 1;
			int right_index = 2 * current + 2;
			int min_index = current ;
			if (left_index < size - 1 && arrayHeap[left_index]->weight < arrayHeap[min_index]->weight   ) {
				min_index = left_index;
			}
			if (right_index < size - 1 && arrayHeap[right_index]->weight < arrayHeap[min_index]->weight  ) {
				min_index = right_index;
			}

			if (min_index == current) break; // �����ҽڵ㶼��currentҪ��
			
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
	MinHeap& operator=(const MinHeap& temp); // ��ֹ��ֵ 
	MinHeap(const MinHeap& other);			 // ��ֹ��������
};


 
void printCodes(MinHeapNode* current , uint8_t arr[] , int level )// level��0��ʼ
{
	if ( current->left != NULL  ) {
		arr[level] = 0;
		printCodes(current->left, arr, level+1 );
	}

	if (current->right != NULL) {
		arr[level] = 1;
		printCodes(current->right, arr, level + 1);
	}

	if (current->right == NULL && current->left == NULL ) { // Ҷ�ӽڵ�
		printf("char %c , freq %d , code : " , current->data, current->weight );
		for (int i = 0; i < level; i++) {
			printf("%c", arr[i]==0 ? '0':'1' );
		}
		printf("\n");
	}
}

/*
	���ڵ� һ������  Ԫ��
	Ҷ�ڵ� һ����    Ԫ��

	���û�������ӽڵ�  ����Ҷ�ڵ�  ����Ԫ��

	����нڵ� ���ҽڵ�һ����ͬʱ����

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
	
 
	// Step 1. ͳ�� 
	uint8_t statistic[256]; // ascii�ַ��±�
	memset(statistic,0, sizeof(statistic) );
	uint8_t * current = mappedFileAddress;
	int heapSize = 0;
	for (int i = 0; i < fileSize; i++) {
		statistic[ 0xFF & *current]++;
		if (statistic[0xFF & *current] == 1) heapSize++;
		current++;
	}
	assert(heapSize > 1);// Ԫ��������1���������û�б�Ҫ  ���������� 

	// Step2. ������С�� ��Ϊ���ȶ���
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

	// Step3. ������������
	MinHeapNode* left = NULL;
	MinHeapNode* right = NULL;
	MinHeapNode head(-1, 0); head.next = NULL; 
	MinHeapNode* list_ptr = &head;
	MinHeapNode* temp = NULL;
	while ( heap->getSize() > 1 ) {
		left = heap->pop();
		right = heap->pop();
		temp = new MinHeapNode('$', left->weight + right->weight ); // ??? һ��ż�� ??? --> ֻҪ����1��
		temp->left = left;
		temp->right = right; // ������ 
		list_ptr->next = temp ;
		list_ptr = temp;
		heap->push(temp);
	} //  2(n-1) *  log(n)    2=left,right  n-1 ѭ������   pop() logN

	// Step4. ��ӡ����������  
	MinHeapNode* treeRoot = heap->pop();
	uint8_t codec_array[MAX_HUFFMAN_CODEC]; // ���MAX_HUFFMAN_CODEC��
	memset(codec_array,0, sizeof(codec_array));
	printCodes( treeRoot, codec_array, 0 );


	// �ͷŽڵ� 
	list_ptr = head.next ;
	while (list_ptr != NULL) {
		temp = list_ptr->next;
		delete list_ptr;
		list_ptr = temp;
	}
	// �ͷ���С��
	delete heap;
	// �ͷ�Ҷ�ӽڵ�
	free(array);

	UnmapViewOfFile(mappedFileAddress);
	CloseHandle(fileMappingObject);
	CloseHandle(dumpFileDescriptor);


 

    return 0;
}

