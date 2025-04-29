#include <stdio.h>
#include <cs50.h>

int main(void)
{
    // input a height
    int height;
    do
    {
        height = get_int("Height: ");
    }
    while (height < 1);

    // using a for loop with two for loop inside to print the complex stairs
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
        // print two blank space
        printf("  ");
        for (int k = 0; k < i + 1; k++)
        {
            printf("#");
        }
        printf("\n");
    }

}
