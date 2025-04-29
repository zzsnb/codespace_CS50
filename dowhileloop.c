//学习dowhile 这常用来确保用户输入的是我想要的
#include<stdio.h>
#include<cs50.h>

int main(void)
{
    int n;
    do
    {
        n = get_int("What's the number? ");
    }
    while(n < 1);//注意此处应为括号
}
