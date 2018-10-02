// ʹ��boost��.cpp : �������̨Ӧ�ó������ڵ㡣
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
����mt��ʾ���̣߳�
sgd�е�s��ʾruntime ��static��
gd��ʾdebug�汾��?
 

/MT�� 
"multithread, static version �� 
��˼�Ƕ��߳̾�̬�İ汾
��������LIBCMT.lib���õ�OBJ�ļ��У���������ʹ��LIBCMT.lib�����ⲿ���š�

/MD��
"multithread- and DLL-specific version�� 
��˼�Ƕ��߳�DLL�汾
��������MSVCRT.lib���õ�OBJ�ļ��У������ӵ�DLL�ķ�ʽ�Ǿ�̬����
ʵ���Ϲ����Ŀ���MSVCR80.DLL

����
��̬����ʱ�⣺LIBCMT.lib
��̬����ʱ�⣺MSVCRT.lib + MSVCR80.DLL

Single Threaded				/ML		LIBC	(none)
Static MultiThread			/MT		LIBCMT	_MT
Dynamic Link (DLL)			/MD		MSVCRT	_MT and _DLL
Debug Single Threaded		/MLd	LIBCD	_DEBUG
Debug Static MultiThread	/MTd	LIBCMTD	_DEBUG and _MT
Debug Dynamic Link (DLL)	/MDd	MSVCRTD	_DEBUG, _MT, and _DLL

*/