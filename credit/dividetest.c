#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int number = get_int("Number: ");
    do
    {
        printf("%i\n",number);
        number = number / 10;
    }
    while(number > 0);
}
