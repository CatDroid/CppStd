// �̳�_����_using���캯��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;


class Partner {
public:
	Partner(int id) :mID(id) {}
private:
	int mID;
	// ���������е���Ԫ����,����������ȫ����������.
	// �����ڶ������Ԫ��������ʱ������и������͵�ʵ��,���߾��дӸ�����(ʵ���Ǳ�����)ת�����β����� 
	friend ostream& operator<< (ostream& os, Partner& self) {
		os << self.mID;
		return os;
	}
};


class Base {
public:
	Base(int temp):mInt(temp){}
	Base(float temp):mFloat(temp){}
	Base(double temp) :mDouble(temp) {}

	void overload_func(int temp) {
		cout << "Base::overload_func(int temp) " << temp << endl;
	}
	void overload_func(Partner& p) {
		cout << "Base::overload_func(Partner temp) temp = " << p << endl;
	}
 
	virtual void virtual_func(Partner& p) { // �麯��ֱ�Ӽ̳��ˣ����麯�����еǼ� ����Ҫʹ��using���� 
		cout << "Base::virtual_func(Partner temp) temp = " << p << endl;
	}

private:
	int mInt{0};
	float mFloat{0};
	double mDouble{0};
};

class Derive : public Base {
public:
	using Base::Base;			// �̳й��캯��
	using Base::overload_func;	// �̳з����Ա���� ���� d.overload_func(p); => error: no viable conversion from 'Partner' to 'double'

	void overload_func(double temp) {
		cout << "Derive::overload_func(double temp) " << temp << endl;
	}


private:
	double mDD{ 0 };			// ʹ�� using�̳й��캯�� ��  ��Ա������ʼ�� ����C++����
};

int main()
{
	Partner p(123);
	// Derive d ;	//	����!	Deriveû�д�Base�ϼ̳е��޲ι��캯��
	Derive d(12); 


	d.overload_func(12);
	d.Base::overload_func(p);	// ���� using Base::overload_func;
	d.overload_func(p);			// ���� using Base::overload_func; �̳з����Ա����
	d.virtual_func(p);			// �麯��ֱ�Ӵӻ����� ����Ҫusing����
    return 0;
}

