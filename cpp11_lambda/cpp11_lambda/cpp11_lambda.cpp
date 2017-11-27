// cpp11_lambda.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std ;

// int g_catch = 2; // lambda 不能捕捉的全局变量


//template <class T>
typedef int T;
static int intcompare(const T *p1, const T *p2)
{
	T i = *((T *)p1);
	T j = *((T *)p2);
	return (i < j);
}

 

class MyClass {
private:
	
public:
	int more;
	MyClass(int temp):more(temp) {
		cout << "MyClass()" << endl;
	}
	~MyClass() {
		cout << "~MyClass()" << endl;
	}

	int sum() {
		int a = 10;
		int b = 20;
		//auto b2 = [a, &b, &more](int c) -> int {	 //  成员变量 不能=在捕捉列表	
		auto b2 = [a, &b ,this ](int c) -> int {
			b = a + c; // +more;   // 封闭函数局部变量不能再lambda中引用，除非位列于捕捉列表
			b = a + c + this->more;//  成员变量不能直接在lambda中使用  
			this->more = 2;			// OK  lambda中成员变量可以通过传递this来修改
			//this = 0x111;			// ERROR
			return a + c;
		};

		int result = b2(200);
	}

};

/*
	不仅具有函数指针的灵活性，还可以通过捕获局部变量提高可扩展性
	Lambda表达式 把 函数 看作 对象
	[](int x, int y) -> int { int z = x + y; return z + x; };
	如果我们将 lambda表达式 比作 函数，可以看到它与“函数名”对应的是一对空的“方括号”，即“捕获表达式”
	 


	[var]   传值方式（只读）将变量传递到匿名函数中
	[=]     父作用范围的所有变量以传值方式（只读）,传递到匿名函数中（包括this）
	[&var]  引用方式（读写）将变量传递到匿名函数中
	[&]     父作用范围的所有变量以引用方式（读写）,传递到匿名函数中（包括this）
	[=,&var1,&var]  var1,var2以读写方式传递到匿名函数中，其他变量以只读方式传递到函数中
	[&, var1,this]   var1,this以只读方式传递到函数中，其他变量以读写方式传递到函数中

	捕捉非父作用范围的变量，或者非自变量（如，静态常量）等，都将导致编译错误。故可以看出，匿名函数
	非动态函数，在编译期就定义了，故不会产生额外开销。
*/
int main()
{
	{
		/*
			比较函数需要单独声明。这增加了将错误的比较函数传递给 qsort() 操作的风险。
			比较函数接受 void * 参数，因此缺失了某种程度的类型检查。
			比较函数看不到任何局部作用的变量。因此，如果存在其他影响排序的因素，必须在更大范围内声明
		*/
		int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		//qsort((void *)a, 10, sizeof(int), intcompare<int>); // ERROR
		qsort((void *)a, 10, sizeof(int), (int(*)(const void *p1, const void *p2))intcompare);
		for (int i = 0; i < 10; i++) { printf("%d ", a[i]); } printf("\n");
	}

	{
		/*
			C++ std::sort() 算法 与 lambda表达式 结合使用
			std::sort()是一个模板，因此会保留所有类型信息
		*/
		int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		std::sort(a, &a[10], [](int x, int y) -> int { return x < y; }); // 指明返回值 
		//std::sort(a, &a[10], [](int x, int y) { return x < y; });
		for (int i = 0; i < 10; i++) { printf("%d ", a[i]); } printf("\n");
	}

	{
		int a = 10;
		int b = 20;
		// static int s_static = 22;  // 静态变量---无法在lambda中,捕获带有静态存储持续时间的变量
		// auto b2 = [a, &b, g_catch](int c) -> int { // 全局变量---无法在lambda中,捕获带有静态存储持续时间的变量
		auto b2 = [a, &b ](int c) -> int {	// a 只读  b 读写
			//a = 12;						// 表达式必须是可修改的左值
			b = a + c ;
			return a + c;
		};
		 
		int result = b2(200);
		cout  << "b = " << b << " result = " << result << endl;
	}

    return 0;
}

