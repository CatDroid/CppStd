// 数组同时多个索引赋值.cpp : 定义控制台应用程序的入口点。
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
				if (*i + 1 > d.size()) { d.resize(*i + 1); }// 索引超出 增大空间
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
	vector<int> idx; // 辅助函数 用于记录index  array[{1,2,3}] = 2;  array[1] = 2 ;
	vector<int> d;
};

int main()
{
	{ // 数组 多个元素 赋同样的值
		Mydata d;
		d[{2, 3, 6}] = 8;
		d[{1, 4, 7, 8 }] = 2;
		d[0] = 1;
		d.print();
	}

    return 0;
}

