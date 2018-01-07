// 右值引用的左值给左值引用.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <inttypes.h>

using namespace std;

class DefClass {
public:
	// vptr  
	uint64_t self;			// vptr +8
	uint64_t temp[100];		// vptr +8 +8   
	uint64_t other;			// vptr +8 +8 +8*100
	uint64_t isMove;		// vptr +8 +8 +8*100 +8 
							// sizeof(DefClass)  = 832 

	DefClass() :self((uint64_t)this), other(0), isMove(0) {
		cout << "DefClass() " << this << endl;
	}
	virtual ~DefClass() {
		cout << "~DefClass() " << this << endl;
	}
	DefClass(DefClass&& other) :self((uint64_t)this), other((uint64_t)&other), isMove(1) {
		cout << "DefClass(DefClass&& other)       this:" << this << " other: " << &other << endl;
	}

	DefClass(const DefClass& other) :self((uint64_t)this), other((uint64_t)&other), isMove(0) {
		cout << "DefClass(const DefClass& other)  this:" << this << " other: " << &other << endl;
	}

	DefClass& operator=(const DefClass& other) {
		cout << "operator=(const DefClass& other)  this:" << this << " other: " << &other << endl;
		return *this;
	}

	DefClass& operator=(DefClass&& other) {
		cout << "operator=(DefClass&& other)       this:" << this << " other: " << &other << endl;
		return *this;
	}

	void dump() const {
		printf("this %0" PRIx64 " other %0" PRIx64 " %s\n", self, other, (isMove ? " Move " : "Non-Move"));
	}
};



DefClass& inRightRef_outLeftRef(DefClass && right ) {
	right.temp[0] = 1111;	// 修改右值引用
	return right;			// 具名的右值引用是 左值 可以给到 左值引用 !!!! 
	
}

DefClass& inLeftRef_outLeftRef(DefClass& left) {
	left.temp[0] = 2222;		// 形参是左值引用 实参是具名的左值引用变量
	return left;				//	类似'自增运算符'
}								//	返回函数参数中的(左值)引用
 

DefClass inLeftRef_outValue (DefClass & left) {
	return left;				//	拷贝构造函数  @VS2015/Clang++  临时对象 右值
}

//////////////////////////////////////////////////////////////

void callme(DefClass&& right) {
	right.dump();
	cout << "callme(DefClass&& !" << endl;
}

void callme(DefClass& left) {
	left.dump();
	cout << "callme(DefClass& !" << endl;
}

/////////////////////////////////////////////////////////////

DefClass get_a_DefClass() {
	DefClass a;
	a.temp[0] = 1212 ;
	return  a;
}

DefClass& foo(DefClass&& x) {
	cout << "foo" << endl;
	x.temp[0] = x.temp[0] + 1 ;
	return x;
}

/*
VS2015 (x86) 连续定义的int变量，地址相差12个字节。这是为什么？

按照我们的理解，int占用4个字节，应该相差4个字节。

在VS2015在Debug模式下，int变量占用12个字节。可以这样认为，Debug模式下，在int变量的前后各增加了4个字节，用于存储调试信息，
那么aa的后面4个字节，bb的前面4个字节，再加上aa本身的4个字节，刚好相差12个字节。

当我们把模式设为Release，就会发现栈上连续定义的int变量，地址相差4个字节。

注意：栈上地址从高向低增长。 
*/
int main()
{
	{	// 1. sizeof 引用类型 等于 类型 本来的大小 
																		//	clang++  /	vs2015+Release Mode+x86
		cout << "sizeof(char &)=" << sizeof(char &) << endl;			//	sizeof(char &)=1
		cout << "sizeof(int  &)=" << sizeof(int  &) << endl;			//	sizeof(int  &) = 4
		cout << "sizeof(long long &)=" << sizeof(long long &) << endl;	//	sizeof(long long &) = 8
		cout << "sizeof(long long)=" << sizeof(long long) << endl;
	}

	{	// 2. 左值引用和右值引用本来也占内存，所以具名的引用类型变量可以取地址,是左值
		long long size = 1;			cout << &size << endl;		// 0xffffcbf0
		long long& size_ref = size; cout << &size_ref << endl;	// 0xffffcbf0
		long long size_2 = 2;		cout << &size_2 << endl;	// 0xffffcbe0

	}

	{
		DefClass&& r1 = DefClass();
		//DefClass&& r2 = r1;	// 无法将右值引用绑定到左值
		DefClass& lr = r1;		// 具名的右值引用也是左值 所有变量都是左值 可以给到左值引用,如果变量本来是引用类型的话,左值引用就引用了对应的对象

		DefClass l;
		DefClass& l1 = l;
		DefClass& l2 = l1;  // OK  一切变量都是有名字的,所以都是左值
	}


	{	// 右值引用 是一种类型  如果变量是左值(有名字 可去地址) 那么可以给到左值引用变量初始化
		// 如果函数形参是右值引用类型，那么实参要是‘右值’来初始化参数

		cout << "-----*------" << endl;
		DefClass&& right = DefClass();
		DefClass& left = inRightRef_outLeftRef(std::move(right));
		left.dump();
		cout << left.temp[0] << endl;
	}cout << "-----*-----" << endl;

	{   // 函数返回左值引用 并给到左值引用变量 
		// 返回(左值)引用: 1.实参中的引用 2.对象本身 3.对象内部属性 
		//		不能返回:  1. 局部变量 
		cout << "-----**------" << endl;
		DefClass&& right = DefClass();
		DefClass& left = inLeftRef_outLeftRef(right);
		left.dump();
		cout << left.temp[0] << endl;
	}cout << "-----**-----" << endl;


	
	/*{ // 函数返回左值引用  不能给到 右值引用变量
		DefClass&& returnRight = inRightRef_outLeftRef(  DefClass() );
		// ERROR 类型DefClass的右值引用 不能绑定到 类型DefClass的左值
	} */


	{
		cout << "-----***-----" << endl;
		callme(inRightRef_outLeftRef(DefClass())); // 返回的左值引用，没有区分左值还是右值，调用 左值引用参数 函数
	}cout << "-----***-----" << endl;			   // 返回的右值引用，是将亡值，右值引用的右值 

	{
		cout << "-----*** std::move 给到右值引用变量 -----" << endl;
		DefClass c;
		DefClass&& lvalue_of_right_ref = std::move(c);
		callme(lvalue_of_right_ref);// 这个调用的是左值引用的版本  右值引用给到一个右值引用变量就是左值
		callme(std::move(c));
	}cout << "-----***-----" << endl;

	{
		cout << "-----****------" << endl;
		DefClass& def = foo(get_a_DefClass());
		def.dump();
		cout << def.temp[0] << endl;
	}cout << "-----****-----" << endl;

	{
		DefClass c;
		DefClass& c1 = c;
		//DefClass&& c2 = c1;
		DefClass&& c2 = std::move(c1); // std::move是函数 返回 右值引用的右值(将亡值) (右值引用可绑定)
	}

	/*
	
	总结：
		
		右值引用	可绑定的: 
							字面值   
							临时对象    
							将亡值(右值引用的右值)  
					不包含:
							右值引用的左值(具名的右值引用)
							左值引用(特别是,函数返回的),除非使用std::move
	
	*/

	cout << "------$$$$$------" << endl;
    return 0;
}

