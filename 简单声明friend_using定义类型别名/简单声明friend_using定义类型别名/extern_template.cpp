
#include "stdafx.h"

#include "extern_template.h"

#include <iostream>
using namespace std;


// ȫ�ػ� ��ģ��
template<>
struct which_kind<int> {
	static void type() {
		cout << "int" << endl;
	}
};

template<>
struct which_kind<double> {
	static void type() {
		cout << "double" << endl;
	}
};

template<>
struct which_kind<float> {
	static void type() {
		cout << "float" << endl;
	}
};


// ����ģ�� ���� 
template<typename T>
void extern_template_func(T a) {
	cout << a << endl;
	which_kind<T>::type();
}



// ��ʾ������/ǿ�������� 
template void extern_template_func<int>(int);
template void extern_template_func<double>(double);
template void extern_template_func<float>(float);

void call(int arg) {
	extern_template_func<int>(arg);
}