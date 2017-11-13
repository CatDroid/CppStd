// map_unorder_map.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include<string>  
#include<iostream>  
#include<unordered_map>  
#include<map>
using namespace std;

// һ����hash value ���ǲ���� 
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

//	Hash����
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


//	��Ⱥ���
class PersonKey
{
public:
	bool operator() (const Person &lhs, const Person &rhs) const
	{
		return lhs.name == rhs.name && lhs.age == rhs.age;
	}
};


class Cat		// ����std::map 
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
		Person p5("Tom4", 24); // ��ȫ��� Ҳ���� hash_value �� ==  ������insertʱ�����unorder_map 
#endif 
 

		m.insert(make_pair(p3, 103));
		m.insert(umap::value_type(p4, 104)); // 1. value_type ����typedef   std::pair<Person,int>
		m.insert(umap::value_type(p5, 105)); // 2. insert����ÿ������캯��
		m.insert(umap::value_type(p1, 101)); // 3. insert key��hashֵ��== �����һ���Ļ������Ḳ��ԭ��key��Ӧ��value
		m.insert(umap::value_type(p2, 102));

		for (umap::iterator iter = m.begin(); iter != m.end(); iter++) {
			cout << iter->first.name << "\t" << iter->first.age << "\t" << iter->second << "\tthis = " << &iter->first << endl;
		}

#if SAME_HASH_VALUE_BUT_NOT_EQUAL
		cout << "after m[p5] = 555 " << endl;		// 4. ����keyʱ�� ����key��hash_value �ҵ���Ӧbulket(Ͱ),Ȼ����Ͱ�� operator== �ҵ���Ӧ��value 
		m[p5] = 555;
#else
		cout << "after m[p5] = 105 " << endl;
		m[p5] = 105;								//  4. ����ͨ��map[key]=value���޸�key��Ӧ��ֵ
#endif 

		for (umap::iterator iter = m.begin(); iter != m.end(); iter++) {
			cout << iter->first.name << "\t" << iter->first.age << "\t" << iter->second << "\tthis = " << &iter->first << endl;
		} 
		//	unordered_map��������г�ͻ�Ŀ��ܣ�����ÿһ��key�� hash value ��Ӧһ��bucket(std::listʵ��)
		//	unordered_map��ÿ����hash value����Ӧһ��bucket������һ����key����Ӧһ��bucket
	}

	{
		std::map<Cat, int> cat_map;
		Cat cat1("Cat1", 31);
		Cat cat2("Cat2", 32);
		Cat cat3("Cat3", 33);
		Cat cat4("Cat4", 34);
		Cat cat5("Cat5", 35);
		cat_map.insert(make_pair(cat3, 203));		//	1. std::map ����ʱ�� ����� operator< ��ѭ�����
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
