//substitution algorithm for encrypt the text by using the distance from 'a'
#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

int main(int argc, string argv[])
{
    string key;
    // get and judge the input
    if (argc != 2)
    {
        printf("Usage: ./substitution key\n");
        return 1;
    }
    else if (strlen(argv[1]) != 26)
    {
        printf("Key must contain 26 characters.\n");
        return 1;
    }
    else
    {
        // handle the duplicate or ivalid characters in key

        for (int i = 0; i < 26; i++)
        {
            // handle invalid characters
            if (!isalpha(argv[1][i]))
            {
                printf("Key must contain 26 characters.\n");
                return 1;
            }
        }
        // make sure that they are all characters(if there is this kind of side case)
        // for(int i = 0)
        key = argv[1];
    }

    // keep the data with an array with 24(change them all to number or uppercase or lowercase
    // how much are they from the origin number? caculate and store
    //(uppercase ande lowercase should be handle respectively)
    int keynumber[26];
    // checkduplicate here
    int checkduplicate[26] = {0};
    for (int i = 0; i < 26; i++)
    {
        key[i] = tolower(key[i]);
        keynumber[i] = key[i] - 'a' - i;
        if (checkduplicate[key[i] - 'a'] == 0)
        {
            checkduplicate[key[i] - 'a'] = 1;
        }
        else
        {
            printf("Key must contain 26 characters.\n");
            return 1;
        }
    }

    // get the plaintext
    string plaintext = get_string("plaintext:  ");

    // change it to cipher text
    // variable distance to discribe the char from 'a/A'
    int distance = 0;
    string cipher = plaintext;
    for (int i = 0; i < strlen(plaintext); i++)
    {
        if (isupper(plaintext[i]))
        {
            cipher[i] = plaintext[i] + keynumber[plaintext[i] - 'A'];
        }
        else if (islower(plaintext[i]))
        {
            cipher[i] = plaintext[i] + keynumber[plaintext[i] - 'a'];
        }
        else
        {
            cipher[i] = plaintext[i];
        }
    }

    // output the ciphertext
    printf("ciphertext: %s\n", cipher);
    return 0;
}
