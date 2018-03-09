//#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data.h"

void main()
{
	GList L;
	L = Init_list();
	ElementType X;
	int Row, Col;
	int i, j, k;
	int Chose;
	i = 5;
	while (i--)
	{
		printf("Input your element,like this Row,Col,Value:\n");
		scanf("%d,%d,%d", &Row, &Col, &X);
		Add_element(L, Row, Col, X);
	}
}

