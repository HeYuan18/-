/*************************************************************************
	> File Name: hashTable.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月10日 星期日 11时42分06秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

/*
 *1.定义一个指针数组
 *2.数组的初始化形式：size = 5
 *      0--->head1--->null
 *      1--->head2--->null
 *      2--->head3--->null
 *      3--->head4--->null
 *      4--->head5--->null
 *      
 *
 */

#define size 5
 
typedef struct node
{
    int data;
    struct node* next;
}Node;
typedef Node* List;

typedef struct hash
{
    List arr[size];
}hashTable;

hashTable hashLink;

Node* createNode()
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = 0;
    node->next = NULL;

    return node;
}

void initHashTable()
{
    for(int i = 0; i < size; ++i)
    {
        hashLink.arr[i] = createNode();
    }
}

int hash(int value)
{
    return value % size;
}

Node* findDataT(int data)
{
    int key = hash(data);

    Node* tmp = hashLink.arr[key]->next;
    while(tmp)
    {
        if(tmp->data == data)
        {
            return tmp;
        }

        tmp = tmp->next;
    }

    return NULL;
}

void insertNumber()  //遇0结束
{
    int value = 0;
    int key = 0;

    printf("please input data:\n");
    scanf("%d", &value);
    if(findDataT(value) == NULL)
    {
        while(value != 0)
        {
            key = hash(value);

            Node* node = createNode();
            node->data = value;
            node->next = hashLink.arr[key]->next;
            hashLink.arr[key]->next = node;

            scanf("%d", &value);
        }
    }
}

void deleteNumber()
{
    int value = 0;
    printf("please input data to Delete:");
    scanf("%d", &value);
    
    if(findDataT(value))
    {
        int key = hash(value);

        Node* previous = hashLink.arr[key];
        Node* del = hashLink.arr[key]->next;
        while(del)
        {
            if(del->data == value)
            {
                previous->next = del->next;
                free(del);
            }

            previous = previous->next;
            del = del->next;
        }
    }
}

void findData()
{
    int data = 0;
    printf("Please input data to Find: ");
    scanf("%d", &data);
    int key = hash(data);

    int column = 1;
    int flag = 0;
    Node* tmp = hashLink.arr[key]->next;
    while(tmp)
    {
        if(tmp->data == data)
        {
            flag = 1;
            break;
        }
        ++column;

        tmp = tmp->next;
    }
    
    if(flag)
    {
        printf("data:%d在第[%d]条链的第[%d]列.\n", data, (key + 1), column);
    }
    else
    {
        printf("data:%d没有找到.\n", data);
    }
}

void printHashTable()
{
    for(int i = 0; i < size; ++i)
    {
        Node* tmp = hashLink.arr[i]->next;
        printf("hashLink[%d]: ", (i + 1));
        while(tmp != NULL)
        {
            printf("%d--->", tmp->data);
            tmp = tmp->next;
        }
        printf("null\n");
    }
}

void freeHashTable()
{
    for(int i = 0; i < size; ++i)
    {
        Node* del = hashLink.arr[i];
        Node* tmp = hashLink.arr[i]->next;

        while(tmp)
        {
            free(del);
            del = tmp;
            tmp = tmp->next;
        }
        free(del);
    }
}

int main()
{
    initHashTable();

    insertNumber();
    printHashTable();
    findData();
    deleteNumber();
    printHashTable();


    freeHashTable();
    return 0;
}
