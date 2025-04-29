#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string str = "A!Bb";
    printf("%c\n",toupper(str[0]));
    printf("%c\n",toupper(str[1]));
}
