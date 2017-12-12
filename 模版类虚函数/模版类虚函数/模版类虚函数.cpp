// ģ�����麯��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
using namespace std;

template<class Item, class Self>
class IIterator { // ģ�����д����麯��
public:
	virtual ~IIterator() {};
	virtual Self operator ++ () = 0;
	virtual const Self operator ++ (int) = 0;
	virtual bool operator == (const Self& other) = 0; 
	virtual Item& operator * () = 0;
};

class MyClass : public IIterator<int, MyClass>
{
private:
	int mNum;
public:
	explicit MyClass(int num) :mNum(num) {
		cout << "MyClass(TYPE num)"<< endl;  
	}

	virtual ~MyClass() { 
		cout << " ~MyClass()" << endl; 
	}

	// �ڶ��������������������Ǻ��������⣬��û���������壬����������п���.
	// Ϊ������ǰ���� operator++()��ʾǰ�������� operator++(int)������

	// ++i
	// ��Ϊ����ǰ�����ı�׼����,Ӧ��֧��"++++a"���﷨,��������ǰ������Ӧ���Ƕ�a������������,�������A����,�ǵڶ���ǰ�������õ�����ʱ�����ǰ��������
	virtual MyClass operator ++ () override  {
		mNum++;
		return MyClass(mNum);
	}
	
	// i++ 
	// ������Ӧ�÷���"const Complex".����Է�ֹ����"a++++"���÷�
	virtual const MyClass operator ++ (int ) override {
		int old = mNum; 
		mNum++;
		return MyClass(old);
	}

 
	virtual bool operator == (const MyClass & other) override {
		if (mNum == other.mNum) return true;
		return false;
	}

	virtual int& operator* () {
		return mNum;
	}

};



int main()
{

	MyClass a(1);
	MyClass b(1);

	if (a == b) {
		cout << "equal" << endl; 
	}
	else {
		cout << "not equal" << endl; 
	}

	*b = 3;
	b++;		// 4
	++++b;		// 5 

	cout << *b << endl; 

    return 0;
}

