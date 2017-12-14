// 宽字符串_更多种类的字符串类型.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>


int main()
{
	{
// _Pragma("once") // 跟sizeof一样 是操作符  不是函数或者预处理指令 
// #pragma once   //  预处理指令
		std::cout << __func__ << std::endl;
		std::cout << __STDC_HOSTED__ << std::endl;
	}

	



    return 0;
}

