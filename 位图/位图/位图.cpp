// λͼ.cpp : �������̨Ӧ�ó������ڵ㡣
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
��char a[n],char b[m]�������飬n > m > 1000 
b�����е�Ԫ��a�ж��У�
������Ҫ��������c����a����b��û�е�Ԫ�ض��ŵ�c���棬Ҫ���Ч��
��c/c++����ʵ�֡�

*/
int main()
{

	char a[] = {50,49,11,1,2,3,4,5,6,6,7,10,11,11};
	char b[] = {7,1,4}; // �������飬n > m > 1000
	// ��Ҫ�� char ���ַ�Χ�� -128 ~ 127 ֮��  

	// step 1  ����λͼ  ��� b[] ��ʹ�õ����� 
	unsigned char bitMap[256]; memset(bitMap , 0 , 256 );
	for (int i = 0; i < sizeof(b); i++) {
		bitMap[b[i]] = 1;
	}

	// ���� 
	char* c = (char*)malloc(sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b));
	int valid_c = 0;
	for (int j = 0; j < sizeof(a); j++ ) {
		if (bitMap[a[j]] == 0 ) {
			c[valid_c] = a[j];
			valid_c++;
			bitMap[a[j]] = 1; // �����ظ�
		}
	}

	// ���
	for (int k = 0; k < valid_c; k++) {
		printf("c[%d] = %d \n", k , c[k] );
	}

    return 0;
}

