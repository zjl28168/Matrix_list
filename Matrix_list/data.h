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
		GList Next;
	}URegion;
	GList Right;
}; //Ԫ�ؽṹ��


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
};//λ��ָ��

int Add_element(GList L, int Row, int Col, ElementType X);
GList Init_list();
#pragma once
