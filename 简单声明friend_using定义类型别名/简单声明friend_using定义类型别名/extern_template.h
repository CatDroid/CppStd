#pragma once


// ����ģ�� ���� 
template<typename T>
void extern_template_func(T a);

// ��ģ�嶨��
template<typename T>
struct which_kind {
	static void type(){}
};

