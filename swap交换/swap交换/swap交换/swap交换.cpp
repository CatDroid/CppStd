// swap交换.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

using namespace std;

int main()
{
	{
		int a = 1;
		int b = 2;
		int& a_ref = a;
		int& b_ref = b;
		//unsigned char * pObj1 = reinterpret_cast<unsigned char *>(&obj1);
		//unsigned char * pObj2 = reinterpret_cast<unsigned char *>(&obj2);

		cout << "before swap 交换引用 " << endl;
		cout << "a_ref = " << a_ref << endl; // 1 
		cout << "b_ref = " << b_ref << endl; // 2
		cout << "a = " << a << " b = " << b << " &a = " << &a << " &b = " << &b << " &a_ref " << &a_ref <<  " &b_ref " << &b_ref << endl;
		std::swap(a_ref, b_ref); // a和b 交换了值 !!
		cout << "after swap " << endl;
		cout << "a_ref = " << a_ref << endl; // 2
		cout << "b_ref = " << b_ref << endl; // 1 
		cout << "a = " << a << " b = " << b << " &a = " << &a << " &b = " << &b << " &a_ref " << &a_ref << " &b_ref " << &b_ref << endl;
	}

    return 0;
}

