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
    return 0;
}

