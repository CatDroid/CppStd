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



DefClass& inRightRef_outLeftRef(DefClass && right ) {
	right.temp[0] = 1111;	// �޸���ֵ����
	return right;			// ��������ֵ������ ��ֵ ���Ը��� ��ֵ���� !!!! 
	
}

DefClass& inLeftRef_outLeftRef(DefClass& left) {
	left.temp[0] = 2222;		// �β�����ֵ���� ʵ���Ǿ�������ֵ���ñ���
	return left;				//	����'���������'
}								//	���غ��������е�(��ֵ)����
 

DefClass inLeftRef_outValue (DefClass & left) {
	return left;				//	�������캯��  @VS2015/Clang++  ��ʱ���� ��ֵ
}

//////////////////////////////////////////////////////////////

void callme(DefClass&& right) {
	right.dump();
	cout << "callme(DefClass&& !" << endl;
}

void callme(DefClass& left) {
	left.dump();
	cout << "callme(DefClass& !" << endl;
}

/////////////////////////////////////////////////////////////

DefClass get_a_DefClass() {
	DefClass a;
	a.temp[0] = 1212 ;
	return  a;
}

DefClass& foo(DefClass&& x) {
	cout << "foo" << endl;
	x.temp[0] = x.temp[0] + 1 ;
	return x;
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
	{	// 1. sizeof �������� ���� ���� �����Ĵ�С 
																		//	clang++  /	vs2015+Release Mode+x86
		cout << "sizeof(char &)=" << sizeof(char &) << endl;			//	sizeof(char &)=1
		cout << "sizeof(int  &)=" << sizeof(int  &) << endl;			//	sizeof(int  &) = 4
		cout << "sizeof(long long &)=" << sizeof(long long &) << endl;	//	sizeof(long long &) = 8
		cout << "sizeof(long long)=" << sizeof(long long) << endl;
	}

	{	// 2. ��ֵ���ú���ֵ���ñ���Ҳռ�ڴ棬���Ծ������������ͱ�������ȡ��ַ,����ֵ
		long long size = 1;			cout << &size << endl;		// 0xffffcbf0
		long long& size_ref = size; cout << &size_ref << endl;	// 0xffffcbf0
		long long size_2 = 2;		cout << &size_2 << endl;	// 0xffffcbe0

	}

	{
		DefClass&& r1 = DefClass();
		//DefClass&& r2 = r1;	// �޷�����ֵ���ð󶨵���ֵ
		DefClass& lr = r1;		// ��������ֵ����Ҳ����ֵ ���б���������ֵ ���Ը�����ֵ����,��������������������͵Ļ�,��ֵ���þ������˶�Ӧ�Ķ���

		DefClass l;
		DefClass& l1 = l;
		DefClass& l2 = l1;  // OK  һ�б������������ֵ�,���Զ�����ֵ
	}


	{	// ��ֵ���� ��һ������  �����������ֵ(������ ��ȥ��ַ) ��ô���Ը�����ֵ���ñ�����ʼ��
		// ��������β�����ֵ�������ͣ���ôʵ��Ҫ�ǡ���ֵ������ʼ������

		cout << "-----*------" << endl;
		DefClass&& right = DefClass();
		DefClass& left = inRightRef_outLeftRef(std::move(right));
		left.dump();
		cout << left.temp[0] << endl;
	}cout << "-----*-----" << endl;

	{   // ����������ֵ���� ��������ֵ���ñ��� 
		// ����(��ֵ)����: 1.ʵ���е����� 2.������ 3.�����ڲ����� 
		//		���ܷ���:  1. �ֲ����� 
		cout << "-----**------" << endl;
		DefClass&& right = DefClass();
		DefClass& left = inLeftRef_outLeftRef(right);
		left.dump();
		cout << left.temp[0] << endl;
	}cout << "-----**-----" << endl;


	
	/*{ // ����������ֵ����  ���ܸ��� ��ֵ���ñ���
		DefClass&& returnRight = inRightRef_outLeftRef(  DefClass() );
		// ERROR ����DefClass����ֵ���� ���ܰ󶨵� ����DefClass����ֵ
	} */


	{
		cout << "-----***-----" << endl;
		callme(inRightRef_outLeftRef(DefClass())); // ���ص���ֵ���ã�û��������ֵ������ֵ������ ��ֵ���ò��� ����
	}cout << "-----***-----" << endl;			   // ���ص���ֵ���ã��ǽ���ֵ����ֵ���õ���ֵ 

	{
		cout << "-----*** std::move ������ֵ���ñ��� -----" << endl;
		DefClass c;
		DefClass&& lvalue_of_right_ref = std::move(c);
		callme(lvalue_of_right_ref);// ������õ�����ֵ���õİ汾  ��ֵ���ø���һ����ֵ���ñ���������ֵ
		callme(std::move(c));
	}cout << "-----***-----" << endl;

	{
		cout << "-----****------" << endl;
		DefClass& def = foo(get_a_DefClass());
		def.dump();
		cout << def.temp[0] << endl;
	}cout << "-----****-----" << endl;

	{
		DefClass c;
		DefClass& c1 = c;
		//DefClass&& c2 = c1;
		DefClass&& c2 = std::move(c1); // std::move�Ǻ��� ���� ��ֵ���õ���ֵ(����ֵ) (��ֵ���ÿɰ�)
	}

	/*
	
	�ܽ᣺
		
		��ֵ����	�ɰ󶨵�: 
							����ֵ   
							��ʱ����    
							����ֵ(��ֵ���õ���ֵ)  
					������:
							��ֵ���õ���ֵ(��������ֵ����)
							��ֵ����(�ر���,�������ص�),����ʹ��std::move
	
	*/

	cout << "------$$$$$------" << endl;
    return 0;
}

