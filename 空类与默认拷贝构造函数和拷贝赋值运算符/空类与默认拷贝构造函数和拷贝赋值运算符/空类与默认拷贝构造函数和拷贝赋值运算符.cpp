// 空类与默认拷贝构造函数和拷贝赋值运算符.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>

using namespace std;

class Base {
public:
	Base() {
		cout << "Base " << this << endl;
	}
	virtual ~Base() {
		cout << "~Base " << this << endl;
	}
	virtual void run() {
		cout << "Base run " << this << endl;
	}

};

class Derive : public Base {
public:
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
public:
	Derive1(){
		cout << "Derive1 " << this << endl;
	}
	virtual ~Derive1() {
		cout << "~Derive1 " << this << endl;
	}

	virtual void run() {
		cout << "Derive1 run " << this << endl;
	}
};

class Empty {
public  :
	const int CONSTANT; // 有const成员或者引用成员 必须自定义构造函数 没有默认无参数/拷贝构造函数
 
};





int main()
{


	// Base* b = new Derive1();
	// delete b;

	// Empty* empty = new Empty();
	// delete empty;

	return 0;


}


/*


空类：
	1. 一个空的class在C++编译器处理过后就不再为空, 编译器会自动为你生成一个默认构造函数、一个拷贝默认构造函数、一个默认拷贝赋值运算符和一个默认析构函数
	2. 只有当你需要用到这些函数的时候，编译器才会去定义它们
	3. 所有这些函数都是inline和public的

参考：
class Empty
{
	public:
		Empty();				// 缺省构造函数
		Empty( const Empty& );  // 拷贝构造函数
		~Empty();				// 析构函数
		Empty& operator=( const Empty& );	// 赋值运算符
		Empty* operator&();					// 取址运算符
		const Empty* operator&() const;		// 取址运算符 const
};


默认构造函数和默认拷贝赋值运算符:

1. 拷贝默认构造函数和默认拷贝赋值运算符 只是单纯将来源对象的每一个非静态成员拷贝到对象目标中（bitwise copy）

2. ‘默认拷贝赋值运算符’只有在生成的“代码合法”并且“有机会证明它有意义存在时”才会生成。
	这就说明，如果你打算在一个“内含引用成员”或者“内含const成员”的类内支持赋值操作，
	就必须定义自己的默认拷贝赋值运算符。
	(因为C++本身不允许'在构造函数初始化列表之后'引用改指不同的对象，也不允许更改const成员)
	(默认的“拷贝构造函数” 也是 如果有const成员和引用成员  编译器都不会自动生成  )

3. 当基类将自己的默认拷贝赋值运算符声明为private时，子类就不会产生自己的的默认拷贝赋值运算符。
	(因为假如产生了这样的默认拷贝赋值运算符，
	它会试着去调用基类的默认拷贝赋值运算符去处理基类的部分，不幸的是，它没有权利)


4. 将成员函数声明为private而且故意不实现它们
	(为了驳回编译器自动提供的技能，可将相应的成员函数声明为private并且不予实现)

	参考写法:
	
	class Uncopybale {
	protected:
		Uncopyable() {}
		~Uncopyable() {}
	private:
		Ucopyable(const Uncopyable&);				// ***
		Uncopyable& operator=(const Uncopyable&);	// ***
	};
	
	为了阻止对象被拷贝，我们唯一需要做的就是继承Uncopyable
	Boost提供的noncopyable类也有类似的功能

*/

