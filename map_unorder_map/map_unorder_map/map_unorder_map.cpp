// map_unorder_map.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include<string>  
#include<iostream>  
#include<unordered_map>  
#include<map>
using namespace std;

// 一样的hash value 但是不相等 
//#define SAME_HASH_VALUE_BUT_NOT_EQUAL	1 

class Person
{
public:
	string name;
	int age;

	Person(string name, int age)
	{
		cout << "Person:" << this << " " << name << " " << age  << endl;
		this->name = name;
		this->age = age;
	}

	Person(const Person& other) {
		this->name = other.name;
		this->age = other.age;
		cout << "Person(other):" << this << " " << name << " " << age << endl;
	}

	bool operator== (const Person& p) const
	{
		return name == p.name && age == p.age;
	}

	void dump() const {
		cout << this << endl;
	}

	~Person() {
		cout << "~Person() " << this  << endl;;
	}
	
};


template<class T>
inline void hash_combine(std::size_t& seed, const T& val){

	seed ^= std::hash<T>()(val)  + 0x9e3779b9 + (seed << 6) + (seed >> 2);
}

//	Hash函数
class PersonHash
{
public:
	std::size_t operator()(const Person& p) const
	{	
#if SAME_HASH_VALUE_BUT_NOT_EQUAL
		return p.age;
#else 
		size_t seed = 0;
		hash_combine(seed, std::hash_value(p.name));
		hash_combine(seed, std::hash_value(p.age));
		return seed;
#endif 
		
	}
};


//	相等函数
class PersonKey
{
public:
	bool operator() (const Person &lhs, const Person &rhs) const
	{
		return lhs.name == rhs.name && lhs.age == rhs.age;
	}
};


class Cat		// 测试std::map 
{
public:
	string name;
	int age;
	Cat(string name, int age)
	{
		this->name = name;
		this->age = age;
	}

	bool operator < (const Cat& p) const
	{
		return this->age < p.age;
	}
};



int main()
{
	{
		typedef std::unordered_map<Person, int, PersonHash, PersonKey > umap;
		umap m;
		Person p1("Tom1", 21);
		Person p2("Tom2", 22);
		Person p3("Tom3", 23);
		Person p4("Tom4", 24);
#if SAME_HASH_VALUE_BUT_NOT_EQUAL
		Person p5("Tom5", 24);
#else
		Person p5("Tom4", 24); // 完全相等 也就是 hash_value 和 ==  不会再insert时候加入unorder_map 
#endif 
 

		m.insert(make_pair(p3, 103));
		m.insert(umap::value_type(p4, 104)); // 1. value_type 就是typedef   std::pair<Person,int>
		m.insert(umap::value_type(p5, 105)); // 2. insert会调用拷贝构造函数
		m.insert(umap::value_type(p1, 101)); // 3. insert key的hash值和== 如果都一样的话，不会覆盖原来key对应的value
		m.insert(umap::value_type(p2, 102));

		for (umap::iterator iter = m.begin(); iter != m.end(); iter++) {
			cout << iter->first.name << "\t" << iter->first.age << "\t" << iter->second << "\tthis = " << &iter->first << endl;
		}

#if SAME_HASH_VALUE_BUT_NOT_EQUAL
		cout << "after m[p5] = 555 " << endl;		// 4. 搜索key时候 先求key的hash_value 找到对应bulket(桶),然后在桶中 operator== 找到对应的value 
		m[p5] = 555;
#else
		cout << "after m[p5] = 105 " << endl;
		m[p5] = 105;								//  4. 可以通过map[key]=value来修改key对应的值
#endif 

		for (umap::iterator iter = m.begin(); iter != m.end(); iter++) {
			cout << iter->first.name << "\t" << iter->first.age << "\t" << iter->second << "\tthis = " << &iter->first << endl;
		} 
		//	unordered_map本身可能有冲突的可能，所以每一个key的 hash value 对应一个bucket(std::list实现)
		//	unordered_map是每个“hash value”对应一个bucket，不是一个“key”对应一个bucket
	}

	{
		std::map<Cat, int> cat_map;
		Cat cat1("Cat1", 31);
		Cat cat2("Cat2", 32);
		Cat cat3("Cat3", 33);
		Cat cat4("Cat4", 34);
		Cat cat5("Cat5", 35);
		cat_map.insert(make_pair(cat3, 203));		//	1. std::map 迭代时候 会根据 operator< 按循序迭代
		cat_map.insert(make_pair(cat4, 204));
		cat_map.insert(make_pair(cat5, 205));
		cat_map.insert(make_pair(cat1, 201));
		cat_map.insert(make_pair(cat2, 202));

		for (map<Cat, int>::iterator itor = cat_map.begin(); itor != cat_map.end(); itor++) {
			cout << itor->first.name << "\t" << itor->first.age << endl;
		}

	}
	
	return 0;
}
