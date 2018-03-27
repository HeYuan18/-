/*************************************************************************
	> File Name: hash.c
	> Author: 
	> Mail: 
	> Created Time: 2017年12月10日 星期日 10时49分27秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int *arr = NULL;
int len = 0;

void print_arr()
{
    for(int i = 0; i < len; ++i)
    {
        printf("%d\t", arr[i]);
    }
    putchar(10);
}

void initArr()
{
    arr = (int*)malloc(len * sizeof(int));
    memset(arr, 0, sizeof(arr));
}

int hash(int key)
{
    return key % len;
}

void setNumber()
{
    int i = 0;
    int value = 0;
    int key = 0;

    while(i != len)
    {
        printf("please input data: ");
        scanf("%d", &value);
        i += 1;
        key = hash(value);
        
        while(arr[key] != 0)
        {
            key = hash(key + 1); 
        }

        arr[key] = value;
    }
}

int find(int value)
{
    int key = hash(value);
    int count = 0;
    while((arr[key] != value) && (count != len))
    {
        key = hash(key + 1);
        count += 1;
    }

    return len == count ? 0 : (key + 1);
}

void find_data()
{
    int value =  0;
    printf("Find data: ");
    scanf("%d", &value);
    int point = find(value);
    printf("%d\n", point);
    if(point)
    {
        printf("值%d的位置[%d]\n", value, point);
    }
    else
    {
        printf("值%d找不到\n", value);
    }
}

int main()
{

    printf("Please input len of Arr: ");
    scanf("%d", &len);
    
    initArr();

    setNumber();
    
    print_arr();

    find_data();

    free(arr);
    arr = NULL;

    return 0;
}
