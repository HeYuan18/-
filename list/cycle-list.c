/********************************************************************
    > File  : cycle-list.c
	> Author: Karma1996
	> Mail:   Karma1996@foxmail.com
	> Created Time: 2018年05月22日 星期二 15时52分02秒
 ********************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<stdbool.h>

typedef int elementType;

typedef struct node
{
    elementType     data;
    struct node*    next;
}Node;
typedef Node* List;
typedef struct cycleList
{
    int     len;
    List    list;
}Clist;

Clist init_clist(void)
{
    Clist cl;
    cl.len = 0;
    cl.list = NULL;
    cl.list = (Node*)malloc(sizeof(Node));
    if(NULL == cl.list)
    {
        printf("err: init\n");

        return cl;
    }
    cl.list->data = 0;
    cl.list->next = NULL;

    return cl;
}

bool is_empty(Clist cl)
{
    if(0 == cl.len || NULL == cl.list)
    {
        return true;
    }

    return false;
}

Clist head_insert(Clist cl, elementType data)
{
    if(NULL == cl.list)
    {
        printf("err: head_insert\n");

        return cl;
    }
    
    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("err: head_insert\n");

        return cl;
    }
    q->data = data;
    q->next = NULL;
    
    int clen = cl.len + 1;
    Node* p = cl.list;
    q->next = p->next;
    p->next = q;
    p = q;
    while(--clen)
    {
        p = p->next;
    }
    p->next = q;
    p = NULL;
    q = NULL;

    ++cl.len;
    
    return cl;
}

Clist tail_insert(Clist cl, elementType data)
{
    if(NULL == cl.list)
    {
        printf("err: tail_insert\n");

        return cl;
    }

    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("err: tail_insert\n");

        return cl;
    }
    q->data = data;
    q->next = cl.list->next;

    int clen = cl.len + 1;
    Node* p = cl.list;
    while(--clen)
    {
       p = p->next; 
    }
    p ->next = q;
    p = NULL;
    q = NULL;

    ++cl.len;
    
    return cl;
}

Clist delete_list(Clist cl, int pos)
{
    if(0 >= pos || pos > cl.len)
    {
        printf("err: delete\n");

        return cl;
    }
    if(is_empty(cl))
    {
        printf("err: delete\n");

        return cl;
    }

    int i = 1;
    Node* p = cl.list;
    while(pos != i)
    {
        p = p->next;
        ++i;
    }
    Node* q = p->next;
    if(cl.len == pos)
    {
        p->next = cl.list->next;
        free(q);
    }
    else
    {
        p->next = q->next;
        free(q);
        if(1 == pos)
        {
            while(cl.len == i)
            {
                p = p->next;
                ++i;
            }
            p->next = cl.list->next;
        }
    }
    --cl.len;
    q = NULL;
    p = NULL;
    
    return cl;
}

void print_list(Clist cl, int start)
{
    if(is_empty(cl))
    {
        printf("err: print\n");

        return;
    }
    
    printf("len=%d\ncycle-list: ", cl.len);
    int i = 0;
    start = start % (cl.len + 1);
    if(0 == start)
    {
        ++start;
    }
    Node* p = cl.list;
    while(start != i)
    {
        p = p->next;
        ++i;
    }
    i = cl.len;
    while(i--)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

Clist destory_list(Clist cl)
{
    if(NULL == cl.list)
    {
        cl.len = 0;

        return cl;
    }

    Node* p = cl.list->next;
    Node* q = p;
    while(cl.len--)
    {
        q = p->next;
        free(p);
        p = q;
    }
    q = NULL;
    p = NULL;
    
    free(cl.list);
    cl.list = NULL;

    return cl;
}

int main()
{
    Clist Cl = init_clist();

    Cl = head_insert(Cl, 5);
    Cl = head_insert(Cl, 4);
    Cl = head_insert(Cl, 3);
    Cl = head_insert(Cl, 2);
    Cl = head_insert(Cl, 1);
    Cl = tail_insert(Cl, 6);
    Cl = tail_insert(Cl, 7);
    Cl = tail_insert(Cl, 8);
    Cl = tail_insert(Cl, 9);

    for(int i = 1; i <= Cl.len; ++i)
    {
        print_list(Cl, i);
    }

    Cl = destory_list(Cl);

    return 0;
}
