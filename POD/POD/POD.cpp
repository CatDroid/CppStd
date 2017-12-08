// POD.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>  

using namespace std;

class A { A() {} };
class B { B(B&) {} };
class C { C(C&&) {} };
class D { D operator=(D&) {} };
class E { E operator=(E&&) {} };
class F { ~F() {} };
class G { virtual void foo() = 0; };
class H : G {};
class I {};
class J { int temp = 5; int test{ 5 }; /*ֱ�ӳ�ʼ��*/ };

class K 
{
public:
	K() { cout << "K()"<< endl; } 		// �û��ṩ���޲ι��캯��  ���Բ��� trivially 
										// ���� trivially_copyable �������ɱ�
	//K(int temp):a(temp) { cout << "K(temp)" << endl; }
public:
	int a;
};

class M
{
public:
	int m1;
};

class N :public M
{
public:
	int n1;
};

/////////////////////////////////

class As
{
private:
	int a;
public:
	int b;
};

class B1s
{
	static int x1;
};

class B2s
{
	int x2;
};

class Bs : B1s, B2s
{
	int x;
};

class C1s {};
class Cs : C1s
{
	C1s c;
};

class Ds { virtual void foo() = 0; };
class Es : Ds {};
class Fs { As x; };

/////////////////////////////////

class MyPod
{
public:
	int x;
	double y;
};

/////////////////////////////////

int main()
{


	// ��ƽ�� ���� �û��ṩ��   
	std::cout << std::is_trivial<A>::value << std::endl;  // �в�ƽ���Ĺ��캯��  
	std::cout << std::is_trivial<B>::value << std::endl;  // �в�ƽ���Ŀ������캯��  
	std::cout << std::is_trivial<C>::value << std::endl;  // �в�ƽ���Ŀ�����ֵ�����  
	std::cout << std::is_trivial<D>::value << std::endl;  // �в�ƽ���Ŀ�����ֵ�����  
	std::cout << std::is_trivial<E>::value << std::endl;  // �в�ƽ�����ƶ���ֵ�����  
	std::cout << std::is_trivial<F>::value << std::endl;  // �в�ƽ������������  
	std::cout << std::is_trivial<G>::value << std::endl;  // ���麯��  
	std::cout << std::is_trivial<H>::value << std::endl;  // �������  

	std::cout << std::is_trivial<I>::value << std::endl;  // ƽ������ 


	std::cout << "--------------" << std::endl;

	std::cout << std::is_trivial<J>::value << std::endl;  // ����Aggregate��C++11���� ��static���ݳ�Ա ���� ֱ�ӳ�ʼ��	
									
	std::cout << std::is_trivially_copyable<K>::value << endl;
	std::cout << std::is_trivial<K>::value << std::endl; //  ����Aggregate ���� �б��ʼ�� { }
	K k1[3] = { K() };									  // ������Χ�� ����� ֵ��ʼ�� ���� �޲ι��캯�� 
	//K k2 = { 1 };										  // �� �û��ṩ�޲ι��캯��  std::is_trivial = 0
														  // ֧�ֶ�����ͨ���캯��


	std::cout << "*---------***----------*"<< std::endl;
	std::cout << std::is_trivial<N>::value << std::endl;			// 1
	std::cout << std::is_trivially_copyable<N>::value << std::endl; // 1 
	//N n = { 1  };  // ERROR 

	std::cout << "��׼����" << std::endl;
	std::cout << std::is_standard_layout<As>::value << std::endl;  // Υ������1����Աa��b���в�ͬ�ķ���Ȩ��  
	std::cout << std::is_standard_layout<Bs>::value << std::endl;  // Υ������2���̳���������(��)���ϵ���,�зǾ�̬��Ա  
	std::cout << std::is_standard_layout<Cs>::value << std::endl;  // Υ������3����һ���Ǿ�̬��Ա�ǻ�������  
	std::cout << std::is_standard_layout<Ds>::value << std::endl;  // Υ������4�����麯��  
	std::cout << std::is_standard_layout<Es>::value << std::endl;  // Υ������5���������  
	std::cout << std::is_standard_layout<Fs>::value << std::endl;  // Υ������6���Ǿ�̬��Աx���� standard_layout


	if (std::is_pod<MyPod>::value)
	{
		std::cout << "before" << std::endl;
		MyPod a;
		a.x = 8;
		a.y = 10.5;
		std::cout << a.x << std::endl;
		std::cout << a.y << std::endl;

		size_t size = sizeof(a);
		char *p = new char[size];
		memcpy(p, &a, size);			// �����ƿ���
		MyPod *pA = (MyPod*)p;

		std::cout << "after" << std::endl; 
		std::cout << pA->x << std::endl;
		std::cout << pA->y << std::endl;

		delete p;
	}

    return 0;
}

