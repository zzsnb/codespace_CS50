#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int compute_point(string str);

int main(void)
{
    // input 2 words
    string p1 = get_string("Player 1: ");
    string p2 = get_string("Player 2: ");

    // compute the two points
    int point1 = compute_point(p1);
    int point2 = compute_point(p2);

    // compare them and have an output
    if (point1 > point2)
    {
        printf("Player 1 wins!\n");
    }
    else if (point1 < point2)
    {
        printf("Player 2 wins!\n");
    }
    else
    {
        printf("Tie!\n");
    }
}

int compute_point(string str)
{
    // set the point each letter has
    int pointletter[]={1,3,3,2,1,4,2,4,1,8,5,1,3,1,1,3,10,1,1,1,1,4,4,8,4,10};
    // get the length of the string
    int length = strlen(str);

    // change the lower to upper by using the toupper()
    // add the points up by a for loop
    int sum_point = 0;
    for (int i = 0; i < length; i++)
    {
        str[i] = toupper(str[i]);
        // 此处应小心可能出现不是字母的字符
        int number = str[i] - 'A';
        if (number < 26 && number > -1) // 第一次做的时候没有考虑到可能为负数的情况
        {
            sum_point += pointletter[number];
        }
    }

    return sum_point;
}
