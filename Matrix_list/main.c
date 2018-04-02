//#define _CRT_SECURE_NO_DEPRECATE

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"data.h"

void main()
{
 GList L;
 Location local_list;
 L = Init_list();
 ElementType X;
 int Row, Col;
 int i, j, k;
 int Chose;
 printf("Input the number of your matrix want to input:\n");
 scanf("%d", &i);
 while (i--)
 {
  printf("Input your element,like this Row,Col,Value:\n");
  scanf("%d,%d,%d", &Row, &Col, &X);
  data_add(L, Row, Col, X);
  Matrix_save(L);
  my_printf_matrix(L);
 }
 local_list = Find(L);
 my_printf_local(local_list);
 system("pause"); 
}

