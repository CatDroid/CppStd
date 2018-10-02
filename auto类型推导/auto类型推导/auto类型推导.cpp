// auto类型推导.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <list>
#include <vector>

using namespace std;

#define BLOCK cout<<"---------------------------------------"<<endl;

class MyClass
{
private:
	std::vector<float> buf;

public:
	MyClass(int a):mAttrInt(a){
		cout << "MyClass(int a)" << endl;
	}
 
	MyClass(MyClass& other) {
		cout << "MyClass(MyClass& other) " << endl;
		mAttrInt = other.mAttrInt;
	}

	MyClass(MyClass&& other) {
		cout << "MyClass(MyClass&& other) " << endl;
		mAttrInt = other.mAttrInt;
	}

	MyClass(const MyClass& other) {
		cout << "MyClass(const MyClass& other)" << endl;
		mAttrInt = other.mAttrInt;
	}

	MyClass& operator= (MyClass& other) {
		cout << "operator= (MyClass& other)" << endl;
		mAttrInt = other.mAttrInt;
	}
	MyClass& operator= (MyClass&& other) {
		cout << "operator= (MyClass&& other)" << endl;
		mAttrInt = other.mAttrInt;
	}
	MyClass& operator= (const MyClass& other) {
		cout << "operator= (const MyClass& other" << endl;
		mAttrInt = other.mAttrInt;
	}


	virtual ~MyClass() {
		cout << "~MyClass() " << mAttrInt << endl;
	}

	void add() {
		mAttrInt++;
	}

	std::vector<float>& data() {
		std::cout <<"data = " << &buf << std::endl;
		return buf;
	}

private:
	int mAttrInt;
};

// C++11 后置返回值类型 可以根据模板函数的形参类型
template<typename T>
auto cbegin(const T& container) -> decltype(std::begin(container)) {
	// std::begin对于const的容器 返回的是const的迭代器 
	// const int [6]  返回的是 const int*  指针(迭代器)本身是可修改的 指涉的内存地址是不可改的
	return std::begin(container);
}


int main()
{
	{
		list<MyClass> list;
		list.push_back(MyClass(1));
		list.push_back(MyClass(2));
		list.push_back(MyClass(3));
		list.push_back(MyClass(4));
		list.push_back(MyClass(5));
		list.push_back(MyClass(6));

		for (auto temp = list.begin(); temp != list.end(); temp++) {
			auto thiz = (*temp); // (*temp) 是 MyClass&  auto是MyClass 所以会导致拷贝构建函数 
			thiz.add();
		}
	}BLOCK

	{
		MyClass list(666);
	//auto d = list.data()	// 这个推导成 std::vector<float> 
	auto& d = list.data();  // 这个推导成 std::vector<float>& 
	std::cout << "data = " << &d << std::endl;

	}BLOCK

	{
		int data[16];
		const auto& dataConst = data; // auto不能转成const版本 可以自己加上
		// dataConst[12] = 5; // 必须可修改的左值

		std::cout << "itor 1 = " << &data[0] << std::endl;

		auto itor = std::begin(dataConst); // 数组版本 std::begin特例化 直接返回指针
		std::cout << "itor 2 = " << itor << std::endl;

	}

	{
		int data[16];
		std::cout << "cbegin 1 = " << &data[0] << std::endl;
		auto itor = ::cbegin(data); // vs2015 存在std::cbegin(C++14) 所以自定义的要用::cbegib
		// itor是 const int*
		std::cout << "cbegin 2 = " << itor  << std::endl;
	}

    return 0;
}

