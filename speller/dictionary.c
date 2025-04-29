// Implements a dictionary's functionality

#include <ctype.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <strings.h>
#include <stdio.h>
#include <stdlib.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
} node;

// TODO: Choose number of buckets in hash table
const unsigned int N = 456976; // the biggest n for 26 to the powder of n,
unsigned int SIZE = 0;

// Hash table
node *table[N];


int dfa(char letter);
bool check_link(const char *word,node *link);
void free_link(node *link);

// Returns true if word is in dictionary, else false
bool check(const char *word)
{
    // TODO
    // return true if the word is found

    // caculate the subscript of the word
    // 676 is 2 for 26,17576 is 3 for 26
    unsigned int subscript = hash(word);
    // find the word in the hashmap
    if (subscript > N - 1)
    {
        return false;
    }
    if (check_link(word,table[subscript]) == true)
    {
        return true;
    }
    else
    {
        return false;
    }
}

// Hashes word to a number
unsigned int hash(const char *word)
{
    // TODO: Improve this hash function
    unsigned int subscript = 0;
    int min = 3;
    if (3 > strlen(word))
    {
        min = strlen(word);
    }
    for (int i = 0; i < min; i++)
    {
        subscript += dfa(word[i]) * pow(26,3-1-i);
    }
    return subscript;
}

// Loads dictionary into memory, returning true if successful, else false
bool load(const char *dictionary)
{
    // TODO
    // Open the dictionary file
    FILE *file = fopen(dictionary,"r");
    if (file == NULL)
    {
        printf("Dictionary can't be opened.");
        fclose(file);
        return false;
    }

    // Read each word in the file
    char *word = malloc(LENGTH + 1);
    // 此处其实也可以用%c来找\n
    memset(table, 0, sizeof(table));
    while (fscanf(file, "%s", word) == 1) // 此处能不能动态分配内存？
    {
        // Add each word to the hash table
        // Create new node to load word
        node *new = malloc(sizeof(node));
        new->next = NULL;
        if (new == NULL)
        {
            printf("There is no enough place.\n");
            fclose(file);
            free(word);
            return false;
        }
        strcpy(new->word, word);
        SIZE++;
        //link the node to the end of the link
        // 由于table本身处并没有分配link，所以可能导致访问空指针
        unsigned int index = hash(word);

        if (table[index] == NULL)
        {
            table[index] = new; // 插入第一个节点
        }
        else
        {
            node *last = table[index];
            while (last->next != NULL)
            {
                last = last->next;
            }
            last->next = new; // 插入链表尾部
        }

        // free(new); 假如这么写了，那不是永远都不会有新的节点？
    }
    free(word);
    // Close the dictionary file
    fclose(file);
    return true;
}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return SIZE;
}

// Unloads dictionary from memory, returning true if successful, else false
bool unload(void)
{
    // TODO
    // loop over the hash table
    for (int i = 0; i < N; i++)
    {
        // use recursion to free each bucket
        if (table[i] != NULL)
        {
            free_link(table[i]->next);
            free(table[i]);
        }
    }
    // free the table(table is not malloc)
    return true;
    return false;
}

// caculate a letter's distance from 'a' or 'A'
int dfa(char letter)
{
    int distance = tolower(letter) - 'a';
    return distance;
}

// to check in the link after find the subscript
// Done without check
bool check_link(const char *word,node *link)
{
    // if the word appears,return true
    if (link == NULL)
    {
        return false;
    }
    if (strcasecmp(link->word,word) == 0)
    {
        return true;
    }
    // check the next word in the link,if the function return true, return true.
    if (check_link(word,link->next))
    {
        return true;
    }
    else
    {
        return false;
    }
}

void free_link(node *link)
{
    // if (link->next != NULL) 这么写会导致如果link->next 是NULL则没有free
    if (link != NULL)
    {
        free_link(link->next);
        free(link);
    }
}
