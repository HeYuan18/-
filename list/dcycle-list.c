/*************************************************************************
	> File Name: dcycle-list.c
	> Author: karma1996
	> Mail: karma1996@foxmail.com
	> Created Time: 2018年05月25日 星期五 20时42分12秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

#define tail 0
#define head 1

typedef int elementType;

typedef struct node
{
    struct node*    prev;
    elementType     data;
    struct node*    next;
}Node;
typedef Node* List;

typedef struct dclist
{
    int     len;
    List    list;
}DClist;

bool init_list(DClist* const dcl)
{
    dcl->len = 0;
    dcl->list = NULL;

    dcl->list = (List)malloc(sizeof(Node));
    if(NULL == dcl->list)
    {
        printf("err: init\n");

        exit(0);
    }
    dcl->list->prev = NULL;
    dcl->list->data = 0;
    dcl->list->next = NULL;

    return true;
}

bool is_empty(DClist dcl)
{
   if(0 == dcl.len || NULL == dcl.list)
    {
        return true;
    }

    return false;
}

bool insert(DClist* const dcl, elementType data, int kind)      //kind偶数尾插，奇数头插
{
    if(NULL == dcl->list)
    {
        printf("err: insert\n");

        return false;
    }
    
    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("err: insert\n");

        return false;
    }
    q->prev = NULL;
    q->data = data;
    q->next = NULL;
    
    kind %= 2;
    Node* p = dcl->list;
    if(0 == dcl->len)
    {
        q->prev = q;
        q->next = q;
    }
    else
    {
        q->prev = p->next->prev;
        q->next = p->next;
        p->next->prev = q;
        q->prev->next = q;
    }
    if(kind)
    {
        p->next = q;
    }
    p = NULL;
    q = NULL;

    ++(dcl->len);

    return true;
}

bool delete_list(DClist* const dcl, int pos)
{
    if(0 >= pos || pos > dcl->len)
    {
        printf("err: delete_list\n");

        return false;
    }
    if(is_empty(*dcl))
    {
        printf("err: delete_list\n");

        return false;
    }

    int i = 1;
    Node* p = dcl->list;
    while(pos != i)
    {
        p = p->next;
        ++i;
    }
    Node* q = p->next;
    if(1 == dcl->len)
    {
        free(q);
        p->next = NULL;
    }
    else
    {
        p->next = q->next;
        if(1 == pos)
        {
            q->next->prev = q->prev;
            q->prev->next = q->next;
        }
        else
        {
            q->next->prev = q->prev;
        }
        free(q);
    }
    q = NULL;
    p = NULL;

    --(dcl->len);

    return true;
}

void print_list(DClist dcl, int pos)
{
    if(is_empty(dcl))
    {
        printf("err: print_list\n");

        return;
    }
    pos = 0 == pos ? 1 : pos;
    pos %= (dcl.len + 1);

    int i = 0;
    Node* p = dcl.list;
    while(pos != i)
    {
        p = p->next;
        ++i;
    }
    Node* q = p;
    
    printf("-> ");
    for(i = 0; i < dcl.len; ++i)
    {
        printf("%d ", q->data);
        q = q->next;
    }
    printf(" len=%d\n", dcl.len);
    q = NULL;

    printf("<- ");
    for(i = 0; i < dcl.len; ++i)
    {
        printf("%d ", p->data);
        p = p->prev;
    }
    printf("\n");
    p = NULL;
}

bool destory_list(DClist* const dcl)
{
    if(NULL == dcl->list)
    {
        return true;
    }

    int i = 0;
    Node* p = dcl->list;
    Node* q = p;
    while(dcl->len >= i)
    {
        q = q->next;
        free(p);
        p = q;
        ++i;
    }
    q = NULL;
    p = NULL;

    dcl->len = 0;

    return true;
}

int main()
{
    DClist DCL;
    init_list(&DCL);
    insert(&DCL, 5, head);
    insert(&DCL, 4, head);
    insert(&DCL, 3, head);
    insert(&DCL, 2, head);
    insert(&DCL, 1, head);

    insert(&DCL, 6,tail);
    insert(&DCL, 7,tail);
    insert(&DCL, 8,tail);
    insert(&DCL, 9,tail);

    int i = 1,len = DCL.len;
    for(; i <= len; ++i)
    {
        print_list(DCL, i);
        delete_list(&DCL, DCL.len);
    }
    
    destory_list(&DCL);

    return 0;
}
