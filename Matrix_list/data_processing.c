#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include"data.h"

int Matrix_save(GList L)
    {
    FILE *fp;
    GList L_0,L_down;
    char string[430] = {'\0'};
    char buf[50];
    fp=fopen("D:\\Matrix.txt","w+");
    if(fp == NULL) 
        {
        printf("Can not open file!\n");
        exit(0);
        }
    L_0 = L_down = L;

    sprintf(buf, " %X-%X(%d-[%d,%d]:%d)-%X", (unsigned int)L,(unsigned int)L->Down, L->Tag, L->URegion.Element.Row, L->URegion.Element.Col, L->URegion.Element.Value, (unsigned int)L->Right);
    strcpy(string, buf);

    L = L->Right;
    do
        {
        while (L != L_down)
            {
            sprintf(buf, " %X-%X(%d-[%d,%d]:%d)-%X", (unsigned int)L,(unsigned int)L->Down, L->Tag, L->URegion.Element.Row, L->URegion.Element.Col, L->URegion.Element.Value, (unsigned int)L->Right);
            strcat(string, buf);
            L = L->Right;
            }
        fwrite(string, strlen(string), 1, fp);
        fwrite("\r\n", 1, 2, fp);
        L=L_down = L_down->Down;
        sprintf(buf, " %X-%X(%d-[%d,%d]:%d)-%X",  (unsigned int)L,(unsigned int)L->Down, L->Tag, L->URegion.Element.Row, L->URegion.Element.Col, L->URegion.Element.Value, (unsigned int)L->Right);
        strcpy(string, buf);
        L = L_down->Right;
        } while (L_down != L_0);
    fclose(fp);
    }


/*��ʼ��*/
GList Init_list()
    {
     GList L;
     L = (GList)malloc(sizeof(struct GNode));
     if (L == NULL) 
         {
          printf("Failed to creat Element list!\n");
          return NULL;
         }
     memset(L, 0, sizeof(struct GNode));
     L->Tag = 0;
     L->Down = L;
     L->Right = L;
     printf("Sucssed to creat Element list!\n");
     return L;
    }

/*����*/
int data_add(GList L,int Row,int Col,ElementType X)
    {
    if (X == 0) 
        {
        printf("You can only input non-zero elements.\n ");
        return -1;
        }
    GList L0 = L,L_flag;
    GList L_local;
    GList L_add;
    L_add= (GList)malloc(sizeof(struct GNode));   //�����µĽڵ�
    memset(L_add, 0, sizeof(struct GNode));
    L_add->Tag = 1;
    L_add->URegion.Element.Col = Col;
    L_add->URegion.Element.Row = Row;
    L_add->URegion.Element.Value = X;

    if (Col > L->URegion.Element.Col) 
        {                                           //�����У��ھ��������Ԫ��
        L->URegion.Element.Col = Col;              //�ж��Ƿ��ھ��������Ԫ�أ��Ǿ�����
        while (L->Right != L0)
            {
            L = L->Right;                         // �ҵ����һ��Ԫ��
            }   
        L->Right=(GList)malloc(sizeof(struct GNode));   
        memset(L->Right, 0, sizeof(struct GNode));
        L = L->Right;
        L->Right = L0;
        L->Down = L_add;                         // ����Ԫ��
        L_add->Down = L;  
        L->URegion.Element.Col = Col;
        L0->URegion.Element.Value++;            //����Ԫ������
        L->URegion.Element.Value++;
        }
    else
        {                                      //Locatde in Matrix,��ԭ�еľ��������Ԫ��
        L_flag=L;  
        while (L->Right->URegion.Element.Col <= Col && L->Right != L_flag)  //��λ
            {
            L = L->Right;
            }
        L_local = L;          //��¼�е�ַ
        if (L->URegion.Element.Col == Col) 
            {   //��ȣ�����������
            L_flag = L;
            while (L->Down->URegion.Element.Row <= Row && L->Down != L_flag)
                {
                L = L->Down;
                }
            if (L->URegion.Element.Row == Row) 
                {
                printf("Date already exists,Do you want to replace it? Y/N\n");
                char Order;
                getchar();
                scanf("%c", &Order);
                if ((Order == 'Y')|(Order == 'y') )
                L->URegion.Element.Value = X;    //�滻��ǰֵ
                free(L_add);         //�ͷ���Ԫ��ָ��
                return 0;
                }
            else
                {
                L_flag = L->Down;       //����Ԫ��
                L->Down = L_add;
                L_add->Down = L_flag;
                L0->URegion.Element.Value++;
                L_local->URegion.Element.Value++;  //�м�����һ
                }
            }
        else
            {          //����ȣ������м����²���һ��
            L_flag = L->Right;
            L->Right = (GList)malloc(sizeof(struct GNode));
            memset(L->Right, 0, sizeof(struct GNode));
            L = L->Right;
            L->Right = L_flag;
            L->Down = L_add;        // ����Ԫ��
            L_add->Down = L;        //Downָ��Head
            //L0->URegion.Element.Col++;
            L->URegion.Element.Col = Col;
            L0->URegion.Element.Value++;
            L_local->Right->URegion.Element.Value++;  //�м�����һ
            }
        }

    L = L0;            //������
    if (Row > L->URegion.Element.Row) 
        {     //�ھ����������
        L->URegion.Element.Row = Row;
        while (L->Down != L0)
            {
            L = L->Down;        //���ҵ����һ��
            }
        L->Down = (GList)malloc(sizeof(struct GNode));
        memset(L->Down, 0, sizeof(struct GNode));
        L = L->Down;
        L->URegion.Element.Row = Row;
        L->Down = L0;
        L->Right = L_add;
        L_add->Right = L;
        L->URegion.Element.Value++;
        }
    else 
        {           //�ھ����ڲ���Ԫ��
        L_flag = L;
        while (L->Down->URegion.Element.Row <= Row && L->Down != L_flag)
            {
            L = L->Down;
            }
        L_local = L;
        if (L->URegion.Element.Row == Row)
            {   
            L_flag = L;
            while (L->Right->URegion.Element.Col <= Col && L->Right != L_flag)
                {
                L = L->Right;
                }
            if (L->URegion.Element.Col == Col) 
                {
                printf("Date already exists,Do you want to replace it? Y/N\n");
                char Order;
                getchar();
                scanf("%c", &Order);
                if ((Order == 'Y') | (Order == 'y'))
                    {
                    L->URegion.Element.Value = X; //�滻��ǰֵ
                    }
                free(L_add);                     //�ͷ���Ԫ��ָ��
                return 0;
                }
            else
                {
                L_flag = L->Right;       //����Ԫ��
                L->Right = L_add;
                L_add->Right = L_flag;
                L_local->URegion.Element.Value++;
                }
            }
        else
            {
            L_flag = L->Down;
            L->Down = (GList)malloc(sizeof(struct GNode));
            memset(L->Down, 0, sizeof(struct GNode));
            L = L->Down;
            L->Down = L_flag;
            L->Right = L_add;
            L->URegion.Element.Row = Row;
            L_add->Right = L;     // ָ��Head
            L_local->Down->URegion.Element.Value++;
            }
        }
    }

Location Add_location()
    {
     Location List;
     List = (Location)malloc(sizeof(struct location));
     if (List == NULL) 
         {
          printf("Failed to creat Location list!\n");
          return NULL;
         }
     memset(List, 0, sizeof(struct location));
     return List;
    }


/*����*/
Location Find(GList L)
    {
    int x;
    GList L0,L_down;
    Location List_local,List_local_0;//��λָ������
    List_local_0 = List_local = Add_location();
    if (L->Down == 0 | L->Right == 0)
        {
        printf("This is an empty matrix!\n "); 
        free(List_local);
        }
    else
        { 
        printf("Enter the element you want to find:\n ");
        scanf("%d", &x); 
        L0 = L;
        L_down = L->Down;//��¼��һ��
        L = L->Down;// ָ���һ��
        while ( L!=L0)
            {
            L = L->Right;//ָ���һ������
            while (L != L_down)
                {
                if (L->URegion.Element.Value == x)
                    {   
                    List_local->Next = Add_location();
                    List_local = List_local->Next;
                    List_local_0->Sum++;
                    List_local->Row = L->URegion.Element.Row;
                    List_local->Col = L->URegion.Element.Col;
                    }
                L = L->Right;//go to next element
                }
            L = L_down->Down;
            L_down = L_down->Down;
            }
        return List_local_0;
        }
    }


/*��ӡ*/
int my_printf_matrix(GList L)
    {
    GList L0,L_Down;
    int Zero = 0;
    int i,j,Row,Col;
    if (L->URegion.Element.Row == 0)
        {
        printf("This is an empty matrix!\n");
        return -1;
        }
    Row = L->URegion.Element.Row;
    Col = L->URegion.Element.Col; 
    L_Down =L= L->Down;    //ָ���һ��
    for (i = 1; i <= Row; i++)
        {
        if (i == L->URegion.Element.Row)
            {
            L = L->Right;
            for (j = 1; j <= Col; j++)
                {
                if (j == L->URegion.Element.Col && L!=L_Down)
                    {
                    printf("%5d\t", L->URegion.Element.Value);
                    L = L->Right;
                    }
                else
                    {
                    printf("%5d\t", Zero);
                    }
                }
            L = L_Down->Down;
            L_Down = L_Down->Down;
            }
        else
            {
            for (j = 0; j < Col; j++)
                {
                printf("%5d\t", Zero);
                }
            }
        printf("\n");
        }
}

int my_printf_local(Location local_list)
    {
    local_list = local_list->Next;
    if (NULL == local_list)
        {
        printf("There is no the num.\n");
        }
    else
        {
        printf("Your find num is located:\n");
        while (local_list != NULL)
            {
            printf("(%d,%d)", local_list->Row, local_list->Col);
            local_list = local_list->Next;
            }
        }
    }