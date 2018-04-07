/*************************************************************************
	> File Name: reversion.c
	> Author: 
	> Mail: 
	> Created Time: 2018年04月07日 星期六 11时29分33秒
 ************************************************************************/

#include<stdio.h>
#include"stdfx.h"

List reversion(List l)
{
    Node* p = l;
    if(NULL == p && NULL == p->next)
    {
        return NULL;
    }

    p = p->next;
    l->next = NULL;
    Node* pr = p;

    Node* q = NULL;
    while(p)
    {
        pr = p->next;
        p->next = q;
        q = p;
        p = pr;
    }
    l ->next = q;

    q = NULL;
    pr = NULL;
    p = NULL;

    return l;
}
