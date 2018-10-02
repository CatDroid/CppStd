// 使用boost库.cpp : 定义控制台应用程序的入口点。
//
#include "stdafx.h"

#include <iostream>
using namespace std;

#include "boost/thread.hpp"

void mythread()
{
	cout << " hello,thread! " << endl;
}

template<typename T>
void func(const T& param) {
	using boost::typeindex::type_id_with_cvr;

	cout << "T= " << typeid(T).name() << endl;
	cout << "ParamType = " << typeid(param).name() << endl;
	// T= char const *
	// ParamType = char const *
	cout << "T= " << type_id_with_cvr<T>().pretty_name() << endl;
	cout << "ParamType = " << type_id_with_cvr<decltype(param)>().pretty_name() << endl;
	// T = char const *
	//	ParamType = char const * const &
}

int main(int argc, _TCHAR* argv[])
{
	boost::function<void()> f(mythread);
	boost::thread t(f);
	t.join();
	cout << " thread is over! " << endl;

	const char* str = "helloworld";
	func(str);

	return 0;
}

/*

libboost_log-vc120-mt-sgd-1_58.lib
其中mt表示多线程，
sgd中的s表示runtime 是static，
gd表示debug版本。?
 

/MT是 
"multithread, static version ” 
意思是多线程静态的版本
编译器把LIBCMT.lib安置到OBJ文件中，让链接器使用LIBCMT.lib处理外部符号。

/MD是
"multithread- and DLL-specific version” 
意思是多线程DLL版本
编译器把MSVCRT.lib安置到OBJ文件中，它连接到DLL的方式是静态链接
实际上工作的库是MSVCR80.DLL

即：
静态运行时库：LIBCMT.lib
动态运行时库：MSVCRT.lib + MSVCR80.DLL

Single Threaded				/ML		LIBC	(none)
Static MultiThread			/MT		LIBCMT	_MT
Dynamic Link (DLL)			/MD		MSVCRT	_MT and _DLL
Debug Single Threaded		/MLd	LIBCD	_DEBUG
Debug Static MultiThread	/MTd	LIBCMTD	_DEBUG and _MT
Debug Dynamic Link (DLL)	/MDd	MSVCRTD	_DEBUG, _MT, and _DLL

*/