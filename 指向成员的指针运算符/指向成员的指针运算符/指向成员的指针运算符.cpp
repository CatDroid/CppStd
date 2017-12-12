// 指向成员的指针运算符.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Base {
public:
	void base_func() {
		cout << "Base::base_func " << this << " mNumber = "<< mNumber << " mPri = " << mPri  << endl;
	}

	virtual void call_func(int i) {
		cout << "Base::call_func " << this << " i = " << i << endl;
		mPri = i;
	}

	int mNumber ;

protected:
	int mPri; 
};

class Derive :public Base {
public:
	virtual void call_func(int i) {
		cout << "Derive::call_func " << this << " i = " << i << endl;
		mPri = -i ;
	}
	
};

// 指针到成员运算符		.* 和 ->*  第一操作数 必须是类的对象 第二操作数 必须是'指向成员的指针类型 '
// 成员访问运算符		. 和 ->

/*
	1. 类外 不能指向私有成员
	2. 可以指向成员函数  也支持多态
	3. int Base::*pVar = &Base::mNumber; ==>  pVar 是一个指针  指向Base类/域中 int类型
		void (Base::*pFun)(int)	= &Base::call_func ; ==>  pFun 是一个指针  指向Base类/域中 void (int)的函数
*/
int main()
{
	// pVar 是一个指针  指向Base类/域中 int类型  
	// int Base::* 类型 不能转换为 int* 
	//int *p = &Base::mNumber;
	int Base::*pVar = &Base::mNumber; // 指向成员的指针类型
	//int Base::*n = &Base::mPri;  // 不可访问成员  不能指向

	// pFun 是一个指针  指向Base类/域中 void (int)的函数 
	void (Base::*pFun)(int) = &Base::call_func ;


	Base b; 
	b.*pVar = 1;		// .*   ->* 
	(b.*pFun)(110);
	b.base_func();


	Derive d;
	d.*pVar = 2;
	(d.*pFun)(220);// 还是支持多态的!  执行override的Derive::call_func(int)
	d.base_func();


    return 0;
}

