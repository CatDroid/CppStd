// ������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

using namespace std;

class MyString {

private:
	uint8_t* buf;
	int32_t len;	// actual 
	int32_t cap ;   // total  

public:
	MyString():buf(NULL),len(0){

	}

	explicit MyString(const char* in_buf ) { // ���ι��캯��'����������ʾ��
		if (in_buf != NULL) {
			cap = len = strlen(in_buf) + 1;
			buf = new uint8_t[len];
			memcpy(buf, in_buf, len);
		}
		else {
			buf = NULL;
			cap = len = 0;
		}
	}

	MyString(const MyString& other) {
		buf = new uint8_t[other.len];
		cap = len = other.len;
		memcpy((char*)buf, (const char*)other.buf, len);
	}

	~MyString() {
		delete[] buf; buf = NULL; 
	}

	MyString& operator = (const MyString& other) {
		if (this == &other){
			return *this;
		}
		if ( other.len > cap) {
			delete buf;
			buf = new uint8_t[other.len];
			cap = len = other.len;
		}
		else {
			len = other.len;
		}
		memset(buf,  0,  cap);
		memcpy(buf, other.buf, len);
		return *this;
	}

	void dump() {
		printf("buf=%s\n" , buf);
	}

private:
	/*

	���������������캯�������������͸�ֵ����

	���캯��������һ������/���ƹ��캯���������ĳ�Ϊ��ͨ���캯��

	a.������ͬʱ��ʼ����
		MyString s1 = s2;	//	ע���ʱ��Ȼ����=�����ǲ��ǵ���operator=
							//	������ MyString s1 ; s1 = s2 ; // ���Ƹ�ֵ�����
		MyString s1(s2);
		
	
	b.���ú���ʱʹ�ð�ֵ���ݣ������ǰ����ô��ݣ�
		void f(MyString s);
		MyString s1;
		f(s1);
	
	c.ͨ��ֵ���ض���
		MyString f()
		{
			MyString s1;
			return s1;
		}

	explicit
		������ֹ�ɹ��캯���������ʽת��
		�����á�����ʵ�Ρ������õĹ��캯��  ������  ���β����͵��������͵�һ����ʽת��
		GoogleԼ������'�������Ĺ��캯��'����������ʾ�ģ�ֻ�м���������£��������캯�������Բ�����explicit

		MyString a3 ;
		a3 = "123"; // �� ��ʽת����MyString ---> �� MyString���Ƹ�ֵ�����

	����д '��ֵ����' �� '�������캯��'
	�ֲ��������ʹ�ñ��������ɵ�ȱʡ������
	��ô���ǿ���ֻ�轫 �������캯���͸�ֵ���� ����Ϊ˽�к��������ñ�д����
	*/
	//MyString& operator = (const MyString& other);
	//MyString(const MyString& other);
};

int main()
{

	MyString a1("hello world");
	MyString a2("i");
	a1.dump();
	a2.dump();

	a2 = a1;
	a2.dump();


	//MyString a3 = "implicit" ;
	//a3.dump();

    return 0;
}

