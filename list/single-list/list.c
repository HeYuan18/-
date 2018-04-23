/*************************************************************************
	> File Name: list.c
	> Author: HeYuan
	> Mail: HeYuan951@Gmail.com
	> Created Time: 2018年04月21日 星期六 20时06分28秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>

typedef int elementType;
typedef struct node
{
    elementType data;
    struct node* next;
}Node;
typedef Node* List;

List init_list(List l)
{
    if(NULL != l)
    {
        printf("error: abnormal\n");

        return l;
    }

    l = (List)malloc(sizeof(Node));
    if(NULL == l)
    {
        printf("error: abnormal\n");

        return l;
    }
    l->data = -1;
    l->next = NULL;

    return l;
}

bool is_empty(List l)
{
    if(NULL == l)
    {
        printf("error: abnormal\n");

        return true;
    }
    if(NULL == l->next)
    {
        printf("listP: empty\n");

        return true;
    }

    return false;
}

List head_insert(List l, elementType data)
{
    if(NULL == l)
    {
        printf("error: abnormal\n");

        return l;
    }

    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("error: insert falure\n");

        return l;
    }
    q->data = data;
    q->next = NULL;

    if(NULL == l->next)
    {
        l ->next = q;
        q = NULL;

        return l;
    }
    Node* p  = l;
    q->next = p->next;
    p->next = q;

    p = NULL;
    q = NULL;
    
    return l;
}

List tail_insert(List l, elementType data)
{
    if(NULL == l)
    {
        printf("error: abnormal\n");

        return l;
    }

    Node* q = (Node*)malloc(sizeof(Node));
    if(NULL == q)
    {
        printf("error: insert falure\n");

        return l;
    }
    q->data = data;
    q->next = NULL;

    Node* p = l;
    while(p->next)
    {
        p = p->next;
    }
    p->next = q;
    
    p = NULL;
    q = NULL;

    return l;
}

Node* get_node(List l, int position)     //起点->1
{
    if(true == is_empty(l))
    {
        return NULL;
    }

    Node* p = l->next;
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

List delete_Node(List l, int position)
{
    if(true == is_empty(l))
    {
        return l;
    }

    if(1 == position)           //case 0:首节点
    {
        Node* p = l;
        Node* q = l->next;

        p->next = q->next;

        free(q);
        q = NULL;
        p = NULL;

        return l;
    }

    Node *p = get_node(l, position - 1);
    if(NULL == p || NULL == p->next)
    {
        return l;
    }

    Node* q = p->next;          //q->要删除的节点
    if(NULL == q->next)         //case 1:末尾节点
    {
        p->next = NULL;
        free(q);
        q = NULL;
        p = NULL;

        return l;
    }
    
    p->next = q->next;          //case 2:中间节点
    q->next = NULL;

    free(q);
    q = NULL;
    p = NULL;

    return l;
}

List reversion_list(List l)
{
    if(true == is_empty(l))
    {
        return l;
    }

    Node* p = l->next;
    Node* np = p->next;
    Node* r = p;
    
    l->next = NULL;
    r->next = NULL;

    while(np)
    {
        p = np;
        np = np->next;
        p->next = r;
        r = p;
    }
    l->next = r;

    r =  NULL;
    np = NULL;
    p =  NULL;

    return l;
}

Node* recurrence_reversion(Node* pre, Node* cur)
{
    if(NULL == cur->next)
    {
        cur->next = pre;

        return cur;
    }

    Node* next = cur->next;
    cur->next = pre;
    Node* head = recurrence_reversion(cur, next);

    return head;
}

Node* recurrence_reversion_list(Node* root)     //真.递归版单链表逆置
{
    if(NULL == root)
    {
        return root;
    }

    return recurrence_reversion(NULL, root);
}

Node* recurrence_reversion_list0(Node* root)     //递归版单链表逆置
{
    if(NULL == root)
    {
        return root;
    }

    Node* p = recurrence_reversion_list0(root->next);
    if(NULL == p)
    {
        return root;
    }

    Node* q = p;
    while(q->next)
    {
        q = q->next;
    }

    q->next = root;
    root->next = NULL;
    root = p;
    q = NULL;
    p = NULL;
    
    return root;
}

void print_list(List l)
{
    if(NULL == l)
    {
        printf("error: abnormal\n");

        return;
    }
    if(NULL == l->next)
    {
        printf("list: empty\n");
        return;
    }

    printf("listP: ");
    Node* p = l->next;
    while(p)
    {
        printf("%d ", p->data);
        p = p->next;
    }
    printf("\n");
}

List destory_list(List l)
{
    if(NULL == l)
    {
        printf("error: abnormal\n");

        return l;
    }

    Node* p = l;
    Node* pr = l->next;
    while(pr)
    {
        free(p);
        p = pr;
        pr = pr->next;
    }
    pr = NULL;
    free(p);
    p = NULL;
    l = NULL;

    return l;
}

int main()
{
    List L = NULL;
    L = init_list(L);
    if(NULL == L)
    {
        return 0;
    }

    L = head_insert(L, 5);
    L = head_insert(L, 4);
    L = head_insert(L, 3);
    L = head_insert(L, 2);
    L = head_insert(L, 1);
    L = tail_insert(L, 6);
    L = tail_insert(L, 7);
    L = tail_insert(L, 8);
    L = tail_insert(L, 9);
    L = tail_insert(L, 10);

    print_list(L);

    L = delete_Node(L, 10);
    L = delete_Node(L, 6);
    L = delete_Node(L, 5);
    L = delete_Node(L, 1);
    
    print_list(L);

    //L = reversion_list(L);
    L->next = recurrence_reversion_list(L->next);

    print_list(L);

    L = destory_list(L);

    return 0;
}
