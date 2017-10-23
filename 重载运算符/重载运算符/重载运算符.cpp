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

	// friend  
	// 它破坏了类的封装性和隐藏性，使得非成员函数可以访问类的私有成员
	// 建议仅仅在重载操作符的时候使用 
	// operator <运算符>(<参数1>,<参数2>) 它等价于 <参数1><运算符><参数2> 
	// cout = operator<<(cout,x1); //  显示调用
	// cout = cout<<x1;   //  OK  等价这个 
	// >>和<<（输入输出运算符）
	// 友元函数不是类的成员函数，定义在类内或者类外没有区别
	// 定义在类中的友元函数  定义在类中的友元函数,其作用域在全局作用域下. 
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
