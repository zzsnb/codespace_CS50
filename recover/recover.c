#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BLOCK_SIZE 512
#define SIGN_SIZE 4
#define FILENAME_NUMBER 7

typedef uint8_t BYTE;

const BYTE Heads[SIGN_SIZE - 1] = {0xff, 0xd8, 0xff};

bool judge_head(BYTE buffer[BLOCK_SIZE]);

int main(int argc, char *argv[])
{
    // Accept a single command-line argument
    if (argc != 2)
    {
        printf("Usage: ./recover FILE \n");
        return 1;
    }

    // Open the memory card
    FILE *card = fopen(argv[1], "r");
    if (card == NULL)
    {
        printf("Could not find the file.\n");
        fclose(card);
        return 1;
    }

    BYTE *buffer = malloc(BLOCK_SIZE * sizeof(BYTE));
    if (buffer == NULL)
    {
        free(buffer);
        fclose(card);
        return 1;
    }
    // 这四行可以直接改成BYTE buffer[BLOCK_SIZE];然后在后面fread的第一个参数改成&buffer
    // While there's still data left to read from the memory card
    int file_count = 0;

    // 会不会在jpeg开始之前就有垃圾值？
    bool is_start = false;
    char *file_name = malloc((FILENAME_NUMBER + 1) * sizeof(char));
    while (fread(buffer, sizeof(BYTE), BLOCK_SIZE, card) != 0)
    {
        // head_judge should be write as a function
        if (judge_head(buffer))
        {
            // Create a new file (how to create a file_name with 3 char)
            sprintf(file_name, "%03d.jpg", file_count);
            file_count++;
            is_start = true;

            // fopen the file
            FILE *file = fopen(file_name, "ab");
            if (file == NULL)
            {
                free(buffer);
                fclose(card);
                return 1;
            }
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, file);

            // fclose the file
            fclose(file);
        }
        else if ((!judge_head(buffer)) && is_start)
        {
            FILE *file = fopen(file_name, "ab");
            if (file == NULL)
            {
                free(buffer);
                fclose(card);
                return 1;
            }
            fwrite(buffer, sizeof(BYTE), BLOCK_SIZE, file);
            fclose(file);
        }
    }
    free(file_name);
    free(buffer);
    fclose(card);
}

bool judge_head(BYTE buffer[BLOCK_SIZE])
{
    for (int i = 0; i < SIGN_SIZE - 1; i++)
    {
        if (buffer[i] != Heads[i])
        {
            return false;
        }
    }
    if (!((buffer[SIGN_SIZE - 1] & 0xF0) == 0xE0))
    {
        return false;
    }
    return true;
}
