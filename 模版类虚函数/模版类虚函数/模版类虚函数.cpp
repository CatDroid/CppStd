// 模版类虚函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;

template<class Item, class Self>
class IIterator { // 模版类中带有虚函数
public:
	virtual ~IIterator() {};
	virtual Self operator ++ () = 0;
	virtual const Self operator ++ (int) = 0;
	virtual bool operator == (const Self& other) = 0; 
	virtual Item& operator * () = 0;
};

class MyClass : public IIterator<int, MyClass>
{
private:
	int mNum;
public:
	explicit MyClass(int num) :mNum(num) {
		cout << "MyClass(TYPE num)"<< endl;  
	}

	virtual ~MyClass() { 
		cout << " ~MyClass()" << endl; 
	}

	// 第二个参数除了用于区分是后置运算外，并没有其他意义，故起参数可有可无.
	// 为了区分前后，用 operator++()表示前自增，用 operator++(int)后自增

	// ++i
	// 因为按照前自增的标准定义,应该支持"++++a"的语法,而且两次前自增都应该是对a对象的自身操作,如果返回A类型,那第二次前自增调用的是临时对象的前自增操作
	virtual MyClass operator ++ () override  {
		mNum++;
		return MyClass(mNum);
	}
	
	// i++ 
	// 后自增应该返回"const Complex".这可以防止形如"a++++"的用法
	virtual const MyClass operator ++ (int ) override {
		int old = mNum; 
		mNum++;
		return MyClass(old);
	}

 
	virtual bool operator == (const MyClass & other) override {
		if (mNum == other.mNum) return true;
		return false;
	}

	virtual int& operator* () {
		return mNum;
	}

};



int main()
{

	MyClass a(1);
	MyClass b(1);

	if (a == b) {
		cout << "equal" << endl; 
	}
	else {
		cout << "not equal" << endl; 
	}

	*b = 3;
	b++;		// 4
	++++b;		// 5 

	cout << *b << endl; 

    return 0;
}

