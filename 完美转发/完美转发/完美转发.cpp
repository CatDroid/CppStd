// 完美转发.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;

void RunCode(int&& m) {
	cout << "void RunCode(int&& m)" << endl;
}
void RunCode(const int&& m) {
	cout << "void RunCode(const int&& m)" << endl;
}


void RunCode(int& m) {
	cout << "void RunCode(int&m)" << endl;
}
void RunCode(const int& m) {
	cout << "void RunCode(const int& m)" << endl;
}

// 函数参数传递:
// 1.为了节省空间 使用引用
// 2.为了兼容目标函数 使用引用折叠(只要有左值引用 折叠为左值引用)

// 完美转发:
// 依赖: 1.引用折叠  2.static_cast<T&&>右值引用的左值强制成右值引用
// 主要用于 模板函数 比如make_pair等   使转发函数的版本减少(const 非const 左值 右值 都不用了)
template <class T>
void PerfectForward(T&& who) { // 转发函数
	 //RunCode(static_cast<T&&>(who));// 目标函数
	RunCode(std::forward<T>(who));  
}

// 包装函数 ??? 作用 ??? 
template <typename T, typename U>
void PerfectForward_Calc_Warp(T &&t, U& func) {
	//if (t < 1.0) t = 1.0; // ?? 
	func(static_cast<T&&>(t));
}

void RunAdd(double &&m) {
	cout <<"RunAdd" << endl;
}

void RunDec(double &&m) {
	cout << "RunDec" << endl;
}

void RunMul(double &&m) {
	cout << "RunMul" << endl;
}

int main()
{
	int i = 3;
	PerfectForward(i); // void RunCode(int&m)
	PerfectForward(std::move(i)); // void RunCode(int&& m)
 
	PerfectForward_Calc_Warp(1.1 , RunAdd);
	PerfectForward_Calc_Warp(3,    RunDec);
	PerfectForward_Calc_Warp(4.5,  RunMul);
    return 0;
}

