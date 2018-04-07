/*************************************************************************
	> File Name: list.c
	> Author: 
	> Mail: 
	> Created Time: 2017年09月23日 星期六 14时36分06秒
 ************************************************************************/

#include"stdfx.h"

/*打印一维数组*/
void printArr(const int* const arr, int len)
{
    const int* p = arr;
    int i = 0;
    for (; i < len; ++i)
    {
        printf("%d\t", p[i]);
    }
    printf("\n");

    p = NULL;
}

/*链表初始化*/
List listInit()
{
    Node* l = NULL;

    l = (Node*)malloc(size_node);
    if(NULL == l)
    {
        printf("内存分配失败\n");

        return NULL;
    }

    l->data = 0;
    l->next = NULL;

    return l;
}

_bool_ isEmpty(const List l)
{
    if(NULL == l)
    {
        printf("链表异常\n");
        
        exit(1);
    }
    if(NULL == l->next)
    {
        return _empty_;
    }
    else
    {
        return _unempty_;
    }
}

/*获取链表头*/
List getLHead(const List l)
{
    if(NULL == l)
    {
        printf("链表异常\n");

        exit(1);
    }

    Node* p = l;

    return p;
}

/*获取链表第一个节点*/
Node* getLFNode(const List l)
{
    if(NULL != l && NULL != l->next)
    {
        Node* p = l->next;

        return p;
    }
    else
    {
        return NULL;
    }
}

/*获取链表长度*/
int getLLen(const List l)
{
    if(_empty_ == isEmpty(l))
    {
        printf("empty...!\n");

        return 0;
    }

    int len = 0;
    Node* p = l->next;

    while(NULL != p)
    {
        ++len;
        p = p->next;
    }

    return len;
}

/*获取元素所在位置*/
_bool_ getEPos(const List l, elementType data)
{
    if(_empty_ == isEmpty(l))
    {
        printf("empty...\n");
        
        return _false_;
    }

    Node* p = l->next;
    int count = 0;
    int len = getLLen(l);
    int* arr = malloc(sizeof(int) * len);
    memset(arr, 0 , len);

    while(NULL != p)
    {
        p = p->next;
        if(data == p->data)
        {
            arr[count] = 1;
        }
        ++count;
    }

    printArr(arr, len);
    free(arr);
    arr = NULL;
    p = NULL;

    return _true_;
}

/*获取i号位置元素*/
Node* getINode(const List l, int pos)
{
    if(_empty_ == isEmpty(l))
    {
        printf("empty...\n");

        return NULL;
    }

    Node* p = l->next;
    int i = 1;

    while(NULL != p && i < pos)
    {
        p = p->next;
        ++i;
    }

    return p;
}

/*头插法*/
List insertHead(List const l, elementType data)
{
    Node* tmp = (Node*)malloc(size_node);
    tmp->data = data;
    tmp->next = NULL;

    Node* p = l->next;
    l->next = tmp;          //tmp->next = p;
    (l->next)->next = p;    //l->next = tmp;

    return l;
}

/*尾插法*/
List insertTail(List const l, elementType data)
{
    Node* tmp = (Node*)malloc(size_node);
    tmp->data = data;
    tmp->next = NULL;
    
    Node* p = l;
    while(NULL != p->next)
    {
        p = p->next;
    }
    p->next = tmp;
    
    return l;
}

/*链表第i号位插入元素*/
List insertIPos(List const l, elementType data, int pos)
{
    if(_empty_ == isEmpty(l))
    {
        printf("empty...\n");

        return NULL;
    }
    if(0 == pos)
    {
        printf("pos范围：1~n\n");

        return NULL;
    }

    Node* tmp = (Node*)malloc(size_node);
    tmp->data = data;
    tmp->next = NULL;

    Node* p = getINode(l, pos - 1); 

    tmp->next = p->next;
    p->next = tmp;

    return l;
}

/*删除第i个元素*/
_bool_ deleteIPos(List const l, int pos)
{
    if(_empty_ == isEmpty(l))
    {
        printf("empty...\n");

        return _false_;
    }
    if(0 == pos)
    {
        printf("pos范围：1~n\n");

        return _false_;
    }
    
    Node* p = getINode(l, pos - 1);

    Node* q = (Node*)malloc(size_node);

    if(NULL == p)
    {
        printf("第%d个节点不存在!\n", pos - 1);

        return _false_;
    }
    else
    {
        if(NULL == p->next)
        {
            printf("第%d个节点不存在!\n", pos);

            return _false_;
        }
        else
        {
            q = p->next;
            p->next = q->next;

            q->next = NULL;
            free(q);
            q = NULL;
        }
    }

    return _true_;
}

/*链表置数*/
_bool_ memsetList(List const l, elementType data)
{
    if(_empty_ == isEmpty(l))
    {
        return _false_;
    }
    
    Node* p = l->next;
    while(NULL != p)
    {
        p->data = data;
        p = p->next;
    }

    return _true_;
}

/*销毁链表*/
List destroyList(List l)
{
    Node* p = l;
    while(NULL != l)
    {
        p = l;
        l = p->next;
        
        free(p);
        p = NULL;
    }

    return l;
}

/*打印链表*/
void printList(const List const l)
{
    if (_empty_ == isEmpty(l))
    {
        printf("empty...\n");

        return;
    }

    Node* p = l->next;
    while(NULL != p)
    {
        printf("%d\t", p->data);
        p = p->next;
    }
    printf("\n");

    p = NULL;
}

int main()
{
    List list = listInit();

    list = insertHead(list, 4);
    list = insertHead(list, 3);
    list = insertHead(list, 2);
    list = insertHead(list, 1);
    printf("len=%d\n", getLLen(list));
    printList(list);

    list = insertIPos(list, 5, 5);
    list = insertIPos(list, 6, 6);
    printf("len=%d\n", getLLen(list));
    printList(list);

    list = insertTail(list, 7);
    list = insertTail(list, 8);
    list = insertTail(list, 9);
    list = insertTail(list, 10);
    printf("len=%d\n", getLLen(list));
    printList(list);

    list = reversion(list);
    printList(list);

    deleteIPos(list, 4);
    deleteIPos(list, 4);
    deleteIPos(list, 4);
    deleteIPos(list, 4);
    printf("len=%d\n", getLLen(list));
    printList(list);

    memsetList(list, 0);
    printf("len=%d\n", getLLen(list));
    printList(list);

    list = destroyList(list);
    
    return 0;
}
