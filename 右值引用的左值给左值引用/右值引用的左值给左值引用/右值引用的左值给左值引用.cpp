// ��ֵ���õ���ֵ����ֵ����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <iostream>
#include <inttypes.h>

using namespace std;

class DefClass {
public:
	// vptr  
	uint64_t self;			// vptr +8
	uint64_t temp[100];		// vptr +8 +8   
	uint64_t other;			// vptr +8 +8 +8*100
	uint64_t isMove;		// vptr +8 +8 +8*100 +8 
							// sizeof(DefClass)  = 832 

	DefClass() :self((uint64_t)this), other(0), isMove(0) {
		cout << "DefClass() " << this << endl;
	}
	virtual ~DefClass() {
		cout << "~DefClass() " << this << endl;
	}
	DefClass(DefClass&& other) :self((uint64_t)this), other((uint64_t)&other), isMove(1) {
		cout << "DefClass(DefClass&& other)       this:" << this << " other: " << &other << endl;
	}

	DefClass(const DefClass& other) :self((uint64_t)this), other((uint64_t)&other), isMove(0) {
		cout << "DefClass(const DefClass& other)  this:" << this << " other: " << &other << endl;
	}

	DefClass& operator=(const DefClass& other) {
		cout << "operator=(const DefClass& other)  this:" << this << " other: " << &other << endl;
		return *this;
	}

	DefClass& operator=(DefClass&& other) {
		cout << "operator=(DefClass&& other)       this:" << this << " other: " << &other << endl;
		return *this;
	}

	void dump() const {
		printf("this %0" PRIx64 " other %0" PRIx64 " %s\n", self, other, (isMove ? " Move " : "Non-Move"));
	}
};


void dumpByleft(DefClass & left) {
	left.dump();
}


DefClass& returnLeftRef(DefClass& left) {
	return left; // ����'���������'
}
// �����ֵ������һ����ʱ���������纯���ķ���ֵ������ô��������ֵ
// 

DefClass dumpReturn (DefClass & left) {
	return left; //  �������캯��  @VS2015/Clang++
}


DefClass get_a_DefClass() {
	DefClass a;
	a.temp[0] = 1212 ;
	return  a;
}

DefClass& foo(DefClass&& x) {
	x.temp[0] = x.temp[0] + 1 ;
	return x; // ��������ֵ������ ��ֵ ���Ը��� ��ֵ���� !!!!
}

/*
VS2015 (x86) ���������int��������ַ���12���ֽڡ�����Ϊʲô��

�������ǵ���⣬intռ��4���ֽڣ�Ӧ�����4���ֽڡ�

��VS2015��Debugģʽ�£�int����ռ��12���ֽڡ�����������Ϊ��Debugģʽ�£���int������ǰ���������4���ֽڣ����ڴ洢������Ϣ��
��ôaa�ĺ���4���ֽڣ�bb��ǰ��4���ֽڣ��ټ���aa�����4���ֽڣ��պ����12���ֽڡ�

�����ǰ�ģʽ��ΪRelease���ͻᷢ��ջ�����������int��������ַ���4���ֽڡ�

ע�⣺ջ�ϵ�ַ�Ӹ���������� 
*/
int main()
{
	// clang++ 	/ vs2015+Release Mode
	cout << "sizeof(char &)=" << sizeof(char &) << endl; // sizeof(char &)=1
	cout << "sizeof(int  &)=" << sizeof(int  &) << endl; //	sizeof(int  &) = 4
	cout << "sizeof(long long &)=" << sizeof(long long &) << endl; // sizeof(long long &) = 8
	cout << "sizeof(long long)=" << sizeof(long long) << endl;
	long long size = 1;			cout << &size << endl;		// 0xffffcbf0
	long long& size_ref = size; cout << &size_ref << endl;	// 0xffffcbf0
	long long size_2 = 2;		cout << &size_2 << endl;	// 0xffffcbe0
	


	//DefClass&& r1 = DefClass();
	//DefClass&& r2 = r1; // �޷�����ֵ���ð󶨵���ֵ

	DefClass r;
	DefClass& r1 = r;
	DefClass& r2 = r1;  // OK 



	DefClass&& right = DefClass();
	dumpByleft(right); // ��ֵ���� ��һ������  �����������ֵ(������ ��ȥ��ַ) ��ô���Ը�����ֵ���ñ�����ʼ��
					   // ���������������ֵ�������ͣ���ôʵ��Ҫ�ǡ���ֵ������ʼ������ 

//	{
//		DefClass&& returnRight = dumpReturnRight(right);  // ERROR ����DefClass����ֵ���� ���ܰ󶨵� ����DefClass����ֵ
//	}

	//DefClass* addr = &returnLeftRef(right);
	//cout << "DefClass* " << addr << endl;





	DefClass& addr =  returnLeftRef(right);

	//dumpByleft(dumpReturnRight(right));
	
	//{
	//	DefClass&& ret = dumpReturn(right);
	//	ret.dump();
	//}

	cout << "-------------" << endl;
    return 0;
}

