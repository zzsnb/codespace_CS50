#include<cs50.h>
#include<stdio.h>

int main(void)
{
    string a;
    string b;
    b="boy";
    a=get_string("What's your name? ");
    printf("Hi,%s\n",a);
    printf("%%s\n");//真正打印%n
    printf("Hi,%s,%s\n",a,b);//print more things
}
//rename like $ mv easy_io.c easyio.c
