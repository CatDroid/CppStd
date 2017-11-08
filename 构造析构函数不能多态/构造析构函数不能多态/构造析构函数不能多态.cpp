// ���������������ܶ�̬.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
 
using namespace std; 

class Base {
public:
	Base() {
		cout << "Base " << this  << endl; 
	}
	virtual ~Base() {
		cout << "~Base " << this << endl;
	}
	virtual void run() {
		cout << "Base run " << this << endl;
	}
	
};

class Derive : public Base {
public :
	Derive() {
		cout << "Derive " << this << endl;
		run(); 
		/*
			������õ��Ǳ�����߻��� �е�run()
			������಻overrideʵ��run() ��ô�ͻ���û����
		*/
	}
	virtual ~Derive() {
		cout << "~Derive " << this << endl;
	}
	virtual void run() {
		cout << "Derive run " << this << endl;
	}
};


class Derive1 : public Derive {
private:
	const int CONSTANT_COPY; 
	static const int STATIC_CONSTANT_DEFINED ;
public:
	Derive1(): CONSTANT_COPY(0){
		cout << "Derive1 " << this << endl;
	}
	virtual ~Derive1() {
		cout << "~Derive1 " << this << endl;
	}

	virtual void run() {
		cout << "Derive1 run " << this << endl;
	}
};

const int Derive1::STATIC_CONSTANT_DEFINED = 5;

int main()
{
	Base* b = new Derive1();
	//b->run();
	delete b;

	Derive1 d1;
	Derive1 d2;
	// d2 = d1; Dervie1 ���� const�������� ��Ա ��ô�����Լ�ʵ�ֿ�����ֵ�����

    return 0;
}

/*

����������
1. Ĭ�ϵ����������Ƿ��麯�������ǻ������Լ�������������������

2. ����������ֻ����ñ�����߻����е��麯��,�����ڶ�̬


*/
