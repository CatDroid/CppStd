// cpp11_lambda.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>

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
	int more;
	int privateFun() {
		return more;
	}
public:
	
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

	/*
		若一个 lambda函数被定义于某类型的成员函数中，会被当作该类型的friend
		只有当该 lambda函数创建的 作用域 是在 该类的成员函数内部时才能运作
		在成员函数中指涉对象的this指针，必须要显式的传入 lambda 函数， 否则成员函数中的 lambda 函数无法使用任何该对象的参数或函数
		若是 lambda 函数使用 [&] 或是 [=] 的形式，this在 lambda 函数即为可见

		使用 auto 关键字让我们能够存储 lambda 函数


	*/
	auto getLambda(int a ){
		return [this ,a]()->int{  return this->privateFun() * a ; /*friend*/ };
	}

 

};

/*
	不仅具有函数指针的灵活性，还可以通过捕获局部变量提高可扩展性
	Lambda表达式 把 函数 看作 对象
	[](int x, int y) -> int { int z = x + y; return z + x; };
	如果我们将 lambda表达式 比作 函数，可以看到它与“函数名”对应的是一对空的“方括号”，即“捕获表达式”
	 
	[](int x, int y) { return x + y; }
	匿名函数的回返类型是 decltype(x+y)。只有在 lambda 函数符合"return expression"的形式下，它的返回类型才能被忽略
	如果 lambda 函数没有传回值(例如 void )，其回返类型可被完全忽略

	传值/传引用:
	[var]   传值方式（只读）将变量传递到匿名函数中
	[=]     父作用范围的所有变量以传值方式（只读）,传递到匿名函数中（包括this）
	[&var]  引用方式（读写）将变量传递到匿名函数中
	[&]     父作用范围的所有变量以引用方式（读写）,传递到匿名函数中（包括this）
	[=,&var1,&var]  var1,var2以读写方式传递到匿名函数中，其他变量以只读方式传递到函数中
	[&, var1,this]   var1,this以只读方式传递到函数中，其他变量以读写方式传递到函数中
	定义在 与lambda函数 相同作用域的参数/引用 也可以被使用, 参数集合一般被称作 closure (闭包)
	若不使用引用的符号&，则代表参数以传值的方式传入 lambda 函数  , "传值的话就是只读"

	捕捉非父作用范围的变量，或者非自变量（如，静态常量）等，都将导致编译错误。故可以看出，匿名函数
	非动态函数，在编译期就定义了，故不会产生额外开销

	lambda函数可以不在被声明的地方就地使用,若参数是以传引用的方式链接到 closure中,是无意义甚至是危险的行为
	若lambda 函数只在定义的作用域使用， 则可以用 [&] 声明 lambda 函数，代表所有引用到栈/stack中的参数，都是以引用的方式传入

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

	{ // 多次调用  lambda表达式 (没有闭包 只是一个局部的匿名函数)
		auto ftn = [](int x, int y) -> int { int z = x + y; return z + x; }; 
		cout << ftn(3, 2) << endl; // 8
		cout << ftn(3, 3) << endl; // 9 	
	}

	{
		int total = 0;
		int value = 5;
		auto ftn = [&, value](int x) { total += (x * value); return total; };
		cout << ftn(3) << endl; // 15 
		value = 6;  // 值传递 不影响
		cout << ftn(4) << endl; // 35 

	}
	{ // 闭包 与 std::vector  std::for_each 
		std::vector<int> someList;
		for (int i = 0; i < 10; i++) {
			someList.push_back(i);
		}
		int total = 0;
		std::for_each(someList.begin(), someList.end(), [&total](int x) { total += x;});
		cout << total << endl; // 45
	}

	{
		MyClass my(12);
		auto ftn = my.getLambda(4); // 48
		cout << ftn() << endl;
	}



	{
		/*
			lambda函数 是编译器从属类型的函数对象, 这种类型名称只有编译器自己能够使用
			如果用户希望将 lambda函数 作为参数传入，该类型必须是模版类型，或是必须，创建一个std::function ,去获取lambda的值
		
			????
			但是，如果 lambda 函数是以‘引用’的方式获取到它‘所有’的 closure 参数，或者是没有 closure 参数，
			那么所产生的函数对象会被给予一个特殊的类型:std::reference_closure<R(P)>，
			其中 R(P) 是包含回返类型的函数签名。
			比起由 std::function 获取而来，这会是lambda函数更有效率的代表：
			std::reference_closure<void()> myLambdaFunc = [this]() { this->SomePrivateMemberFunction(); };
			myLambdaFunc();

		*/
		auto myOnheapLambdaFunc = new auto( [=]()->int{ return 2; });
		cout << (*myOnheapLambdaFunc)() << endl;  // 在堆上分配的lambda表达式
		delete myOnheapLambdaFunc;
	}

    return 0;
}

