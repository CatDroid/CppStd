// 列表初始化.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>

#include <map>
#include <list>
#include <vector>
#include <string>

using namespace std;

class Foo
{
public:
	int a;
	float b;
	float c;
public:
	Foo() :a(0), b(0), c(0) { cout << "Foo的无参构造函数" << endl; }
	/*explicit*/ Foo(int temp) :a(temp), b(0), c(0) { cout << "Foo的单参构造函数" << endl;  }
	/*explicit*/ Foo(float t1, float t2):a(0),b(t1),c(t2) { cout << "Foo的双参构造函数" << endl;  }
	// 要使用 initialzer_list , 必须支持隐式构造 

	Foo(Foo&& rhs) :a(rhs.a), b(rhs.b), c(rhs.c) { // std::vector容器需要移动构造函数
		rhs.a = 0; rhs.b = 0; rhs.c = 0;
		cout << "Foo的移动构造函数 "<< endl;
	}
public:
//private:
	Foo(const Foo & other ):a(other.a),b(other.b),c(other.c) {
		cout << "Foo的拷贝构造函数 " << endl;
	}
 

	/*
	用std::initialzer_list将类改写，类Foo也具有了接受可变长参数的能力
	'固定数目的'数据成员来说使用std::initialzer_list来改写后，
	如果'列表初始化的参数' 刚好是3个则数据成员完全初始化，如果列表初始化的个数小于3个则未给予的值是一个随机值

	虽然std::initialzer_list可以改写我们自定义的类
	但是对于用于固定的数据成员的类来说这种改写意义不大
	除非 如果我们自定义的类也是一个容器类
	*/
#if 0 
	Foo(std::initializer_list<float> list){
		cout << "initializer_list构造函数 " << endl;
		auto it = list.begin(); // const int*
		if (it == list.end()) cout << "initializer_list构造函数 a end " << endl; 
		a = *it++;
		if (it == list.end()) cout << "initializer_list构造函数 b end " << endl;
		b = *it++;
		if (it == list.end()) cout << "initializer_list构造函数 c end " << endl;
		c = *it++;

	}
#endif 

};


class FooVec
{
private:
	std::vector<int> m_vec;
public:
	/*
		自定义的容器类，和STL中的容器类，一样拥有“接受可变长”“相同数据类型”的数据的能力
		注意数据类型必须相同
	*/
	FooVec(std::initializer_list<int> list) // 数据类型必须是int 
	{
		cout << "initializer_list构造函数 " << endl;
		for (auto it = list.begin(); it != list.end(); it++)
			m_vec.push_back(*it);
	}
};



class MyElem{
private:
	int counter;
public:

	explicit MyElem(int temp) :counter(temp) {
		cout << "VecBase(int temp) = " << counter << " " << this << endl;
	}

	~MyElem() {
		cout << "~VecBase() " << this << endl;
	}

	MyElem(const MyElem& other) {
		cout << "VecBase(const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
	}

	MyElem(MyElem&& other) {
		cout << "VecBase(VecBase && other) " << this << " other " << &other << endl;
		counter = other.counter;
		other.counter = -1;
	}

	MyElem& operator = (const MyElem& other) {	// 拷贝赋值函数
		cout << "opertor= (const VecBase& other) " << this << " other " << &other << endl;
		counter = other.counter;
		return *this;
	}

	MyElem& operator = (MyElem&& other) {	    // 移动赋值函数
		cout << "opertor = (  VecBase&& other) " << this << endl;
		counter = other.counter;
		other.counter = -1;
		return *this;
	}

	int get() const {
		return counter;
	}
};


class MyVec
{
private:
	std::vector<MyElem> m_vec;
public:
	/*
	自定义的容器类，和STL中的容器类，一样拥有“接受可变长”“相同数据类型”的数据的能力
	注意数据类型必须相同
	*/
	MyVec(std::initializer_list<MyElem> list) // 数据类型必须是int 
	{
		cout << "initializer_list构造函数 " << endl;
		for (auto it = list.begin(); it != list.end(); it++) {
			cout << " -----*------ " << endl;
			m_vec.push_back(  (*it) );  // 返回的是 const _Elem *
			cout << " -----^----- "<< endl;
			// 第一次push进入 是用 拷贝构造(因为是const _Elem* )
			// 重新分配内存 使用 移动构造 
		}
			
	}
};

// 相同类型 变长参数
void func(std::initializer_list<MyElem> list)
{
	for (auto it = list.begin(); it != list.end(); it++)
	{// const MyElem* it 
		cout << it->get() << endl; // 因为指针是const的 所以get必须 限定const 才能调用
	}

}

// initialzer_list<T>保存的是T类型的引用，并不对T类型的数据进行拷贝
// 注意变量的生存期
std::initializer_list<int> initializer_out_of_range(void){
	int a = 2, b = 3;
	//return{ new int(2), new int(3) };
	//return { 2 ,3 };
	return{ a, b }; // 返回的 std::initializer_list 实例 内部包含指针指向 数据
}


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


	// C++98/03中  只能对 普通数组 和 
	// POD(plain old data 简单来说就是可以用memcpy复制的对象 )类型 可以使用"列表初始化"
	int arr[] = { 1,2,3 };	// 数组 初始化
	struct A
	{
		int x;
		int y;
	}a = { 1,2 };			// 结构体变量 初始化

	// C++11中为了统一初始化方式,提出了列表初始化(list-initialization),可以作用于任何类型对象的初始化

	Foo a1(123);	// 调用Foo(int)构造函数初始化  
	Foo a2 = 123;	// 隐式调用Foo(int)构造函数
	//Foo a3 = a2;	// ERROR Foo的拷贝构造函数声明为私有的 

	Foo a3 = { 123 }; // 列表初始化  
	Foo a4{ 123 };	  // 列表初始化  都是调用Foo(int)构造函数

	int a5 = { 3 };	  // C++98/03所不具备的，是C++11新增的写法
	int a6 { 3 };
	double af = double{ 12.12 };

	// 列表初始化方法 适用于用new操作等圆括号进行初始化
	int* a7  = new int(3);
	int* a8  = new int{3};	// 都是值为3的int 
	int* a9  = new int[5]();// 都初始化为0
	int* a10 = new int[5];	// 元素值不确定
	int * a12 = new int[5]{ 1, 2, 3 }; // C++11可以在创建数组时候初始化元素 , 其他初始化为0 

	printf("new int(3)	%d 0x%x 0x%x 0x%x 0x%x \n", a7[0], a7[1], a7[2], a7[3], a7[4]);
	printf("new int{3}	%d 0x%x 0x%x 0x%x 0x%x \n", a8[0], a8[1], a8[2], a8[3], a8[4]);
	printf("new int[5]()	%d %d %d %d %d \n",			a9[0],  a9[1],  a9[2],  a9[3],  a9[4]);
	printf("new int[5]	0x%x 0x%x 0x%x 0x%x 0x%x \n",a10[0], a10[1], a10[2], a10[3], a10[4]);
	printf("new int[5]{1,2,3} %d %d %d %d %d \n",		a12[0], a12[1], a12[2], a12[3], a12[4]);

	// 复杂类型数组 的 列表初始化
	Foo* foo_list = new Foo[3]{ {11.0,1.0},{22.0,1.0} }; // 仅当类存在无参构造函数 列表初始化才能没有
	cout << "foo_list: " << endl;
	printf("[0] = %d %f %f\n", foo_list[0].a, foo_list[0].b, foo_list[0].c);
	printf("[1] = %d %f %f\n", foo_list[1].a, foo_list[1].b, foo_list[1].c);
	printf("[2] = %d %f %f\n", foo_list[2].a, foo_list[2].b, foo_list[2].c);
	

	/* 普通的POD类型 和 聚合体 aggregate 
		C++中关于类是否是一个聚合体的定义
			a.无用户自定义构造函数 
			b.无私有private或者受保护protected的非静态数据成员
			c.无基类
			d.无虚函数
			e.无{}和=直接初始化的非静态数据成员  

		非聚合体的类型 列表初始化是给到构造函数,所以必须有对应参数的构造函数
						否则列表初始化只能是空的,调用无参构造函数
	*/
	struct A1{
		int x;
		int y;
	}A1a1 = { 123, 321 };// 相当于直接memcopy到结构体
	// .x = 123 .y = 321  
	struct B1{
		int x;
		int y;
		B1(int, int) :x(0), y(0) { cout <<"B1(int, int) call" << endl; }
		// 成员初始化列表
	}B1b1 = { 123, 321 }; // 列表初始化给到构造函数 
	// .x = 0  .y = 0 
	struct C1 {
	protected:
		int z;
	public:
		int x;
		int y;
	} C1c1 = {};// { 1, 2, 4 }; 有保护或私有的非static成员,列表初始化会调用构造函数,必须有对应的构造函数
	// .x=0 .y=0

	struct D1 {
		int x;
		int y;
		virtual void vfun() {};// 类含有基类或者虚函数,必须要有对应构造函数,才能有列表初始化,否则列表初始化只能是空的,调用无参构造函数
		D1(int t1,int t2):x(t1),y(t2){}
	};
	D1 D1d1{ 123,456 };   // 调用(int,int)构造函数 

	struct E1 {
		int x;
		int y = 5;		 //  {}或者=直接初始化的非静态数据成员
		//E1(int t1 , int t2):x(t1),y(t2){} // 没有这个构造函数 { 2,3 }列表初始化就编译错误
	};
	//E1 E1e1{ 2,3 };		 //  无法从"inializer list" 转换为 main::E1 

	printf("普通的POD类型                       .x %d .y %d\n", A1a1.x, A1a1.y );
	printf("非聚合体的类 要有对应 构造函数      .x %d .y %d\n", B1b1.x, B1b1.y);
	printf("保护或私有的非static成员 列表初始化 .x %d .y %d\n", C1c1.x, C1c1.y);
	printf("类含有基类或者虚函数     列表初始化 .x %d .y %d\n", D1d1.x, D1d1.y);
	printf("类中 非静态数据成员 直接 使用=初始化 \n");


	// "自定义构造函数+成员初始化列表" 的方式解决了上述类是非聚合类型使用列表初始化的限制


	struct NonAggregate  // 非聚类体类型
	{
		int x;
		int y = 5;				// 非static成员 使用=直接初始化 
		virtual void func() {}  // 虚函数
	private:
		int z;					// private/protected的成员
	public:
		NonAggregate(int i, int j, int k) :x(i), y(j), z(k)  // 自定义构造函数
		{ 
			cout << "NonAggregate Construct " << endl; 
		}
	};
	NonAggregate non_a{ 123,456,789 };
	cout << "非聚类体 自定义构造函数+成员初始化列表 : " << non_a.x << " " << non_a.y << endl;


	// 在C++11中，对于任意的STL容器，都与 没有显式指定长度的数组 一样的初始化能力
	int arr_no_length[] = { 1, 2, 3, 4, 5 };
	std::map < int, int >  map_t{ { 1, 2 },{ 3, 4 },{ 5, 6 },{ 7, 8 } };
	std::list<std::string> list_str{ "hello", "world", "china" };
	std::vector<double>    vec_d{ 0.0,0.1,0.2,0.3, 0.4, 0.5 };

	//std::vector<Foo>  vec_foo{ 0.0,0.1,0.2,0.3,0.4,0.5 };	// 无法从'double'转换到'Foo' 需要收缩转换
	//std::vector<Foo>  vec_foo{ 0, 1/*隐式构造*/ , 2 , 3 , 4 , 5  };			// 单参数构造函数 (必须支持隐式构造)	 
	//std::vector<Foo>  vec_foo{ {0}, {1} , {2} , {3} , {4} , {5} };	// 单参数(或者是initializer_list<float>的构造) 
	std::vector<Foo>  vec_foo{ { 1.0f, 66.6f }/*隐式构造*/,{ 2.0f, 66.6f } ,{ 3.0f, 66.6f } ,{ 4.0f, 66.6f } };
	// 无法访问private成员 Foo(const Foo &); 不会使用 Foo(Foo&&) 构造 ， 因为std::initializer_list.begin返回的是const Foo*  
	// 
	// vs2015/clang++ 都是 双参构造函数(或者是initializer_list<float>的构造 不能是<int>) + 拷贝构造函数 

	for (std::vector<Foo>::iterator itor = vec_foo.begin(); itor < vec_foo.end(); itor++) {
		const Foo& thing = (*itor);
		cout << "thing [" << thing.a << " " << thing.b << " " << thing.c << " ]" << endl;
	}

	// 使用'列表初始化方法'是将'initializer-list'转换成对应的类类型
	
	// STL容器 跟 数组一样 可以 填入 任何需要的任何长度的同类型的数据
	// 而我们自定义的Foo类型，却不具备这种能力，只能按照构造函数的初始化列表顺序，进行依次赋值
	
	// 实际上之所以STL容器，拥有这种可以用任意长度的"同类型数据"，进行初始化能力，
	// 是因为STL中的容器，使用了std::initialzer_list这个轻量级的类模板
	
	// std::initialzer_list<T> 可以接受任意长度的"同类型" 的数据，也就是接受可变长参数{ ... }


	//FooVec foo1{ 1, 2.0 , 3, 4, 5, 6 }; // 只要出现不同类型 就不能用类中定义的initialzer_list构造函数
	//FooVec foo2{ 1.0f, 2.0f, 3.0f, 4.0f, 5.0f, 6.0f, 7.0f, 8.0f, 9.0f };
	FooVec foo2{ 1, 2, 3, 4, 5, 6, 7, 8, 9 };

	{// 自定义数据类型的自定义容器
		cout << "自定义容器 的 自定义数据类型：" << endl;
		MyVec myFoo{ MyElem(4) , MyElem(5), MyElem(6) };
		cout << "-------------{----------------" << endl; // 这里释放了匿名的对象MyElem
	}cout << "-------------}--------------" << endl; // 这里释放MyVec容器和内部元素MyElem
	

	{// std::initializer_list   a.用于自定义类型的列表初始化方法   b. 传递相同类型数据的集合
		cout << "函数 传递 相同类型变长参数 std::initializer_list" << endl;
		func({ MyElem(111) , MyElem(222), MyElem(333) });  
	}cout << "------------------------------ " << endl;

	/*
	std::initialzer_list
	1. 轻量级的容器类型 , 内部定义了迭代器iterator等容器必须的一些概念
	2. 可以接受任意长度的初始化列表, 元素必须是要相同的或者可以转换为T类型的
	std::initialzer_list<T>   { {a1,b1,c1}, {a2,b2,c2}, {a3,b3,c3} <-调用T的构造函数   }
	std::initialzer_list<T>   { a1 , a2 , a3 <- 也是调用T的构造函数    }
	3. 	只有三个成员接口，begin(),end(),size()
	4.  它只能被整体的初始化和赋值，遍历只能通过begin和end迭代器来，
		遍历取得的数据是可读的，是不能对单个进行修改的(const T*)
	5.  initialzer_list<T>保存的是T类型的引用，并不对T类型的数据进行拷贝，因此需要注意变量的生存期
	*/

	std::initializer_list<int> out_of_range =  initializer_out_of_range();
	for (std::initializer_list<int>::iterator itor = out_of_range.begin();
		itor < out_of_range.end(); itor++) {
		cout << *itor << endl; // 非法未知的内容
	}

	cout << endl;
    return 0;
}

