// lamba���ʽ_�հ���_�հ�����.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <list>
#include <functional>
#include <iostream>

std::list< std::function<bool(int)> > gLambaContainer;

void addFilter()
{
	static int maxValue = 1;

#define CHOOSE_FILTER 2 

#if CHOOSE_FILTER == 0 
	gLambaContainer.emplace_back([=](int value) { // ��Ҫʹ��Ĭ�ϵĲ�׽ģʽ: ʵ�������lambdaû�в����κζ���(�Ǿ�̬�ľֲ���������β�)
		return value > maxValue ? true : false;	  //						 ���ַ�ʽ�������е�lambda�հ�����һ�� 
	});
#elif CHOOSE_FILTER	== 1 
	gLambaContainer.emplace_back([maxValue](int value) {	//				 ����:�޷���lambda�в�׽���о�̬�洢����ʱ��ı���
		return value > maxValue ? true : false;				//				 ��ʽ�Ĳ�׽��ʽ ����ͨ�������������������
	});
#else
	int current = maxValue;
	gLambaContainer.emplace_back([current](int value) {		// ÿ�ε��ö��в�ͬ�ıհ��Ķ���
		return value > current ? true : false;
	});
#endif
	maxValue++;

}


int main()
{
	{
		addFilter();
		addFilter();
		addFilter();
		addFilter();
		addFilter();

		for (const auto& temp : gLambaContainer) {
			std::cout << temp(3) << std::endl;
		}// CHOOSE_FILTER == 1 ȫ������false  CHOOSE_FILTER ==2 true true false false false

	}

    return 0;
}

