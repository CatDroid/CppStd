// ����ת��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;

void RunCode(int&& m) {
	cout << "void RunCode(int&& m)" << endl;
}
void RunCode(const int&& m) {
	cout << "void RunCode(const int&& m)" << endl;
}


void RunCode(int& m) {
	cout << "void RunCode(int&m)" << endl;
}
void RunCode(const int& m) {
	cout << "void RunCode(const int& m)" << endl;
}

// ������������:
// 1.Ϊ�˽�ʡ�ռ� ʹ������
// 2.Ϊ�˼���Ŀ�꺯�� ʹ�������۵�(ֻҪ����ֵ���� �۵�Ϊ��ֵ����)

// ����ת��:
// ����: 1.�����۵�  2.static_cast<T&&>��ֵ���õ���ֵǿ�Ƴ���ֵ����
// ��Ҫ���� ģ�庯�� ����make_pair��   ʹת�������İ汾����(const ��const ��ֵ ��ֵ ��������)
template <class T>
void PerfectForward(T&& who) { // ת������
	 //RunCode(static_cast<T&&>(who));// Ŀ�꺯��
	RunCode(std::forward<T>(who));  
}

// ��װ���� ??? ���� ??? 
template <typename T, typename U>
void PerfectForward_Calc_Warp(T &&t, U& func) {
	//if (t < 1.0) t = 1.0; // ?? 
	func(static_cast<T&&>(t));
}

void RunAdd(double &&m) {
	cout <<"RunAdd" << endl;
}

void RunDec(double &&m) {
	cout << "RunDec" << endl;
}

void RunMul(double &&m) {
	cout << "RunMul" << endl;
}

int main()
{
	int i = 3;
	PerfectForward(i); // void RunCode(int&m)
	PerfectForward(std::move(i)); // void RunCode(int&& m)
 
	PerfectForward_Calc_Warp(1.1 , RunAdd);
	PerfectForward_Calc_Warp(3,    RunDec);
	PerfectForward_Calc_Warp(4.5,  RunMul);
    return 0;
}

