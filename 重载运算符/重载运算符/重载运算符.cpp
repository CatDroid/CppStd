// 重载运算符.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <algorithm> // sort 
#include <string>

using namespace std;

/*

C++不能重载的运算符有五个
（1） "."（成员访问运算符）
（2）" .*"（成员指针访问运算符）
（3） "::"（域运算符）
（4）"siezof"（长度运算符）
（5） " ?:"（条件运算符）

*/
class MyString {

private:
	uint8_t* buf;
	int32_t len;	// actual 
	int32_t cap;    // total  

public:
	MyString() :buf(NULL), len(0) {
		cout << "MyString() " << this << endl;
	}

	explicit MyString(const char* in_buf) {
		cout << "MyString(const char* in_buf) " << this << endl;
		if (in_buf != NULL) {
			cap = len = strlen(in_buf) + 1;
			buf = new uint8_t[len];
			memcpy(buf, in_buf, len);
		}
		else {
			buf = NULL;
			cap = len = 0;
		}
	}

	MyString(const MyString& other) {
		cout << "MyString(const MyString& other) " << this << " other " << &other << endl;
		buf = new uint8_t[other.len];
		cap = len = other.len;
		memcpy((char*)buf, (const char*)other.buf, len);
	}

	~MyString() {
		cout << "~MyString() " << this << endl;
		delete[] buf; buf = NULL;
	}

	MyString& operator = (const MyString& other) {
		cout << "MyString& operator = (const MyString& other) " << this << " other " << &other << endl;
		if (this == &other) {
			return *this;
		}
		if (other.len > cap) {
			delete buf;
			buf = new uint8_t[other.len];
			cap = len = other.len;
		}
		else {
			len = other.len;
		}
		memset(buf, 0, cap);
		memcpy(buf, other.buf, len);
		return *this;
	}

	// 类型转换符
	operator int() const {
		return  len; 
	}

	bool operator < (const MyString& other) const {
		cout << "operator <   " << this << " " << &other << endl;
		if (buf == NULL) return true;
		if (other.buf == NULL) return false;
		return strcmp((const char*)buf, (const char*)other.buf) < 0;
	}

	void dump() {
		printf("buf=%s\n", buf);
	}

	/* friend  
	// * 它破坏了类的封装性和隐藏性，使得非成员函数可以访问类的私有成员
	// * 建议仅仅在重载操作符的时候使用 
	// * operator <运算符>(<参数1>,<参数2>) 它等价于 <参数1><运算符><参数2> 
	// * cout = operator<<(cout,x1); //  显示调用
	// * cout = cout<<x1;   //  OK  等价这个 
	// * >>和<<（输入输出运算符）
	// * 友元函数不是类的成员函数，定义在类内或者类外没有区别
	// **! 定义在类中的友元函数,其作用域在全局作用域下.
	// **! 类域内定义的友元函数调用时必须具有该类类型的实参,或者具有从该类型(实参是本类型)转换到形参类型 
	
	友元函数有两种，
	一种不属于任何类的,这种其实和c的外部函数一样属于全局函数
	一种是其他某个类的成员函数
	
	只有全局性质的友元函数才会直接定义在类的内部,友元函数虽然不是类的成员函数,却是类的接口
	和类关系密切,所以可定义在类的内部
	
	
	当调用一个友元函数时,名字搜索域也包含与"实参"(是实参 不是形参)关联的那些“名称空间和类”中的名字，
	于是，一个如下定义的友元函数可以被调用：
	friend void f( A& a ) {}
	但是如果f的形参不是A类型的行不行呢？
	当然行，但必须具备有效的从A到f形参类型的转换，
	class A
	{
	public:
		friend void f( int a ){ }
	 
		operator int( ){ return a; } // 从本类型 转换到 friend形参类型
	 
	private:
	 
		int a;
	};

	int main( void )
	{
		A a;
		f( a ); 		// 实参是A类型 所以会在A类域 中 找友元函数f 
		return 0;
	}

	
	*/
	friend ostream& operator<< (ostream& out, MyString& self);
};

// 不是类的成员函数 
ostream& operator<< (ostream& out, MyString& self) {
	out << "地址值：" << static_cast<void *>(self.buf) << " 字符串: " << self.buf  <<  endl;
	return out;
}

int main()
{
	MyString arr[] = { MyString("abc"), MyString("789"),MyString("ABCDE123") };
	for (MyString& temp : arr) {
		cout << temp;
		cout << "长度：" << int(temp) << endl;
	}
	return 0;
}
