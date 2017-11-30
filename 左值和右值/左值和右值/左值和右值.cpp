// 左值和右值.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

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
		cout << "const Base& other" << endl;
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


class VecBase {
private:
	int counter;
public:
	 
	explicit VecBase(int temp) :counter(temp){
		cout << "VecBase(int temp) = " << counter << " " << this << endl;
	}

	~VecBase() {
		cout << "~VecBase() " << this << endl;
	}

	VecBase(const VecBase& other) { 
		cout << "VecBase(const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
	}
 
	VecBase(VecBase&& other) {
		cout << "VecBase(VecBase && other) " << this << " other " << &other << endl;
		counter = other.counter;
		other.counter = -1;
	} 

	VecBase& operator = (const VecBase& other) {	// 拷贝赋值函数
		cout << "opertor= (const VecBase& other) " << this <<  " other " <<  &other << endl;
		counter = other.counter;
		return *this;
	}
 
	VecBase& operator = (VecBase&& other) {			// 移动赋值函数
		cout << "opertor = (  VecBase&& other) " << this << endl;
		counter = other.counter;
		other.counter = -1;
		return *this;
	} 

	void dump() {
		cout << "dump = " <<  counter << endl;
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


Base getBase() {
	Base b;
	return b; // 不会创建 临时对象返回 而是返回后的 对象构造使用 移动构造函数
	// return Base() ; // 这样编译不加 -fno-elide-constructors 会被优化 只会有一次构造 不会有任何拷贝/移动构造函数
};

// 如果程序员声明了自定义的拷贝构造函数、拷贝赋值函数、移动赋值函数、析构函数中??还是移动构造函数??的一个或者多个，编译器都不会再为程序员生成默认版本。
// 在C++11中，拷贝构造/赋值和移动构造/赋值函数必须同时提供，或者同时不提供，程序员才能保证类同时具有拷贝和移动语义。只声明其中一种的话，类都仅能实现一种语义。
class DefaultMove {

public:
	~DefaultMove() {
		cout << "~DefaultMove" << endl;
	}

	//DefaultMove() {
	//	cout << "DefaultMove()" << endl;
	//}

	//DefaultMove(const DefaultMove& other) {
	//	cout << "DefaultMove(const DefaultMove& other)" << endl;
	//}
};

/*
clang++ std=c++11 加 -fno-elide-constructors 打印: 
	Base()
	Base(Base && other)
	~Base()
	Base(Base && other)
	~Base()
	~Base()

g++ 和clang++ 不加的话 return b ; 和 return Base();
都只有 
	Base()		不会有拷贝构造或者移动构造
	~Base()

vs2015 默认:
	Base()
	Base(Base && other)
	~Base()
	~Base()
*/

template <typename T>
void callTemplateFun(T arg1, T arg2)
{
	cout << arg1 + arg2 << endl;
}

// 无法将常量左值引用 给到 非常量 左值引用
// 传递值是OK的  ，可以用 常量左值引用(4种引用类型都可以) 来初始化 左值
//void IrunCodeActually(int& t) { cout << "IrunCodeActually = " << t << endl;  }
void IrunCodeActually(int t) { cout << "IrunCodeActually = " << t << endl; }
template <typename T>
void IamForwording(const T & t) { IrunCodeActually(t); }


template <typename T, typename U>
void PerfectForward(T &&t, U& Func) {
	cout << t << "\tforwarded..." << endl;
	Func(forward<T>(t));
}

// 同样的名字会导致 无法推动 模板参数 U 
//void RunCode(double & left) { cout << "RunCode(double & left)" << endl; }
void RunCodeL(double & left) { cout << "RunCodeL(double & left)" << endl; }
void RunCode(double && m) { cout << "RunCode(double && m)"<< endl; }
void RunHome(double && h) { cout << "RunHome(double && h) "<< endl; }
void RunComp(double && c) { cout << "RunComp(double && c)" << endl; }


void RightAndRight(Base && right) {
	cout << "RightAndRight" << endl;
}

void Right(Base&& right) {
	cout << "Right" << endl; // 右值引用 本身是个左值
	//RightAndRight(right);// 无法将 右值引用绑定到左值
	RightAndRight(static_cast<Base&&>(right));
}

// std::move(foo)					std::move 返回 对象foo 的右值引用(rvalue reference) ,实现就是一个static_cast 
// std::vector<std::unique_ptr<T>>	在容器 std::vector 中放入了不可复制只能移动的类的实例(std::unique_ptr 的拷贝构造函数是被删除的)

int main()
{
	{
		Base tempA;
		Base tempB(std::move(tempA)); // 如果没有constructor(Base&& other) 那么就用 constructor(const Base& other) 但是不能改other
									  // 如果都没有，就用默认的拷贝构造函数  注意buf的数据等于tempA的

		cout << hex << tempB.buf[2] << endl;	// 0xccccccc
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

		cout << "返回值 是左值 会优先移动构造  其他情况按常量左值的拷贝构造" << endl;
		Base nBase;			// Base()
		Base n2Base(nBase); // const Base& other
		LINE

	}LINE

	{
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
		//	右值引用本身也既可以作为左值也可以作为右值
	}LINE
						

	{
		People a_people("Alice");			//	传入右值 移动构造 
		string b_people_name = "Bob";
		People b_people(b_people_name);		//	传入左值 拷贝构造name
	} LINE

	{
		Base funB = getBase();				 

	}LINE
	

	{
		DefaultMove dm;
		DefaultMove dm2( std::move(dm)); // 即使有析构函数，还是会有默认的移动构造函数
	}LINE 

	{
		callTemplateFun(1.2,4.5); // 模板函数可以不指定模板参数
	}LINE

	{
		IamForwording(12);
	}LINE

	{
		/* 完美转发: 
			1. 不产生额外的开销 不会有临时对象拷贝  -- 需要传递引用类型
			2. 转发函数 要支持 目标函数可能需要能够既接受左值引用，又接受右值引用 

			“万能”的常量左值引用
			但是，由于目标函数的参数类型是非常量左值引用类型，因此无法接受常量左值引用作为参数，
			这样一来，虽然“转发函数的接受能力很高”，但在“目标函数的接受上却出了问题”
			这需要通过一些常量和非常量的重载来解决目标函数的接受问题，但“函数参数比较多”的情况下，就会造成代码的冗余
			
			另外如果 ‘目标函数的参数是个右值引用’ 的话，同样无法接受任何‘左值’类型作为参数(需要std::move)，间接地，也就导致无法使用移动语义

			“引用折叠”（reference collapsing）的新语言规则，并结合新的模板推导规则来完成完美转发
		*/

		double a = 2.1;
		PerfectForward(a, RunCodeL);

	}LINE

	{
		string str_a = "123456";
		cout << str_a.length() << endl;
		string str_b(std::move(str_a)); // 移动构造函数：字符串移到b上了
		cout << "str_a=" << str_a << ":" << str_a.length() << endl;
		cout << "str_b=" << str_b << ":" << str_b.length() << endl;
	}LINE

	{
		cout << endl << endl;
		cout << "std::vector的增长 重新分配内存会调用 移动构造函数!!" << endl;
		// vector<VecBase> list(4) ; // 没有无参数构造函数 不能这样初始化vector长度
		vector<VecBase> list ;
		int cap = 0;
		for (int i = 0; i < 4; i++) {
			{
				list.push_back(VecBase(i));
			}
			if (cap != list.capacity()) {
				cap = list.capacity();
				cout << ">>--->>--->>--->>--->>--- after push_back capacity change : " << list.capacity() << endl;
			}
			
			// capacity永远是大于等于size的，当size和capacity相等时继续添加数据时vector会扩容
			// 增加当前空间的50%(第一次除外)
			// 1  2     3    4    6     9     13    19      28       42     63     94     141 
			//    2/2=1           6/2=3             19/2=9  28/2=14 
			// Windows上的STL源码都是P.J. Plauger写的  增长时会调用 移动构造函数 
			// g++ v6.4.0/clang++ v4.0.1 中 是按 1 2 4  8 16 32 ...   两倍的方式增长  增长时调用的是 拷贝构造函数
		}
		cout << "std::vector --------------------------out of loop-- " << endl;
		cout << endl << endl;
		// 重新分配内存时候 如果类不支持 移动构造函数 就会调用拷贝构造函数
	}LINE

	{
		unique_ptr<VecBase> old_ptr(new VecBase(555));
		unique_ptr<VecBase> new_ptr;
		new_ptr  = std::move(old_ptr); // unique_ptr的移动赋值运算符
		cout << "old_ptr reset " << endl;
		old_ptr.reset();
		cout << "new_ptr reset " << endl;
		new_ptr.reset();
		cout << "unique_ptr reset end" << endl;
	}LINE 



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

