//Nathan Little COP3502
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Trie node structure
struct Trie {
    struct Trie* children[26]; // One child for each lowercase letter
    int count; // Number of occurrences of the word
};

// Initializes a new trie node
struct Trie* createTrie() {
    struct Trie* newNode = (struct Trie*)malloc(sizeof(struct Trie));
    newNode->count = 0;
    for (int i = 0; i < 26; ++i) {
        newNode->children[i] = NULL;
    }
    return newNode;
}

// Inserts a word into the trie
void insert(struct Trie* root, char* word) {
    struct Trie* curr = root;
    for (int i = 0; word[i]; ++i) {
        int index = word[i] - 'a'; // Convert character to index (0-25)
        if (!curr->children[index]) {
            curr->children[index] = createTrie();
        }
        curr = curr->children[index];
    }
    curr->count++; // Increment word count
}

// Computes the number of occurrences of a word in the trie
int numberOfOccurrances(struct Trie* root, char* word) {
    struct Trie* curr = root;
    for (int i = 0; word[i]; ++i) {
        int index = word[i] - 'a';
        if (!curr->children[index]) {
            return 0; // Word not found
        }
        curr = curr->children[index];
    }
    return curr->count;
}

// Deallocates the entire trie
void deallocateTrie(struct Trie* root) {
    if (!root) return;
    for (int i = 0; i <= 26; ++i) {
        deallocateTrie(root->children[i]);
    }
    free(root);
}
// this function will return number of words in the dictionary,
// and read all the words in the dictionary to the structure words
int readDictionary(char *filename, char **pInWords)
{
	int limit = 0;
    char entry[256];
    
    FILE* fp = fopen(filename, "r");
    if (fp == NULL)  {return 0;}
    
    fscanf(fp,"%d\n",  &limit);
    
    for (int i = 0; i<limit; i++){
        fscanf(fp,"%s\n", entry);
        pInWords[i] = malloc(strlen(entry));
        strcpy(pInWords[i], entry);
    }
	return limit;
}

int main(void)
{
	char *inWords[256];
	//read the number of the words in the dictionary
	int numWords = readDictionary("dictionary.txt", inWords);
	for (int i=0;i<numWords;++i)
	{
		printf("%s\n",inWords[i]);
	}
	
	struct Trie *pTrie = createTrie();
	for (int i=0;i<numWords;i++)
	{
		insert(pTrie, inWords[i]);
	}
	// parse lineby line, and insert each word to the trie data structure
	char *pWords[] = {"notaword", "ucf", "no", "note", "corg"};
	for (int i=0;i<5;i++)
	{
		printf("\t%s : %d\n", pWords[i], numberOfOccurrances(pTrie, pWords[i]));
	}
	deallocateTrie(pTrie);
	if (pTrie != NULL)
		printf("There is an error in this program\n");
	return 0;
}
