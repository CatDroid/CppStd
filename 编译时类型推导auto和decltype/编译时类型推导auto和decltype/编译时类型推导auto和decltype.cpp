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
// 返回类型后置语法 语法形式为：auto 函数名(函数签名) -> 返回类型  
// void f(int); 就将被改写为： auto f(int) -> void;
// lambda	 [](int) -> void{}; 
// lambda表达式使用[] 符号，而普通函数则使用auto关键字
// 
// http://www.cnblogs.com/ThatsMyTiger/p/7085309.html
// http://blog.csdn.net/zwvista/article/details/5472096  
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

//  只用decltype而不用返回类型后置语法
template<class T, class U> 
decltype(*(T*)0 * *(U*)0) mul3(T x, U y) { 
	return x*y; 
} 

template<class T, class U> 
decltype(std::declval<T>()*std::declval<U>())  mul4(T x, U y) { 
	return x*y; 
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


	/*
		decltype推导四规则:

		如果e是一个‘没有带括号’的‘标记符表达式’或者‘类成员 访问表达式’，decltype（e）就是e所命名的实体的类型。
		此外，如果e是一个被重载的函数，则会导致编译错误(无法确定需要哪个重载函数实例)
		否则，假设e的类型是T，如果e是一个将亡值，那么decltype（e）为T&&
		否则，假设e的类型是T，如果e是一个左值，那么decltype（e）为T&。
		否则，假设e的类型是T，则decltype（e）为T

		'标记符'指的是除去'关键字、字面量'等编译器需要使用的标记之外的程序员自己定义的标记

		‘单个标记符’对应的表达式即为‘标记符表达式’ int arr[4]  arr为一个标记符表达式(可以decltype(arr))，而arr[3]+0不是
	
		字符串字面值常量是个左值，且是const左值，而非字符串字面值常量则是个右值

		“将亡值”概念的产生，是由右值引用的产生而引起的，将亡值与右值引用息息相关。
		所谓的将亡值表达式，就是下列表达式：
		1）返回"右值引用的函数"的调用表达式
		2）"转换为右值引用的转换函数"的调用表达式

		C++11标准库 模板类
		is_lvalue_reference 来判断 表达式是否为左值		结果1表示为左值，结果为0为非右值
		is_rvalue_reference 来判断 decltype推断结果是否为右值

	*/
	{
		int tempi = 10;
		decltype(tempi) test = 2;	// 推倒为int 没有括号-->标记符-->单个标记符--> 标记符表达式 
		decltype(tempi + 1) test2 = 2; // 推倒为int 
		decltype((tempi + 1)) test3 = 3;// 还是推倒为int 
		decltype(tempi) a;			// a推导为int：i是一个标记符表达式，根据推导规则1，类型被推导为int
		decltype((tempi)) b = tempi;// b推倒为int& 必须初始化：(i)为一个左值表达式，类型被推导为int&
		
		// 先声明 
		int i = 4;
		int arr[5] = { 0 };
		int *ptr = arr;
		struct S { double d; }s;
		void Overloaded(int);  // 函数内部可以声明函数 但是不能定义函数
		void Overloaded(char); // 重载的函数
		int && RvalRef();
		const bool Func(int);
		Person ppp;

		//规则一：推导为其类型( 都是没有带括号的 )
		decltype (arr) var1;	//	int		标记符表达式
		decltype (ptr) var2;	//	int *	标记符表达式
		decltype (s.d) var3;	//	double	成员访问表达式
		//decltype(ppp_person_type) var4;   成员访问表达式 私有成员是不可以的
		//decltype(Overloaded) var4;//重载函数。编译错误:无法确定需要哪个重载函数Overloaded实例

		//规则二：将亡值。推导为类型的右值引用(???? decltype推倒成右值引用: 或者本来就是 右值引用)
		decltype (RvalRef()) var5 = 1; // int&& 

		//规则三：左值，推导为类型的引用。
		decltype ((i))var6 = i;				//int&  带() 返回左值
		decltype (true ? 0 : 1) var7 = i;	//int&  条件表达式返回左值。
		decltype (++i) var8 = i;			//int&  ++i返回i的左值。
		decltype(arr[5]) var9 = i;			//int&. []操作返回左值
		decltype(*ptr)var10 = i;			//int&  *操作返回左值

		decltype("hello")var11 = "hello";	//const char(&)[6]  字符串字面常量为左值，且为const左值。

		//规则四：以上都不是，则推导为本类型
		decltype(1) var12;					//const int
		decltype(Func(1)) var13 = true;		//const bool
		decltype(i++) var14 = i;			//int	i++返回“右值” 但不是 “将亡值” 
		decltype(var5) var15 = 2;			//var5 本来就是 右值引用
	
		

		cout << "decltype(++i)是否左值引用?" << is_lvalue_reference<decltype(++i)>::value << endl;// 1
		// decltype(i++) 既不是右值引用 又不是左值引用  就是 int类型
		cout << "decltype(i++)是否左值引用?" << is_lvalue_reference<decltype(i++)>::value << endl;// 0
		cout << "decltype(i++)是否右值引用?" << is_rvalue_reference<decltype(i++)>::value << endl;// 0 
	}

    return 0;
}

