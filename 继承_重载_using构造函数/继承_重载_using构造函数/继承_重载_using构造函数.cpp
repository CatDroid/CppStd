// 继承_重载_using构造函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;


class Partner {
public:
	Partner(int id) :mID(id) {}
private:
	int mID;
	// 定义在类中的友元函数,其作用域在全局作用域下.
	// 类域内定义的友元函数调用时必须具有该类类型的实参,或者具有从该类型(实参是本类型)转换到形参类型 
	friend ostream& operator<< (ostream& os, Partner& self) {
		os << self.mID;
		return os;
	}
};


class Base {
public:
	Base(int temp):mInt(temp){}
	Base(float temp):mFloat(temp){}
	Base(double temp) :mDouble(temp) {}

	void overload_func(int temp) {
		cout << "Base::overload_func(int temp) " << temp << endl;
	}
	void overload_func(Partner& p) {
		cout << "Base::overload_func(Partner temp) temp = " << p << endl;
	}
 
	virtual void virtual_func(Partner& p) { // 虚函数直接继承了，在虚函数表中登记 无需要使用using声明 
		cout << "Base::virtual_func(Partner temp) temp = " << p << endl;
	}

private:
	int mInt{0};
	float mFloat{0};
	double mDouble{0};
};

class Derive : public Base {
public:
	using Base::Base;			// 继承构造函数
	using Base::overload_func;	// 继承非虚成员函数 否则 d.overload_func(p); => error: no viable conversion from 'Partner' to 'double'

	void overload_func(double temp) {
		cout << "Derive::overload_func(double temp) " << temp << endl;
	}


private:
	double mDD{ 0 };			// 使用 using继承构造函数 和  成员变量初始化 两个C++特性
};


class A {
public:
	A() {
		cout << "A()" << endl;
	}// 因为 C 要从 B 中 using继承 构造函数 B(double)
	A(int a) {
		cout << "A(int a)" << endl;
	}
};

class B {
public:
	//B() {
	//	cout << "B()" << endl;
	//}
	B(int b) {
		cout << "B(int b)" << endl;
	}

	B(double b) {
		cout << "B(double b)" << endl;
	}
};

class C: public A,B {
public:
	using A::A;
	using B::B; // 错误:函数 C(int) 已经从 A中继承 --> using继承冲突! 需要显式定义冲突的构造函数
	C(int c):A(c),B(c) {	
				// 通过显式定义继承类的冲突构造函数 阻止隐式生成相应继承构造函数函数
				// 如果不在显式定义中 调用基类构造函数 基类就要实现无参数 默认构造函数
		cout << "C" << endl;
	}
	// using从B继承的 C(double) 会调用B(double) 但是A只会调用无参数默认构造函数  如果A没有定义默认构造函数 编译错误
	// 也就是: C(double):B(double),A() 
};

class DefaultA {
public:
	DefaultA(int a = 3, double e = 2.4) {
		cout << "DefaultA [" << this << "] a = " << a << " e = " << e  << endl;
	}
	/*
		默认参数构造函数 会产生多个不同的构造函数:
		1. (int a = 3 , double e = 2.4 )
		2. (int a = 3 )
		3. ()
		4. (const Base&)
		这样using继承构造函数 也会产生这些，特别是无参默认构造函数
	*/
	~DefaultA() {
		cout << "~DefaultA()" << this  << endl;
	}
};

class DefaultB : public DefaultA {
private: // 不影响 using继承构造函数
	using DefaultA::DefaultA;
};


class Temp 
{
public:
	Temp(int t) {

	}// 自定义了构造函数 编译器不会产生默认构造函数 但是还是会产生拷贝构造函数(没有移动构造函数 实参是右值情况下调用拷贝构造函数)
};


int main()
{
	{
		Partner p(123);
		// Derive d ;	//	错误!	Derive没有从Base上继承到无参构造函数
		Derive d(12);


		d.overload_func(12);
		d.Base::overload_func(p);	// 不用 using Base::overload_func;
		d.overload_func(p);			// 必须 using Base::overload_func; 继承非虚成员函数
		d.virtual_func(p);			// 虚函数直接从基类获得 不需要using声明
	} cout << "---------" << endl;

	{
		C temp(1.24);
	} cout << "---------" << endl;

	{
		DefaultB temp(12) ;
		DefaultB temp2(temp);
		DefaultB temp3;
	}
	{
		Temp t(123);
		Temp t1(t);
	}
    return 0;
}

