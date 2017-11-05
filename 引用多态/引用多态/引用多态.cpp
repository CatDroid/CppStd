// 引用多态.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std; 

/*
	C++中虚操作符和其他虚函数的规则一样，操作符可以为虚函数，进行动态绑定， 
	虽然这种情况并不多见!!

	1. 派生类中要重定义基类虚函数，要注意参数必须为基类引用类型
		override virtual Base&/Derive& operator= (const Base& b) // 必须是Base

	2. 派生类除了重定义基类的虚操作符，还要定义自身的操作符重载
		即派生层次每增加一层，理论上派生类就需要多定义一个操作符重载
		(因为参数不一样!!)
		virtual Derive& operator= (const Derive & b)

*/
class base {
public:
	base() {
		cout <<"base()" << endl;
	}

	base(const base& other) {
		cout << "base(const base& other)" << endl;
	}

	virtual ~base() {
		cout << "~base()" << endl;
	}
	
	virtual base& operator= ( const base& other ) {
		cout << "base& operator= base " << endl; 
		return *this;
	}

	virtual void shot() {
		cout << "base::shot()" << endl;
	}

};

class derive : public base {

public:
	derive() {
		cout << "derive()" << endl;
	}
	virtual ~derive() {
		cout << "~derive()" << endl;
	}
	// 与基类的operator=完全不同，不是重新定义，不会动态绑定。   
	// 如果不定义该操作符，会自动合成一个，并自动调用基类的operator=，不会动态绑定  
	virtual derive& operator= (const derive& other) {
		cout << "derive& operator= derive" << endl;
		return *this;
	}

	// 重新定义基类的operator=，会动态绑定   
	// virtual base& operator=(const base& rhs)  //返回值两种都可以   
	virtual derive& operator=(const base& rhs)
	{
		cout << "derive& operator= base " << endl;
		return *this;
	}


	virtual void shot() {
		cout << "derive::shot()" << endl;
	}

};


class derive2 : public derive {
public:
	derive2() {
		cout << "derive2()" << endl;
	}
	virtual ~derive2() {
		cout << "~derive2（()" << endl;
	}

	// 实际上这个没有override基类的 因为参数都不一样 !!
	virtual derive2& operator= (const derive2& other)  { // 不能 override
		cout << "derive2& operator= derive2 " << endl;
		return *this;
	}

#if 0 
	virtual derive2& operator= (const derive& other) override {
		cout << "derive2& operator= derive2 " << endl;
		return *this;
	}
#endif 

#if 0 
	virtual derive2& operator= (const base& other) override {
		cout << "derive2& operator= base " << endl;
		return *this;
	}
#endif 

	virtual void shot() {
		cout << "derive2::shot()" << endl;
	}
};


int main()
{
	cout << "----------begin of main --------------" << endl;
	{
		derive2 d2;
		base& b = d2; // 引用是指针意外的另外一种多态(在函数参数传递中 base& 和 base* 都可以多态 但是 base 的话会导致拷贝构造函数 ) 
		b.shot();


		cout << "--------------------------------------" << endl;
		derive d1;
		cout << "引用初始化 之后 后面就变成 赋值运算了 " << endl;
		b = d1;  // derive2不重写operator(base/derive)的话，就调用 derive& operator= base 
 
		cout << "--------------------------------------" << endl; 
		b.shot();// 没有改变引用

	}
	{
		cout << "----------------Stage 2-----------------" << endl;
		derive d;
		base b;
		base& b_ref = d ;
		b_ref = b; // device& operator = base 
		cout << "-----------------------------------------" << endl;
	}

	cout << "------------end of main --------------" << endl;
    return 0;
}

