// ����ͬʱ���������ֵ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>
#include <vector>
using namespace std;

class Mydata {
public:
	Mydata& operator [] (std::initializer_list<int> l)
	{
		idx.clear();
		for (auto i = l.begin(); i != l.end(); ++i) {
			idx.push_back(*i);
		}
		return *this;
	}
	int& operator[](int i) {
		if (i < d.size()) {
			return d[i];
		}
		throw string("out of range");
	}

	Mydata& operator = (int v)
	{
		if (!idx.empty()) {
			for (auto i = idx.begin(); i != idx.end(); i++) {
				if (*i + 1 > d.size()) { d.resize(*i + 1); }// �������� ����ռ�
				d[*i] = v;
			}
		}
		return *this;
	}

	void print() {
		for (auto i = d.begin(); i != d.end(); ++i) {
			cout << *i << " ";
		}
		cout << endl;
	}

private:
	vector<int> idx; // �������� ���ڼ�¼index  array[{1,2,3}] = 2;  array[1] = 2 ;
	vector<int> d;
};

int main()
{
	{ // ���� ���Ԫ�� ��ͬ����ֵ
		Mydata d;
		d[{2, 3, 6}] = 8;
		d[{1, 4, 7, 8 }] = 2;
		d[0] = 1;
		d.print();
	}

    return 0;
}

