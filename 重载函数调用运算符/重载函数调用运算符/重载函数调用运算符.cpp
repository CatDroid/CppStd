// 重载函数调用运算符.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <algorithm> // sort 

using namespace std;

class MyString {

private:
	uint8_t* buf;
	int32_t len;	// actual 
	int32_t cap;    // total  

public:
	MyString() :buf(NULL), len(0) {
		cout << "MyString() " << endl;
	}

	//explicit
	MyString(const char* in_buf) {  
		cout << "MyString(const char* in_buf) " << endl; 
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
		buf = new uint8_t[other.len];
		cap = len = other.len;
		memcpy((char*)buf, (const char*)other.buf, len);
	}

	~MyString() {
		cout << "~MyString()" << endl;
		delete[] buf; buf = NULL;
	}

	MyString& operator = (const MyString& other) {
		cout << "MyString& operator = (const MyString& other) " << endl;
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

	// 重载函数调用运算符 
	void operator() (const MyString& other1, const  MyString& other2) {
		printf("%s %s %s\n" , buf , other1.buf , other2.buf );
	}

	void operator() (const MyString& other1) {
		printf("%s %s\n", buf, other1.buf);
	}

	void dump() {
		printf("buf=%s\n", buf);
	}

};

class Func_call {
private:
	bool ascend ;
public:
	Func_call(bool asc):ascend(asc) { cout << "Func_call()" << endl; }
	~Func_call() { cout << "~Func_call()" << endl; }

	//重载了函数调用运算符的类，在其调用运算符执行时，可以称作"函数对象"
	bool operator()(int a, int b) // 返回true,a排在前 
	{
		cout << "Func_call::operator()" << endl;
		return ascend ? (a < b) : (a > b) ;
	}
};


int main()
{
	MyString a1 ;
	a1 = "123";   // 先 隐式转换成MyString  再 MyString复制赋值操作符
	cout << "end" << endl;


	MyString a2("Hello");
	MyString a3("World");
	MyString a4("this is");
	a4(a2, a3);
	a4(a2);


	int m[] = { 34,45,312,3,21,4,3246 };
	cout << "before:" << endl;
	for (int k : m) cout << k << " ";
	cout << endl;

	sort(m,  m + sizeof(m) / sizeof(m[0])  , Func_call(false ) );
	
	cout << "sorted:" << endl;
	for (int k : m) cout << k << " ";
	cout << endl;

	return 0;
}