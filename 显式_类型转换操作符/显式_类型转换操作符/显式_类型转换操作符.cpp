// 显式_类型转换操作符.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
using namespace std;

class ConvertTo{};

template <typename T>
class Ptr {

public:
	explicit Ptr(T*p) :_p(p) { // 显式_构造函数 单参数构造函数 建议用 explicit 避免1.赋值 Ptr t = 1 ; 2. 函数传递 func(1) --> func(Ptr t)
		
	}

	explicit operator bool() const  {	 // 反向 显式_类型转换操作符  C++11 扩展
		if (_p != nullptr)
			return true;
		else
			return false;
	}

	explicit operator ConvertTo() {
		return ConvertTo();
	}
private:
	T* _p = nullptr;
};

void callConvertTo(ConvertTo&& right) {
	return;
}

int main()
{
	{
		int  a;
		//Ptr<int> p = &a;  // 显式 构造函数  避免从基本类型 隐式构造 自定义类型
		Ptr<int> p(&a);

		if (p) { // 隐式 类型转换操作符  自动转换成bool ok   即使显式 也是ok的  可以直接构造bool 但是全局的operator+不支持bool而是bool-->int  
			cout << "valid" << endl;
		}
		else {
			cout << "invalid" << endl;
		}

		// Ptr<double> pd(nullptr); // p && pd 是ok的 因为全局operator &&支持bool 只要Ptr-->bool就可以 全局operator+ 需要 bool-->int 不能直接构造出int
		// cout << p + pd << endl; // 不加explicit 自动转换成bool 语义上没作用 error 
	}


	{
		Ptr<double> pd(nullptr);
		// callConvertTo(pd);   // 错误  1.不存在显式从Ptr到ConvertTo的构造 2.不存在显式从Ptr到ConvertTo的转换 
		callConvertTo(static_cast<ConvertTo>(pd));

		//ConvertTo pt = pd;	// (非直接)类型转换(单参数构造函数)-->拷贝构造初始化
		ConvertTo pt(pd);		// 直接初始化
		ConvertTo pt2 = static_cast<ConvertTo>(pd); // 显式 强制转换

	}
	

    return 0;
}

