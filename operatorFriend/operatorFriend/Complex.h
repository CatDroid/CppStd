#pragma once
class Complex
{
public:
	Complex(double r = 0.0, double i = 0.0) {
		real = r;
		image = i;
	}

	// 应该声明是认为::operator+ 全局的  也可以同时定义在这里 作为inline
	friend Complex operator+(const Complex&, const Complex&);

	Complex Complex::operator+(const Complex&);

	void display();
private:
	double real;
	double image;

};

