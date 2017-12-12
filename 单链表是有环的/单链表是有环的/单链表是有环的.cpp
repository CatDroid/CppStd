// ���������л���.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"

/*
����ж�һ�����������л��ģ� �ж�һ���������Ƿ��л����������ӵ�

��ע�ⲻ���ñ�־λ�����ֻ������������ָ�룩

�ⷨ��
1����������1��ʹ��׷�ϵķ������趨����ָ��slow��fast����ͷָ�뿪ʼ��ÿ�ηֱ�ǰ��1����2��������ڻ����������������粻���ڻ���fast����NULL�˳���
2����������2����¼������1����ײ��p��slow��fast�Ӹõ㿪ʼ���ٴ���ײ���߹��Ĳ��������ǻ��ĳ���s��
3������3���ж�����ײ��p�����ӵ�ľ���=ͷָ�뵽���ӵ�ľ��룬��ˣ��ֱ����ײ�㡢ͷָ�뿪ʼ�ߣ��������Ǹ���������ӵ㡣(֤���ں��渽ע)
4������3���Ѿ�������ӵ����ͷָ��ĳ��ȣ���������2������Ļ��ĳ��ȣ�����֮�;��Ǵ���������ĳ���

*/

struct node { 
	char val; 
	node* next; 
};

//return false : �޻���true: �л�
// һ��O��n���İ취���ǣ�������ָ�룬һ��ÿ�ε���һ����һ��ÿ�ε�������������л��Ļ����߱�Ȼ�غϣ���֮��Ȼ����
bool check( node* const head)
{
	if (head == NULL) return false;
	node *low = head, *fast = head->next;
	if (low == fast) {
		printf("ָ���Լ�  ������ = 0  \n" );
		return true;
	}

	while (fast != NULL && fast->next != NULL)
	{
		low = low->next;
		fast = fast->next->next;
		if (low == fast) {
			int i = 1; 
			low = low->next;
			//fast = fast->next->next;
			while (low != fast) {
				low = low->next;
				//fast = fast->next->next;
				i++;
			}
			printf("������ %d \n", i );
			return true;
		}
	}
	return false;
}

int main()
{
	{
		node nHead;
		nHead.next = &nHead;
		printf("check %s \n", check(&nHead) ? "true" : "false");
	}

	{
		node nHead;
		node n1; nHead.next = &n1; n1.next = NULL;
		node n2; n1.next = &n2; n2.next = NULL;
		node n3; n2.next = &n3; n3.next = NULL;
		node n4; n3.next = &n4; n4.next = NULL;
		node n5; n4.next = &n5; n5.next = NULL;
		node n6; n5.next = &n6; n6.next = NULL;
		node n7; n6.next = &n7; n7.next = NULL;
		node n8; n7.next = &n8; n8.next = NULL;
		node n9; n8.next = &n9; n9.next = &n5;

		printf("check %s \n", check(&nHead) ? "true" : "false");
	}

    return 0;
}

