// 左值和右值.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

#define LINE  drawLine();
void drawLine() {
	cout << "----------------------------------------" << endl;
}

class Base {
public:
	int buf[100];
	Base() {
		cout << "Base()" << endl;
		memset(buf, 0xA5, 100);
	}

	~Base() {
		cout << "~Base()" << endl;
	}

	Base(const Base& other) { // 注意 如果自己实现了拷贝构造 buf的内容就要自己初始化
		cout << "const A& other" << endl;
		//other.buf[1] = 0xBB;
	}

	Base(Base&& other) {
		cout << "Base(Base && other) " << endl;
		other.buf[2] = 0xBB;  // 与const引用不一样 右值引用可以修改对象
	}

	Base& operator = (const Base& other) {
		cout << "opertor = (const A& other) " << endl;
		return *this;
	}
};


class People {
public:
	People(string name)		// 按值传入字符串，可接收左值、右值。接收左值时为复制，接收右值时为移动
		: name_(move(name)) // 显式移动构造，将传入的字符串移入成员变量
	{
		cout << "People(string name)" << endl;
	}
 
	string name_;
};



// std::move(foo)					std::move 返回 对象foo 的右值引用(rvalue reference) ,实现就是一个static_cast 
// std::vector<std::unique_ptr<T>>	在容器 std::vector 中放入了不可复制只能移动的类的实例(std::unique_ptr 的拷贝构造函数是被删除的)

int main()
{
	Base tempA;
	Base tempB(std::move(tempA)); // 如果没有constructor(Base&& other) 那么就用 constructor(const Base& other) 但是不能改other
								  // 如果都没有，就用默认的拷贝构造函数  注意buf的数据等于tempA的
 
	cout << hex << tempB.buf[2]  << endl;	// 0xccccccc
	cout << hex << tempA.buf[2] << endl;	// 0xbb


	LINE
	Base&& tempC = std::move(tempA);		// 0xbb
	cout << hex << tempC.buf[2] << endl;
	LINE

	Base&& tempD = static_cast<Base&&>(tempA);// 0xbb 
	cout << hex << tempD.buf[2] << endl;
	LINE

	Base& tempE = std::move(tempA);			// OK 左值引用 绑定 右值引用 ??
	LINE

	int a = 2;
	cout << &a << endl;
	int&& b = std::move(a);
	const int& c = std::move(a);//	返回对象a的右值引用 
	//int&& d = a;				//	右值引用 不能 绑定到左值
	int&& d = a + 1;			//  右值引用 绑定到右值(临时变量)
	//int& d = a++;				//	左值引用 不能 绑定到右值
	const int& dd = a++;		//  常量左值引用 绑定 右值
	//int& d = a;				//   
	//const int& d = a;			//  
	cout << &a << endl;
	a = 3;
	cout << a << endl;
	
	LINE
	int& a_ref = a;
	int& a_ref_ref = a_ref;		//	左值引用 本身 可以作为'左值' 或者 '右值'
	a_ref_ref = 4;
	int a_temp = ++a_ref;		//	前置自增运算符返回左值引用，在这里赋值给a_temp，此时'左值引用作为右值'
	cout << a << endl;		 
	
	LINE
								//	右值引用本身也既可以作为左值也可以作为右值


	People a_people("Alice");			//	传入右值 移动构造 
	string b_people_name = "Bob";
	People b_people(b_people_name);		//	传入左值 拷贝构造name


	// 在C中 右值 是不能在赋值运算符左边的， 左值可以在任何一边
	// 在C++中 一个表达式是左值还是右值，取决于我们使用的是'它的值'还是'它在内存中的位置'
	// 需要右值的地方可以用左值来替代，但需要左值的地方，‘一定不能’用右值来替代
	//  C++ 中的实例本身可以是一个表达式 ???

	//	左值存放在实例中，有持久的状态 
	//	右值要么是'字面常量'，要么是在表达式求值过程中创建的'临时实例'，没有持久的状态
	
	// 两种对实例的引用：左值引用和右值引用
	// 将一个实例的内存空间绑定到另一个变量上，那么这个变量就是左值引用
	// 在建立引用的时候，我们是「将内存空间绑定」
	// 使用的是一个实例在内存中的位置

 

	// 左值引用 绑定 左值
	// 常量左值引用 可绑定到 右值 (常量左值引用保证了我们不能通过引用改变对应内存空间的值)
	// 右值引用也是引用，但是它只能且必须绑定在右值上


	// 右值引用的对象，是临时的，即将被销毁；并且右值引用的对象，不会在其它地方使用
	// 接受和使用右值引用的代码，可以自由地接管所引用的实例的资源，而无需担心对其他代码逻辑造成数据破坏 ???



	// 右值引用的意义通常解释为两大作用：移动语义和完美转发
	// 移动语义:对象的资源所有权转移
	// 如何标识对象的资源是可以被移动的呢?  右值所包含的对象都是可以安全的被移动的

	// 不严格的来说，左值对应变量的存储位置，而右值对应变量的值本身

	// C++中右值可以被'赋值给左值'或者'绑定到引用'
	// 类的右值是一个临时对象，如果'没有被绑定到引用'，在表达式结束时就会被废弃
	// 于是我们可以在右值被废弃之前，移走它的资源进行废物利用，从而避免无意义的复制。被移走资源的右值在废弃时已经成为空壳，析构的开销也会降低

	//	对于左值，如果我们明确放弃对其资源的所有权，则可以通过std::move()来将其转为右值引用

	//	std::move()实际上是static_cast<T&&>()的简单封装。

	//  
	//	构造对象时, 左值引用和右值引用可以被分别重载，这样确保左值和右值分别调用到拷贝和移动的两种语义实现

    return 0;
}

