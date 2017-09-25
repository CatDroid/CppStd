// 三大函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class MyString {

private:
	uint8_t* buf;
	int32_t len;	// actual 
	int32_t cap ;   // total  

public:
	MyString():buf(NULL),len(0){

	}

	explicit MyString(const char* in_buf ) { // 单参构造函数'都必须是显示的
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
		delete[] buf; buf = NULL; 
	}

	MyString& operator = (const MyString& other) {
		if (this == &other){
			return *this;
		}
		if ( other.len > cap) {
			delete buf;
			buf = new uint8_t[other.len];
			cap = len = other.len;
		}
		else {
			len = other.len;
		}
		memset(buf,  0,  cap);
		memcpy(buf, other.buf, len);
		return *this;
	}

	void dump() {
		printf("buf=%s\n" , buf);
	}

private:
	/*

	三大函数：拷贝构造函数、析构函数和赋值函数

	构造函数：包含一个拷贝/复制构造函数，其它的称为普通构造函数

	a.声明的同时初始化：
		MyString s1 = s2;	//	注意此时虽然出现=，但是不是调用operator=
							//	区别于 MyString s1 ; s1 = s2 ; // 复制赋值运算符
		MyString s1(s2);
		
	
	b.调用函数时使用按值传递（而不是按引用传递）
		void f(MyString s);
		MyString s1;
		f(s1);
	
	c.通过值返回对象
		MyString f()
		{
			MyString s1;
			return s1;
		}

	explicit
		用来防止由构造函数定义的隐式转换
		可以用‘单个实参’来调用的构造函数  定义了  从形参类型到该类类型的一个隐式转换
		Google约定所有'单参数的构造函数'都必须是显示的，只有极少数情况下，拷贝构造函数，可以不声明explicit

		MyString a3 ;
		a3 = "123"; // 先 隐式转换成MyString ---> 后 MyString复制赋值运算符

	懒得写 '赋值函数' 和 '拷贝构造函数'
	又不允许别人使用编译器生成的缺省函数，
	那么我们可以只需将 拷贝构造函数和赋值函数 声明为私有函数，不用编写代码
	*/
	//MyString& operator = (const MyString& other);
	//MyString(const MyString& other);
};

int main()
{

	MyString a1("hello world");
	MyString a2("i");
	a1.dump();
	a2.dump();

	a2 = a1;
	a2.dump();


	//MyString a3 = "implicit" ;
	//a3.dump();

    return 0;
}

