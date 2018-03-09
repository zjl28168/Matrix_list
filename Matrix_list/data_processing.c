#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"data.h"

//#define Size_Find 10

//Position Location[Size_Find][Size_Find];

/*初始化*/
GList Init_list()
{
	GList L;
	L = (GList)malloc(sizeof(GList));
	if (L == NULL) {
		printf("Failed to creat Element list!\n");
		return NULL;
	}
	memset(L, 0, sizeof(GList));
	L->Tag = 1;
	L->Down = L;
	L->Right = L;
	printf("Sucssed to creat Element list!\n");
	return L;
}

Location Init_local()
{

}



/*增加*/


int Add_element(GList L,int Row,int Col,ElementType X)
{
	if (X == 0) {
		printf("You can only input non-zero elements.\n ");
		return -1;
	}
	
	GList L0 = L,L_flag;
									
	GList L_add = (GList)malloc(sizeof(GList));			//建立新的节点
	memset(L_add, 0, sizeof(GList));
	L_add->Tag = 1;
	L_add->URegion.Element.Col = Col;
	L_add->URegion.Element.Row = Row;
	L_add->URegion.Element.Value = X;
						
	if (Col > L->URegion.Element.Col) {					//处理列，在矩阵外插入元素
		L->URegion.Element.Col = Col;					//判断是否在矩阵外加入元素，是就增加
		while (L->Right != L0)		
			L = L->Right;								//	找到最后一个元素
		L->Right = (GList)malloc(sizeof(GList));
		memset(L->Right, 0, sizeof(GList));
		L = L->Right;
		L->Right = L0;
		L->Down = L_add;								//	接上元素
		L_add->Down = L;
		L0->URegion.Element.Col++;					
		L->URegion.Element.Col = Col;
	}
	else	{										//Locatde in Matrix,在原有的矩阵里插入元素
		L = L->Right;
		while (L->Right->URegion.Element.Col<=Col)		//定位
			L = L->Right;
		
		if (L->URegion.Element.Col = Col) {			//相等，代表已有列
			L = L->Down;

			while (L->Down->URegion.Element.Row <= Row)
				L = L->Down;

			if (L->URegion.Element.Row == Row) {
				printf("Date already exists,Do you want to replace it? Y/N\n");
				char Order;
				scanf("%c", &Order);
				if ((Order == 'Y')|(Order == 'y') )
					L->URegion.Element.Value = X;	//替换当前值
				
				free(L_add);						//释放新元素指针
				return 0;
			}
			else
			{
				L_flag = L->Down;				   //插入元素
				L->Down = L_add;
				L_add->Down = L_flag;

			}

		}
		else{										//不相等，就在中间重新插入一列
			L_flag = L->Right;
			L->Right = (GList)malloc(sizeof(GList));
			L = L->Right;
			L->Right = L_flag;
			L->Down = L_add;								//	接上元素
			L_add->Down = L;								//Down指向Head
			L0->URegion.Element.Col++;
			L->URegion.Element.Col = Col;

		}
	}

	L = L0;												//处理行
	if (Row > L->URegion.Element.Row) {					//在矩阵外插入行
		L->URegion.Element.Row = Row;
		while (L->Down != L0)
			L = L->Down;								//查找到最后一行
		L->Down = (GList)malloc(sizeof(GList));
		memset(L->Down, 0, sizeof(GList));
		L = L->Down;
		L->Down = L0;
		L0->URegion.Element.Row++;

		L->Right = L_add;
		L_add->Right = L;
	}
	else {											//在矩阵内插入元素
		L = L->Down;
		while (L->Down->URegion.Element.Row<=Row)
			L = L->Down;
		if (L->URegion.Element.Row = Row) {
			
			while (L->Down->URegion.Element.Col <= Col)
				L = L->Right;

			if (L->URegion.Element.Col == Col) {
				printf("Date already exists,Do you want to replace it? Y/N\n");
				char Order;
				scanf("%c", &Order);
				if( (Order == 'Y') | (Order == 'y'))
					L->URegion.Element.Value = X;	//替换当前值

				free(L_add);						//释放新元素指针
				return 0;
			}
			else
			{
				L_flag = L->Right;				   //插入元素
				L->Right = L_add;
				L_add->Right = L_flag;
			}

		}
		else
		{
			L_flag = L->Down;
			L->Down = (GList)malloc(sizeof(GList));
			L = L->Down;
			L->Down = L_flag;
			L0->URegion.Element.Row++;

			L->Right = L_add;
			L_add->Right = L;					//	指向Head

		}
	}



}

Location Add_location()
{
	Location List;
	List = (Location)malloc(sizeof(Location));
	if (List == NULL) {
		printf("Failed to creat Location list!\n");
		return NULL;
	}
	memset(List, 0, sizeof(Location));	
	return List;
}


/*查找*/
Location Find(GList L, ElementType X)
{
	GList L0,L_down;
	Location List_local,List_local_0;//定位指针链表
	//int row, col;
	//int i, j,k;	
	List_local_0 = List_local = Add_location();	
	if (L->Down == 0 | L->Right == 0) {
		printf("This is an empty matrix!\n ");
		//return ;
	}
	else
	{

		L0 = L;
		L_down = L->Down;//记录第一行
		L = L->Down;//	指向第一行

		while ( L!=L0)
		{
			L = L->Right;//指向第一个数据
			while (L != L_down){
				if (L->URegion.Element.Value == X) {			
					List_local->Next = Add_location();
					List_local = List_local->Next;
					List_local_0->Sum++;
					List_local->Row = L->URegion.Element.Row;
					List_local->Col = L->URegion.Element.Col;
				}
				L = L_down->Down;//指向下一行
			}
		}
		return List_local_0;
	}
	
}