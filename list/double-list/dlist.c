/*************************************************************************
	> File Name: dlist.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月21日 星期六 17时29分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>

typedef int elementType;
typedef struct node
{
    struct node* prev;
    elementType  data;
    struct node* next;
}Node;
typedef Node* Dlist;

Dlist init_dlist(Dlist dl)
{
    if(NULL != dl)
    {
        printf("error: abnomal\n");

        return dl;
    }

    dl = (Dlist)malloc(sizeof(Node));
    if(NULL == dl)
    {
        printf("error: abnormal\n");

        return dl;
    }

    dl->prev = NULL;
    dl->data = -1;
    dl->next = NULL;

    return dl;
}

Dlist insert_dlist(Dlist dl, elementType data)
{
    if(NULL == dl)
    {
        printf("error: abnormal\n");

        return dl;
    }

    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("error: insert faliure\n");

        return dl;
    }
    q->prev = NULL;
    q->data = data;
    q->next = NULL;

    Node* p = dl;
    if(NULL == p->next)
    {
        p->next = q;
        q->prev  = p;
        p = NULL;

        return dl;
    }
    q->prev = p;
    q->next = p->next;
    p = p->next;
    dl->next = q;
    p->prev = q;
    p = NULL;

    return dl;
}

void print_dlist(Dlist dl)
{
    if(NULL == dl || NULL == dl->next)
    {
        printf("error: abnormal\n");

        return;
    }

    printf("dlistP:   ");
    Node* p = dl->next;
    Node* pr = NULL;
    while(p)
    {
        printf("%d ", p->data);
        if(NULL == p->next)
        {
            pr = p;
        }
        p = p->next;
    }
    
    printf("\ndlistPR:  ");
    while(dl != pr)
    {
        printf("%d ", pr->data);
        pr = pr->prev;
    }
    printf("\n");

    pr = NULL;
}

Dlist destory_dlist(Dlist dl)
{
    if(NULL == dl)
    {
        printf("error: abnormal\n");

        return dl;
    }

    Node* p = dl;
    while(p->next)
    {
        p = p->next;
        free(p->prev);
        p->prev = NULL;
    }

    free(p);
    p = NULL;
    dl = NULL;

    return dl;
}

int main()
{
    Dlist DL = NULL;
    DL = init_dlist(DL);
    if(NULL == DL)
    {
        printf("error: abnormal\n");

        return 0;
    }
    
    DL = insert_dlist(DL, 5);
    DL = insert_dlist(DL, 4);
    DL = insert_dlist(DL, 3);
    DL = insert_dlist(DL, 2);
    DL = insert_dlist(DL, 1);

    print_dlist(DL);

    DL = destory_dlist(DL);

    return 0;
}

