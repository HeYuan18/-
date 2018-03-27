/*************************************************************************
	> File Name: queue.c
	> Author: 
	> Mail: 
	> Created Time: 2017年11月12日 星期日 21时40分07秒
 ************************************************************************/
 /*数据结构之队列*/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define Normal 0
#define Empty 1
#define Full 2
#define Abnormal 3

typedef int elementType;

/*定义结构体*/
typedef struct queue{
    int capacity, size;
    int front, rear;
    elementType arr[0];
}Que;

/*创建队列*/
Que *makeQueue()
{
    int length = 0;

    printf("please input length of queue:   ");
    scanf("%d", &length);
    
    /*清空输入缓冲区*/
    char tmp = '0';
    while((tmp = getchar()) != '\n' && tmp != EOF){}

    Que *queue = (Que*)malloc(sizeof(Que) + (length) * sizeof(int));
    if(queue != NULL)
    {
        queue->capacity = length;
        queue->size = 0;
        queue->front = 0;
        queue->rear = -1;

        memset(queue->arr, 0, length);

        return queue;
    }
    else
    {
        printf("error: memory.\n");

        return NULL;
    }
}

/*判断队列是否满*/
int isFull(Que *queue)
{
    if(queue->capacity != queue->size)
    {
        return Normal;
    }
    else
    {
        return Full;
    }
}

/*判断队列是否空*/
int isEmpty(Que *queue)
{
    if(queue->size != 0)
    {
        return Normal;
    }
    else
    {
        return Empty;
    }
}

/*入队操作*/
int enQueue(Que *queue)
{
    if(isFull(queue) != Full)
    {
        int tmp_data = 0;

        printf("please input data:   ");
        scanf("%d", &tmp_data);

        char tmp = '0';
        while((tmp = getchar()) != '\n' && tmp != EOF){}

        if(queue->rear == queue->capacity)
        {
            queue->rear = 0;
        }
        else
        {
            queue->rear += 1;
        }
        queue->arr[queue->rear] = tmp_data;

        queue->size += 1;
    }
    else
    {
        return Abnormal;
    }
}

/*出队操作*/
int deQueue(Que *queue, elementType *data)
{
    if(isEmpty(queue) != Empty)
    {
        *data = queue->arr[queue->front];

        if(queue->front == queue->capacity)
        {
            queue->front = 0;
        }
        else
        {
            queue->front += 1;
        }
    }
    else
    {
        return Abnormal;
    }
}

/*释放队列*/
void destroyQueue(Que **queue)
{
    if(*queue != NULL)
    {
        free(*queue);
        *queue = NULL;
    }
}

int main()
{
    Que *q = makeQueue();
    enQueue(q);
    enQueue(q);
    enQueue(q);
    
    int result = 0;

    deQueue(q, &result);
    printf("%d\n", result);

    deQueue(q, &result);
    printf("%d\n", result);

    deQueue(q, &result);
    printf("%d\n", result);

    destroyQueue(&q);
    return 0;
}
