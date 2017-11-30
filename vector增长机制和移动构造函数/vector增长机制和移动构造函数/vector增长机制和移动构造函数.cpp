// vector增长机制和移动构造函数.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;



class VecBase {
private:
	int counter;
public:

	explicit VecBase(int temp) :counter(temp) {
		cout << "VecBase(int temp) = " << counter << " " << this << endl;
	}

	~VecBase() {
		cout << "~VecBase() " << this << endl;
	}

	VecBase(const VecBase& other) {
		cout << "VecBase(const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
	}

	VecBase(VecBase&& other) {
		cout << "VecBase(VecBase && other) " << this << " other " << &other << endl;
		counter = other.counter;
		other.counter = -1;
	}

	VecBase& operator = (const VecBase& other) {	// 拷贝赋值函数
		cout << "opertor= (const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
		return *this;
	}

	VecBase& operator = (VecBase&& other) {			// 移动赋值函数
		cout << "opertor = (  VecBase&& other) " << this << endl;
		counter = other.counter;
		other.counter = -1;
		return *this;
	}

};


int main()
{
	{
		cout << endl << endl;
		cout << "std::vector的增长 重新分配内存会调用 移动构造函数!!" << endl;
		// vector<VecBase> list(4) ; // 没有无参数构造函数 不能这样初始化vector长度
		vector<VecBase> list;
		int cap = 0;
		for (int i = 0; i < 16; i++) {
			{
				list.push_back(VecBase(i));
			}
			if (cap != list.capacity()) {
				cap = list.capacity();
				cout << ">>--->>--->>--->>--->>--- after push_back capacity change : " << list.capacity() << endl;
			}

			// capacity永远是大于等于size的，当size和capacity相等时继续添加数据时vector会扩容
			// 增加当前空间的50%(第一次除外)
			// 1  2     3    4    6     9     13    19      28       42     63     94     141 
			//    2/2=1           6/2=3             19/2=9  28/2=14 
			// Windows上的STL源码都是P.J. Plauger写的  增长时会调用 移动构造函数 
			// g++ v6.4.0/clang++ v4.0.1 中 是按 1 2 4  8 16 32 ...   两倍的方式增长  增长时调用的是 拷贝构造函数
		}
		cout << "std::vector --------------------------out of loop-- " << endl;
		cout << endl << endl;
		// 重新分配内存时候 如果类不支持 移动构造函数 就会调用拷贝构造函数
	}

    return 0;
}

