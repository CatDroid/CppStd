// ָ���Ա��ָ�������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>

using namespace std;

class Base {
public:
	void base_func() {
		cout << "Base::base_func " << this << " mNumber = "<< mNumber << " mPri = " << mPri  << endl;
	}

	virtual void call_func(int i) {
		cout << "Base::call_func " << this << " i = " << i << endl;
		mPri = i;
	}

	int mNumber ;

protected:
	int mPri; 
};

class Derive :public Base {
public:
	virtual void call_func(int i) {
		cout << "Derive::call_func " << this << " i = " << i << endl;
		mPri = -i ;
	}
	
};

// ָ�뵽��Ա�����		.* �� ->*  ��һ������ ��������Ķ��� �ڶ������� ������'ָ���Ա��ָ������ '
// ��Ա���������		. �� ->

/*
	1. ���� ����ָ��˽�г�Ա
	2. ����ָ���Ա����  Ҳ֧�ֶ�̬
	3. int Base::*pVar = &Base::mNumber; ==>  pVar ��һ��ָ��  ָ��Base��/���� int����
		void (Base::*pFun)(int)	= &Base::call_func ; ==>  pFun ��һ��ָ��  ָ��Base��/���� void (int)�ĺ���
*/
int main()
{
	// pVar ��һ��ָ��  ָ��Base��/���� int����  
	// int Base::* ���� ����ת��Ϊ int* 
	//int *p = &Base::mNumber;
	int Base::*pVar = &Base::mNumber; // ָ���Ա��ָ������
	//int Base::*n = &Base::mPri;  // ���ɷ��ʳ�Ա  ����ָ��

	// pFun ��һ��ָ��  ָ��Base��/���� void (int)�ĺ��� 
	void (Base::*pFun)(int) = &Base::call_func ;


	Base b; 
	b.*pVar = 1;		// .*   ->* 
	(b.*pFun)(110);
	b.base_func();


	Derive d;
	d.*pVar = 2;
	(d.*pFun)(220);// ����֧�ֶ�̬��!  ִ��override��Derive::call_func(int)
	d.base_func();


    return 0;
}

