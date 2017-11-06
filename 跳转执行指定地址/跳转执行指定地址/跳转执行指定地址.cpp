// 跳转执行指定地址.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <inttypes.h>

void jump()
{
	printf("jump run \n");
}

void jumpABS()
{
	printf("jumpABS run \n");
}

int main()
{
	void(*pFunc)(void) = jump; 

	(*pFunc)(); 
	pFunc();

	typedef void(*PFUNC)(void);
	
	uint64_t pAddr = (uint64_t)jumpABS;
	printf("跳转指定地址 %llx\n" , pAddr );
	((PFUNC)pAddr)();
	
	printf("下面也是跳转指定地址 但是相关内存内容未知 会崩溃\n");
	void(*pFunc2)(void) = (PFUNC)0x102135c;
	pFunc2();

	



    return 0;
}

