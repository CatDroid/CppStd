// 容器.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <set>
#include <iostream>

int main()
{
//  std::set std::map 都是红黑树
//  stp::map 是key-value对
//	std::set 是元素集合				set没有operator[]	set使用场景 对重复元素过滤和排序  std::set<int>::iterator *itor返回的是常量引用
	
	int array[5] = { 12, 34, 10, 98, 3 };
	const size_t array_size = sizeof(array) / sizeof(array[0]);
	std::set<int> set;
	for (size_t i = 0; i<array_size; ++i){
		set.insert(array[i]);				//	把数据插入集合，数据自动排序
	}
 

	
	std::set<int>::iterator b = set.begin();
	for (; b != set.end(); ++b){			//	此时已经排序了，下面依次输出
		std::cout << *b << '\n';
		//if( *b == 10 )  *b = 90 ;  
	}

    return 0;
}

