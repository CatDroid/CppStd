// ��С���������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std ;

#define TYPE int 

//	����������ʱ�����Ҫ������˳��Ϊ��С��������ѡ�����ѣ���֮��ѡ����С��
//	��С�� ������ ��ȫ������ + �ӽڵ� ����� ���ڵ� ҪС 	
//	ɾ����Сֵ ������һ����������Сֵ    ʱ�临�Ӷ� O(log2N)��дΪO(logN)
 
// current_root ������  ��ǰֵ�����ҽڵ�ҪС�Ļ�����С�Ľڵ� ���³� 
void sortDown(TYPE* heap, int len , int current_root) { 

	//if ( current_root > len - 1 ) return;

	int left = current_root * 2 + 1;
	int right = current_root * 2 + 2;
	int compare_index = -1;
	
	if (right <= len - 1) {			//	�����ӽڵ㶼����
		if (heap[left] > heap[right]) {
			compare_index = right;
		}
		else {
			compare_index = left;
		}
	} else if( left == len -1 ){	//	ֻ���� ���ӽڵ� 
		compare_index = left;
	}
	else {							//	�����ӽڵ㶼������ 
		return;
	}


	if ( heap[compare_index] < heap[current_root]) {	//	��ǰֵ�³�
		TYPE temp = heap[compare_index];
		heap[compare_index] = heap[current_root];
		heap[current_root] = temp;						//	swap 
		sortDown(heap, len , compare_index );
	}
}

// current_root ������ ��ǰֵ�ȸ��ڵ�С�Ļ� �ϸ�
void sortUp(TYPE* heap, int len, int current_root) {	

	int next = current_root;
	while (next > 0) {
		int parent = (next - 1) / 2;  // 9/2 = 4.5 = 4 �ض� 
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


// ���� 
void HeapAdd(TYPE* heap_old, int len_old , TYPE* heap_new /*���������� ����len_old+1*/ , TYPE new_value ) {

	memcpy(heap_new , heap_old , len_old * sizeof(TYPE) );
	heap_new[len_old] = new_value;
	sortUp(heap_new, len_old + 1 , len_old/*�¼�Ԫ�ص�index*/);
}

// ɾ�� (���Ǵ�buf[0]ɾ��)  ɾ��buf[0]֮������һ��Ԫ���Ƶ�buf[0] ������������
TYPE HeapDel(TYPE* heap_old, int len_old, TYPE* heap_new /*���������� ����len_old-1*/) {

	heap_new[0] = heap_old[ len_old - 1 ];
	memcpy(heap_new + 1 , heap_old + 1 , (len_old - 2)  * sizeof(TYPE));

	sortDown(heap_new, len_old - 1, 0 );

	return heap_old[0];
}


// ������  �� �� С 
void HeapSort( TYPE* heap /* �Ѿ����õ���С�� */, int len) {
	int index = len - 1 ;
	while (index > 0) {
		// swap  ��ǰ��ͷ������С��  �Ƶ��ѵ������
		TYPE temp = heap[index];
		heap[index] = heap[0];
		heap[0] = temp;
		sortDown(heap , index /*���ٶѳ���*/ , 0  /*����ĸ��ڵ㿪ʼ���µ��� ��Ϊֻ�����Ԫ���޸���*/ );
		index--;
	}
}

// ������  С �� ��
void HeapSortIncrease(TYPE* heap /* �Ѿ����õ���С�� */, int len) {
	int index = len - 1;
	while (index > 0) {
		// swap  ��ǰ��ͷ������С��  �Ƶ��ѵ������
		TYPE temp = heap[index];
		heap[index] = heap[0];
		heap[0] = temp;
		sortDown(heap, index /*���ٶѳ���*/, 0  /*����ĸ��ڵ㿪ʼ���µ��� ��Ϊֻ�����Ԫ���޸���*/);
		index--;
	}
	// ��С�� �ʺ�  �� �� С
	// ���� �ʺ�  С �� ��
	for (int i = 0 ; i < len / 2; i++) { //reverse 
		TYPE temp = heap[i];
		heap[i] = heap[len - 1 - i];
		heap[len - 1 - i] = temp;
	}
}

// ���� 
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

	HeapSortIncrease(a, LENGTH); // �ظ�ֵ ������Ҳ�ǿ��Ե� �� 8 
	cout << "after sort" << endl;
	for (TYPE thr : a) {
		cout << thr << " ";
	}
	cout << endl;

 
	 
	TYPE add[LENGTH + 1]; memset( add, 0, LENGTH + 1 );
	HeapAdd(a, LENGTH , add, -72); // ����֮�� ԭ������õĻ�Ū�� ��������С��
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

