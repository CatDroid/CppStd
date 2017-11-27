// cpp11_lambda.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>

using namespace std ;

// int g_catch = 2; // lambda ���ܲ�׽��ȫ�ֱ���


//template <class T>
typedef int T;
static int intcompare(const T *p1, const T *p2)
{
	T i = *((T *)p1);
	T j = *((T *)p2);
	return (i < j);
}

 

class MyClass {
private:
	
public:
	int more;
	MyClass(int temp):more(temp) {
		cout << "MyClass()" << endl;
	}
	~MyClass() {
		cout << "~MyClass()" << endl;
	}

	int sum() {
		int a = 10;
		int b = 20;
		//auto b2 = [a, &b, &more](int c) -> int {	 //  ��Ա���� ����=�ڲ�׽�б�	
		auto b2 = [a, &b ,this ](int c) -> int {
			b = a + c; // +more;   // ��պ����ֲ�����������lambda�����ã�����λ���ڲ�׽�б�
			b = a + c + this->more;//  ��Ա��������ֱ����lambda��ʹ��  
			this->more = 2;			// OK  lambda�г�Ա��������ͨ������this���޸�
			//this = 0x111;			// ERROR
			return a + c;
		};

		int result = b2(200);
	}

};

/*
	�������к���ָ�������ԣ�������ͨ������ֲ�������߿���չ��
	Lambda���ʽ �� ���� ���� ����
	[](int x, int y) -> int { int z = x + y; return z + x; };
	������ǽ� lambda���ʽ ���� ���������Կ������롰����������Ӧ����һ�Կյġ������š�������������ʽ��
	 


	[var]   ��ֵ��ʽ��ֻ�������������ݵ�����������
	[=]     �����÷�Χ�����б����Դ�ֵ��ʽ��ֻ����,���ݵ����������У�����this��
	[&var]  ���÷�ʽ����д�����������ݵ�����������
	[&]     �����÷�Χ�����б��������÷�ʽ����д��,���ݵ����������У�����this��
	[=,&var1,&var]  var1,var2�Զ�д��ʽ���ݵ����������У�����������ֻ����ʽ���ݵ�������
	[&, var1,this]   var1,this��ֻ����ʽ���ݵ������У����������Զ�д��ʽ���ݵ�������

	��׽�Ǹ����÷�Χ�ı��������߷��Ա������磬��̬�������ȣ��������±�����󡣹ʿ��Կ�������������
	�Ƕ�̬�������ڱ����ھͶ����ˣ��ʲ���������⿪����
*/
int main()
{
	{
		/*
			�ȽϺ�����Ҫ�����������������˽�����ıȽϺ������ݸ� qsort() �����ķ��ա�
			�ȽϺ������� void * ���������ȱʧ��ĳ�̶ֳȵ����ͼ�顣
			�ȽϺ����������κξֲ����õı�������ˣ������������Ӱ����������أ������ڸ���Χ������
		*/
		int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		//qsort((void *)a, 10, sizeof(int), intcompare<int>); // ERROR
		qsort((void *)a, 10, sizeof(int), (int(*)(const void *p1, const void *p2))intcompare);
		for (int i = 0; i < 10; i++) { printf("%d ", a[i]); } printf("\n");
	}

	{
		/*
			C++ std::sort() �㷨 �� lambda���ʽ ���ʹ��
			std::sort()��һ��ģ�壬��˻ᱣ������������Ϣ
		*/
		int a[10] = { 9, 8, 7, 6, 5, 4, 3, 2, 1, 0 };
		std::sort(a, &a[10], [](int x, int y) -> int { return x < y; }); // ָ������ֵ 
		//std::sort(a, &a[10], [](int x, int y) { return x < y; });
		for (int i = 0; i < 10; i++) { printf("%d ", a[i]); } printf("\n");
	}

	{
		int a = 10;
		int b = 20;
		// static int s_static = 22;  // ��̬����---�޷���lambda��,������о�̬�洢����ʱ��ı���
		// auto b2 = [a, &b, g_catch](int c) -> int { // ȫ�ֱ���---�޷���lambda��,������о�̬�洢����ʱ��ı���
		auto b2 = [a, &b ](int c) -> int {	// a ֻ��  b ��д
			//a = 12;						// ���ʽ�����ǿ��޸ĵ���ֵ
			b = a + c ;
			return a + c;
		};
		 
		int result = b2(200);
		cout  << "b = " << b << " result = " << result << endl;
	}

    return 0;
}

