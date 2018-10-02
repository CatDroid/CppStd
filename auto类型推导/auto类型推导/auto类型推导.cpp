// auto�����Ƶ�.cpp : �������̨Ӧ�ó������ڵ㡣
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

// C++11 ���÷���ֵ���� ���Ը���ģ�庯�����β�����
template<typename T>
auto cbegin(const T& container) -> decltype(std::begin(container)) {
	// std::begin����const������ ���ص���const�ĵ����� 
	// const int [6]  ���ص��� const int*  ָ��(������)�����ǿ��޸ĵ� ָ����ڴ��ַ�ǲ��ɸĵ�
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
			auto thiz = (*temp); // (*temp) �� MyClass&  auto��MyClass ���Իᵼ�¿����������� 
			thiz.add();
		}
	}BLOCK

	{
		MyClass list(666);
	//auto d = list.data()	// ����Ƶ��� std::vector<float> 
	auto& d = list.data();  // ����Ƶ��� std::vector<float>& 
	std::cout << "data = " << &d << std::endl;

	}BLOCK

	{
		int data[16];
		const auto& dataConst = data; // auto����ת��const�汾 �����Լ�����
		// dataConst[12] = 5; // ������޸ĵ���ֵ

		std::cout << "itor 1 = " << &data[0] << std::endl;

		auto itor = std::begin(dataConst); // ����汾 std::begin������ ֱ�ӷ���ָ��
		std::cout << "itor 2 = " << itor << std::endl;

	}

	{
		int data[16];
		std::cout << "cbegin 1 = " << &data[0] << std::endl;
		auto itor = ::cbegin(data); // vs2015 ����std::cbegin(C++14) �����Զ����Ҫ��::cbegib
		// itor�� const int*
		std::cout << "cbegin 2 = " << itor  << std::endl;
	}

    return 0;
}

