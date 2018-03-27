/*************************************************************************
	> File Name: list.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 14时36分06秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define BOOL int
#define LINK_LIST_EMENTY 0
#define LINK_LIST_UNEMENTY 1

typedef int ElementType;

typedef struct node
{
    ElementType data;
    struct node *next;
}Node;

typedef Node *List;

/*创建空链表*/
List MakeEmpty(void)
{
    Node *l;
    l = (Node*)malloc(sizeof(Node));
    if(l == NULL)
    {
        printf("申请内存失败!\n");

        return NULL;
    }

    l->data = 0;
    l->next = NULL;

    return l;
}

/*判断链表是否为空*/
BOOL Is_Ementy(List L)
{
    if (NULL == L->next)
    {
        return LINK_LIST_EMENTY;
    }
    else
    {
        return LINK_LIST_UNEMENTY;
    }
}

/*得到链表头节点*/
List GetHead(List L)
{
    if (NULL != L)
    {
        return L;
    }
    else
    {
        return NULL;
    }
}

/*得到第一个节点*/
Node *GetFirst(List L)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!\n");
        return NULL;
    }

    Node *p = L;
    
    p = p->next;

    return p;
}

/*得到链表长度*/
int GetLength(List L)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!");
        return 0;
    }

    int length = 0;
    while (NULL != L->next)
    {
        ++length;
        L = L->next;
    }

    return length;
}

/*得到元素所在位置*/
int *GetPoint(List L, ElementType data)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!\n");
        return NULL;
    }

    int *arr;
    arr = malloc(sizeof(int) * (GetLength(L)));
    memset(arr, 0 , sizeof(GetLength(L)));

    int count = 0;
    while (NULL != L->next)
    {
        L = L->next;
        if (data == L->data)
        {
            arr[count] = 1;
        }
        ++count;
    }

    return arr;
}

/*查找第i个元素*/
Node* GetNode(List L, int point)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!\n");
        return NULL;
    }
    
    Node *p = L;

    if (1 == point)
    {
        p = GetFirst(L);
    }
    else
    {
        int i = 0;
        while (p != NULL && i < point)    /*当未查找到链尾且i小于num时继续查找*/
        {
            p = p->next;
            ++i;
        }
    }

    return p;
}

/*头插法*/
List InsertHead(List L, ElementType data)
{
    Node *temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;

    Node *p = L;
    p = p->next;
    L->next = temp;
    (L->next)->next = p;

    return L;
}

/*尾插法*/
List InsertTail(List L, ElementType data)
{
    Node *temp;
    temp = (Node*)malloc(sizeof(Node));
    temp->data = data;
    temp->next = NULL;

    Node *p = L;
    while (p->next != NULL)
    {
        p = p->next;
    }

    p->next = temp;
    
    return L;
}

/*在链表第i个位置插入元素*/
List InsertElement(List L, int num, ElementType data)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!\n");
        return NULL;
    }

    if (0 == num)
    {
        printf("error: num == 0\n");
        exit(1);    /*异常终止*/
    }

    Node *tmp;
    tmp = (Node*)malloc(sizeof(Node));
    tmp->data = data;
    tmp->next = NULL;

    Node *p = GetNode(L, num - 1); 

    tmp->next = p->next;
    p->next = tmp;

    return L;
}

/*删除第i个元素*/
void DeleteElement(List L, int point)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!\n");
        return;
    }

    if (0 == point)
    {
        printf("error: num == 0\n");
        exit(1);
    }
    
    Node *p = GetNode(L, point - 1);

    Node *q;
    q = (Node*)malloc(sizeof(Node));

    if (p == NULL)
    {
        printf("第%d个节点不存在!\n", point - 1);
    }
    else
    {
        if (p->next == NULL)
        {
            printf("第%d个节点不存在!\n", point);
        }
        else
        {
            q = p->next;
            p->next = q->next;

            /*回收临时变量内存*/
            q->next = NULL;
            free(q);
            q = NULL;
        }
    }
}

/*清空链表*/
void ClearList(List L)
{
    L->next = NULL;
}

/*摧毁链表
List DestroyList(List L)
{
    free(L);
    L = NULL;

    return L;
}*/

/*打印链表*/
void PrintList(List L)
{
    if (0 == Is_Ementy(L))
    {
        printf("List Ementy!\n");
        return;
    }

    printf("Print：");
    while(L->next != NULL)
    {
        L = L->next;
        printf("%d\t", L->data);
    }
    putchar(10);
}

/*打印一维数组*/
void PrintArr(int *arr, int length)
{
    for (int i = 0; i < length; ++ i)
    {
        printf("%d\t", arr[i]);
    }
    putchar(10);
}

/*------------------------------------多文件编译--------------------------------------*/
//USL BLL DAL 三层架构

List USLinsertHead(List L)
{
    ElementType elv_tmpInput = 0;   //e:elementType l:local v:variable

    printf("请输入数据：\t");
    scanf("%d", &elv_tmpInput);

    return InsertHead(L, elv_tmpInput);
}

List USLinsertTail(List L)
{
    ElementType elv_tmpInput = 0;   //e:elementType l:local v:variable

    printf("请输入数据：\t");
    scanf("%d", &elv_tmpInput);

    return InsertTail(L, elv_tmpInput);
}

List USLinsertElement(List L)
{
    ElementType elv_tmpInput;
    int ilv_point = 0;

    printf("请输入数据：\t");
    scanf("%d", &elv_tmpInput);
    printf("请输入位置：\t");
    scanf("%d", &ilv_point);
    
    while (ilv_point > GetLength(L))
    {
        if(ilv_point == (1 + GetLength(L)))
        {
            return InsertTail(L, elv_tmpInput);
        }
        printf("位置输入太大，请重新输入：\t");
        scanf("%d", &ilv_point);
    }

    return InsertElement(L, ilv_point, elv_tmpInput);
}

void USLgetLength(List L)
{
    int ilv_length = GetLength(L);

    printf("链表长度：%d\n", ilv_length);
}

void USLGetNode(List L)
{
    int ilv_point = 0;

    printf("请输入位置：\t");
    scanf("%d", &ilv_point);

    while (ilv_point > GetLength(L))
    {
        printf("位置输入太大，请重新输入：\t");
        scanf("%d", &ilv_point);
    }
    
    Node * nlv_tmpNode = GetNode(L, ilv_point);

    printf("data：%d\n", nlv_tmpNode->data);
}

void USLGetPoint(List L)
{
    ElementType elv_tmpInput = 0;
    
    printf("请输入数据：\t");
    scanf("%d", &elv_tmpInput);

    PrintArr(GetPoint(L, elv_tmpInput), GetLength(L));
}

void USLdeleteElement(List L)
{
    int ilv_point = 0;

    printf("请输入位置：\t");
    scanf("%d", &ilv_point);

    while (ilv_point > GetLength(L))
    {
        printf("位置输入太大，请重新输入：\t");
        scanf("%d", &ilv_point);
    }

    DeleteElement(L, ilv_point);
}

void USLprintList(List L)
{
    PrintList(L);
}

void USLclearList(List L)
{
    ClearList(L);
}


List USLdestoryList(List L)
{
    free(L);
    L = NULL;
    
    return L;
}

/*菜单函数*/
void Menu()
{
    printf("-------------------------------\n");
    printf("===============================\n");

    printf("1----------头插法\n");
    printf("2----------尾插法\n");
    printf("3----------在第i个位置插入元素\n");
    printf("4----------得到链表长度\n");
    printf("5----------查找第i个元素\n");
    printf("6----------得到元素所在位置\n");
    printf("7----------删除第i个元素\n");
    printf("8----------打印链表\n");
    printf("9----------清空链表\n");
    printf("10---------摧毁链表\n");
    printf("0----------退出\n");

    printf("-------------------------------\n");
    printf("===============================\n");
}

int main()
{
    List list = MakeEmpty();
    
    int chosen = 0;
    do
    {
        Menu();

        printf("请输入您的选择：<0~10>\n");
        scanf("%d", &chosen);

        switch(chosen)
        {
            case 1:
                list = USLinsertHead(list);
                break;
            case 2:
                list = USLinsertTail(list);
                break;
            case 3:
                list = USLinsertElement(list);
                break;
            case 4:
                USLgetLength(list);
                break;
            case 5:
                USLGetNode(list);
                break;
            case 6:
                USLGetPoint(list);
                break;
            case 7:
                USLdeleteElement(list);
                break;
            case 8:
                USLprintList(list);
                break;
            case 9:
                USLclearList(list);
                break;
            case 10:
                list = USLdestoryList(list);
                chosen = 0;
                //break;
            case 0:
                printf("正在退出系统...\n");
                break;
            default:
                printf("<请输入整形数字０～１０!>\n");
        }

    }while(0 != chosen);
    
    return 0;
}
