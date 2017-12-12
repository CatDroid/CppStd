// inline构造.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Inline.h"

int main()
{
	Inline* line = new Inline();
	line->call();
	delete line;
    return 0;
}

