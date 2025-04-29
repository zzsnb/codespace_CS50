#include <stdio.h>
#include <cs50.h>

int main(void)
{
    int height;

    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // using blank space to produce the stair
    // two for loops and one if in each loop
    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < height; j++)
        {
            if (height - j > i + 1)
            {
                printf(" ");
            }
            else
            {
                printf("#");
            }
        }
        printf("\n");
    }
}
