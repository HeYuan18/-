/*************************************************************************
	> File Name: stack.c
	> Author: 
	> Mail: 
	> Created Time: 2017年10月26日 星期四 20时47分54秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

/*栈状态标志*/
enum FLAG {Normal, Abnormal, Success, False, Full, Empty, Exist, Nothing};

/*数据类型*/
typedef int elementType;

/*栈结构体*/
typedef struct stack
{
    int length;
    int top;
    elementType arr[0];
}Stack;

/*初始化栈,为栈开辟空间*/
Stack *makeStatic()
{
    int length = 0;

    printf("please input length of stack:   ");
    scanf("%d", &length);

    int tmp = 0;
    while((tmp = getchar()) != '\n' && tmp != EOF){}   //清空输入缓冲区

    Stack *s = (Stack*)malloc(sizeof(Stack) + (length) * sizeof(int));
    if(s == NULL)
    {
        printf("error: memory.\n");
        return NULL;
    }
    else
    {
        s->length = length;
        memset(s->arr, 0, length);
        s->top = -1;
        system("clear");
        return s;
    }
}

/*判断栈是否满*/
int isFull(Stack *s)
{
    if((1 + s->top) == s->length)
    {
       return  Full;
    }
    else
    {
        return Normal;
    }
}

/*判断栈是否空*/
int isEmpty(Stack *s)
{
    if(s->top == -1)
    {
        return Empty;
    }
    else
    {
        return Normal;
    }
}

/*入栈，返回成功<Success>或失败<False>*/
int push(Stack *s)
{
    if(isFull(s) == Full)
    {
        printf("|----------------------------------|\n");
        printf("   error:stack is full. |<False>\n");
        printf("|----------------------------------|\n");
        return False;
    }
    else
    {
        (s)->top += 1;
        printf("please input data:   ");
        scanf("%d", &((s)->arr[(s)->top]));
        
        int tmp = 0;
        while((tmp = getchar()) != '\n' && tmp != EOF){}   //清空输入缓冲区
        system("clear");

        return Success;
    }
}

/*出栈，返回成功<Success>或失败<False>*/
int pop(Stack *s, elementType *data)
{
    if(isEmpty(s) == Empty)
    {
        printf("|----------------------------------|\n");
        printf("   error:stack is empty. |<False>\n");
        printf("|----------------------------------|\n");
        return False;
    }
    else
    {
        *data = s->arr[(s->top)];
        s->top -= 1;

        return Success;
    }
}

/*查看栈顶元素，返回成功<Success>或失败<False>*/
int peek(Stack *s, elementType *data)
{
    if(isEmpty(s) == Empty)
    {
        printf("|----------------------------------|\n");
        printf("   error:stack is empty. |<False>\n");
        printf("|----------------------------------|\n");
        return False;
    }
    else
    {
        *data = s->arr[(s->top)];

        return Success;
    }
}

/*清空栈，返回成功<Success>或失败<False>*/
int clearStack(Stack *s)
{
    if(s != NULL)
    {
        s->top = -1;
        return Success;
    }
    else
    {
        return False;
    }
}

/*摧毁栈，释放栈内存*/
void destoryStack(Stack **s)
{
    if(*s != NULL)
    {
        free(*s);
        *s = NULL;
    }
}

int print_info(Stack *s)
{
    if(isEmpty(s) == Empty)
    {
        printf("|-------------------------------------\n");
        printf("   error:stack is empty. |<False>\n");
        printf("|-------------------------------------\n");
        return False;
    }
    else
    {
        printf("|-----------------------------------------|\n");
        printf("   length: %d,   data:", s->length);
        for(int i = 0; i <= s->top; ++i)
        {
            printf("   %d", s->arr[i]);
        }
        putchar(10);
        printf("|-----------------------------------------|\n");
        return Success;
    }
}

/*菜单函数*/
void Menu()
{
    printf("\t\t\t\t\t+=========================================+\n");
    printf("\t\t\t\t\t+------------------STACK------------------+\n");
    printf("\t\t\t\t\t+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+\n");
    printf("\t\t\t\t\t|                                         |\n");
    printf("\t\t\t\t\t|          1----------- createStack       |\n");
    printf("\t\t\t\t\t|          2----------- push              |\n");
    printf("\t\t\t\t\t|          3----------- pop               |\n");
    printf("\t\t\t\t\t|          4----------- peek              |\n");
    printf("\t\t\t\t\t|          5----------- clearStack        |\n");
    printf("\t\t\t\t\t|          6----------- destoryStack      |\n");
    printf("\t\t\t\t\t|          7----------- printInfo         |\n");
    printf("\t\t\t\t\t|                                         |\n");
    printf("\t\t\t\t\t|=========================================|\n");
    printf("\t\t\t\t\t|                                         |\n");
    printf("\t\t\t\t\t|          8----------- cls               |\n");
    printf("\t\t\t\t\t|          0----------- quit              |\n");
    printf("\t\t\t\t\t|                                         |\n");
    printf("\t\t\t\t\t|=========================================|\n");
    printf("\t\t\t\t\t+^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^+\n");
    printf("\t\t\t\t\t+--------~.~--------.~---------~.~--------+\n");
    printf("\t\t\t\t\t+=========================================+\n");
}

/*处理菜单选择异常*/
int dealInput(char ch)
{
    if(ch >= 48 && ch <= 56)
    {
        return Normal;
    }
    else
    {
        return Abnormal;
    }
}

/*结束语*/
void byebye(char ch, int count, int time)
{
    for(int i = 0; i < count; ++i)
    {
        printf("%c", ch);fflush(stdout);usleep(time);
    }
}

int main()
{
    system("clear");
    char choice = 48;
    Stack *s;
    int data;   //存放pop和peek的数据
    enum FLAG flag_menu = Nothing;

    do
    {
        Menu();
        printf("\t\t\t\t\tPlease input choice<0~8>:   ");
        scanf("%c", &choice);

        int tmp = 0;
        while((tmp = getchar()) != '\n' && tmp != EOF){}   //清空输入缓冲区

        if(dealInput(choice) == Abnormal)
        {
            continue;
        }
        else
        {
            switch(choice)
            {
                case 48:                        //退出系统
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        destoryStack(&s);
                        printf("   Release Memory ");
                        byebye('.', 6, 420000);
                        printf("   |\n");

                        printf("===========================|\n");
                        flag_menu = Nothing;
                    }
                    printf("\t    | Exit Success |\n");
                    printf("\t    |==============|\n");
                    break;
                case 49:                        //为栈指针分配内存
                    system("clear");
                    if(flag_menu == Nothing)
                    {
                        s = makeStatic();
                        if(s != NULL)
                        {
                            flag_menu = Exist;
                            printf("   make");
                            byebye('.', 6, 200000);
                            printf("Success.          |\n");
                            printf("===============================|\n");
                            printf("   stack length is %d \n", s->length);
                            printf("===============================|\n");
                        }
                    }
                    else
                    {
                        printf("|-----------------------------------------|\n");
                        printf("   stack is inexistence. |<make False>\n");
                        printf("|-----------------------------------------|\n");
                    }
                    break;
                case 50:                        //入栈
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        if(push(s) == Success)
                        {
                            printf("|-------------------------------|\n");
                            printf("   data = %d |<push Success>\n", s->arr[s->top]);
                            printf("|-------------------------------|\n");
                        }
                    }
                    else
                    {
                        printf("|-----------------------------------------|\n");
                        printf("   stack is inexistence. |<push False>\n");
                        printf("|-----------------------------------------|\n");
                    }
                    break;
                case 51:                        //出栈
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        if(pop(s, &data) == Success)
                        {
                            printf("|-------------------------------|\n");
                            printf("   data = %d |<pop Success>\n", data);
                            printf("|-------------------------------|\n");
                        }
                    }
                    else
                    {
                        printf("|-----------------------------------------|\n");
                        printf("   stack is inexistence. |<pop False>\n");
                        printf("|-----------------------------------------|\n");
                    }
                    break;
                case 52:                        //观星
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        if(peek(s, &data) == Success)
                        {
                            printf("|-------------------------------|\n");
                            printf("   data = %d |<peek Success>\n", data);
                            printf("|-------------------------------|\n");
                        }
                    }
                    else
                    {
                        printf("|-----------------------------------------|\n");
                        printf("   stack is inexistence. |<peek False>\n");
                        printf("|-----------------------------------------|\n");
                    }
                    break;
                case 53:                        //清空栈
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        clearStack(s);
                        printf("   clean");
                        byebye('.', 6, 300000);
                        printf("Success.   |\n");
                        printf("=========================|\n");
                    }
                    else
                    {
                        printf("|-----------------------------------------|\n");
                        printf("   stack is inexistence. |<clean False>\n");
                        printf("|-----------------------------------------|\n");
                    }
                    break;
                case 54:                        //摧毁栈
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        destoryStack(&s);
                        printf("   destory");
                        byebye('.', 6, 380000);
                        printf("Success.   |\n");
                        printf("===========================|\n");
                        flag_menu = Nothing;
                    }
                    else
                    {
                        printf("|-------------------------------------------|\n");
                        printf("   stack is inexistence. |<destory False>\n");
                        printf("|-------------------------------------------|\n");
                    }
                    break;
                case 55:                        //打印栈
                    system("clear");
                    if(flag_menu == Exist)
                    {
                        if(print_info(s) == Success)
                        {
                            printf("   printInfo Success.   |\n");
                            printf("========================|\n");
                        }
                    }
                    else
                    {
                        printf("|--------------------------------------------|\n");
                        printf("   stack is inexistence. |<printInfo False>\n");
                        printf("|--------------------------------------------|\n");
                    }
                    break;
                case 56:                        //清屏
                    system("clear");
                    break;
                default:
                    printf("error.\n");
                    break;
            }
        }
    }while(choice != 48);

    return 0;
}
