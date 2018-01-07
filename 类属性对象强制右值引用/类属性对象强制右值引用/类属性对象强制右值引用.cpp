// 类属性对象强制右值引用.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;



class HugeMem {

#define TLINE(func)  cout << func << "[" << this << "]:" << ",data:" << mData << ",other:" << mOther \
					<< ",copy?" << mIsCopy << ",move?" << mIsMove  <<  endl;

public:
	HugeMem(int size) :mSize(size>0?size:1), mData(new int[mSize]) {
		TLINE("HugeMem(int size)                 ") ;
	}
	HugeMem(const HugeMem& other):mSize(other.mSize), mData(new int[other.mSize]),mOther((void*)&other),mIsCopy(true){
		TLINE("HugeMem(const HugeMem& other      ");
		// Maybe it should be copy other.c to this.mData;
	}
	HugeMem(HugeMem&& other):mSize(other.mSize), mData(other.mData),mOther((void*)&other),mIsMove(true) {
		TLINE("HugeMem(HugeMem&& other)           ");
		other.mData = nullptr;
	}
	
	HugeMem& operator=( HugeMem&& other ){ 
		if (mData != nullptr) delete[] mData;
		mData = other.mData;
		mSize = other.mSize;
		mOther = &other;
		mIsCopy = false;
		mIsMove = true;
		other.mData = nullptr;
		TLINE("HugeMem& operator=( HugeMem&& other )");
		return *this;
	}
	
	~HugeMem() {
		TLINE("~HugeMem()                          ");
		if(mData !=nullptr ) delete[] mData;
	}
	void dump() {
		TLINE(__func__);
	}
protected:
	int mSize{ 0 };
	int * mData { nullptr };	// 就地初始化

	void* mOther{ nullptr };
	bool mIsCopy{ false }; 
	bool mIsMove{ false };
};

class Movable {
public:

#define MLINE(func)  cout << func << "[" << this << "]" <<  endl;

	Movable(int size) :i(new int(-1)), h(size) {
		MLINE("Movable(int size)           ");
	}

	Movable(const Movable& other) :i(other.i), h(other.h) {
		MLINE("Movable(const Movable& other)");
	}

	Movable(Movable&& other) noexcept(true)  :i(other.i),h(std::move(other.h)) //** 如果类属性是对象 遇到本类的移动构造或者移动拷贝 一定要用std::move试到类属性对象也应用移动语义
	{ // 如果移动构造产生 excpetion的话 直接terminal程序  
	  // 或者使用std::move_if_noexcept 如果类的移动构造函数有noexcpt关键字修饰,返回右值应用 
		other.i = nullptr;
		MLINE("Movable(Movable&& other)     ");
	}

	Movable& operator = ( Movable&& other) {
		if (i != nullptr) { delete i; }
		i = other.i; other.i = nullptr;
		h = std::move(other.h); // ** 右值引用变量的实例属性 要用std::move强制转成右值
		MLINE("Movable& operator = ( Movable&& other)");
		return *this;
	}
	
	~Movable(){
		MLINE("~Movable()                   ");
		if (i != nullptr) { delete i;  }
	}

	void dump() {
		cout << __func__ << "[" << this << "]:" << i << "," << *i << endl;
		h.dump();
	}

private:
	int* i = { nullptr };
	HugeMem h;
};

Movable GetTemp() {
	Movable temp = Movable(12);
	temp.dump();
	return temp;
}

// 利用移动语义 高性能调用两个实例的值
template <typename T>
void swap(T& a, T&b) {
	T tmp(std::move(a));
	a = std::move(b);
	b = std::move(tmp);
}

int main()
{
	{
		Movable temp(GetTemp());
		temp.dump();
	}

	{ cout << endl << endl << "高性能交换两个变量(类)的值" << endl << endl ;
		Movable a1(10);
		Movable a2(20);
		a1.dump();
		a2.dump();
		cout << "---" << endl;
		::swap(a1, a2);
		cout << "---" << endl;
		a1.dump();
		a2.dump();
	}
 

	/*

vs2015:

HugeMem[0104FA54]:,data:03503718,other:00000000,copy?0,move?0
Movable[0104FA50]
dump[0104FA50]:03509A48,-1
dump[0104FA54]:,data:03503718,other:00000000,copy?0,move?0
HugeMem[0104FB68]:,data:03503718,other:0104FA54,copy?0,move?1
Movable[0104FB64]
~Movable[0104FA50]
~HugeMem[0104FA54]:,data:00000000,other:00000000,copy?0,move?0
dump[0104FB64]:03509A48,-1
dump[0104FB68]:,data:03503718,other:0104FA54,copy?0,move?1
~Movable[0104FB64]
~HugeMem[0104FB68]:,data:03503718,other:0104FA54,copy?0,move?1
	

clang++
clang++ 类属性对象强制右值引用.cpp -o main.exe --std=c++11

HugeMem[0xffffcbe8]:,data:0x600000480,other:0,copy?0,move?0
Movable[0xffffcbe0]
dump[0xffffcbe0]:0x600000460,-1
dump[0xffffcbe8]:,data:0x600000480,other:0,copy?0,move?0
dump[0xffffcbe0]:0x600000460,-1
dump[0xffffcbe8]:,data:0x600000480,other:0,copy?0,move?0
~Movable[0xffffcbe0]
~HugeMem[0xffffcbe8]:,data:0x600000480,other:0,copy?0,move?0


clang++ 类属性对象强制右值引用.cpp -o main.exe --std=c++11 -fno-elide-constructors

HugeMem[0xffffcb10]:,data:0x600000480,other:0,copy?0,move?0
Movable[0xffffcb08]

HugeMem[0xffffcb38]:,data:0x600000480,other:0xffffcb10,copy?0,move?1
Movable[0xffffcb30]
~Movable[0xffffcb08]
~HugeMem[0xffffcb10]:,data:0,other:0,copy?0,move?0
dump[0xffffcb30]:0x600000460,-1
dump[0xffffcb38]:,data:0x600000480,other:0xffffcb10,copy?0,move?1


HugeMem[0xffffcbc0]:,data:0x600000480,other:0xffffcb38,copy?0,move?1
Movable[0xffffcbb8]
~Movable[0xffffcb30]
~HugeMem[0xffffcb38]:,data:0,other:0xffffcb10,copy?0,move?1


HugeMem[0xffffcbe8]:,data:0x600000480,other:0xffffcbc0,copy?0,move?1
Movable[0xffffcbe0]
~Movable[0xffffcbb8]
~HugeMem[0xffffcbc0]:,data:0,other:0xffffcb38,copy?0,move?1
dump[0xffffcbe0]:0x600000460,-1
dump[0xffffcbe8]:,data:0x600000480,other:0xffffcbc0,copy?0,move?1
~Movable[0xffffcbe0]
~HugeMem[0xffffcbe8]:,data:0x600000480,other:0xffffcbc0,copy?0,move?1



	*/
    return 0;
}

