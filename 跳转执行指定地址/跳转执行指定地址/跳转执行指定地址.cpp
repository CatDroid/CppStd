// ��תִ��ָ����ַ.cpp : �������̨Ӧ�ó������ڵ㡣
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
	printf("��תָ����ַ %llx\n" , pAddr );
	((PFUNC)pAddr)();
	
	printf("����Ҳ����תָ����ַ ��������ڴ�����δ֪ �����\n");
	void(*pFunc2)(void) = (PFUNC)0x102135c;
	pFunc2();

	



    return 0;
}

