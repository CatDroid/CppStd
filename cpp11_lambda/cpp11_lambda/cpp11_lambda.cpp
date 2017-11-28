// cpp11_lambda.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdlib.h>
#include <stdio.h>
#include <algorithm>
#include <iostream>
#include <vector>
#include <functional>

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
	int more;
	int privateFun() {
		return more;
	}
public:
	
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

	/*
		��һ�� lambda������������ĳ���͵ĳ�Ա�����У��ᱻ���������͵�friend
		ֻ�е��� lambda���������� ������ ���� ����ĳ�Ա�����ڲ�ʱ��������
		�ڳ�Ա������ָ������thisָ�룬����Ҫ��ʽ�Ĵ��� lambda ������ �����Ա�����е� lambda �����޷�ʹ���κθö���Ĳ�������
		���� lambda ����ʹ�� [&] ���� [=] ����ʽ��this�� lambda ������Ϊ�ɼ�

		ʹ�� auto �ؼ����������ܹ��洢 lambda ����


	*/
	auto getLambda(int a ){
		return [this ,a]()->int{  return this->privateFun() * a ; /*friend*/ };
	}

	auto getLambdaWithArgs() {
		return [](MyClass * my)->int {  return my->more; /*����ʱ��������� ���������˽�г�Ա*/ };
	}
};


auto getLambda()
{
	vector<string> temp;
	temp.push_back(string("abc"));
	temp.push_back(string("def"));
	temp.push_back(string("yui"));

	//vector<string>&& tempp = std::move(temp);
	return [&temp]()->int {  return temp.size(); };
}


void setLambda(int a, int b , std::function<int(int, int)> ftn)
{
	cout << "std::function��ʹ�� " << ftn(a, b) << endl;
}

template <typename Type, typename Fn>
void setLambdaTemplate(Type a, Type b, Fn ftn) // ����ʹ��std::function ����ʹ��ģ�庯��
{
	cout << "ģ�庯�� ����lambda " << ftn(a, b) << endl;
}

/*
	�������к���ָ�������ԣ�������ͨ������ֲ�������߿���չ��
	Lambda���ʽ �� ���� ���� ����
	[](int x, int y) -> int { int z = x + y; return z + x; };
	������ǽ� lambda���ʽ ���� ���������Կ������롰����������Ӧ����һ�Կյġ������š�������������ʽ��
	[] Lambda�Ĳ����Ӿ䣬Ҳ������Lambda���﷨���������������������ʱ����֪��������дһ��Lambda��
	() Lambda�Ĳ����б�
	{} Lambda�ĺ�����

	[](int x, int y) { return x + y; }
	���������Ļط������� decltype(x+y)��ֻ���� lambda ��������"return expression"(ֻ��һ���������)����ʽ�£����ķ������Ͳ��ܱ�����
	a.��� lambda ����û�д���ֵ(���� void )����ط����Ϳɱ���ȫ����
	b.������ֻ����һ���������

	��ֵ/������:
	[var]   ��ֵ��ʽ��ֻ�������������ݵ�����������
	[=]     �����÷�Χ�����б����Դ�ֵ��ʽ��ֻ����,���ݵ����������У�����this��
	[&var]  ���÷�ʽ����д�����������ݵ�����������
	[&]     �����÷�Χ�����б��������÷�ʽ����д��,���ݵ����������У�����this��
	[=,&var1,&var]  var1,var2�Զ�д��ʽ���ݵ����������У�����������ֻ����ʽ���ݵ�������
	[&, var1,this]   var1,this��ֻ����ʽ���ݵ������У����������Զ�д��ʽ���ݵ�������
	������ ��lambda���� ��ͬ������Ĳ���/���� Ҳ���Ա�ʹ��, ��������һ�㱻���� closure (�հ�)
	����ʹ�����õķ���&�����������Դ�ֵ�ķ�ʽ���� lambda ����  , "��ֵ�Ļ�����ֻ��"

	[&, a, &b]��[=, &a, b]��Щд������Ч�� 

	��׽�Ǹ����÷�Χ�ı��������߷��Ա������磬��̬�������ȣ��������±�����󡣹ʿ��Կ�������������
	�Ƕ�̬�������ڱ����ھͶ����ˣ��ʲ���������⿪��

	lambda�������Բ��ڱ������ĵط��͵�ʹ��,���������Դ����õķ�ʽ���ӵ� closure��,��������������Σ�յ���Ϊ
	��lambda ����ֻ�ڶ����������ʹ�ã� ������� [&] ���� lambda �����������������õ�ջ/stack�еĲ��������������õķ�ʽ����

	http://www.cnblogs.com/allenlooplee/archive/2012/07/03/2574119.html

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

	{ // ��ε���  lambda���ʽ (û�бհ� ֻ��һ���ֲ�����������)
	  // auto�ؼ����൱��C#��var�����������������������ʼ��f1������ֵ�ƶ�����ʵ������
	  // ��������Ǿ�̬�ģ�"auto�ڱ���ʱ���"
		auto ftn = [](int x, int y) -> int { int z = x + y; return z + x; }; 
		cout << ftn(3, 2) << endl; // 8
		cout << ftn(3, 3) << endl; // 9 	
	}

	/*{
		auto ftn = [](float x, float y)-> float {return x + y; };
		ftn(4, 2);
		ftn = [](int a)->int {return a + 1; };// ��֧�ָ�ֵ ��ͬ����
	}*/

	{
		/*
		   ��ֵ����������Lambda����һ�̾��Ѿ�ȷ��������ֵ�ˣ�����֮��������ô�޸ģ�����ֻ�ܷ��ʵ�����ʱ�������İ汾
		   �����ô�����պ��෴����������濴������ͬһ������������ڵ���Lambda֮ǰ������κ��޸Ķ����涼�ǿɼ���
		*/
		int total = 0;
		int value = 5;
		auto ftn = [&, value](int x) { total += (x * value); return total; };
		cout << ftn(3) << endl; // 15 
		value = 6;  // ֵ���� ��Ӱ��
		cout << ftn(4) << endl; // 35 

	}
	{ // �հ� �� std::vector  std::for_each 
		std::vector<int> someList;
		for (int i = 0; i < 10; i++) {
			someList.push_back(i);
		}
		int total = 0;
		std::for_each(someList.begin(), someList.end(), 
			[&total](int& x)   /*ע�������в��� ������Ԫ�ص����� Ҳ��ʼ������!*/
			{ 
				total += x;
			}
		);
		cout << "std::for_each ����vector+lambda���ʽ " <<  total << endl; // 45
	}

	{
		MyClass my(12);
		auto ftn = my.getLambda(4); // 48
		cout << ftn() << endl;
		auto fun = my.getLambdaWithArgs(); // �հ����Է������˽�г�Ա
		MyClass my2(14);
		cout << fun(&my2) << endl; // 14
	}



	{
		/*
			lambda���� �Ǳ������������͵ĺ�������, ������������ֻ�б������Լ��ܹ�ʹ��
			����û�ϣ���� lambda���� ��Ϊ�������룬�����ͱ�����ģ�����ͣ����Ǳ��룬����һ��std::function ,ȥ��ȡlambda��ֵ
		
			????
			���ǣ���� lambda �������ԡ����á��ķ�ʽ��ȡ���������С��� closure ������������û�� closure ������
			��ô�������ĺ�������ᱻ����һ�����������:std::reference_closure<R(P)>��
			���� R(P) �ǰ����ط����͵ĺ���ǩ����
			������ std::function ��ȡ�����������lambda��������Ч�ʵĴ���
			std::reference_closure<void()> myLambdaFunc = [this]() { this->SomePrivateMemberFunction(); };
			myLambdaFunc();

		*/
		auto myOnheapLambdaFunc = new auto( [=]()->int{ return 2; });
		cout << (*myOnheapLambdaFunc)() << endl;  // �ڶ��Ϸ����lambda���ʽ
		delete myOnheapLambdaFunc;
	}

	{
		auto ftn = getLambda();
		cout << ftn() << endl;
	}

	{
		/*
			mutable����,ʹ�����ǿ�����Lambda�ĺ�����" �޸İ�ֵ���ݵı���" ��
			����Щ�޸Ķ�Lambda����������ǲ��ɼ��ģ���Ȥ���ǣ���Щ�޸���Lambda�Ķ�ε���֮���ǹ���� 
			��ʵ�ϣ�Lambda�Ǻ�������Function Object�����﷨�ǣ�
			Lambda���ջᱻת���� Functor��

		*/
		cout << "Lambda�Ǻ�������" << endl;
		int step = 2;
		int i = 0;
		std::vector<int> seq(10);
		std::generate(seq.begin(), seq.end(),
			[i, step]() mutable
			{
				return (i += step); // ��ֵ�Ļ� i ֻ�� , ��Ҫ���� mutable  
			}
		);
		cout << "std::generateʹ�ñհ�Lambda "<< endl;
		std::for_each(seq.begin(), seq.end(),
			[](int & temp) // ������������ʹ������ !!
			{
				cout << temp << endl;
			}
		);

		class Functor {
		public:
			Functor(int i, int step) :_i(i), _step(step) {}
			int operator()() { return (_i += _step); } // ����֧�� operator() 
			// ��Ϊstd::generate(,,Func)ʵ���Ͼ��ǵ��� 
			// ret = Func() 
			// Func�����������ʱ�������� Ҳ����lambda ,�����ߵĵ��÷�ʽ��һ�� 
		private:
			int _i;
			int _step;
		};
		std::vector<int> seq2(10);
		std::generate(seq2.begin(), seq2.end(), Functor(0,3));
		cout << "std::generate ʹ�� �� ���� operator()" << endl;
		std::for_each(seq2.begin(), seq2.end(),
			[](int & temp) // ������������ʹ������ !!
		{
			cout << temp << endl;
		}
		);

		cout << "--------------------------------------" <<endl;
	}
 
	{// ��Lambda��Ϊ����  ���������� ����Ϊ functionģ�����ͣ���������Ͳ�����ӳ�ˡ�Lambda��ǩ������ ����int������һ��int����ֵ
	 // ���õ�ʱ����һ���ģ��������Ƕ��ܽ���"Lambda���ߺ�������"��Ϊ����

		setLambda(2, 4, [](int a, int b)->int { return a + 2 * b; }); // 10 

		setLambdaTemplate(2, 4, [](int a, int b)->int {return a * 2 + b; }  ); // 8 
	
	
		class Function final{
		public:
			Function() {
				cout << "Function()" << endl;
			}
			~Function() {
				cout << "~Function()" << endl;
			}
			int operator()(int a, int b) {
				return a + b;
			}
		};

		Function(); // ��ʱ����  �� Function instant(); <= ���Ǵ����
	
		setLambda(3, 2, Function()); // 5 
		setLambdaTemplate(11, 22, Function()); // 33 

	}

    return 0;
}

