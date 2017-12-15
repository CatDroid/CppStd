// �͵س�ʼ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

class Mem {

public:
 
	Mem(int a, int b) :ma(a), mb(b) {
		std::cout << "[" << this << "] Mem(int a, int b) = " << ma << "; mb = " << mb << std::endl;
	}

	// clang++ �͵س�ʼ��.cpp  -o main --std=c++98  �������
	// clang++ �͵س�ʼ��.cpp  -o main --std=c++11  ����ͨ��  noexcept C++ ���� 
	virtual ~Mem() noexcept(true) {
		std::cout << "[" << this << "] ~Mem " << std::endl;
	}

	void dump() {
		std::cout << "[" << this << "] dump  ma = " << ma << "; mb = " << mb << std::endl;
	}

private:
	int ma;
	int mb;
};

class Group {
public:
	Group() {
		cout << "[" << this << "] Group() " << endl;
	}

	Group(int a):m(a,13) { 
		// ������� ֻ����ó�ʼ���б�Ĺ���,������� �͵س�ʼ��
		// �͵س�ʼ�� ���� �๹�캯�� ���ʼ����Ա ���龰 �кô�
		// C++98 ֻ�ܵ��ù�����ʼ������ �� ʵ�� ��ͬ���ֵĳ�Ա��ʼ�� C++11�Ľ�Ч�ʺ͸��ӳ̶�
		cout << "[" << this << "] Group(int a) a = " << a << endl;
	}

	~Group( ){
		cout << "[" << this << "] ~Group( ) "<< endl;
	}

	void dump() {
		m.dump();
	}
private:
	//Mem m(1, 2);
	//string s("12345");  // �Ǿ�̬��Ա �͵س�ʼ�� ֻ��ʹ�� = ���� ���ϳ�ʼ�� ����ʹ��()
	Mem m = { 1,2 };
	//string s{ "123344" };

	// static int STATIC_NUM = 2; // C++11��98�Էǳ�����̬��Ա���� ��������ͷ�ļ����� ��Դ�ļ�����/��ʼ�� ��֤�����������ֻ��һ��Ŀ���ļ�����
	static int STATIC_NUM;
};

int Group::STATIC_NUM = 2;

 

class MemE {
public:
	// noexcept ���� ������ Ҳ�� ������ (���ݱ��ʽ�� �Ƶ� �����Ƿ���׳��쳣 )
	//~MemE() noexcept(true) {  // һ���쳣ֱ��std::terminal abort���� ��ֹ�쳣��ɢ
	~MemE() noexcept(false) { // C++11 
	//~MemE() throw(int) { // C++98
		throw 666; // int 
	}
};

int main()
{
	{ // ʹ�� try �� catch ��׽�쳣
		try {
			MemE e;
		}
		catch (int ex) {
			cout << "Exception !  ex = " << ex << endl;
		}
		catch (...) {
			cout << "what Exception ? " << endl;
		}
	}cout << "------------------------------" << endl;


	{
		Group g1;
		g1.dump();
	}cout << "------------------------------" << endl;


	{
		Group g(999);
		g.dump();
	}cout << "------------------------------" << endl;



    return 0;
}

