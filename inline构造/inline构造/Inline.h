#pragma once

#include <iostream>

class Inline
{
public:
	//inline Inline();
	Inline();
	~Inline();
	inline void call() { // 多个编译单元包含这个头文件 一旦出现不能inline的话 就会在链接时候重复定义
		for (int i = 0; i<10; i++){
			std::cout <<" this "<< std::endl;
		}
	}
};

