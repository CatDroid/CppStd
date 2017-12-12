// ConsoleApplication1.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

typedef int DATA_TYPE;

class MiniHeap {
	
public:
	DATA_TYPE* buf;
	int size;
	int cap;

	MiniHeap() {
		size = 0;
		cap = 16;
		buf = (DATA_TYPE*)malloc(cap*sizeof(DATA_TYPE)); memset(buf, 0, cap * sizeof(DATA_TYPE));
	}

	void swap(DATA_TYPE& a , DATA_TYPE& b ) {
		DATA_TYPE temp = a; 
		a = b;
		b = temp;
	}

	void push(DATA_TYPE value) {
		if (size + 1 > cap) {
			cap = cap * 2;
			buf = (DATA_TYPE*)realloc(buf,cap*sizeof(DATA_TYPE));
		}
		int current = size  ;
		while (current > 0) {
			int parent = (current - 1) / 2;
			if (buf[parent] > value) {
				buf[current] = buf[parent];
				current = parent;
			}
			else {
				break;
			}
			
		}
		buf[current] = value;
		size += 1;
	}

	bool pop(DATA_TYPE& out) {
		if (size <= 0) return false;

		out = buf[0];
		buf[0] = buf[ size - 1 ];
 
		int current = 0;
		while (current < size - 1) {

			int smaller_index = current;
			int left_index = current * 2 + 1;
			int right_index = current * 2 + 2;
			if (left_index < size - 1 && buf[left_index] < buf[smaller_index]) {
				smaller_index = left_index;
			}

			if (right_index < size - 1 && buf[right_index] < buf[smaller_index]) {
				smaller_index = right_index;
			}

			if (smaller_index == current) break;
			
			swap(buf[current], buf[smaller_index]);

			current = smaller_index;

		}
		size -= 1;
		return true;
	}

	

};

int main(int argc, char* argv[]) {


	MiniHeap* heap = new MiniHeap();

	heap->push(18);
	heap->push(7);
	heap->push(29);
	heap->push(-1);
	heap->push(30);

	heap->push(67);
	heap->push(1);
	heap->push(56);
	heap->push(-8);
	heap->push(-22);

	heap->push(79);
	heap->push(12);
	heap->push(-100);
	heap->push(-98);
	heap->push(-94);

	heap->push(5);
	heap->push(9);
	heap->push(23);
	heap->push(19);
	heap->push(222);


	DATA_TYPE value = 0;
	while (heap->pop(value)) {
		cout << value << endl;
	}
	return 0;
}
