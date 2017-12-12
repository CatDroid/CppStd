// 右值引用的左值给左值引用.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <inttypes.h>

using namespace std;

class DefClass {
public:
	// vptr  
	uint64_t self;			// vptr +8
	uint64_t temp[100];		// vptr +8 +8   
	uint64_t other;			// vptr +8 +8 +8*100
	uint64_t isMove;		// vptr +8 +8 +8*100 +8 
							// sizeof(DefClass)  = 832 

	DefClass() :self((uint64_t)this), other(0), isMove(0) {
		cout << "DefClass() " << this << endl;
	}
	virtual ~DefClass() {
		cout << "~DefClass() " << this << endl;
	}
	DefClass(DefClass&& other) :self((uint64_t)this), other((uint64_t)&other), isMove(1) {
		cout << "DefClass(DefClass&& other)       this:" << this << " other: " << &other << endl;
	}

	DefClass(const DefClass& other) :self((uint64_t)this), other((uint64_t)&other), isMove(0) {
		cout << "DefClass(const DefClass& other)  this:" << this << " other: " << &other << endl;
	}

	DefClass& operator=(const DefClass& other) {
		cout << "operator=(const DefClass& other)  this:" << this << " other: " << &other << endl;
		return *this;
	}

	DefClass& operator=(DefClass&& other) {
		cout << "operator=(DefClass&& other)       this:" << this << " other: " << &other << endl;
		return *this;
	}

	void dump() const {
		printf("this %0" PRIx64 " other %0" PRIx64 " %s\n", self, other, (isMove ? " Move " : "Non-Move"));
	}
};


void dumpByleft(DefClass & left) {
	left.dump();
}


DefClass& returnLeftRef(DefClass& left) {
	return left; // 类似'自增运算符'
}
// 如果左值引用是一个临时变量（例如函数的返回值），那么它就是右值
// 

DefClass dumpReturn (DefClass & left) {
	return left; //  拷贝构造函数  @VS2015/Clang++
}


DefClass get_a_DefClass() {
	DefClass a;
	a.temp[0] = 1212 ;
	return  a;
}

DefClass& foo(DefClass&& x) {
	x.temp[0] = x.temp[0] + 1 ;
	return x; // 具名的右值引用是 左值 可以给到 左值引用 !!!!
}

/*
VS2015 (x86) 连续定义的int变量，地址相差12个字节。这是为什么？

按照我们的理解，int占用4个字节，应该相差4个字节。

在VS2015在Debug模式下，int变量占用12个字节。可以这样认为，Debug模式下，在int变量的前后各增加了4个字节，用于存储调试信息，
那么aa的后面4个字节，bb的前面4个字节，再加上aa本身的4个字节，刚好相差12个字节。

当我们把模式设为Release，就会发现栈上连续定义的int变量，地址相差4个字节。

注意：栈上地址从高向低增长。 
*/
int main()
{
	// clang++ 	/ vs2015+Release Mode
	cout << "sizeof(char &)=" << sizeof(char &) << endl; // sizeof(char &)=1
	cout << "sizeof(int  &)=" << sizeof(int  &) << endl; //	sizeof(int  &) = 4
	cout << "sizeof(long long &)=" << sizeof(long long &) << endl; // sizeof(long long &) = 8
	cout << "sizeof(long long)=" << sizeof(long long) << endl;
	long long size = 1;			cout << &size << endl;		// 0xffffcbf0
	long long& size_ref = size; cout << &size_ref << endl;	// 0xffffcbf0
	long long size_2 = 2;		cout << &size_2 << endl;	// 0xffffcbe0
	


	//DefClass&& r1 = DefClass();
	//DefClass&& r2 = r1; // 无法将右值引用绑定到左值

	DefClass r;
	DefClass& r1 = r;
	DefClass& r2 = r1;  // OK 



	DefClass&& right = DefClass();
	dumpByleft(right); // 右值引用 是一种类型  如果变量是左值(有名字 可去地址) 那么可以给到左值引用变量初始化
					   // 如果函数参数是右值引用类型，那么实参要是‘右值’来初始化参数 

//	{
//		DefClass&& returnRight = dumpReturnRight(right);  // ERROR 类型DefClass的右值引用 不能绑定到 类型DefClass的左值
//	}

	//DefClass* addr = &returnLeftRef(right);
	//cout << "DefClass* " << addr << endl;





	DefClass& addr =  returnLeftRef(right);

	//dumpByleft(dumpReturnRight(right));
	
	//{
	//	DefClass&& ret = dumpReturn(right);
	//	ret.dump();
	//}

	cout << "-------------" << endl;
    return 0;
}

