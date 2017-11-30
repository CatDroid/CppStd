// 列表初始化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>

using namespace std;

int main()
{
	// 列表初始化 
	vector<int> v1{ 0, 5, 10, 15, 20, 25 };
	vector<int> v2{ 0, 5, 10, 15, 20, 25 };
	vector<int> v3{ 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
	vector<int> v4{ 0, 5, 10, 15, 20 };

	// equal比较算法  当且仅当第一个序列和第二个序列相同，返回true，否则返回false
	// 不同范围的  如果不指定第二个序列的end,那么必须第一个比第二个序列更长或相等,在第一个序列长度范围内都相等,返回ture
	//             如果指定第二个序列的end,那么就要长度相等和个个元素相等
	bool b = equal(v1.begin(), v1.end(), v2.begin());
	cout << "v1 and v2 are equal: " << b << endl;// true, as expected

	b = equal(v1.begin(), v1.end(), v3.begin());
	cout << "v1 and v3 are equal: " << b << endl; // true, surprisingly

	b = equal(v1.begin(), v1.end(), v3.begin(), v3.end());
	cout << "v1 and v3 are equal with dual-range overload: " << b << endl;// false

	//b = equal(v1.begin(), v1.end(), v4.begin()  );  // crash !!
	//cout << "v1 and v4 are equal with dual-range overload: " << b << endl; 

    return 0;
}

