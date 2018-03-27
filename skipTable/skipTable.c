/*************************************************************************
	> File Name: skipTable.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月12日 星期二 10时08分15秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<time.h>

#define max_level 5

typedef struct node
{
    int data;
    struct node* next;
    struct node* down;
}Node;
typedef Node* List;

typedef struct skiptable
{
    int level;
    List table[max_level];
}skipTable;

skipTable skipList;

Node* createNode(int data)
{
    Node* node = (Node*)malloc(sizeof(Node));
    node->data = data;
    node->next = NULL;
    node->down = NULL;

    return node;
}

void initSkipTable(int level)
{
    skipList.level = level;
    for(int i = 0; i < skipList.level; ++i)
    {
        skipList.table[i] = createNode(0);
    }
}

int randomLevel()
{
    int k = 1;
    while(rand() % 2)
    {
        ++k;
    }
    return (k < (skipList.level - 1)) ? k : (skipList.level - 1);
}

Node* find(int value)
{
    int k = skipList.level - 1;
    for(; k >= 0; --k)
    {
        Node* previous = skipList.table[k];
        Node* tmp = skipList.table[k]->next;
        while(tmp)
        {
            if(tmp->data <= value)
            {
                if(tmp->data == value)
                {
                    return tmp;               
                }
                else
                {
                    tmp = tmp->next;
                    previous = previous->next;
                    while(tmp == NULL)
                    {
                        if(previous->down == NULL)
                        {
                            break;
                        }
                        tmp = (previous->down)->next;
                        previous = previous->down;
                    }
                }
            }
            else
            {
                if(previous->down == NULL)
                {
                    break;
                }
                tmp = (previous->down)->next;
                previous = previous->down;
            }

            k = 0;
        }
    }
    return NULL;
}

void insert(int value)
{
    if(find(value) == NULL)
    {
        Node* node = createNode(value);

        int l = randomLevel();
        for(; l >= 0; --l)
        {
            Node* previous = skipList.table[l];
            Node* tmp = skipList.table[l]->next;
            if(tmp == NULL)
            {
                skipList.table[l]->next = node;

                if(l != 0)
                {
                    node = createNode(value);
                    skipList.table[l]->next->down = node;
                }
                continue;
            }
            while(tmp)
            {
                if(node->data > tmp->data)
                {
                    previous = previous->next; 
                    tmp = tmp->next;

                    if(tmp == NULL)
                    {
                        previous->next = node;
                        break;
                    }
                }
                else
                {
                    node->next = tmp;
                    previous->next = node;
                    break;
                }
            }
            node = createNode(value);
            previous->next->down = node;
        }
    }
}

void delete(int value)
{
    if(find(value) != NULL)
    {
        for(int i = 0; i < skipList.level; ++i)
            {
            Node* previous = skipList.table[i];
            Node* del = skipList.table[i]->next;
            while(del)
            {
                if(value == del->data)
                {
                    previous->next = del->next;
                    free(del);
                    del = NULL;

                    break;
                }
                previous = previous->next;
                del = del->next;
            }
        }
    }
}

void printSkipTable()
{
    for(int i = (skipList.level - 1); i >= 0; --i)
    {
        Node* tmp = skipList.table[i]->next;
        printf("List[%d]: ", (i + 1));
        while(tmp)
        {
            printf("%d--->", tmp->data);
            tmp = tmp->next;
        }
        printf("null\n");
    }
}

void freeSkipTable()
{
    for(int i = (skipList.level - 1); i >= 0; --i)
    {
        Node* del = skipList.table[i];
        Node* tmp = skipList.table[i]->next;
        while(tmp)
        {
            free(del);
            del = tmp;
            tmp = tmp->next;
        }
        free(del);
    }
}

int main(int argc, char* argv[])
{

    initSkipTable(max_level);
    srand((unsigned)time(NULL));
    
    int value = 0;
    printf("input data:\n");
    scanf("%d", &value);
    while(value)
    {
        insert(value);

        scanf("%d", &value);
    }

    printSkipTable();

    printf("please input find Data: ");
    scanf("%d", &value);
    Node* fdata = find(value);
    if(fdata == NULL)
    {
        printf("没找到.\n");
    }
    else
    {
        printf("找到了.\n");
    }

    delete(value);

    printSkipTable();

    freeSkipTable();
    return 0;
}
