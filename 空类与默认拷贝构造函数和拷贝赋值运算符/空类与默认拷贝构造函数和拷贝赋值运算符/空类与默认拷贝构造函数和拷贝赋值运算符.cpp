// ������Ĭ�Ͽ������캯���Ϳ�����ֵ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"


#include <iostream>

using namespace std;

class Base {
public:
	Base() {
		cout << "Base " << this << endl;
	}
	virtual ~Base() {
		cout << "~Base " << this << endl;
	}
	virtual void run() {
		cout << "Base run " << this << endl;
	}

};

class Derive : public Base {
public:
	 Derive() {
		cout << "Derive " << this << endl;
		run();
		/*
		������õ��Ǳ�����߻��� �е�run()
		������಻overrideʵ��run() ��ô�ͻ���û����
		*/
	}
	virtual ~Derive() {
		cout << "~Derive " << this << endl;
	}
	virtual void run() {
		cout << "Derive run " << this << endl;
	}
};


class Derive1 : public Derive {
public:
	Derive1(){
		cout << "Derive1 " << this << endl;
	}
	virtual ~Derive1() {
		cout << "~Derive1 " << this << endl;
	}

	virtual void run() {
		cout << "Derive1 run " << this << endl;
	}
};

class Empty {
public  :
	const int CONSTANT; // ��const��Ա�������ó�Ա �����Զ��幹�캯�� û��Ĭ���޲���/�������캯��
 
};





int main()
{


	// Base* b = new Derive1();
	// delete b;

	// Empty* empty = new Empty();
	// delete empty;

	return 0;


}


/*


���ࣺ
	1. һ���յ�class��C++�������������Ͳ���Ϊ��, ���������Զ�Ϊ������һ��Ĭ�Ϲ��캯����һ������Ĭ�Ϲ��캯����һ��Ĭ�Ͽ�����ֵ�������һ��Ĭ����������
	2. ֻ�е�����Ҫ�õ���Щ������ʱ�򣬱������Ż�ȥ��������
	3. ������Щ��������inline��public��

�ο���
class Empty
{
	public:
		Empty();				// ȱʡ���캯��
		Empty( const Empty& );  // �������캯��
		~Empty();				// ��������
		Empty& operator=( const Empty& );	// ��ֵ�����
		Empty* operator&();					// ȡַ�����
		const Empty* operator&() const;		// ȡַ����� const
};


Ĭ�Ϲ��캯����Ĭ�Ͽ�����ֵ�����:

1. ����Ĭ�Ϲ��캯����Ĭ�Ͽ�����ֵ����� ֻ�ǵ�������Դ�����ÿһ���Ǿ�̬��Ա����������Ŀ���У�bitwise copy��

2. ��Ĭ�Ͽ�����ֵ�������ֻ�������ɵġ�����Ϸ������ҡ��л���֤�������������ʱ���Ż����ɡ�
	���˵��������������һ�����ں����ó�Ա�����ߡ��ں�const��Ա��������֧�ָ�ֵ������
	�ͱ��붨���Լ���Ĭ�Ͽ�����ֵ�������
	(��ΪC++��������'�ڹ��캯����ʼ���б�֮��'���ø�ָ��ͬ�Ķ���Ҳ���������const��Ա)
	(Ĭ�ϵġ��������캯���� Ҳ�� �����const��Ա�����ó�Ա  �������������Զ�����  )

3. �����ཫ�Լ���Ĭ�Ͽ�����ֵ���������Ϊprivateʱ������Ͳ�������Լ��ĵ�Ĭ�Ͽ�����ֵ�������
	(��Ϊ���������������Ĭ�Ͽ�����ֵ�������
	��������ȥ���û����Ĭ�Ͽ�����ֵ�����ȥ�������Ĳ��֣����ҵ��ǣ���û��Ȩ��)


4. ����Ա��������Ϊprivate���ҹ��ⲻʵ������
	(Ϊ�˲��ر������Զ��ṩ�ļ��ܣ��ɽ���Ӧ�ĳ�Ա��������Ϊprivate���Ҳ���ʵ��)

	�ο�д��:
	
	class Uncopybale {
	protected:
		Uncopyable() {}
		~Uncopyable() {}
	private:
		Ucopyable(const Uncopyable&);				// ***
		Uncopyable& operator=(const Uncopyable&);	// ***
	};
	
	Ϊ����ֹ���󱻿���������Ψһ��Ҫ���ľ��Ǽ̳�Uncopyable
	Boost�ṩ��noncopyable��Ҳ�����ƵĹ���

*/

