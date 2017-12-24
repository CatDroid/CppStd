// 委派构造函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

/*
	在Java中 早就支持委派构造函数  相对于继承构造函数 委派构造函数的设计和实现都比较早

	C++11特性:
	1. 成员直接初始化(就地初始化)
	2. 委派构造函数
	3. 继承构造函数

*/
#include <iostream>
#include <string>
using namespace std;


class Base {
public:
	Base(int i):pid(i) {
		cout << "Base(int i) i= " << i << endl;
	}

	Base(const Base& other) {
		cout << "Base(const Base& other) other = " << other.pid << endl;
		pid = other.pid;
	}

	Base& operator= (const Base& other) {
		cout << "Base& operator= (const Base& other) " << other.pid << endl;
		pid = other.pid;
	}

	~Base() {
		cout << "~Base() pid = " << pid << endl;
	}
private :
	int pid;
};

class Info:public Base {

public:
	Info():Base(-1) {
		cout << "Info() "<< endl;
		initSetup();
	}

	Info(int temp) :id(temp),Base(temp+1) {
		//this->Info(); 编译器不允许构造函数中 调用构造函数
		cout << "Info(int temp) temp = " << temp << endl;
	}

	Info(const char* temp) :name(temp),Base(id + 1) {
		cout << "Info(const char* temp) temp = " << temp << endl;

		new (this) Info(); 
		// name = temp;		// 不能在初始化列表位置 否则错误
		
	}

	Info(string&& temp) :name(std::move(temp)),Base(id+1) {
		cout << "string&& temp " << temp << endl;
	}
	
	void dump() {
		cout << "id = " << id << " name = " << name << endl;
	}

private:
	int id{ -1 };			// 即使是就地初始化 但是也是在基类构造之后才初始化 
	string name{ "default" };
	/*
		1.使用就地初始化的方式  简化每个构造函数对数据成员的初始化
		2.使用placement new强制在本对象地址调用构造函数(1.构造函数调用了两次  2.使用初始化列表会错误)
	*/

	void initSetup() {
		id += 1;
	}

};

int main()
{
	Info test("test");
	test.dump();

    return 0;
}

