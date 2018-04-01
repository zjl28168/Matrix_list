typedef int ElementType;
typedef struct GNode * GList;
typedef struct location * Location;

struct GNode {
	int Tag;//0 mean Head,1 mean Term
	GList Down;
	union {
		struct Term {
			int Row;
			int Col;
			ElementType Value;
		}Element;
		//GList Next;
	}URegion;
	GList Right;
}; //元素结构体


struct location
{
	union data
	{
		int Sum;//
		struct loca
		{
			int Row;
			int Col;
		};
		
	};	
	Location Next;	
};//位置指针

GList Init_list();
int Add_element(GList L, int Row, int Col, ElementType X);
int my_printf_matrix(GList L);
int Matrix_save(GList L);
Location Find(GList L);
int my_printf_local(Location local_list);
#pragma once
