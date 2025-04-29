#include <cs50.h>
#include <stdio.h>


int main(void)
{
    string trial = "abcde";
    printf("%c\n",trial[0] + 1);//还真可以，只要它最后输出的是c，那么就一定会是ASCII转化成字符后的样子
}
