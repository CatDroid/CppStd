// lamba表达式_闭包类_闭包对象.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <list>
#include <functional>
#include <iostream>

std::list< std::function<bool(int)> > gLambaContainer;

void addFilter()
{
	static int maxValue = 1;

#define CHOOSE_FILTER 2 

#if CHOOSE_FILTER == 0 
	gLambaContainer.emplace_back([=](int value) { // 不要使用默认的捕捉模式: 实际上这个lambda没有捕获任何对象(非静态的局部对象或者形参)
		return value > maxValue ? true : false;	  //						 这种方式导致所有的lambda闭包对象都一样 
	});
#elif CHOOSE_FILTER	== 1 
	gLambaContainer.emplace_back([maxValue](int value) {	//				 错误:无法在lambda中捕捉带有静态存储持续时间的变量
		return value > maxValue ? true : false;				//				 显式的捕捉方式 可以通过编译器发现这个问题
	});
#else
	int current = maxValue;
	gLambaContainer.emplace_back([current](int value) {		// 每次调用都有不同的闭包的对象
		return value > current ? true : false;
	});
#endif
	maxValue++;

}


int main()
{
	{
		addFilter();
		addFilter();
		addFilter();
		addFilter();
		addFilter();

		for (const auto& temp : gLambaContainer) {
			std::cout << temp(3) << std::endl;
		}// CHOOSE_FILTER == 1 全部都是false  CHOOSE_FILTER ==2 true true false false false

	}

    return 0;
}

