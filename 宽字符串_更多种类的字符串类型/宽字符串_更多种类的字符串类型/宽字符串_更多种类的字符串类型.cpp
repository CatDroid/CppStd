// 宽字符串_更多种类的字符串类型.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"


#include <iostream>
#include <locale>


int main()
{
	{
// _Pragma("once") // 跟sizeof一样 是操作符  不是函数或者预处理指令 
// #pragma once   //  预处理指令
		std::cout << __func__ << std::endl;
		std::cout << __STDC_HOSTED__ << std::endl;
	}

	{// 宽字符(UCS-2 或UTF-16),用wcout输出,并且要设置locale  vs2015在源代码使用GBK和utf-8都编译通过  clang在utf-8才编译通过
		//												// vs2015								// clang++
		std::wcout.imbue(std::locale("chs"));			// 不设置			//	设置			// 设置				不设置
		const wchar_t* hanzi = L"汉字";
		std::cout  << "cout:"  << hanzi << std::endl;	// 00 FB CC 7C		//	00 10 22 AC		//  后面在没输出	01 00 40 30 36
		std::wcout << "wcout:" << hanzi << std::endl;  // 无输出			//	汉字								无输出

	}

	{// 宽字符串的操作函数是把ANSI的str替换为wcs
	 // ANSI     UNICODE
	 // strlen   wcslen  
	 // strcpy   wcscpy  
		const wchar_t* hanzi = L"汉字";
		const wchar_t* other = L"汉东";
		bool equal = wcscmp(hanzi, other); // [wcs|str]cmp 
		std::wcout << "wcscmp ? " << equal << std::endl;
		std::wcout << wcslen(hanzi) << std::endl; // 2 不包含 \0  

		const char* ssss = "123";
		std::wcout << sizeof(ssss) << " " << strlen(ssss) << std::endl;// 4 3 
	}



	std::cout << "---------end of main---------" << std::endl;
    return 0;
}

