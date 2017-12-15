// �͵س�ʼ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class Mem {

public:
	Mem(int a, int b) :ma(a), mb(b) {
		std::cout << "[" << this << "] ma = " << ma << "; mb = " << mb << std::endl;
	}

	// clang++ �͵س�ʼ��.cpp  -o main --std=c++98  �������
	// clang++ �͵س�ʼ��.cpp  -o main --std=c++11  ����ͨ��  noexcept C++ ���� 
	~Mem() noexcept(true) {
		std::cout << "[" << this << "] ~Mem " << std::endl;
	}

	void dump() {
		std::cout << "[" << this << "] ma = " << ma << "; mb = " << mb << std::endl;
	}

private:
	int ma;
	int mb;
};

class MemE {
public:
	// noexcept ���� ������ Ҳ�� ������ (���ݱ��ʽ�� �Ƶ� �����Ƿ���׳��쳣 )
	//~MemE() noexcept(true) {  // һ���쳣ֱ��std::terminal abort���� ��ֹ�쳣��ɢ
	~MemE() noexcept(false) { // C++11 
	//~MemE() throw(int) { // C++98
		throw 666; // int 
	}
};

int main()
{
	try {
		MemE e;
	}
	catch (int ex) {
		cout << "Exception !  ex = " << ex << endl;
	}
    return 0;
}

