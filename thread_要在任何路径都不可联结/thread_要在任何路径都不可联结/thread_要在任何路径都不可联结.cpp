// thread_Ҫ���κ�·������������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <windows.h>

#include <thread>
#include <iostream>

// std::thread Ҫ���κ�·������������ ����


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
	enum class DtorAction; // �޶��������enumĬ����int ���Կ�����ǰ����
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
	
	ThreadRAII(ThreadRAII&&) = default;				// �Ѿ��������������� ���������������ƶ�����
	ThreadRAII& operator=(ThreadRAII&&) = default;  // ֧���ƶ� ��֧�ָ��Ƹ�ֵ�͸�ֵ����
 
	ThreadRAII(const ThreadRAII&) = delete;
	ThreadRAII& operator=(const ThreadRAII&) = delete;

public:
	enum class DtorAction { JOIN, DETACH };
private:
	DtorAction mAction;
	std::thread mTh;
};

void runThreadAnyPathSafe() { // �����е�·���ϱ�֤thread����ǰ���ڲ�������״̬

	Mark _m;
	ThreadRAII th(std::thread(tfunc,12), ThreadRAII::DtorAction::JOIN);
	// join���µĿ����������� �Ǳ׶����µ�ѡ��

	Sleep(2 * 1000);

	// detach ���� δ������Ϊ  �ر����̺߳�����lambda ����ֲ����������
	// join   ���� ��������    ĳ������¿��Բ��õ����ߵȴ�  
	// ������ ���� thread��������������ֹ
}


void runThread() {
	std::thread t(tfunc, 12);
	Mark _m;		  
	Sleep(2 * 1000);  

	if (t.joinable()) { // ������:����threadǰ��join
		t.join();
	}

	return;			  
}

void runThreadCrash() {
	std::thread t(tfunc, 12);
	Mark _m;		  // ��������������Mark 

	Sleep(16 * 1000); // �����������ߵ��̺߳���������� ���� û��ֱ�����
					  // tһֱ��û�е���join�������̣߳����³�����ֹ

	return;			 // thread���ڿ�����״̬ thread�����������ͻ���ֹ���������
}



int main()
{
	runThreadAnyPathSafe();
    return 0;
}

