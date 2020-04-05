
#include "stdafx.h"

#include <string>
#include <iostream>

class Test
{
public:
	Test()
	{
		std::cout << "[" << this << "]" << "Test()" << std::endl;
	}

	~Test()
	{
		std::cout << "[" << this << "]" << "~Test()" << std::endl;
	}

	void func1()
	{
		std::cout << "[" << this << "]" << "func1()" << std::endl;
	}

	int func2(float arg)
	{
		int ret = arg + 3;
		std::cout << "[" << this << "]" << "func2( " << arg << ")" << "=>"  << ret << std::endl;
		return ret;
	}

	bool func3(std::string name)
	{
		std::cout << "[" << this << "]" << "func3( " << name << ")" << "=> false" << std::endl;
		return false ;
	}
};


void (Test::*pFun1)() = &Test::func1;
int  (Test::*pFun2)(float) = &Test::func2;
bool (Test::*pFun3)(std::string) = &Test::func3;


static void Call_Test_Func1(Test& obj)
{
	(obj.*pFun1)();
}

static int Call_Test_Func2(Test& obj, float arg1)
{
	return (obj.*pFun2)(arg1);
}

static bool Call_Test_Func3(Test& obj, std::string arg1)
{
	return (obj.*pFun3)(arg1);
}

void test2()
{
	Test* instance = new Test();
	

	Call_Test_Func1(*instance);

	Call_Test_Func2(*instance, 1.2);

	Call_Test_Func3(*instance, "Hello world");

}

