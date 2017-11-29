// 编译时类型推导auto和decltype.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include <unordered_set>
#include <string>
 
using namespace std;

// 定义两个普通的c类型的函数，实现hash以及对象比较
// 需要使用 关键字 decltype 来显示声明它的类型
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

unordered_set<Record, decltype(&RecordHash), decltype(&RecordCmp)/*这里要给定函数类型*/> 
	records(
		0,
		RecordHash, RecordCmp // 这里要给定函数指针
	);

// 在main函数之前执行某个函数
struct RunBeforeMain
{
	RunBeforeMain() {
		cout << "RunBeforeMain " << endl;
		cout << "unordered_set before insert " << records.size() << endl;
		records.insert({ "a", 100 });
		records.insert({ "b", 100 });
		records.insert({ "c", 100 });
		cout << "unordered_set after  insert " << records.size() << endl;
	}
};
static RunBeforeMain dummyObject;

// 返回值语法
// auto+decltype 追踪函数的返回值类型
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y) -> decltype(x*y) 
{
	return x*y;
}

class Person
{
public:
	enum PersonType { ADULT, CHILD, SENIOR };
	void setPersonType(PersonType person_type);
	PersonType getPersonType();
private:
	PersonType _person_type;
};

void Person::setPersonType(PersonType person_type){
	_person_type = person_type;
}

//PersonType Person::getPersonType()  // ERROR编译不通过 返回值类型 必须加上 Person::
//Person::PersonType Person::getPersonType(){
//	return _person_type;
//}
// 新的返回值语法：因为函数的返回值出现在函数的最后，而不是前面，你不需要补全类作用域
auto Person::getPersonType() -> PersonType
{
	return _person_type;
}

// decltype + 新的返回值语法
template <typename BuiltType, typename Builder>
auto makeAndProcessObject(const Builder& builder)  -> decltype(builder.makeObject()) // 引用了函数参数
{
	BuiltType val = builder.makeObject();
	return val;
}


int main()
{

	// 不使用关键字decltype,直接给函数指针类型 
	typedef unordered_set<Record,  size_t(*)(const Record& rhs), bool(*)(const Record& lhs, const Record& rhs)> RecordSet;
	for (RecordSet::iterator itor = records.begin(); itor != records.end(); itor++) {
		printf("unordered_set : %s %d \n", (*itor).name.c_str(), (*itor).val);//(*itor); // 返回 const Record& 
	}

	cout << "编译时类型推导， auto关键字， decltype关键字" << endl;

	/*
		decltype与auto关键字一样,用于进行编译时类型推导
	
		在泛型编程中，我们更需要的是编译时就要确定类型
		
		编译时类型推导的出现正是为了泛型编程，在非泛型编程中，我们的类型都是确定的，根本不需要再进行推导
		
		编译时类型推导， auto关键字， decltype关键字

		auto类型推导，从‘变量声明’的'初始化表达式' ,获得变量的类型

		decltype类型推导，以一个普通表达式作为参数，返回该表达式的类型，而且decltype并不会对表达式进行求值

		用途：
		a.推导出表达式类型 
		b.与using/typedef合用，用于定义类型 
		c.重用匿名类型 
		d.泛型编程中结合auto，用于追踪函数的返回值类型

	*/
	int i = 4;
	decltype(i+4) a = 5 ; //推导结果为int。a的类型为int
	printf("%d \n" , a );


	cout << "与typedef合用，用于定义类型" << endl;
	typedef decltype(records.begin()) RecordSetType;
	for (RecordSetType itor = records.begin(); itor != records.end(); itor++){
		cout << " unordered_set : " << itor->name << " " << itor->val << endl;
	}

	struct		// 匿名结构体类型
	{
		int d;
		double b;
	}anon_s;	// 变量
	anon_s.d = 2;
	anon_s.b = 3.3;

	decltype(anon_s) other_val  ; //  匿名类型 在其他位置声明变量
	other_val.d = 5;
	other_val.b = 6.6;

	printf("decltype重用匿名类型 [%d %f] [%d %f]\n",
								anon_s.d , anon_s.b, other_val.d, other_val.b );
	
	// 泛型编程中结合auto，用于追踪函数的返回值类型
	auto ret = multiply(2.0, 3.0);
    return 0;
}

