/*************************************************************************
	> File Name: double-list.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月21日 星期六 17时29分21秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

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

bool is_empty(Dlist dl)
{
    if(NULL == dl)
    {
        printf("error: abnormal\n");

        return true;
    }
    if(NULL == dl->next)
    {
        printf("dlistP: empty\n");

        return true;
    }

    return false;
}

Dlist head_insert(Dlist dl, elementType data)
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
        q = NULL;

        return dl;
    }
    q->prev = p;
    q->next = p->next;
    p = p->next;
    dl->next = q;
    p->prev = q;
    p = NULL;
    q = NULL;

    return dl;
}

Dlist tail_insert(Dlist dl, elementType data)
{
    if(NULL == dl)
    {
        printf("error: abnormal\n");

        return dl;
    }

    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("error: insert falure\n");

        return dl;
    }
    q->prev = NULL;
    q->data = data;
    q->next = NULL;

    Node* p = dl;
    while(p->next)
    {
        p = p->next;
    }
    p->next = q;
    q->prev = p;

    p = NULL;
    q = NULL;

    return dl;
}

Node* get_node(Dlist dl, int position)  //起点->1
{
    if(true == is_empty(dl))
    {
        return NULL;
    }

    Node* p = dl->next;
    while((--position) && (p))
    {
        p = p->next;
    }

    if(0 == position)
    {
        return p;
    }

    return NULL;
}

Dlist delete_node(Dlist dl, int position)
{
    if(true == is_empty(dl))
    {
        return dl;
    }

    if(1 == position)
    {
        Node* p = dl;
        Node* q = dl->next;

        p->next = q->next;
        (q->next)->prev = p;
        
        free(q);
        q = NULL;
        p = NULL;

        return dl;
    }

    Node* p = get_node(dl, position - 1);
    if(NULL == p || NULL == p->next)
    {
        return dl;
    }

    Node* q = p->next;
    if(NULL == q->next)
    {
        p->next = NULL;
        
        free(q);
        q = NULL;
        p = NULL;

        return dl;
    }

    p->next = q->next;
    (q->next)->prev = p;

    free(q);
    q = NULL;
    p = NULL;

    return dl;
}

void print_dlist(Dlist dl)
{
    if(true == is_empty(dl))
    {
        return ;
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
    
    DL = head_insert(DL, 5);
    DL = head_insert(DL, 4);
    DL = head_insert(DL, 3);
    DL = head_insert(DL, 2);
    DL = head_insert(DL, 1);
    DL = tail_insert(DL, 6);
    DL = tail_insert(DL, 7);
    DL = tail_insert(DL, 8);
    DL = tail_insert(DL, 9);
    DL = tail_insert(DL, 10);

    print_dlist(DL);

    DL = delete_node(DL, 6);
    DL = delete_node(DL, 5);

    print_dlist(DL);

    DL = destory_dlist(DL);

    return 0;
}
