// 就地初始化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

class Mem {

public:
 
	Mem(int a, int b) :ma(a), mb(b) {
		std::cout << "[" << this << "] Mem(int a, int b) = " << ma << "; mb = " << mb << std::endl;
	}

	// clang++ 就地初始化.cpp  -o main --std=c++98  编译错误
	// clang++ 就地初始化.cpp  -o main --std=c++11  编译通过  noexcept C++ 新增 
	virtual ~Mem() noexcept(true) {
		std::cout << "[" << this << "] ~Mem " << std::endl;
	}

	void dump() {
		std::cout << "[" << this << "] dump  ma = " << ma << "; mb = " << mb << std::endl;
	}

private:
	int ma;
	int mb;
};

class Group {
public:
	Group() {
		cout << "[" << this << "] Group() " << endl;
	}

	Group(int a):m(a,13) { 
		// 这种情况 只会调用初始化列表的构造,不会调用 就地初始化
		// 就地初始化 对于 多构造函数 多初始化成员 的情景 有好处
		// C++98 只能调用公共初始化函数 来 实现 共同部分的成员初始化 C++11改进效率和复杂程度
		cout << "[" << this << "] Group(int a) a = " << a << endl;
	}

	~Group( ){
		cout << "[" << this << "] ~Group( ) "<< endl;
	}

	void dump() {
		m.dump();
	}
private:
	//Mem m(1, 2);
	//string s("12345");  // 非静态成员 就地初始化 只能使用 = 或者 集合初始化 不能使用()
	Mem m = { 1,2 };
	//string s{ "123344" };

	// static int STATIC_NUM = 2; // C++11和98对非常量静态成员变量 都必须在头文件声明 在源文件定义/初始化 保证变量定义最后只在一个目标文件出现
	static int STATIC_NUM;
};

int Group::STATIC_NUM = 2;

 

class MemE {
public:
	// noexcept 既是 描述符 也是 操作符 (根据表达式来 推导 返回是否会抛出异常 )
	//~MemE() noexcept(true) {  // 一旦异常直接std::terminal abort程序 防止异常扩散
	~MemE() noexcept(false) { // C++11 
	//~MemE() throw(int) { // C++98
		throw 666; // int 
	}
};

int main()
{
	{ // 使用 try 和 catch 捕捉异常
		try {
			MemE e;
		}
		catch (int ex) {
			cout << "Exception !  ex = " << ex << endl;
		}
		catch (...) {
			cout << "what Exception ? " << endl;
		}
	}cout << "------------------------------" << endl;


	{
		Group g1;
		g1.dump();
	}cout << "------------------------------" << endl;


	{
		Group g(999);
		g.dump();
	}cout << "------------------------------" << endl;



    return 0;
}

