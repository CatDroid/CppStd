// POD.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>  

using namespace std;

class A { A() {} };
class B { B(B&) {} };
class C { C(C&&) {} };
class D { D operator=(D&) {} };
class E { E operator=(E&&) {} };
class F { ~F() {} };
class G { virtual void foo() = 0; };
class H : G {};
class I {};
class J { int temp = 5; int test{ 5 }; /*直接初始化*/ };

class K 
{
public:
	K() { cout << "K()"<< endl; } 		// 用户提供的无参构造函数  所以不是 trivially 
										// 但是 trivially_copyable 拷贝不可变
	//K(int temp):a(temp) { cout << "K(temp)" << endl; }
public:
	int a;
};

class M
{
public:
	int m1;
};

class N :public M
{
public:
	int n1;
};

/////////////////////////////////

class As
{
private:
	int a;
public:
	int b;
};

class B1s
{
	static int x1;
};

class B2s
{
	int x2;
};

class Bs : B1s, B2s
{
	int x;
};

class C1s {};
class Cs : C1s
{
	C1s c;
};

class Ds { virtual void foo() = 0; };
class Es : Ds {};
class Fs { As x; };

/////////////////////////////////

class MyPod
{
public:
	int x;
	double y;
};

/////////////////////////////////

int main()
{


	// 不平凡 就是 用户提供的   
	std::cout << std::is_trivial<A>::value << std::endl;  // 有不平凡的构造函数  
	std::cout << std::is_trivial<B>::value << std::endl;  // 有不平凡的拷贝构造函数  
	std::cout << std::is_trivial<C>::value << std::endl;  // 有不平凡的拷贝赋值运算符  
	std::cout << std::is_trivial<D>::value << std::endl;  // 有不平凡的拷贝赋值运算符  
	std::cout << std::is_trivial<E>::value << std::endl;  // 有不平凡的移动赋值运算符  
	std::cout << std::is_trivial<F>::value << std::endl;  // 有不平凡的析构函数  
	std::cout << std::is_trivial<G>::value << std::endl;  // 有虚函数  
	std::cout << std::is_trivial<H>::value << std::endl;  // 有虚基类  

	std::cout << std::is_trivial<I>::value << std::endl;  // 平凡的类 


	std::cout << "--------------" << std::endl;

	std::cout << std::is_trivial<J>::value << std::endl;  // 根据Aggregate的C++11定义 非static数据成员 不能 直接初始化	
									
	std::cout << std::is_trivially_copyable<K>::value << endl;
	std::cout << std::is_trivial<K>::value << std::endl; //  不是Aggregate 不能 列表初始化 { }
	K k1[3] = { K() };									  // 超出范围的 会进行 值初始化 或者 无参构造函数 
	//K k2 = { 1 };										  // 有 用户提供无参构造函数  std::is_trivial = 0
														  // 支持定义普通构造函数


	std::cout << "*---------***----------*"<< std::endl;
	std::cout << std::is_trivial<N>::value << std::endl;			// 1
	std::cout << std::is_trivially_copyable<N>::value << std::endl; // 1 
	//N n = { 1  };  // ERROR 

	std::cout << "标准布局" << std::endl;
	std::cout << std::is_standard_layout<As>::value << std::endl;  // 违反定义1。成员a和b具有不同的访问权限  
	std::cout << std::is_standard_layout<Bs>::value << std::endl;  // 违反定义2。继承树有两个(含)以上的类,有非静态成员  
	std::cout << std::is_standard_layout<Cs>::value << std::endl;  // 违反定义3。第一个非静态成员是基类类型  
	std::cout << std::is_standard_layout<Ds>::value << std::endl;  // 违反定义4。有虚函数  
	std::cout << std::is_standard_layout<Es>::value << std::endl;  // 违反定义5。有虚基类  
	std::cout << std::is_standard_layout<Fs>::value << std::endl;  // 违反定义6。非静态成员x不是 standard_layout


	if (std::is_pod<MyPod>::value)
	{
		std::cout << "before" << std::endl;
		MyPod a;
		a.x = 8;
		a.y = 10.5;
		std::cout << a.x << std::endl;
		std::cout << a.y << std::endl;

		size_t size = sizeof(a);
		char *p = new char[size];
		memcpy(p, &a, size);			// 二进制拷贝
		MyPod *pA = (MyPod*)p;

		std::cout << "after" << std::endl; 
		std::cout << pA->x << std::endl;
		std::cout << pA->y << std::endl;

		delete p;
	}

    return 0;
}

