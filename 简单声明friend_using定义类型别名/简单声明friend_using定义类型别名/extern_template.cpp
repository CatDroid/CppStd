
#include "stdafx.h"

#include "extern_template.h"

#include <iostream>
using namespace std;


// 全特化 类模板
template<>
struct which_kind<int> {
	static void type() {
		cout << "int" << endl;
	}
};

template<>
struct which_kind<double> {
	static void type() {
		cout << "double" << endl;
	}
};

template<>
struct which_kind<float> {
	static void type() {
		cout << "float" << endl;
	}
};


// 函数模板 定义 
template<typename T>
void extern_template_func(T a) {
	cout << a << endl;
	which_kind<T>::type();
}



// 显示特例化/强制特例化 
template void extern_template_func<int>(int);
template void extern_template_func<double>(double);
template void extern_template_func<float>(float);

void call(int arg) {
	extern_template_func<int>(arg);
}