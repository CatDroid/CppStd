// memory_share_weak_auto_ptr.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <iostream>
#include <vector>
#include <memory>

using namespace std;

class Base {
public:
	Base() {
		cout << "Base() "  << this  << endl;
	}
	virtual ~Base() {
		cout << "~Base() " << this  << endl;
	}
};


void sink(unique_ptr<Base> temp) {

	cout << "unique_ptr<Base> 作为参数 丢失生命" << endl;
}

unique_ptr<Base> create() {
	cout << "unique_ptr<Base> 作为返回值 不用std::move " << endl;
	// nique_ptr不支持拷贝操作，但却有一个例外：可以从函数中返回一个unique_ptr
	return unique_ptr<Base>(new Base());
}


int main()
{
	cout << "--------------begin of main ---------------" << endl;
	{
		unique_ptr<Base> ptr(new Base());
		unique_ptr<Base> ptr2(ptr.release());		//	1. unique_ptr release 释放控制权 但是不析构对象 而是返回
		//unique_ptr<Base> ptr2(std::move(ptr));		// 这样也可以 (std::move相当于把原来的unique_ptr中的mPtr设置为0并返回旧值)
		//unique_ptr<Base> ptr3;			  
		//ptr3 = ptr2;								//	2. unique_ptr不存在operator=
		ptr2.reset();								//	3. unique_ptr reset 提前析构对象 
	}

	cout << "-------------------------------------------" << endl;
	{
		unique_ptr<Base> a1 = create();				// 4.转移所有权 函数返回 不需要std::move
		unique_ptr<Base> a2 = std::move(a1);		// 5.转移所有权 unique_ptr需要配合std::move 
		unique_ptr<Base> a3(new Base());
		sink(std::move(a2));						// 6.转移所有权 参数传递 需要std::move或者release
		cout << ">>>>> a2 参数中丢失生命" << endl;
	}

	cout << "-------------------------------------------" << endl;
	{
		vector<unique_ptr<Base>> vec;
		unique_ptr<Base> p(new Base()); 
		vec.push_back(std::move(p));				// 7.vector使用注意push_back和pop/pack(返回的是引用)之前std::move转义语义 
		vec.push_back(unique_ptr<Base>(new Base()));
		vec.push_back(unique_ptr<Base>(new Base()));
		vec.push_back(unique_ptr<Base>(new Base()));// 8.临时unique_ptr<>() 不需要std::move 
		unique_ptr<Base> p2(std::move(vec.back()));		 
		vec.pop_back();
		cout << "vector.back()后 std::move转移语义" << endl;
		p2.reset();									
	
		cout << "vector begin " << endl;
		vector<unique_ptr<Base>>::iterator itor = vec.begin();
		int i = 0;
		while (itor != vec.end()) {
			i++;
			if (i == 1) {
				itor = vec.erase(itor);				//  9.vector.erase 会析构std::unque_ptr 从而析构被管理对象 
				cout << "vector erase " << endl;	//		vector 内部空间不够 realloc 所以不会赋值???
			}
			else {
				itor++;
			}
		}
		cout << "vector end " << endl;			
		
		cout << "vector析构 其中的 unique_ptr对象也析构 " << endl;
													//  10. vector对象析构 其中的unique_ptr也会析构控制的对象
	}
	cout << "-------------------------------------------" << endl;
	{
		unique_ptr<int[]> p(new int[5]{ 1, 2, 3, 4, 5 }); 
		p[0] = 0;									// 11. 管理数组 支持operator[]
	}

	cout << "-------------------------------------------" << endl;
	{
		unique_ptr<Base> p1(new Base());
		unique_ptr<Base> p2(new Base());
		std::swap(p1, p2);							// 12. 交换管理的对象  
		p1.reset();
		p2.reset();
	}
	cout << "--------------end of main -----------------" << endl;

	// unique_ptr使用场景
	//	1. 为动态申请的资源提供异常安全保证 (局部引用)
	//	2. 返回函数内动态申请资源的所有权   (函数返回)
	//	3. 在容器中保存指针 vector<unique_ptr<Base>>
	//  4. 管理动态数组  
	//  http://www.cnblogs.com/DswCnblog/p/5628195.html

	cout << "-------------------------------------------" << endl;
	{
		//vector< unique_ptr<Base> > unique_v(10);		// 正常
		vector< auto_ptr<Base> > auto_v(10);			// vs2015 正常  但是clang++/g++ 非c++11都会错误 clang++/g++使用c++11就正常！
														// clang++ 实现是   
														// 先分配内存 然后 placement new , 将对象拷贝一份放到p指向的内存上去(拷贝构造)
														// 但实际是 auto_ptr 只是有 constructor(const auto_ptr& rhs)
														// 所以会有错误 passing ‘const std::auto_ptr<XXX>’ as ‘this’ argument of ‘std::auto_ptr<XXX>
		for (int i = 0; i<10; i++){
			auto_v[i] = auto_ptr<Base>(new Base() );
		}
	}

    return 0;
}

// shared_ptr也可以安全地放到标准容器中


// auto_ptr在拷贝构造的时候，一定会修改元素的值。所以STL元素不能使用auto_ptr
// auto_ptr不能作为容器对象，STL容器中的元素经常要支持拷贝，赋值等操作，在这过程中auto_ptr会传递所有权，那么source与sink元素之间就不等价了

// auto_ptr不能指向数组，因为auto_ptr在析构的时候只是调用delete,而数组应该要调用delete[]
//  http://www.cnblogs.com/qytan36/archive/2010/06/28/1766555.html

