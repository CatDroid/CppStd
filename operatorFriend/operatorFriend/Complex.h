#pragma once
class Complex
{
public:
	Complex(double r = 0.0, double i = 0.0) {
		real = r;
		image = i;
	}

	// Ӧ����������Ϊ::operator+ ȫ�ֵ�  Ҳ����ͬʱ���������� ��Ϊinline
	friend Complex operator+(const Complex&, const Complex&);

	Complex Complex::operator+(const Complex&);

	void display();
private:
	double real;
	double image;

};

