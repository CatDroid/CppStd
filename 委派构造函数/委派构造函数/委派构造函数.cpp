// ί�ɹ��캯��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
	��Java�� ���֧��ί�ɹ��캯��  ����ڼ̳й��캯�� ί�ɹ��캯������ƺ�ʵ�ֶ��Ƚ���

	C++11����:
	1. ��Աֱ�ӳ�ʼ��(�͵س�ʼ��)
	2. ί�ɹ��캯��
	3. �̳й��캯��

*/
#include <iostream>
#include <string>
using namespace std;


class Base {
public:
	Base(int i):pid(i) {
		cout << "Base(int i) i= " << i << endl;
	}

	Base(const Base& other) {
		cout << "Base(const Base& other) other = " << other.pid << endl;
		pid = other.pid;
	}

	Base& operator= (const Base& other) {
		cout << "Base& operator= (const Base& other) " << other.pid << endl;
		pid = other.pid;
	}

	~Base() {
		cout << "~Base() pid = " << pid << endl;
	}
private :
	int pid;
};

class Info:public Base {

public:
	Info():Base(-1) {
		cout << "Info() "<< endl;
		initSetup();
	}

	Info(int temp) :id(temp),Base(temp+1) {
		//this->Info(); �������������캯���� ���ù��캯��
		cout << "Info(int temp) temp = " << temp << endl;
	}

	Info(const char* temp) :name(temp),Base(id + 1) {
		cout << "Info(const char* temp) temp = " << temp << endl;

		new (this) Info(); 
		// name = temp;		// �����ڳ�ʼ���б�λ�� �������
		
	}

	Info(string&& temp) :name(std::move(temp)),Base(id+1) {
		cout << "string&& temp " << temp << endl;
	}
	
	void dump() {
		cout << "id = " << id << " name = " << name << endl;
	}

private:
	int id{ -1 };			// ��ʹ�Ǿ͵س�ʼ�� ����Ҳ���ڻ��๹��֮��ų�ʼ�� 
	string name{ "default" };
	/*
		1.ʹ�þ͵س�ʼ���ķ�ʽ  ��ÿ�����캯�������ݳ�Ա�ĳ�ʼ��
		2.ʹ��placement newǿ���ڱ������ַ���ù��캯��(1.���캯������������  2.ʹ�ó�ʼ���б�����)
	*/

	void initSetup() {
		id += 1;
	}

};

int main()
{
	Info test("test");
	test.dump();

    return 0;
}

