// operatorFriend.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include "Complex.h"

#include <iostream>

using namespace std;

int main() {
	Complex c1(3, 4), c2(5, -10), c3;
	c3 = c1 + c2;
	cout << "c1="; c1.display();
	cout << "c2="; c2.display();
	cout << "c1+c2="; c3.display();
	return 0;
}


