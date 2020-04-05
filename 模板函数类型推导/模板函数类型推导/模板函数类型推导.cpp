// 模板函数类型推导.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <iostream>
#include <array>
#include <string>


template <typename T>
// void f( T& param) {		// 调用时 const int i = 5 ; f(i)  T会推导成为const int 
void f(const T& param) {	// 调用时 const int i = 5 ; f(i)  T会推导成为int
	T a;
	a = param;				// 如果T推导成 const int 这里编译就会失败
	std::cout << a << std::endl;
}

template <typename T>
void thisIsPoint(T* param) {			// 调用的必须是指针, 因为int a; 和 int& a; 都可以给到int&  但是只有int* a可以给到int* 
	//(*param) = 2;						// 实参是const int* pj  T是const int ; paramType是const int*
	T temp;								// 对于指针来说 const int 看成类型  * 为指针  * 右边的const看成这边变量的 常量性
	temp = *param;						// 实参是int** pArray   T是int*  paramType是int**
	std::cout <<"thisIsPoint " << temp << std::endl;
}

template <typename T>
void g(T param) {			// 这种模板的目的是 值传递 副本全新的对象
	T temp = param;
	//(*temp) = 1;
	std::cout << temp << std::endl;
}

 

template <typename T>
void thisIsArray(T& param) {
	T temp = { param[0],param[1],2,3,4,5 }; //,6,7 }; // 实参是int[6],所以T是int[6],初始值设定太多
	param[0] = -12;
	std::cout << temp << std::endl;
}


template<typename T , std::size_t N>
constexpr std::size_t arraySize(T(&)[N]) noexcept
{
	return N; // 返回数组元素的个数
}
// constexpr 使返回值在编译期可用 
// noexcept 编程器生成更好的目标码

template <typename T>
void ParamLeftRef_ArguRightRef(T& param)
{
	T temp = param; // 实参是A&& 推导T=A T&=A&
	temp = 5;
	param *= 1000;
}



//std::string&& getString(){
//	return std::string("ABC");
//} // 这样不行 VS2015可以编译过 运行出错

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
// 没有右值引用参数的版本，临时变量就会走上面左值引用的版本(但是对于常量,或者字面量就不会了)
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
		.text:00412430 _main           proc near; CODE XREF : _main_0↑j
		.text : 00412430
		.text : 00412430 var_DC = byte ptr - 0DCh
		.text : 00412430 var_18 = dword ptr - 18h
		.text : 00412430 var	= dword ptr - 0Ch
		.text : 00412430 var_4	= dword ptr - 4

		.....(省略)... 
		.text:00412453					 xor	eax, ebp
		.text : 00412455                 mov	[ebp + var_4], eax
		.text : 00412458                 mov	[ebp + var_18], 0Ah	
		.text:0041245F					 lea	eax, [ebp + var_18]		// ebp + var_18的地址(也就是,ebp指向内存作为起始地址 偏移var_18)给到eax 
		.text : 00412462                 mov	[ebp + var], eax		// var 起始是 存放 ebp+var_18 的地址 
		.text : 00412465                 mov	eax, [ebp + var]		// 在 var 变量的值(地址) 给到 寄存器 eax  
		.text : 00412468                 mov	ecx, [eax]              // [eax] 即使就是把 寄存器eax的值 作为地址 索引到 var_18
		.text:0041246A					 add	ecx, 1                  
		.text : 0041246D                 mov	edx, [ebp + var]
		.text : 00412470                 mov[edx], ecx
			.text : 00412472                 mov     esi, esp

#endif 
	{
		// 总结:
		// a. 10 是作为立即数 在代码里面
		// b. 会有一个在栈上的临时变量(var_18)，是int类型，并且初始化为10 
		// c. var 作为一个右值引用类型的 左值，也会在栈上分配内存，存放的是 上面这个临时变量的地址，
		int &&var = 10;
		var++;
		std::cout << "modify int&& = " << var << std::endl;
	}

#if 0
	{
		long one = 4, two = 5;
		ref_swap(one, two);  // 编译错误   如果参数类型是非const引用, 类型必须一致  如果是const引用,会创建临时变量，参数引用指向这个临时变量
		std::cout << "one = " << one << ", two = " << two << std::endl;
	}
#endif 

	{
	 	//setInt(12); // 非常量引用的初始值必须是左值
		setString(std::string("template arguement")); // 如果有右值引用版本,优先调用，如果没有这个临时变量会作为左值,调用左值引用参数的版本
	
		std::string& result = getString();
		std::cout << "getString result temp to left ref " << result << std::endl; 
	}

	{
		// 编译器根据字符串”hello world”构造一个string类型的临时对象，这个临时对象具有const属性
		// 当这个临时对象传递给非const的string&引用类型时，因为非const引用绑定对象时，要求该对象也是非const对象
		// setString("Hello world"); error 
		// setString(std::string("Hello world")); ok 

		// https://www.zhihu.com/question/21494487
		// https://blog.csdn.net/qq_32693119/article/details/79716462
		// 并非所有的临时对象都是const对象
		// 内置类型产生的临时变量具有常性，而自定义类型产生的临时变量不具有常性
		// 为什么C++中成员函数返回自定义类型对象会被编译器认定为左值
		setString(getString());
		setString(getString(std::string("Helloworld")));
		
 
		//int& temp = 1; // 右值--字面量  因为1无法进行取地址操作，无法对一个立即数取地址，因为立即数并没有在内存中存储，而是存储在寄存器中
		//const int & temp = 1;// 万能引用 可以绑定左值或者右值

		//std::string temp1;
		//std::string&& temp2 = temp1; // 无法将右值引用绑定到左值

		//std::string&& temp2 = std::move(std::string("RightValue2LeftRef"));
		//std::string& temp1 = temp2;  // 可以的,其实temp2是左值,同时是右值引用类型
		// 右值引用类型的目的是:
		// 1. 右值引用用来绑定到右值，绑定到右值以后本来会被销毁的右值的生存期会延长至与绑定到它的右值引用的生存期
		// 2. 充分利用右值(特别是临时对象)的构造来减少对象构造和析构操作以达到提高效率的目的

		std::string& str2 = std::move(std::string("RightValue2LeftRef"));

		std::string& str =  std::string("RightValue2LeftRef");
		std::cout << "RightValue2LeftRef = " << str.c_str() << std::endl;
	}


	{	// cosnt T& 和 T&在实参分别是const T和T情况下的推导情况
		const int i = 5;
		f(i);
	}

	//{
	//	int j = 6;
	//	thisIsPoint(j);	 // 模板参数是T* 实参必须是指针才能推导
	//}

	//{
	//	int j = 6;
	//	const int* pj = &j;	 
	//	thisIsPoint(pj);  // 模板参数是T*  T被推倒成const int, 所以模板函数体内不能修改
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
	//	const char name[] = "hello world"; // name是 const char[12] 数组类型 
	//	name = "this is world";			 // is not assignable	不是指针类型 
	//}

	// 数组名在表达式中表示指向首元素的"指针常量"，这个常量运行时才被分配到栈中，既然是常量当然不允许修改，一旦定义就不能再被赋值了
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
		const int * b = &a;		// 模板函数中 T类型是const int* 但是可以修改param的值 但不能改变指向对象的内存内容
		g(b);
	}


	{
		int keyVals[] = { 1,2,3,4,5,6,7,8 }; // 实际上 keyVals 是个数组类型  int[8]
		std::cout << arraySize(keyVals) << std::endl;  // T(&)[N]   N就是在编译器得到的数组长度
	}

	{
		int keyVals[] = { 1,2,3,4,5,6 };

		thisIsArray(keyVals); // ParamType= int(&)[6]  T=int[6] 数组 模板函数形参是T&
		std::cout << keyVals[0] << std::endl; // -12 

		
		std::array<int, arraySize(keyVals)> mappedVals; // 加了constexpr没有作用 
		mappedVals[1] = 2;


		int mappedVals2[arraySize(keyVals)];

		std::cout << "array size = " << sizeof(mappedVals2) / sizeof(mappedVals2[0]) << std::endl; // 6 

	}


	
	{
		int a = 100;
		int&& b = std::move(a);// b是一个左值 
		int c = b; // ok
		int d = std::move(a);// ok
		//int& e = std::move(a);	// error 非常量左引用 不能应用右值
		//int& e = 10;				// 错误：用类型为‘int’的右值初始化类型为‘int&’的非常量引用无效
		
		ParamLeftRef_ArguRightRef(b); // 其实b是一个左值 类型是 右值引用
		//ParamLeftRef_ArguRightRef(std::move(a)); // 错误 
		//ParamLeftRef_ArguRightRef(1);						// 错误 不能用右值初始化左值
		// ParamLeftRef_ArguRightRef(getInt());				// int作为临时值返回也不行 
		// ParamLeftRef_ArguRightRef(getString());			// ok 
		// ParamLeftRef_ArguRightRef(std::string("123"));   // ok 临时变量 可以给std::string& param 
		std::cout << "ParamLeftRef_ArguRightRef " << a << std::endl;
	}
	


    return 0;
}

