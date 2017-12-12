// 位图.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
/*
有char a[n],char b[m]两个数组，n > m > 1000 
b数组中的元素a中都有，
现在需要生成数组c，将a中有b中没有的元素都放到c里面，要求高效，
用c/c++语言实现。

*/
int main()
{

	char a[] = {50,49,11,1,2,3,4,5,6,6,7,10,11,11};
	char b[] = {7,1,4}; // 两个数组，n > m > 1000
	// 主要是 char 数字范围在 -128 ~ 127 之间  

	// step 1  建立位图  标记 b[] 中使用的数字 
	unsigned char bitMap[256]; memset(bitMap , 0 , 256 );
	for (int i = 0; i < sizeof(b); i++) {
		bitMap[b[i]] = 1;
	}

	// 搜索 
	char* c = (char*)malloc(sizeof(a) > sizeof(b) ? sizeof(a) : sizeof(b));
	int valid_c = 0;
	for (int j = 0; j < sizeof(a); j++ ) {
		if (bitMap[a[j]] == 0 ) {
			c[valid_c] = a[j];
			valid_c++;
			bitMap[a[j]] = 1; // 避免重复
		}
	}

	// 输出
	for (int k = 0; k < valid_c; k++) {
		printf("c[%d] = %d \n", k , c[k] );
	}

    return 0;
}

