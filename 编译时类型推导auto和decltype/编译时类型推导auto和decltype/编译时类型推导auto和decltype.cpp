// ����ʱ�����Ƶ�auto��decltype.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

#include <iostream>

#include <unordered_set>
#include <string>
 
using namespace std;

// ����������ͨ��c���͵ĺ�����ʵ��hash�Լ�����Ƚ�
// ��Ҫʹ�� �ؼ��� decltype ����ʾ������������
struct Record
{
	string name;
	int val;
};

size_t RecordHash(const Record& rhs) {
	return hash<string>()(rhs.name) ^ hash<int>()(rhs.val);
}
bool RecordCmp(const Record& lhs, const Record& rhs) {
	return lhs.name == rhs.name && lhs.val == rhs.val;
}

unordered_set<Record, decltype(&RecordHash), decltype(&RecordCmp)/*����Ҫ������������*/> 
	records(
		0,
		RecordHash, RecordCmp // ����Ҫ��������ָ��
	);

// ��main����֮ǰִ��ĳ������
struct RunBeforeMain
{
	RunBeforeMain() {
		cout << "RunBeforeMain " << endl;
		cout << "unordered_set before insert " << records.size() << endl;
		records.insert({ "a", 100 });
		records.insert({ "b", 100 });
		records.insert({ "c", 100 });
		cout << "unordered_set after  insert " << records.size() << endl;
	}
};
static RunBeforeMain dummyObject;

// ����ֵ�﷨
// auto+decltype ׷�ٺ����ķ���ֵ����
template <typename _Tx, typename _Ty>
auto multiply(_Tx x, _Ty y) -> decltype(x*y) 
{
	return x*y;
}

class Person
{
public:
	enum PersonType { ADULT, CHILD, SENIOR };
	void setPersonType(PersonType person_type);
	PersonType getPersonType();
private:
	PersonType _person_type;
};

void Person::setPersonType(PersonType person_type){
	_person_type = person_type;
}

//PersonType Person::getPersonType()  // ERROR���벻ͨ�� ����ֵ���� ������� Person::
//Person::PersonType Person::getPersonType(){
//	return _person_type;
//}
// �µķ���ֵ�﷨����Ϊ�����ķ���ֵ�����ں�������󣬶�����ǰ�棬�㲻��Ҫ��ȫ��������
// �������ͺ����﷨ �﷨��ʽΪ��auto ������(����ǩ��) -> ��������  
// void f(int); �ͽ�����дΪ�� auto f(int) -> void;
// lambda	 [](int) -> void{}; 
// lambda���ʽʹ��[] ���ţ�����ͨ������ʹ��auto�ؼ���
// 
// http://www.cnblogs.com/ThatsMyTiger/p/7085309.html
// http://blog.csdn.net/zwvista/article/details/5472096  
auto Person::getPersonType() -> PersonType
{
	return _person_type;
}

// decltype + �µķ���ֵ�﷨
template <typename BuiltType, typename Builder>
auto makeAndProcessObject(const Builder& builder)  -> decltype(builder.makeObject()) // �����˺�������
{
	BuiltType val = builder.makeObject();
	return val;
}

//  ֻ��decltype�����÷������ͺ����﷨
template<class T, class U> 
decltype(*(T*)0 * *(U*)0) mul3(T x, U y) { 
	return x*y; 
} 

template<class T, class U> 
decltype(std::declval<T>()*std::declval<U>())  mul4(T x, U y) { 
	return x*y; 
}


int main()
{

	// ��ʹ�ùؼ���decltype,ֱ�Ӹ�����ָ������ 
	typedef unordered_set<Record,  size_t(*)(const Record& rhs), bool(*)(const Record& lhs, const Record& rhs)> RecordSet;
	for (RecordSet::iterator itor = records.begin(); itor != records.end(); itor++) {
		printf("unordered_set : %s %d \n", (*itor).name.c_str(), (*itor).val);//(*itor); // ���� const Record& 
	}

	cout << "����ʱ�����Ƶ��� auto�ؼ��֣� decltype�ؼ���" << endl;

	/*
		decltype��auto�ؼ���һ��,���ڽ��б���ʱ�����Ƶ�
	
		�ڷ��ͱ���У����Ǹ���Ҫ���Ǳ���ʱ��Ҫȷ������
		
		����ʱ�����Ƶ��ĳ�������Ϊ�˷��ͱ�̣��ڷǷ��ͱ���У����ǵ����Ͷ���ȷ���ģ���������Ҫ�ٽ����Ƶ�
		
		����ʱ�����Ƶ��� auto�ؼ��֣� decltype�ؼ���

		auto�����Ƶ����ӡ�������������'��ʼ�����ʽ' ,��ñ���������

		decltype�����Ƶ�����һ����ͨ���ʽ��Ϊ���������ظñ��ʽ�����ͣ�����decltype������Ա��ʽ������ֵ

		��;��
		a.�Ƶ������ʽ���� 
		b.��using/typedef���ã����ڶ������� 
		c.������������ 
		d.���ͱ���н��auto������׷�ٺ����ķ���ֵ����

	*/
	int i = 4;
	decltype(i+4) a = 5 ; //�Ƶ����Ϊint��a������Ϊint
	printf("%d \n" , a );


	cout << "��typedef���ã����ڶ�������" << endl;
	typedef decltype(records.begin()) RecordSetType;
	for (RecordSetType itor = records.begin(); itor != records.end(); itor++){
		cout << " unordered_set : " << itor->name << " " << itor->val << endl;
	}

	struct		// �����ṹ������
	{
		int d;
		double b;
	}anon_s;	// ����
	anon_s.d = 2;
	anon_s.b = 3.3;

	decltype(anon_s) other_val  ; //  �������� ������λ����������
	other_val.d = 5;
	other_val.b = 6.6;

	printf("decltype������������ [%d %f] [%d %f]\n",
								anon_s.d , anon_s.b, other_val.d, other_val.b );
	
	// ���ͱ���н��auto������׷�ٺ����ķ���ֵ����
	auto ret = multiply(2.0, 3.0);


	/*
		decltype�Ƶ��Ĺ���:

		���e��һ����û�д����š��ġ���Ƿ����ʽ�����ߡ����Ա ���ʱ��ʽ����decltype��e������e��������ʵ������͡�
		���⣬���e��һ�������صĺ�������ᵼ�±������(�޷�ȷ����Ҫ�ĸ����غ���ʵ��)
		���򣬼���e��������T�����e��һ������ֵ����ôdecltype��e��ΪT&&
		���򣬼���e��������T�����e��һ����ֵ����ôdecltype��e��ΪT&��
		���򣬼���e��������T����decltype��e��ΪT

		'��Ƿ�'ָ���ǳ�ȥ'�ؼ��֡�������'�ȱ�������Ҫʹ�õı��֮��ĳ���Ա�Լ�����ı��

		��������Ƿ�����Ӧ�ı��ʽ��Ϊ����Ƿ����ʽ�� int arr[4]  arrΪһ����Ƿ����ʽ(����decltype(arr))����arr[3]+0����
	
		�ַ�������ֵ�����Ǹ���ֵ������const��ֵ�������ַ�������ֵ�������Ǹ���ֵ

		������ֵ������Ĳ�����������ֵ���õĲ���������ģ�����ֵ����ֵ����ϢϢ��ء�
		��ν�Ľ���ֵ���ʽ���������б��ʽ��
		1������"��ֵ���õĺ���"�ĵ��ñ��ʽ
		2��"ת��Ϊ��ֵ���õ�ת������"�ĵ��ñ��ʽ

		C++11��׼�� ģ����
		is_lvalue_reference ���ж� ���ʽ�Ƿ�Ϊ��ֵ		���1��ʾΪ��ֵ�����Ϊ0Ϊ����ֵ
		is_rvalue_reference ���ж� decltype�ƶϽ���Ƿ�Ϊ��ֵ

	*/
	{
		int tempi = 10;
		decltype(tempi) test = 2;	// �Ƶ�Ϊint û������-->��Ƿ�-->������Ƿ�--> ��Ƿ����ʽ 
		decltype(tempi + 1) test2 = 2; // �Ƶ�Ϊint 
		decltype((tempi + 1)) test3 = 3;// �����Ƶ�Ϊint 
		decltype(tempi) a;			// a�Ƶ�Ϊint��i��һ����Ƿ����ʽ�������Ƶ�����1�����ͱ��Ƶ�Ϊint
		decltype((tempi)) b = tempi;// b�Ƶ�Ϊint& �����ʼ����(i)Ϊһ����ֵ���ʽ�����ͱ��Ƶ�Ϊint&
		
		// ������ 
		int i = 4;
		int arr[5] = { 0 };
		int *ptr = arr;
		struct S { double d; }s;
		void Overloaded(int);  // �����ڲ������������� ���ǲ��ܶ��庯��
		void Overloaded(char); // ���صĺ���
		int && RvalRef();
		const bool Func(int);
		Person ppp;

		//����һ���Ƶ�Ϊ������( ����û�д����ŵ� )
		decltype (arr) var1;	//	int		��Ƿ����ʽ
		decltype (ptr) var2;	//	int *	��Ƿ����ʽ
		decltype (s.d) var3;	//	double	��Ա���ʱ��ʽ
		//decltype(ppp_person_type) var4;   ��Ա���ʱ��ʽ ˽�г�Ա�ǲ����Ե�
		//decltype(Overloaded) var4;//���غ������������:�޷�ȷ����Ҫ�ĸ����غ���Overloadedʵ��

		//�����������ֵ���Ƶ�Ϊ���͵���ֵ����(???? decltype�Ƶ�����ֵ����: ���߱������� ��ֵ����)
		decltype (RvalRef()) var5 = 1; // int&& 

		//����������ֵ���Ƶ�Ϊ���͵����á�
		decltype ((i))var6 = i;				//int&  ��() ������ֵ
		decltype (true ? 0 : 1) var7 = i;	//int&  �������ʽ������ֵ��
		decltype (++i) var8 = i;			//int&  ++i����i����ֵ��
		decltype(arr[5]) var9 = i;			//int&. []����������ֵ
		decltype(*ptr)var10 = i;			//int&  *����������ֵ

		decltype("hello")var11 = "hello";	//const char(&)[6]  �ַ������泣��Ϊ��ֵ����Ϊconst��ֵ��

		//�����ģ����϶����ǣ����Ƶ�Ϊ������
		decltype(1) var12;					//const int
		decltype(Func(1)) var13 = true;		//const bool
		decltype(i++) var14 = i;			//int	i++���ء���ֵ�� ������ ������ֵ�� 
		decltype(var5) var15 = 2;			//var5 �������� ��ֵ����
	
		

		cout << "decltype(++i)�Ƿ���ֵ����?" << is_lvalue_reference<decltype(++i)>::value << endl;// 1
		// decltype(i++) �Ȳ�����ֵ���� �ֲ�����ֵ����  ���� int����
		cout << "decltype(i++)�Ƿ���ֵ����?" << is_lvalue_reference<decltype(i++)>::value << endl;// 0
		cout << "decltype(i++)�Ƿ���ֵ����?" << is_rvalue_reference<decltype(i++)>::value << endl;// 0 
	}

    return 0;
}

