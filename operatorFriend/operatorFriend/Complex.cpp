#include "stdafx.h"
#include "Complex.h"

#include <iostream>

using namespace std;

// 不用Complex::operator+ 不是成员函数
Complex operator+(const Complex &c1, const Complex &c2) 
{
	cout << "call >> operator+ " << endl;
	return Complex(c1.real + c2.real, c1.image + c2.image);
}

Complex Complex::operator+(const Complex & c2)
{
	cout << "call >> Complex::operator+ " << endl;
	return Complex(this->real + c2.real , this->image + c2.image);
}

void Complex::display() {
	cout << "(" << real << "," << image << "i)" << endl;
}
