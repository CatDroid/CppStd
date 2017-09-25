// ���������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <algorithm> // sort 
#include <string>

using namespace std;

/*

C++�������ص�����������
��1�� "."����Ա�����������
��2��" .*"����Աָ������������
��3�� "::"�����������
��4��"siezof"�������������
��5�� " ?:"�������������

*/
class MyString {

private:
	uint8_t* buf;
	int32_t len;	// actual 
	int32_t cap;    // total  

public:
	MyString() :buf(NULL), len(0) {
		cout << "MyString() " << this << endl;
	}

	explicit MyString(const char* in_buf) {
		cout << "MyString(const char* in_buf) " << this << endl;
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
		cout << "MyString(const MyString& other) " << this << " other " << &other << endl;
		buf = new uint8_t[other.len];
		cap = len = other.len;
		memcpy((char*)buf, (const char*)other.buf, len);
	}

	~MyString() {
		cout << "~MyString() " << this << endl;
		delete[] buf; buf = NULL;
	}

	MyString& operator = (const MyString& other) {
		cout << "MyString& operator = (const MyString& other) " << this << " other " << &other << endl;
		if (this == &other) {
			return *this;
		}
		if (other.len > cap) {
			delete buf;
			buf = new uint8_t[other.len];
			cap = len = other.len;
		}
		else {
			len = other.len;
		}
		memset(buf, 0, cap);
		memcpy(buf, other.buf, len);
		return *this;
	}

	// ����ת����
	operator int() const {
		return  len; 
	}

	bool operator < (const MyString& other) const {
		cout << "operator <   " << this << " " << &other << endl;
		if (buf == NULL) return true;
		if (other.buf == NULL) return false;
		return strcmp((const char*)buf, (const char*)other.buf) < 0;
	}

	void dump() {
		printf("buf=%s\n", buf);
	}

	// friend  
	// ���ƻ�����ķ�װ�Ժ������ԣ�ʹ�÷ǳ�Ա�������Է������˽�г�Ա
	// ������������ز�������ʱ��ʹ�� 
	// operator <�����>(<����1>,<����2>) ���ȼ��� <����1><�����><����2> 
	// cout = operator<<(cout,x1); //  ��ʾ����
	// cout = cout<<x1;   //  OK  �ȼ���� 
	// >>��<<����������������
	// ��Ԫ����������ĳ�Ա���������������ڻ�������û������
	// ���������е���Ԫ����  ���������е���Ԫ����,����������ȫ����������. 
	friend ostream& operator<< (ostream& out, MyString& self);
};

// �����ຯ�� 
ostream& operator<< (ostream& out, MyString& self) {
	out << "��ֵַ��" << static_cast<void *>(self.buf) << " �ַ���: " << self.buf  <<  endl;
	return out;
}

int main()
{
	MyString arr[] = { MyString("abc"), MyString("789"),MyString("ABCDE123") };
	for (MyString& temp : arr) {
		cout << temp;
		cout << "���ȣ�" << int(temp) << endl;
	}
	return 0;
}
