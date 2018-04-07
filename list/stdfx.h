/*************************************************************************
	> File Name: stdfx.h
	> Author: 
	> Mail: 
	> Created Time: 2018年04月07日 星期六 11时30分01秒
 ************************************************************************/

#ifndef _STDFX_H
#define _STDFX_H

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define _bool_      int
#define _true_      0
#define _false_     1
#define _empty_     0
#define _unempty_   1

typedef int elementType;

typedef struct node
{
    elementType  data;
    struct node* next;
}Node;
#define size_node sizeof(Node)

typedef Node* List;

List reversion(List l);

#endif
