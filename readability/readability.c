// examine the readability of a text(for which grade?)
#include <cs50.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

int count_letter(int length, string str);
int count_word(int length, string str);
int count_sentence(int length, string str);

int main(void)
{
    // Prompt the user for some text
    string str = get_string("Text: ");

    // Count the number of letters, words, and sentences in the text
    int length = strlen(str);
    int letter = count_letter(length, str);
    int word = count_word(length, str);
    int sentence = count_sentence(length, str);

    // Compute the L and S
    float L = (100.0 * (float) letter) / (float) word;
    float S = 100.0 * sentence / word;

    // Compute the Coleman-Liau index
    float index = 0.0588 * L - 0.296 * S - 15.8;

    // Print the grade level
    if (index > 16)
    {
        printf("Grade 16+\n");
    }
    else if (index < 1)
    {
        printf("Before Grade 1\n");
    }
    else
    {
        printf("Grade %i\n", (int) round(index));
    }
}

int count_letter(int length, string str)
{

    int letter_sum = 0;
    for (int i = 0; i < length; i++)
    {
        if ((str[i] - 'a' < 26 && str[i] - 'a' > -1) || (str[i] - 'A' < 26 && str[i] - 'A' > -1))
        {
            letter_sum += 1;
        }
    }
    return letter_sum;
}

int count_word(int length, string str)
{
    int word_sum = 0;
    for (int j = 0; j < length; j++)
    {
        if (str[j] == ' ')
        {
            word_sum += 1;
        }
    }
    return word_sum + 1;
    // 太坑了，空格数+1才是单词数，而且他还悄悄给提示
}

int count_sentence(int length, string str)
{
    int sentence_sum = 0;
    for (int j = 0; j < length; j++)
    {
        if (str[j] == '.' || str[j] == '?' || str[j] == '!')
        {
            sentence_sum += 1;
        }
    }
    return sentence_sum;
}
