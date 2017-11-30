// vector�������ƺ��ƶ����캯��.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <string>
#include <vector>
#include <memory>

using namespace std;



class VecBase {
private:
	int counter;
public:

	explicit VecBase(int temp) :counter(temp) {
		cout << "VecBase(int temp) = " << counter << " " << this << endl;
	}

	~VecBase() {
		cout << "~VecBase() " << this << endl;
	}

	VecBase(const VecBase& other) {
		cout << "VecBase(const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
	}

	VecBase(VecBase&& other) {
		cout << "VecBase(VecBase && other) " << this << " other " << &other << endl;
		counter = other.counter;
		other.counter = -1;
	}

	VecBase& operator = (const VecBase& other) {	// ������ֵ����
		cout << "opertor= (const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
		return *this;
	}

	VecBase& operator = (VecBase&& other) {			// �ƶ���ֵ����
		cout << "opertor = (  VecBase&& other) " << this << endl;
		counter = other.counter;
		other.counter = -1;
		return *this;
	}

};


int main()
{
	{
		cout << endl << endl;
		cout << "std::vector������ ���·����ڴ����� �ƶ����캯��!!" << endl;
		// vector<VecBase> list(4) ; // û���޲������캯�� ����������ʼ��vector����
		vector<VecBase> list;
		int cap = 0;
		for (int i = 0; i < 16; i++) {
			{
				list.push_back(VecBase(i));
			}
			if (cap != list.capacity()) {
				cap = list.capacity();
				cout << ">>--->>--->>--->>--->>--- after push_back capacity change : " << list.capacity() << endl;
			}

			// capacity��Զ�Ǵ��ڵ���size�ģ���size��capacity���ʱ�����������ʱvector������
			// ���ӵ�ǰ�ռ��50%(��һ�γ���)
			// 1  2     3    4    6     9     13    19      28       42     63     94     141 
			//    2/2=1           6/2=3             19/2=9  28/2=14 
			// Windows�ϵ�STLԴ�붼��P.J. Plaugerд��  ����ʱ����� �ƶ����캯�� 
			// g++ v6.4.0/clang++ v4.0.1 �� �ǰ� 1 2 4  8 16 32 ...   �����ķ�ʽ����  ����ʱ���õ��� �������캯��
		}
		cout << "std::vector --------------------------out of loop-- " << endl;
		cout << endl << endl;
		// ���·����ڴ�ʱ�� ����಻֧�� �ƶ����캯�� �ͻ���ÿ������캯��
	}

    return 0;
}

