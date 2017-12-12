// ѭ������_����_��������_��������.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include "iostream"

#include "map"

using namespace std;


class Base {
public:
	Base(){
		cout << "Base()" << endl;
	}
	virtual ~Base() {
		cout << "~Base()" << endl;
	}

	Base(const Base& other);
	Base& operator = (const Base& other);

	virtual void func() {
		cout << "Base::func()" << endl;
	}
};

class Derive : public Base {
public:
	Derive() {
		cout << "Derive()" << endl;
	}
	virtual ~Derive() {
		cout << "~Derive()" << endl;
	}
	Derive(const Derive& other);
	Derive& operator = (const Derive& other);

	virtual void func() override  {
		cout << "Derive::func()" << endl;
	}
};

template <typename T1 , typename T2>
std::pair<T1,T2> func(T1 arg1, T2 arg2){
	//	std::pair�Ƕ�Ԫ����ģ��
	//	C++����ģ���ģ�������ʡ�Ե�����(ͨ���������Զ��Ƶ�������ָ��ģ������)
	//	ģ����֧��Ĭ��ģ�������ģ�庯����֧��Ĭ��ģ������������ģ�庯������ȫ�ֺ��������Ա��������
	//	template<class TypeA = int, class TypeB = float> class MyClass{}
	//
	//	std::map<T1,T2>.insert(  std::map<T1,T2>::value_type(t1,t2)  )
	//	typedef std::pair<const _Key, _Tp>   value_type;
	return std::pair<T1,T2>(arg1, arg2);
}

template <typename T1 >
void class_func(T1 arg1 ){
	arg1->func();
}


template <class ELEM_TYPE>
class ArrayLockFreeQueue {
private:
	int  m_readIndex;
	int  m_writeIndex;
	int  m_maximumReadIndex;
	int* m_theQueue;
	int  m_queueSize;
public:
	bool pop(ELEM_TYPE &a_data);
	bool push(const ELEM_TYPE &a_data);
	inline uint32_t countToIndex(uint32_t a_count) {
		return (a_count % m_queueSize);
	}
};
int main()
{
	std::pair<int,float> temp = func(1,2.0);
	cout << temp.first << " " << temp.second << endl;
	class_func( (Base*)(new Derive()) );
	
	ArrayLockFreeQueue<int> a;
	a.push(12);

	return 0;
}




bool CAS(int* value , int old_value, int new_value) {
	if (*value == old_value) {
		*value = new_value;
		return true; 
	}
	return false;
}

template <typename ELEM_T>
bool ArrayLockFreeQueue<ELEM_T>::pop(ELEM_T &a_data)
{
	uint32_t currentMaximumReadIndex;
	uint32_t currentReadIndex;

	do{
		// to ensure thread-safety when there is more than 1 producer thread
		// a second index is defined (m_maximumReadIndex)
		currentReadIndex		= m_readIndex;
		currentMaximumReadIndex = m_maximumReadIndex;

		if (  currentReadIndex ==  currentMaximumReadIndex  ){
			// the queue is empty or
			// a producer thread has allocate space in the queue but is 
			// waiting to commit the data into it
			return false;
		}

		// retrieve the data from the queue
		a_data = m_theQueue[countToIndex(currentReadIndex)];

		// try to perfrom now the CAS operation on the read index. If we succeed
		// a_data already contains what m_readIndex pointed to before we 
		// increased it
		if ( CAS( &m_readIndex, currentReadIndex, (currentReadIndex + 1))  ){
			return true;
		}

		// it failed retrieving the element off the queue. Someone else must
		// have read the element stored at countToIndex(currentReadIndex)
		// before we could perform the CAS operation        

	} while (1); // keep looping to try again!
			 
	assert(0);	// Something went wrong. it shouldn't be possible to reach here

	return false;// Add this return statement to avoid compiler warnings
}


template <typename ELEM_T>
bool ArrayLockFreeQueue<ELEM_T>::push(const ELEM_T &a_data)
{
	uint32_t currentReadIndex;
	uint32_t currentWriteIndex;

	do
	{
		currentWriteIndex = m_writeIndex;
		currentReadIndex  = m_readIndex;
		if ( currentWriteIndex + 1  == currentReadIndex ){
			return false;// the queue is full
		}
	} while (!CAS(&m_writeIndex, currentWriteIndex, (currentWriteIndex + 1)));
	// ��������ǻ����һ���� ���Է����ݽ�ȥ (currentWriteIndex) 
	// �������ߵĻ� �����ܹ����Ի���Լ��Ŀ�

	m_theQueue[countToIndex(currentWriteIndex)] = a_data;

	// �������ߵ�ʱ������ 
	while (!CAS(&m_maximumReadIndex, currentWriteIndex, (currentWriteIndex + 1))){
 
		SwitchToThread(); // �ر����ֻ�е��˵����  ��CPU�����������߳����� (�������̱߳�CPU����Ҫ������)
		//
		//	sched_yield();
		//	
		//	#include <pthread.h>
		//	pthread_yield();
		 
	}// ��������  �����max����Ϊ�Լ���ȡ���Ŀӵ�index 

	return true;
}

/*

src/os/unix/ngx_process.h:
#define ngx_sched_yield() sched_yield()

src/os/win32/ngx_process.h:
#define ngx_sched_yield() SwitchToThread()

*/