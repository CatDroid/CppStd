// ƫ�ػ���ȫ�ػ�.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <unordered_map>
#include <iostream>

using namespace std;

template <typename A >
class TemplateA {
private:
	A a;
public:
	TemplateA(A temp) :a(temp) {
		cout << a << endl;
	}
	~TemplateA() {

	}
};
// ���� template<>�Ļ�  ���� ! ��ʾר�û� ��Ҫ template<> 
template<>
class TemplateA<int> {

};

struct KEY  // unodered_map��ʹ���Զ�����
{
	int first;
	int second;
	int third;
	KEY(int f, int s, int t) : first(f), second(s), third(t) {}
};

namespace std
{
	template <>  // ֱ�������� ģ����
	struct hash<KEY>
	{
		std::size_t operator()(const KEY &key) const
		{
			using std::size_t;
			using std::hash;

			// Compute individual hash values for first,  
			// second and third and combine them using XOR  
			// and bit shifting:  

			return ((hash<int>()(key.first)
				^ (hash<int>()(key.second) << 1)) >> 1)
				^ (hash<int>()(key.third) << 1);
		}
	};
 /*
	template <>  
	struct equal<KEY,KEY,KEY>
	{
		bool operator()( KEY& begin,  KEY& end , KEY& right_end) const
		{
			return false;
		}
	};
 */
}



int main()
{
	TemplateA<float> test(1.2); // ����ֱ�ӵĻ� �Ͳ���Ҫtemplate<>

	
	vector<int> v1{ 0, 5, 10, 15, 20, 25 };// std::vector ���������� ����ʼ��
	vector<int> v2{ 0, 5, 10, 15, 20, 25 };
	vector<int> v3{ 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };

	bool b = equal(v1.begin(), v1.end(), v2.begin());
	cout << "v1 and v2 are equal: " << b << endl; // true, as expected

	b = equal(v1.begin(), v1.end(), v3.begin(), v3.end());
	cout << "v1 and v3 are equal with dual-range overload: " << b << endl; // false

    return 0;
}

