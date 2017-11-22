// ��ֵ����ֵ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <string>

using namespace std;

#define LINE  drawLine();
void drawLine() {
	cout << "----------------------------------------" << endl;
}

class Base {
public:
	int buf[100];
	Base() {
		cout << "Base()" << endl;
		memset(buf, 0xA5, 100);
	}

	~Base() {
		cout << "~Base()" << endl;
	}

	Base(const Base& other) { // ע�� ����Լ�ʵ���˿������� buf�����ݾ�Ҫ�Լ���ʼ��
		cout << "const A& other" << endl;
		//other.buf[1] = 0xBB;
	}

	Base(Base&& other) {
		cout << "Base(Base && other) " << endl;
		other.buf[2] = 0xBB;  // ��const���ò�һ�� ��ֵ���ÿ����޸Ķ���
	}

	Base& operator = (const Base& other) {
		cout << "opertor = (const A& other) " << endl;
		return *this;
	}
};


class People {
public:
	People(string name)		// ��ֵ�����ַ������ɽ�����ֵ����ֵ��������ֵʱΪ���ƣ�������ֵʱΪ�ƶ�
		: name_(move(name)) // ��ʽ�ƶ����죬��������ַ��������Ա����
	{
		cout << "People(string name)" << endl;
	}
 
	string name_;
};



// std::move(foo)					std::move ���� ����foo ����ֵ����(rvalue reference) ,ʵ�־���һ��static_cast 
// std::vector<std::unique_ptr<T>>	������ std::vector �з����˲��ɸ���ֻ���ƶ������ʵ��(std::unique_ptr �Ŀ������캯���Ǳ�ɾ����)

int main()
{
	Base tempA;
	Base tempB(std::move(tempA)); // ���û��constructor(Base&& other) ��ô���� constructor(const Base& other) ���ǲ��ܸ�other
								  // �����û�У�����Ĭ�ϵĿ������캯��  ע��buf�����ݵ���tempA��
 
	cout << hex << tempB.buf[2]  << endl;	// 0xccccccc
	cout << hex << tempA.buf[2] << endl;	// 0xbb


	LINE
	Base&& tempC = std::move(tempA);		// 0xbb
	cout << hex << tempC.buf[2] << endl;
	LINE

	Base&& tempD = static_cast<Base&&>(tempA);// 0xbb 
	cout << hex << tempD.buf[2] << endl;
	LINE

	Base& tempE = std::move(tempA);			// OK ��ֵ���� �� ��ֵ���� ??
	LINE

	int a = 2;
	cout << &a << endl;
	int&& b = std::move(a);
	const int& c = std::move(a);//	���ض���a����ֵ���� 
	//int&& d = a;				//	��ֵ���� ���� �󶨵���ֵ
	int&& d = a + 1;			//  ��ֵ���� �󶨵���ֵ(��ʱ����)
	//int& d = a++;				//	��ֵ���� ���� �󶨵���ֵ
	const int& dd = a++;		//  ������ֵ���� �� ��ֵ
	//int& d = a;				//   
	//const int& d = a;			//  
	cout << &a << endl;
	a = 3;
	cout << a << endl;
	
	LINE
	int& a_ref = a;
	int& a_ref_ref = a_ref;		//	��ֵ���� ���� ������Ϊ'��ֵ' ���� '��ֵ'
	a_ref_ref = 4;
	int a_temp = ++a_ref;		//	ǰ�����������������ֵ���ã������︳ֵ��a_temp����ʱ'��ֵ������Ϊ��ֵ'
	cout << a << endl;		 
	
	LINE
								//	��ֵ���ñ���Ҳ�ȿ�����Ϊ��ֵҲ������Ϊ��ֵ


	People a_people("Alice");			//	������ֵ �ƶ����� 
	string b_people_name = "Bob";
	People b_people(b_people_name);		//	������ֵ ��������name


	// ��C�� ��ֵ �ǲ����ڸ�ֵ�������ߵģ� ��ֵ�������κ�һ��
	// ��C++�� һ�����ʽ����ֵ������ֵ��ȡ��������ʹ�õ���'����ֵ'����'�����ڴ��е�λ��'
	// ��Ҫ��ֵ�ĵط���������ֵ�����������Ҫ��ֵ�ĵط�����һ�����ܡ�����ֵ�����
	//  C++ �е�ʵ�����������һ�����ʽ ???

	//	��ֵ�����ʵ���У��г־õ�״̬ 
	//	��ֵҪô��'���泣��'��Ҫô���ڱ��ʽ��ֵ�����д�����'��ʱʵ��'��û�г־õ�״̬
	
	// ���ֶ�ʵ�������ã���ֵ���ú���ֵ����
	// ��һ��ʵ�����ڴ�ռ�󶨵���һ�������ϣ���ô�������������ֵ����
	// �ڽ������õ�ʱ�������ǡ����ڴ�ռ�󶨡�
	// ʹ�õ���һ��ʵ�����ڴ��е�λ��

 

	// ��ֵ���� �� ��ֵ
	// ������ֵ���� �ɰ󶨵� ��ֵ (������ֵ���ñ�֤�����ǲ���ͨ�����øı��Ӧ�ڴ�ռ��ֵ)
	// ��ֵ����Ҳ�����ã�������ֻ���ұ��������ֵ��


	// ��ֵ���õĶ�������ʱ�ģ����������٣�������ֵ���õĶ��󣬲����������ط�ʹ��
	// ���ܺ�ʹ����ֵ���õĴ��룬�������ɵؽӹ������õ�ʵ������Դ�������赣�Ķ����������߼���������ƻ� ???



	// ��ֵ���õ�����ͨ������Ϊ�������ã��ƶ����������ת��
	// �ƶ�����:�������Դ����Ȩת��
	// ��α�ʶ�������Դ�ǿ��Ա��ƶ�����?  ��ֵ�������Ķ����ǿ��԰�ȫ�ı��ƶ���

	// ���ϸ����˵����ֵ��Ӧ�����Ĵ洢λ�ã�����ֵ��Ӧ������ֵ����

	// C++����ֵ���Ա�'��ֵ����ֵ'����'�󶨵�����'
	// �����ֵ��һ����ʱ�������'û�б��󶨵�����'���ڱ��ʽ����ʱ�ͻᱻ����
	// �������ǿ�������ֵ������֮ǰ������������Դ���з������ã��Ӷ�����������ĸ��ơ���������Դ����ֵ�ڷ���ʱ�Ѿ���Ϊ�տǣ������Ŀ���Ҳ�ή��

	//	������ֵ�����������ȷ����������Դ������Ȩ�������ͨ��std::move()������תΪ��ֵ����

	//	std::move()ʵ������static_cast<T&&>()�ļ򵥷�װ��

	//  
	//	�������ʱ, ��ֵ���ú���ֵ���ÿ��Ա��ֱ����أ�����ȷ����ֵ����ֵ�ֱ���õ��������ƶ�����������ʵ��

    return 0;
}

