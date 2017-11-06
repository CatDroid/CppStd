// ���ö�̬.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std; 

/*
	C++����������������麯���Ĺ���һ��������������Ϊ�麯�������ж�̬�󶨣� 
	��Ȼ��������������!!

	1. ��������Ҫ�ض�������麯����Ҫע���������Ϊ������������
		override virtual Base&/Derive& operator= (const Base& b) // ������Base

	2. ����������ض������������������Ҫ��������Ĳ���������
		���������ÿ����һ�㣬���������������Ҫ�ඨ��һ������������
		(��Ϊ������һ��!!)
		virtual Derive& operator= (const Derive & b)

*/
class base {
public:
	base() {
		cout <<"base()" << endl;
	}

	base(const base& other) {
		cout << "base(const base& other)" << endl;
	}

	virtual ~base() {
		cout << "~base()" << endl;
	}
	
	virtual base& operator= ( const base& other ) {
		cout << "base& operator= base " << endl; 
		return *this;
	}

	virtual void shot() {
		cout << "base::shot()" << endl;
	}

};

class derive : public base {

public:
	derive() {
		cout << "derive()" << endl;
	}
	virtual ~derive() {
		cout << "~derive()" << endl;
	}
	// ������operator=��ȫ��ͬ���������¶��壬���ᶯ̬�󶨡�   
	// ���������ò����������Զ��ϳ�һ�������Զ����û����operator=�����ᶯ̬��  
	virtual derive& operator= (const derive& other) {
		cout << "derive& operator= derive" << endl;
		return *this;
	}

	// ���¶�������operator=���ᶯ̬��   
	// virtual base& operator=(const base& rhs)  //����ֵ���ֶ�����   
	virtual derive& operator=(const base& rhs)
	{
		cout << "derive& operator= base " << endl;
		return *this;
	}


	virtual void shot() {
		cout << "derive::shot()" << endl;
	}

};


class derive2 : public derive {
public:
	derive2() {
		cout << "derive2()" << endl;
	}
	virtual ~derive2() {
		cout << "~derive2��()" << endl;
	}

	// ʵ�������û��override����� ��Ϊ��������һ�� !!
	virtual derive2& operator= (const derive2& other)  { // ���� override
		cout << "derive2& operator= derive2 " << endl;
		return *this;
	}

#if 0 
	virtual derive2& operator= (const derive& other) override {
		cout << "derive2& operator= derive2 " << endl;
		return *this;
	}
#endif 

#if 0 
	virtual derive2& operator= (const base& other) override {
		cout << "derive2& operator= base " << endl;
		return *this;
	}
#endif 

	virtual void shot() {
		cout << "derive2::shot()" << endl;
	}
};


int main()
{
	cout << "----------begin of main --------------" << endl;
	{
		derive2 d2;
		base& b = d2; // ������ָ�����������һ�ֶ�̬(�ں������������� base& �� base* �����Զ�̬ ���� base �Ļ��ᵼ�¿������캯�� ) 
		b.shot();


		cout << "--------------------------------------" << endl;
		derive d1;
		cout << "���ó�ʼ�� ֮�� ����ͱ�� ��ֵ������ " << endl;
		b = d1;  // derive2����дoperator(base/derive)�Ļ����͵��� derive& operator= base 
 
		cout << "--------------------------------------" << endl; 
		b.shot();// û�иı�����

	}
	{
		cout << "----------------Stage 2-----------------" << endl;
		derive d;
		base b;
		base& b_ref = d ;
		b_ref = b; // device& operator = base 
		cout << "-----------------------------------------" << endl;
	}

	cout << "------------end of main --------------" << endl;
    return 0;
}

