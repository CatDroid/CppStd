// std_thread.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <thread>
#include <iostream>

/*
	1. thread_local是一个关键字 
	2. thread_local变量的初始化，全局的初始化一次，可以看到每个线程都会进行一次初始化，并不会影响到其他线程
	3. 声明为thread_local的本地变量在线程中是持续存在的，不同于普通临时变量的生命周期，它具有static变量一样的初始化特征和生命周期，虽然它并没有被声明为static
*/

thread_local int counter = 0 ; 

void loop( ) {
	counter++;
	std::cout << " Tid=" << std::this_thread::get_id() << " Counter=" << counter << std::endl;
}


void callAgain() {
	thread_local int timers = 0; // 局部线程变量 : 同一线程 多次调用 只初始化一次  ，同局部static变量
	timers++;
	std::cout << " Tid=" << std::this_thread::get_id() << " Timers=" << timers << std::endl;
}

int main()
{
	// 静态断言  用于编译的时候 ! 
	//static_assert( 4 < sizeof(long), "Error:smaller long"); // 静态断言失败,原因是"Error:smaller long"

	std::cout << " Main Tid=" << std::this_thread::get_id() << std::endl;
	counter = 999;				// 不影响其他线程上的同名thread_local变量
	std::thread f1(loop);
	std::thread f2(loop);

	f1.join();
	f2.join();  

	callAgain();
	callAgain();
	callAgain();

    return 0;
}

/*
	Main		Tid=10464
	Tid=12792	Counter=1
	Tid=12620	Counter=1
	Tid=10464	Timers=1
	Tid=10464	Timers=2
	Tid=10464	Timers=3
*/

