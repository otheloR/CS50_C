// Implements a dictionary's functionality

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>

#include "dictionary.h"

// Represents a node in a hash table
typedef struct node
{
    char word[LENGTH + 1];
    struct node *next;
}
node;

// Number of buckets in hash table
const unsigned int N = 5382;

// Hash table
node *table[N];

// Returns true if word is in dictionary, else false
// (and is it correctly spelled?)

bool check(const char *word)
{
     int index = hash(word) % N;


    node *cursor = NULL;

    //create cursor pointer that points to first element in linked list
    cursor = table[index];


    //iterate cursor over linked list
    while (cursor != NULL) {

        if (strcasecmp(cursor -> word, word) == 0) {



            return true;

        }

        else {

            cursor = cursor -> next;

        }

    }


    return false;
}

// Hashes word to a number
// take some number to correspond with that word

unsigned int hash(const char *word)
{

    //covert *word to all lower case

    //get length of parameter word
    int strLength = strlen(word);

    //create char array with length of string + 1 for null character
    char strCopy[strLength + 1];


    //get address of word and put into pos_Letter
    const char *pos_Letter = word;

    for (int x = 0; x < strLength; x++) {

        strCopy[x] = tolower(*pos_Letter);

        pos_Letter++;

    }
    strCopy[strLength] = '\0';

    pos_Letter = strCopy;





    // Test: A = 0, Z = 25 of table index
    //DJB2 hash function

        unsigned long hash = 5381;
        int c;

        while ((c = *pos_Letter++))
            hash = ((hash << 5) + hash) + c; /* hash * 33 + c */

        return hash;


}

// Loads all words in dictionary into memory, returning true if successful, else false
// load into data structure, like a hash table

    // Count the amount of words noded, give to size function
    int wordCount = 0;

bool load(const char *dictionary)
{
    FILE *file = fopen(dictionary, "r");

    // return false if can't load file, no address
    if (file == NULL) {

        return false;
    }

    //read strings from file, word is a character array, some place you going to read the word into
    //can access individual characters in word array after it has been called
    char word[LENGTH + 1];

   while (fscanf(file, "%s", word) != EOF) {

       node *n = malloc(sizeof(node));

       if (n == NULL) {

           return false;

       }

       strcpy(n->word, word);

       n->next = NULL;


        // hash word, take a string and return index, some number we can use to index into linked list
        int index = hash(word) % N;

        //add a new node into the corresponding linked list in the table

        // new node points to first node at index, securing from abandonment of other nodes
        n->next = table[index];

        //put address of new node as head of linked list at the corresponding index of table array
        table[index] = n;

    //may need to add wordcount Variable

    wordCount++;


   }
    fclose(file);


   return true;

}

// Returns number of words in dictionary if loaded, else 0 if not yet loaded
unsigned int size(void)
{
    // TODO
    return wordCount;
}

// Unloads dictionary from memory, returning true if successful, else false
//any of the memory that we had to allocate we free up here

bool unload(void)
{





    //iterating over hash table, going over each individual linked list, and freeing each node inside of those linked lists



    bool trigger = false;

    node *cursor = NULL;
   node *tmp  = NULL;


    for (int x = 0; x < N; x++) {

        cursor = table[x];
        tmp = cursor;

        while (cursor != NULL) {

            trigger = true;

            cursor = cursor -> next;

            free(tmp);

            tmp = cursor;


        }



    }




    return trigger;
}
