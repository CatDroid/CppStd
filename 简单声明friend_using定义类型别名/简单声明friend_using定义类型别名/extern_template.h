#pragma once


// 函数模板 声明 
template<typename T>
void extern_template_func(T a);

// 类模板定义
template<typename T>
struct which_kind {
	static void type(){}
};

