// 简单声明friend_using定义类型别名.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "extern_template.h"
#include <iostream>

template <typename T> class DefenderT {
public:
	friend T;  // C++98 不能没有class  C++11支持简单声明friend 
	void Defencde(int x , int y ){}
	void Trckle(int x , int y ){}

private:
	int pos_x = 15;
	int pos_y = 0;
	int speed = 2;
	int stamina = 120;
};

template <typename T> class AttackerT {
public:
	friend T;
	void Move(int x, int y ){}
	void SpeedUp(float radio){}
private:
	int pos_x = 0;
	int pos_y = -30;
	int speed = 3;
	int stamina = 100;

};


/*
	// 不加 template<>的话  错误 ! 显式特例化前必须有‘template <>’
	template<>
	class DefenderT<int> {
	};
*/

extern template void extern_template_func<int>(int); // 外部模板声明
extern template void extern_template_func<double>(double); // 显式实例化 必须在这个声明 之后 或者其他编译单元
extern void call(int arg);

#define  TEST_UNIT  1 

#ifdef TEST_UNIT 
 
class Validator;
using DefenderTest = DefenderT<Validator>;
using AttackerTest = AttackerT<Validator>;

class Validator{
public:
	void validate(int x, int y, DefenderTest& d) {}
	void validate(int x, int y, AttackerTest& a) {}
};


#else

using Attacker = AttackerT<int>;		// 使用using定义类型别名 
typedef  DefenderT<int>  Defender;		// friend int 不会产生友元

#endif 


int main()
{
#ifdef TEST_UNIT
	DefenderTest d;
	AttackerTest a;
#else
	Defender d;
	Attacker a;
#endif

	a.Move(10, 30);
	d.Defencde(15, 30);
	a.SpeedUp(1.5f);
	d.Defencde(15, 30);

#ifdef TEST_UNIT
	Validator v;
	v.validate(7, 0, d);
	v.validate(1, -10, a);
#endif


	extern_template_func<int>(5);
	call(6);
	extern_template_func(6.1); // double 

	// 
	which_kind<double>::type(); // OK 不用在 头文件声明 全特化的模板类

    return 0;
}

