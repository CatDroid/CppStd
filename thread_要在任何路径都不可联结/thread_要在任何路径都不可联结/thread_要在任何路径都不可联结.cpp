// thread_要在任何路径都不可联结.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"

#include <windows.h>

#include <thread>
#include <iostream>

// std::thread 要在任何路径都不可联结 除非


void tfunc(int sleeptime) {
	std::cout << "tfunc sleep begin " << std::endl;
	Sleep(sleeptime*1000);
	std::cout << "tfunc sleep end " << std::endl;
}

class Mark {
public:
	Mark() { std::cout << "Mark Enter" << std::endl; }
	~Mark() { std::cout << "Mark Exit" << std::endl; }
	Mark(const Mark&) = delete;
	Mark(Mark&&) = delete;
	Mark& operator= (const Mark&) = delete;
	Mark& operator= (Mark&&) = delete;
};

class ThreadRAII {

public:
	enum class DtorAction; // 限定作用域的enum默认是int 所以可以提前声明
	ThreadRAII(std::thread&& th, DtorAction a):mAction(a),mTh(std::move(th)){

	}
	~ThreadRAII() {
		if (mTh.joinable()) {
			if (mAction == DtorAction::JOIN) {
				mTh.join();
			}else if (mAction == DtorAction::DETACH) {
				mTh.detach();
			}

		}
	}
	
	ThreadRAII(ThreadRAII&&) = default;				// 已经定义了析构函数 编译器不会生成移动操作
	ThreadRAII& operator=(ThreadRAII&&) = default;  // 支持移动 不支持复制赋值和赋值构造
 
	ThreadRAII(const ThreadRAII&) = delete;
	ThreadRAII& operator=(const ThreadRAII&) = delete;

public:
	enum class DtorAction { JOIN, DETACH };
private:
	DtorAction mAction;
	std::thread mTh;
};

void runThreadAnyPathSafe() { // 在所有的路径上保证thread析构前处于不可联结状态

	Mark _m;
	ThreadRAII th(std::thread(tfunc,12), ThreadRAII::DtorAction::JOIN);
	// join导致的可能性能问题 是弊端最新的选择

	Sleep(2 * 1000);

	// detach 导致 未定义行为  特别是线程函数是lambda 捕获局部对象的引用
	// join   导致 性能问题    某种情况下可以不用调用者等待  
	// 可联结 导致 thread析构整个程序终止
}


void runThread() {
	std::thread t(tfunc, 12);
	Mark _m;		  
	Sleep(2 * 1000);  

	if (t.joinable()) { // 处理方法:析构thread前先join
		t.join();
	}

	return;			  
}

void runThreadCrash() {
	std::thread t(tfunc, 12);
	Mark _m;		  // 函数返回先析构Mark 

	Sleep(16 * 1000); // 无论这里休眠到线程函数运行完成 还是 没有直到完成
					  // t一直都没有调用join来联结线程，导致程序终止

	return;			 // thread处于可联结状态 thread的析构函数就会终止程序的运行
}



int main()
{
	runThreadAnyPathSafe();
    return 0;
}

