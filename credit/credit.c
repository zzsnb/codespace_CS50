#include <stdio.h>
#include <cs50.h>
#include <math.h>

int main(void)
{
    string result = "VALID";
    // input a long variable
    long number;
    do
    {
        number = get_long("Number: ");
    }
    while(number < 0);

    // get the length of the number(有两种方法，一种是疯狂除10（可以融入代码中？），一种的log10法)
    // 此处采用直接融入代码的方式(后来发现长度是无论如何都得获取的)
    int length = (int)log10(number) + 1;

    //获取首两位和首位字母
    int first = number / pow(10,length - 1);
    int firsttwo = number / pow(10,length - 2);
    //printf("%i%i",first,firsttwo);已检验，此代码无错误

    //判断长度和首字母（或首两位字母）是否符合
    if (length == 15 && (firsttwo == 34 || firsttwo == 37))
    {
        result = "AMEX";
    }else if(length == 16 && (firsttwo == 51 || firsttwo == 52|| firsttwo == 53|| firsttwo == 54|| firsttwo == 55))
    {
        result = "MASTERCARD";
    }else if((length == 16 || length == 13) && first == 4)
    {
        result = "VISA";
    }else
    {
        result = "INVALID";
    }
    //printf("%s",result);

    // 选择while循环还是for循环可以考虑我到底是否需要i（作为下标）
    //then get the first sum.
    //防止number本身被破坏
    // firstly,delete the last number through deviding by 10
    long number_1 = number / 10;
    int sum = 0;
    int adding = 0;
    do
    {
        adding = (number_1 % 10) * 2;
        //由于是数字相加而不是数相加，所以这里还要再加一步处理（烦死了）
        do
        {
            sum = sum + adding % 10;
            adding = adding / 10;
        }
        while(adding > 0);
        number_1 = number_1 / 100;
    }
    while(number_1 > 0);
 //   printf("%i\n",sum);经检验以上代码得出的结果正确

    //then get the next sum.
    int sum_1 = 0;
    long number_2 = number;
    do
    {
        sum_1 = sum_1 + (number_2 % 10);
        number_2 = number_2 / 100;
    }
    while(number_2 > 0);

    //then add them up.
    int check = sum + sum_1;
// printf("%i\n",check);检查得以上代码正确

    //because the first or second number has some charactor,so i need to get them

    //the last thing is to check all the works
    if (check % 10 == 0)
    {
        string a = "yeah";
    }
    else
    {
        result = "INVALID";
    }
    printf("%s\n",result);
}

