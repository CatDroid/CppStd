// 偏特化和全特化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <unordered_map>
#include <unordered_set>
#include <iostream>
#include <string>

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
// 不加 template<>的话  错误 ! 显示专用化 需要 template<> 
template<>
class TemplateA<int> {

};

// unodered_map 中 使用自定义类 使用特例化模板函数 方式 实现 hash 和 equal_to 
struct KEY 
{
	int first;
	int second;
	int third;
	KEY(int f, int s, int t) : first(f), second(s), third(t) {}
};

namespace std
{	//  模板类 std::hash 和  std::equal_to  特例化
	template <>  
	struct hash<KEY>
	{
		std::size_t operator()(const KEY &key) const{
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
 
	template<>
	struct equal_to < KEY > {
		bool operator()(const KEY& lhs, const KEY& rhs) const {
			if (lhs.first == rhs.first && lhs.second == rhs.second && lhs.third == rhs.third) {
				return true;
			}
			return false;
		}
	};
}


// 定义两个普通的c类型的函数，实现hash以及对象比较
// 需要使用 关键字 decltype 来减少显示声明它的类型
// decltype与auto关键字一样,用于进行编译时类型推导
struct Record
{
	string name;
	int val;
};

size_t RecordHash(const Record& rhs) {
	return hash<string>()(rhs.name) ^ hash<int>()(rhs.val);
}
bool RecordCmp(const Record& lhs, const Record& rhs) {
	return lhs.name == rhs.name && lhs.val == rhs.val;
}

unordered_set<Record,  decltype(&RecordHash), decltype(&RecordCmp)> records;

// 在main函数之前执行某个函数
struct RunBeforeMain
{
	RunBeforeMain() {
		cout << "RunBeforeMain " << endl;
		//records.insert({ "a", 100 });  
		//records.insert({ "b", 100 });
		//records.insert({ "c", 100 });
	}
};
static RunBeforeMain dummyObject;





int main()
{
	// 模板函数和模板类特例化需要template<> ,但是直接的话,就不需要template<>
	TemplateA<float> test(1.2); 

	// std::vector 可以用 列表初始化(list-initialization) 来初始化 和 使用 std::equal来判断两个容器是否一样 
	vector<int> v1{ 0, 5, 10, 15, 20, 25 };
	vector<int> v2{ 0, 5, 10, 15, 20, 25 };
	vector<int> v3{ 0, 5, 10, 15, 20, 25, 30, 35, 40, 45, 50 };
	bool b = equal(v1.begin(), v1.end(), v2.begin());
	cout << "v1 and v2 are equal: " << b << endl;							// true, as expected
	b = equal(v1.begin(), v1.end(), v3.begin(), v3.end());
	cout << "v1 and v3 are equal with dual-range overload: " << b << endl;	// false

	 
	// 使用模板函数 特例化 实现自定义类型下的unordered_map  hash 和 equal_to 
	std::unordered_map<KEY, string> umap;
	umap.insert(  std::pair<KEY, string>(KEY(1, 2, 3), string("123")  ) );
	umap.insert(  std::pair<KEY, string>(KEY(4, 5, 6), string("456")  ) );
	umap.insert(  std::pair<KEY, string>(KEY(7, 8, 9), string("789")  ) );
	umap.insert(  std::pair<KEY, string>(KEY(0, 1, 2), string("012")  ) );

	for (std::unordered_map<KEY, string>::iterator itor = umap.begin();itor != umap.end(); itor++) {
		printf("umap : key[%d %d %d]:%s\n", itor->first.first, itor->first.second, itor->first.third , itor->second.c_str() );
	}
 
	// C++11新特性之列表初始化  unordered_map 
	unordered_map<KEY, string > umap2 =  {
		{ { 01, 02, 03 }, "one" },
		{ { 11, 12, 13 }, "two" },
		{ { 21, 22, 23 }, "three" },
	};

	for (std::unordered_map<KEY, string>::iterator itor = umap2.begin(); itor != umap2.end(); itor++) {
		printf("umap2 : key[%d %d %d]:%s\n", itor->first.first, itor->first.second, itor->first.third, itor->second.c_str());
	}

	KEY key(11, 12, 13);
	std::unordered_map<KEY, string>::iterator it = umap2.find(key);
	if (it != umap2.end()) {
		cout << "Find Key in unordered_map : "<< it->second << endl;
	}
	else {
		cout << "Find Key Fail in unordered_map " << endl;
	}

	// 使用自定义C函数 实现hash和equal_to 
	//for (std::unordered_set<Record>::iterator itor = records.begin(); itor != records.end(); itor++) {
	//	//(*itor); // 返回 const Record& 
	//	printf("uset : %s %d \n" , (*itor).name.c_str() , (*itor).val );
	//}

    return 0;
}

