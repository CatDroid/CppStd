// 就地初始化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class Mem {

public:
	Mem(int a, int b) :ma(a), mb(b) {
		std::cout << "[" << this << "] ma = " << ma << "; mb = " << mb << std::endl;
	}

	// clang++ 就地初始化.cpp  -o main --std=c++98  编译错误
	// clang++ 就地初始化.cpp  -o main --std=c++11  编译通过  noexcept C++ 新增 
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
	// noexcept 既是 描述符 也是 操作符 (根据表达式来 推导 返回是否会抛出异常 )
	//~MemE() noexcept(true) {  // 一旦异常直接std::terminal abort程序 防止异常扩散
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

