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
	Info():Base(-1) { // 就地初始化 就相当于 在构造函数初始化列表后 加上数据成员初始化
		cout << "Info() "<< endl;
	}

	Info(int temp) :id(temp),Base(id+1) { // 初始化列表 基类和普通数据成员初始化 书写没有顺序 但是一定先调用基类构造
		cout << "Info(int temp) temp = " << temp << endl;

		//this->Info(); 编译器不允许构造函数中 调用构造函数

		new (this) Info();  // 相对于对数据成员 就地初始化 了
		cout << "Info(int temp) id = " << id << endl; // -1 
		// id = temp;		// 不能在初始化列表位置 否则错误
	}

	Info(const char* temp):Info(temp,-1)/*,id(1)*/{ // 委派构造不能具有其他成员初始列表
		cout << "Info(const char* temp) temp = " << temp << endl;
	}

	Info(string&& temp) :name(std::move(temp)),Base(id+1) {
		cout << "string&& temp " << temp << endl;
	}
	
	void dump() {
		cout << "id = " << id << " name = " << name << endl;
	}

private:
	Info(const char* arg1, int arg2): Base(arg2 + 1), name(arg1), id(arg2) {
		cout << "Info(const char* arg1, int arg2)" << endl;
		initSetup();
	}

	int id{ -1 };			// 即使是就地初始化 但是也是在基类构造之后才初始化 
	string name{ "default" };
	/*
		1.使用就地初始化的方式  简化每个构造函数对数据成员的初始化
		2.使用placement new方法 强制在本对象地址调用构造函数(1.构造函数调用了两次  2.使用初始化列表会错误)
		3.委派构造函数  委派和初始化列表 不能同时 使用! 可以有一个私有的目标构造函数
			委派构造函数 delegatin constructor
			目标构造函数 target constructor ('基准版本')
	*/

	void initSetup() {
		id += 1;
	}

};

int main()
{

	{
		Info test(1);
		test.dump();
	}cout << "----------------------" << endl;

	{
		Info test("test");
		test.dump();
	}


    return 0;
}

