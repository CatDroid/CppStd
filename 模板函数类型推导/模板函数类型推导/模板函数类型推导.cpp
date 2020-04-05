// ģ�庯�������Ƶ�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>


template <typename T>
// void f( T& param) {		// ����ʱ const int i = 5 ; f(i)  T���Ƶ���Ϊconst int 
void f(const T& param) {	// ����ʱ const int i = 5 ; f(i)  T���Ƶ���Ϊint
	T a;
	a = param;				// ���T�Ƶ��� const int �������ͻ�ʧ��
	std::cout << a << std::endl;
}

template <typename T>
void thisIsPoint(T* param) {			// ���õı�����ָ��, ��Ϊint a; �� int& a; �����Ը���int&  ����ֻ��int* a���Ը���int* 
	//(*param) = 2;						// ʵ����const int* pj  T��const int ; paramType��const int*
	T temp;								// ����ָ����˵ const int ��������  * Ϊָ��  * �ұߵ�const������߱����� ������
	temp = *param;						// ʵ����int** pArray   T��int*  paramType��int**
	std::cout <<"thisIsPoint " << temp << std::endl;
}

template <typename T>
void g(T param) {			// ����ģ���Ŀ���� ֵ���� ����ȫ�µĶ���
	T temp = param;
	//(*temp) = 1;
	std::cout << temp << std::endl;
}

 

template <typename T>
void thisIsArray(T& param) {
	T temp = { param[0],param[1],2,3,4,5 }; //,6,7 }; // ʵ����int[6],����T��int[6],��ʼֵ�趨̫��
	param[0] = -12;
	std::cout << temp << std::endl;
}


template<typename T , std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{
	return N; // ��������Ԫ�صĸ���
}
// constexpr ʹ����ֵ�ڱ����ڿ��� 
// noexcept ��������ɸ��õ�Ŀ����

template <typename T>
void ParamLeftRef_ArguRightRef(T& param)
{
	T temp = param; // ʵ����A&& �Ƶ�T=A T&=A&
	temp = 5;
	param *= 1000;
}



//std::string&& getString(){
//	return std::string("ABC");
//} // �������� VS2015���Ա���� ���г���

std::string getString(){
	return "ABC" ;
} 

std::string&& getString(std::string&& other) {
	other += "--std::string&&--";
	return std::move(other);
}

std::string&& getString(std::string& other) {
	other += "--std::string&--" ;
	return std::move(other);
}

void setString(std::string &str){
	str += "--setString(&)--";
	std::cout << "setString=" << str << std::endl;
}

#if 0
// û����ֵ���ò����İ汾����ʱ�����ͻ���������ֵ���õİ汾(���Ƕ��ڳ���,�����������Ͳ�����)
void setString(std::string&& str) {
	str += "--setString(&&)--";
	std::cout << "setString=" << str << std::endl;
}
#endif 

void ref_swap(int &a, int &b)
{
	int temp = a;
	a = b;
	b = temp;
}

void setInt(int& temp)
{
	temp *= 1000;
	std::cout << "setInt=" << temp << std::endl;
}

int getInt()
{
	return 666;
}

 


int main() 
{
#if 0
		.text:00412430; int __cdecl main()
		.text:00412430 _main           proc near; CODE XREF : _main_0��j
		.text : 00412430
		.text : 00412430 var_DC = byte ptr - 0DCh
		.text : 00412430 var_18 = dword ptr - 18h
		.text : 00412430 var	= dword ptr - 0Ch
		.text : 00412430 var_4	= dword ptr - 4

		.....(ʡ��)... 
		.text:00412453					 xor	eax, ebp
		.text : 00412455                 mov	[ebp + var_4], eax
		.text : 00412458                 mov	[ebp + var_18], 0Ah	
		.text:0041245F					 lea	eax, [ebp + var_18]		// ebp + var_18�ĵ�ַ(Ҳ����,ebpָ���ڴ���Ϊ��ʼ��ַ ƫ��var_18)����eax 
		.text : 00412462                 mov	[ebp + var], eax		// var ��ʼ�� ��� ebp+var_18 �ĵ�ַ 
		.text : 00412465                 mov	eax, [ebp + var]		// �� var ������ֵ(��ַ) ���� �Ĵ��� eax  
		.text : 00412468                 mov	ecx, [eax]              // [eax] ��ʹ���ǰ� �Ĵ���eax��ֵ ��Ϊ��ַ ������ var_18
		.text:0041246A					 add	ecx, 1                  
		.text : 0041246D                 mov	edx, [ebp + var]
		.text : 00412470                 mov[edx], ecx
			.text : 00412472                 mov     esi, esp

#endif 
	{
		// �ܽ�:
		// a. 10 ����Ϊ������ �ڴ�������
		// b. ����һ����ջ�ϵ���ʱ����(var_18)����int���ͣ����ҳ�ʼ��Ϊ10 
		// c. var ��Ϊһ����ֵ�������͵� ��ֵ��Ҳ����ջ�Ϸ����ڴ棬��ŵ��� ���������ʱ�����ĵ�ַ��
		int &&var = 10;
		var++;
		std::cout << "modify int&& = " << var << std::endl;
	}

#if 0
	{
		long one = 4, two = 5;
		ref_swap(one, two);  // �������   ������������Ƿ�const����, ���ͱ���һ��  �����const����,�ᴴ����ʱ��������������ָ�������ʱ����
		std::cout << "one = " << one << ", two = " << two << std::endl;
	}
#endif 

	{
	 	//setInt(12); // �ǳ������õĳ�ʼֵ��������ֵ
		setString(std::string("template arguement")); // �������ֵ���ð汾,���ȵ��ã����û�������ʱ��������Ϊ��ֵ,������ֵ���ò����İ汾
	
		std::string& result = getString();
		std::cout << "getString result temp to left ref " << result << std::endl; 
	}

	{
		// �����������ַ�����hello world������һ��string���͵���ʱ���������ʱ�������const����
		// �������ʱ���󴫵ݸ���const��string&��������ʱ����Ϊ��const���ð󶨶���ʱ��Ҫ��ö���Ҳ�Ƿ�const����
		// setString("Hello world"); error 
		// setString(std::string("Hello world")); ok 

		// https://www.zhihu.com/question/21494487
		// https://blog.csdn.net/qq_32693119/article/details/79716462
		// �������е���ʱ������const����
		// �������Ͳ�������ʱ�������г��ԣ����Զ������Ͳ�������ʱ���������г���
		// ΪʲôC++�г�Ա���������Զ������Ͷ���ᱻ�������϶�Ϊ��ֵ
		setString(getString());
		setString(getString(std::string("Helloworld")));
		
 
		//int& temp = 1; // ��ֵ--������  ��Ϊ1�޷�����ȡ��ַ�������޷���һ��������ȡ��ַ����Ϊ��������û�����ڴ��д洢�����Ǵ洢�ڼĴ�����
		//const int & temp = 1;// �������� ���԰���ֵ������ֵ

		//std::string temp1;
		//std::string&& temp2 = temp1; // �޷�����ֵ���ð󶨵���ֵ

		//std::string&& temp2 = std::move(std::string("RightValue2LeftRef"));
		//std::string& temp1 = temp2;  // ���Ե�,��ʵtemp2����ֵ,ͬʱ����ֵ��������
		// ��ֵ�������͵�Ŀ����:
		// 1. ��ֵ���������󶨵���ֵ���󶨵���ֵ�Ժ����ᱻ���ٵ���ֵ�������ڻ��ӳ�����󶨵�������ֵ���õ�������
		// 2. ���������ֵ(�ر�����ʱ����)�Ĺ��������ٶ���������������Դﵽ���Ч�ʵ�Ŀ��

		std::string& str2 = std::move(std::string("RightValue2LeftRef"));

		std::string& str =  std::string("RightValue2LeftRef");
		std::cout << "RightValue2LeftRef = " << str.c_str() << std::endl;
	}


	{	// cosnt T& �� T&��ʵ�ηֱ���const T��T����µ��Ƶ����
		const int i = 5;
		f(i);
	}

	//{
	//	int j = 6;
	//	thisIsPoint(j);	 // ģ�������T* ʵ�α�����ָ������Ƶ�
	//}

	//{
	//	int j = 6;
	//	const int* pj = &j;	 
	//	thisIsPoint(pj);  // ģ�������T*  T���Ƶ���const int, ����ģ�庯�����ڲ����޸�
	//}


	{
		int p1 = 1;
		int p2 = 2;
		int p3 = 3;
		int p4 = 4;
		int* pIntArray[] = { &p1,&p2,&p3,&p4 };
		int** pp = pIntArray;
		thisIsPoint(pp);
	}

	//{
	//	const char name[] = "hello world"; // name�� const char[12] �������� 
	//	name = "this is world";			 // is not assignable	����ָ������ 
	//}

	// �������ڱ��ʽ�б�ʾָ����Ԫ�ص�"ָ�볣��"�������������ʱ�ű����䵽ջ�У���Ȼ�ǳ�����Ȼ�������޸ģ�һ������Ͳ����ٱ���ֵ��
	//{
	//	char name1[12] = "123456789";
	//	char name2[12] = "987654321";
	//	name1 = name2 ;
	//}
	
	{
		g(1);
	}
	

	{
		int a = 8;
		const int * b = &a;		// ģ�庯���� T������const int* ���ǿ����޸�param��ֵ �����ܸı�ָ�������ڴ�����
		g(b);
	}


	{
		int keyVals[] = { 1,2,3,4,5,6,7,8 }; // ʵ���� keyVals �Ǹ���������  int[8]
		std::cout << arraySize(keyVals) << std::endl;  // T(&)[N]   N�����ڱ������õ������鳤��
	}

	{
		int keyVals[] = { 1,2,3,4,5,6 };

		thisIsArray(keyVals); // ParamType= int(&)[6]  T=int[6] ���� ģ�庯���β���T&
		std::cout << keyVals[0] << std::endl; // -12 

		
		std::array<int, arraySize(keyVals)> mappedVals; // ����constexprû������ 
		mappedVals[1] = 2;


		int mappedVals2[arraySize(keyVals)];

		std::cout << "array size = " << sizeof(mappedVals2) / sizeof(mappedVals2[0]) << std::endl; // 6 

	}


	
	{
		int a = 100;
		int&& b = std::move(a);// b��һ����ֵ 
		int c = b; // ok
		int d = std::move(a);// ok
		//int& e = std::move(a);	// error �ǳ��������� ����Ӧ����ֵ
		//int& e = 10;				// ����������Ϊ��int������ֵ��ʼ������Ϊ��int&���ķǳ���������Ч
		
		ParamLeftRef_ArguRightRef(b); // ��ʵb��һ����ֵ ������ ��ֵ����
		//ParamLeftRef_ArguRightRef(std::move(a)); // ���� 
		//ParamLeftRef_ArguRightRef(1);						// ���� ��������ֵ��ʼ����ֵ
		// ParamLeftRef_ArguRightRef(getInt());				// int��Ϊ��ʱֵ����Ҳ���� 
		// ParamLeftRef_ArguRightRef(getString());			// ok 
		// ParamLeftRef_ArguRightRef(std::string("123"));   // ok ��ʱ���� ���Ը�std::string& param 
		std::cout << "ParamLeftRef_ArguRightRef " << a << std::endl;
	}
	


    return 0;
}

