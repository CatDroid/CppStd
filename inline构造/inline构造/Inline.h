#pragma once

#include <iostream>

class Inline
{
public:
	//inline Inline();
	Inline();
	~Inline();
	inline void call() { // ������뵥Ԫ�������ͷ�ļ� һ�����ֲ���inline�Ļ� �ͻ�������ʱ���ظ�����
		for (int i = 0; i<10; i++){
			std::cout <<" this "<< std::endl;
		}
	}
};

