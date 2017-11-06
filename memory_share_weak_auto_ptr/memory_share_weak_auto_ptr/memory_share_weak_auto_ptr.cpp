// memory_share_weak_auto_ptr.cpp : �������̨Ӧ�ó������ڵ㡣
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

	cout << "unique_ptr<Base> ��Ϊ���� ��ʧ����" << endl;
}

unique_ptr<Base> create() {
	cout << "unique_ptr<Base> ��Ϊ����ֵ ����std::move " << endl;
	// nique_ptr��֧�ֿ�����������ȴ��һ�����⣺���ԴӺ����з���һ��unique_ptr
	return unique_ptr<Base>(new Base());
}


int main()
{
	cout << "--------------begin of main ---------------" << endl;
	{
		unique_ptr<Base> ptr(new Base());
		unique_ptr<Base> ptr2(ptr.release());		//	1. unique_ptr release �ͷſ���Ȩ ���ǲ��������� ���Ƿ���
		//unique_ptr<Base> ptr2(std::move(ptr));		// ����Ҳ���� (std::move�൱�ڰ�ԭ����unique_ptr�е�mPtr����Ϊ0�����ؾ�ֵ)
		//unique_ptr<Base> ptr3;			  
		//ptr3 = ptr2;								//	2. unique_ptr������operator=
		ptr2.reset();								//	3. unique_ptr reset ��ǰ�������� 
	}

	cout << "-------------------------------------------" << endl;
	{
		unique_ptr<Base> a1 = create();				// 4.ת������Ȩ �������� ����Ҫstd::move
		unique_ptr<Base> a2 = std::move(a1);		// 5.ת������Ȩ unique_ptr��Ҫ���std::move 
		unique_ptr<Base> a3(new Base());
		sink(std::move(a2));						// 6.ת������Ȩ �������� ��Ҫstd::move����release
		cout << ">>>>> a2 �����ж�ʧ����" << endl;
	}

	cout << "-------------------------------------------" << endl;
	{
		vector<unique_ptr<Base>> vec;
		unique_ptr<Base> p(new Base()); 
		vec.push_back(std::move(p));				// 7.vectorʹ��ע��push_back��pop/pack(���ص�������)֮ǰstd::moveת������ 
		vec.push_back(unique_ptr<Base>(new Base()));
		vec.push_back(unique_ptr<Base>(new Base()));
		vec.push_back(unique_ptr<Base>(new Base()));// 8.��ʱunique_ptr<>() ����Ҫstd::move 
		unique_ptr<Base> p2(std::move(vec.back()));		 
		vec.pop_back();
		cout << "vector.back()�� std::moveת������" << endl;
		p2.reset();									
	
		cout << "vector begin " << endl;
		vector<unique_ptr<Base>>::iterator itor = vec.begin();
		int i = 0;
		while (itor != vec.end()) {
			i++;
			if (i == 1) {
				itor = vec.erase(itor);				//  9.vector.erase ������std::unque_ptr �Ӷ�������������� 
				cout << "vector erase " << endl;	//		vector �ڲ��ռ䲻�� realloc ���Բ��ḳֵ???
			}
			else {
				itor++;
			}
		}
		cout << "vector end " << endl;			
		
		cout << "vector���� ���е� unique_ptr����Ҳ���� " << endl;
													//  10. vector�������� ���е�unique_ptrҲ���������ƵĶ���
	}
	cout << "-------------------------------------------" << endl;
	{
		unique_ptr<int[]> p(new int[5]{ 1, 2, 3, 4, 5 }); 
		p[0] = 0;									// 11. �������� ֧��operator[]
	}

	cout << "-------------------------------------------" << endl;
	{
		unique_ptr<Base> p1(new Base());
		unique_ptr<Base> p2(new Base());
		std::swap(p1, p2);							// 12. ��������Ķ���  
		p1.reset();
		p2.reset();
	}
	cout << "--------------end of main -----------------" << endl;

	// unique_ptrʹ�ó���
	//	1. Ϊ��̬�������Դ�ṩ�쳣��ȫ��֤ (�ֲ�����)
	//	2. ���غ����ڶ�̬������Դ������Ȩ   (��������)
	//	3. �������б���ָ�� vector<unique_ptr<Base>>
	//  4. ����̬����  
	//  http://www.cnblogs.com/DswCnblog/p/5628195.html

	cout << "-------------------------------------------" << endl;
	{
		//vector< unique_ptr<Base> > unique_v(10);		// ����
		vector< auto_ptr<Base> > auto_v(10);			// vs2015 ����  ����clang++/g++ ��c++11������� clang++/g++ʹ��c++11��������
														// clang++ ʵ����   
														// �ȷ����ڴ� Ȼ�� placement new , �����󿽱�һ�ݷŵ�pָ����ڴ���ȥ(��������)
														// ��ʵ���� auto_ptr ֻ���� constructor(const auto_ptr& rhs)
														// ���Ի��д��� passing ��const std::auto_ptr<XXX>�� as ��this�� argument of ��std::auto_ptr<XXX>
		for (int i = 0; i<10; i++){
			auto_v[i] = auto_ptr<Base>(new Base() );
		}
	}

    return 0;
}

// shared_ptrҲ���԰�ȫ�طŵ���׼������


// auto_ptr�ڿ��������ʱ��һ�����޸�Ԫ�ص�ֵ������STLԪ�ز���ʹ��auto_ptr
// auto_ptr������Ϊ��������STL�����е�Ԫ�ؾ���Ҫ֧�ֿ�������ֵ�Ȳ��������������auto_ptr�ᴫ������Ȩ����ôsource��sinkԪ��֮��Ͳ��ȼ���

// auto_ptr����ָ�����飬��Ϊauto_ptr��������ʱ��ֻ�ǵ���delete,������Ӧ��Ҫ����delete[]
//  http://www.cnblogs.com/qytan36/archive/2010/06/28/1766555.html

