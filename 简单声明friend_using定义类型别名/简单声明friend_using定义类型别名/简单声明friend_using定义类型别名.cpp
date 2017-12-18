// ������friend_using�������ͱ���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

template <typename T> class DefenderT {
public:
	friend T;  // C++98 ����û��class  C++11֧�ּ�����friend 
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
	// ���� template<>�Ļ�  ���� ! ��ʽ������ǰ�����С�template <>��
	template<>
	class DefenderT<int> {
	};
*/

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

using Attacker = AttackerT<int>;		// ʹ��using�������ͱ��� 
typedef  DefenderT<int>  Defender;		// friend int ���������Ԫ

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



    return 0;
}

