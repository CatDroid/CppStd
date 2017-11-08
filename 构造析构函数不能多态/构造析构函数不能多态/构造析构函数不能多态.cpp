// 构造析构函数不能多态.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
 
using namespace std; 

class Base {
public:
	Base() {
		cout << "Base " << this  << endl; 
	}
	virtual ~Base() {
		cout << "~Base " << this << endl;
	}
	virtual void run() {
		cout << "Base run " << this << endl;
	}
	
};

class Derive : public Base {
public :
	Derive() {
		cout << "Derive " << this << endl;
		run(); 
		/*
			这个调用的是本类或者基类 中的run()
			如果本类不override实现run() 那么就会调用基类的
		*/
	}
	virtual ~Derive() {
		cout << "~Derive " << this << endl;
	}
	virtual void run() {
		cout << "Derive run " << this << endl;
	}
};


class Derive1 : public Derive {
private:
	const int CONSTANT_COPY; 
	static const int STATIC_CONSTANT_DEFINED ;
public:
	Derive1(): CONSTANT_COPY(0){
		cout << "Derive1 " << this << endl;
	}
	virtual ~Derive1() {
		cout << "~Derive1 " << this << endl;
	}

	virtual void run() {
		cout << "Derive1 run " << this << endl;
	}
};

const int Derive1::STATIC_CONSTANT_DEFINED = 5;

int main()
{
	Base* b = new Derive1();
	//b->run();
	delete b;

	Derive1 d1;
	Derive1 d2;
	// d2 = d1; Dervie1 包含 const或者引用 成员 那么必须自己实现拷贝赋值运算符

    return 0;
}

/*

析构函数：
1. 默认的析构函数是非虚函数（除非基类有自己声明的虚析构函数）

2. 析构函数中只会调用本类或者基类中的虚函数,不存在多态


*/
