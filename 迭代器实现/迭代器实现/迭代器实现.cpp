// ������ʵ��.cpp : �������̨Ӧ�ó������ڵ㡣
//

/*

ֻ��˳�������͹�������֧�ֵ���������

����			֧�ֵĵ��������    ����               ֧�ֵĵ��������		����     ֧�ֵĵ��������
vector			�������            deque              �������				list     ˫��
set             ˫��                multiset           ˫��					map      ˫��
multimap        ˫��

stack           ��֧��              queue				��֧��				priority_queue  ��֧��
*/


#include "stdafx.h"

#include <assert.h>

// ���������� 
template<typename ITEM , typename SELF >
class IIterator {
public:
	virtual ~IIterator() {} ;
	virtual SELF& operator ++ () = 0;			// ++itor 
	virtual const SELF operator ++ (int) = 0;	// itor++ 
	virtual bool operator == ( const SELF& other ) = 0; // while( itor == temp.end() ) 
	virtual bool operator != (const SELF& other) = 0; // while( itor != temp.end() ) 
	virtual ITEM& operator * () = 0;
};

// �ۺ������
template<typename ITEM , typename ITOR >
class IAggregate {
public:
	virtual ~IAggregate() {};
	virtual ITOR begin() = 0;
	virtual ITOR end() = 0;
	virtual void add(ITEM) = 0 ;	// ��� ���ظ�
	virtual void remove(ITEM) = 0;  // ɾ����һ��
};

template<typename ITEM>
struct Node {
	Node* next;
	ITEM data;
};


template<typename ITEM>
class MyIterator : public  IIterator<ITEM, MyIterator<ITEM>> { // ������ 
private:
	typedef Node<ITEM> TNODE;
	TNODE * mCurPtr;
public:
	explicit MyIterator(TNODE * cur) {
		mCurPtr = cur;
	}

	MyIterator(const MyIterator<ITEM>& other) {
		mCurPtr = other.mCurPtr;
	}

	virtual MyIterator<ITEM>& operator ++ () override {
		if (mCurPtr == NULL) return *this; // walk to the end
		mCurPtr = mCurPtr->next;
		return *this;
	}

	virtual const MyIterator<ITEM> operator ++ (int) override { // i++
		TNODE* old = mCurPtr;
		if (mCurPtr != NULL) mCurPtr = mCurPtr->next;
		return MyIterator<ITEM>(old);
	}

	virtual ITEM & operator * () override {
		assert(mCurPtr != NULL);
		return  mCurPtr->data;
	}

	virtual bool operator == (const MyIterator<ITEM> & other) override {
		if (mCurPtr == other.mCurPtr) return true;
		return false;
	}

	virtual bool operator != (const MyIterator<ITEM> & other) override {
		if (mCurPtr != other.mCurPtr) return true;
		return false;
	}

};

template<typename T>
class MyList : public IAggregate<T, MyIterator<T> > { // typename MyList<T>::MyIterator

private:
	typedef Node<T> TNODE;
	TNODE* mHead;
public:
	MyList() {
		mHead =   NULL;
	}
	virtual ~MyList() {
		for (TNODE* next = mHead; next != NULL; ) {
			TNODE* temp = next->next;
			delete next ;
			next = temp;
		}
		mHead = NULL;
	}

	typedef MyIterator<T>  iterator ;
 
	virtual iterator begin() override  {
		return iterator(mHead);
	}
	virtual iterator end() override {
		return  iterator(NULL);
	}

	virtual void add(T t )   {
		TNODE* n = new TNODE();
		n->data = t; 
		n->next = mHead ;
		mHead  = n;
	}
	virtual void remove(T) {
		// TODO 
	}

private:
	MyList(const MyList<T>& other);
	MyList<T>& operator = (const MyList<T>& other);
};


void test();
int main()
{
	
	MyList<int> one;
	one.add(3);
	one.add(1);
	one.add(2);

	MyList<int>::iterator itor = one.begin();
	while (itor != one.end()) {
		printf("data = %d \n" , *itor); 
		itor++;
	}

    return 0;
}


#include <iostream>
#include <vector>
using namespace std;

void test() 
{
	std::vector<int> temp;
	temp.push_back(2);
	temp.push_back(1);
	temp.push_back(6);
	temp.push_back(7);

	for (int& i : temp) {
		cout << i;
	}	cout << endl;

	std::vector<int>::iterator itor = temp.begin();
	std::vector<int>::iterator itor_eof = temp.end();

	while (itor != temp.end()) {
		cout << *itor << endl;
		cout << itor._Ptr << endl;
		cout << &itor << endl; // ��ַ����ͬһ�� ������& ??
		if (*itor == 6) {
			itor = temp.erase(itor);
		}
		else if (*itor == 7) {
			*itor++ = 8;	 // 
		}
		else {
			itor++;
		}
	}

	for (int& j : temp) {
		cout << j;
	}	cout << endl;

}
