// 函数对象与比较.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
#include <algorithm> // sort 
#include <string>

using namespace std;

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
		cout << "MyString(const MyString& other) " << this <<  " other " << &other << endl;
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


	bool operator < (const MyString& other) const {
		cout << "operator <   " << this  << " "  << &other << endl;
		if (buf == NULL) return true ;
		if (other.buf == NULL) return false;
		return strcmp((const char*)buf, (const char*)other.buf) < 0;
	}

	void dump() {
		printf("buf=%s\n", buf);
	}

};

class Func_call {
private:
	bool ascend;
public:
	Func_call(bool asc) :ascend(asc) { cout << "Func_call()" << endl; }
	~Func_call() { cout << "~Func_call()" << endl; }

	//重载了函数调用运算符的类，在其调用运算符执行时，可以称作"函数对象"
	bool operator()(int a, int b) // 返回true,a排在前 
	{
		cout << "Func_call::operator()" << endl;
		return ascend ? (a < b) : (a > b);
	}
};


int main()
{

	int m[] = { 34,45,312,3,21,4,3246 };
	cout << "before:" << endl;
	for (int k : m) cout << k << " ";
	cout << endl;

	sort(m, m + sizeof(m) / sizeof(m[0]), Func_call(false));

	cout << "sorted:" << endl;
	for (int k : m) cout << k << " ";
	cout << endl;

	// 标准库 已经有现成的 基于模板的比较函数对象   自定义类型需要支持“<”、“>”等比较运算符
	MyString arr[] = { MyString("abc"), MyString("789"),MyString("ABCDE123") };

	// sort会进行赋值来交换 
	cout << "MyString sort begin" << endl;
	for (MyString& temp : arr) temp.dump(); 

	sort(arr, arr + sizeof(arr)/sizeof(arr[0]) , less<MyString>() /*实例化临时对象*/  );

	cout << "MyString sort end" << endl;
	for (MyString& temp : arr) temp.dump();


	// 既然有迭代器，如果是string 就可以使用反向迭代器来完成逆序排列
	string str("cvicses");
	string s(str.rbegin(), str.rend());
	cout << s << endl;


	return 0;
}
