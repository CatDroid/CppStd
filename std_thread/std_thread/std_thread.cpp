// std_thread.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <thread>
#include <iostream>

/*
	1. thread_local��һ���ؼ��� 
	2. thread_local�����ĳ�ʼ����ȫ�ֵĳ�ʼ��һ�Σ����Կ���ÿ���̶߳������һ�γ�ʼ����������Ӱ�쵽�����߳�
	3. ����Ϊthread_local�ı��ر������߳����ǳ������ڵģ���ͬ����ͨ��ʱ�������������ڣ�������static����һ���ĳ�ʼ���������������ڣ���Ȼ����û�б�����Ϊstatic
*/

thread_local int counter = 0 ; 

void loop( ) {
	counter++;
	std::cout << " Tid=" << std::this_thread::get_id() << " Counter=" << counter << std::endl;
}


void callAgain() {
	thread_local int timers = 0; // �ֲ��̱߳��� : ͬһ�߳� ��ε��� ֻ��ʼ��һ��  ��ͬ�ֲ�static����
	timers++;
	std::cout << " Tid=" << std::this_thread::get_id() << " Timers=" << timers << std::endl;
}

int main()
{
	std::cout << " Main Tid=" << std::this_thread::get_id() << std::endl;
	counter = 999;				// ��Ӱ�������߳��ϵ�ͬ��thread_local����
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

