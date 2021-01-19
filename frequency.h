#ifndef FREQUENCY_H
#define FREQUENCY_H

#define NUMOFLETTERS 26
#define TRUE 1
#define FALSE 0 

typedef struct Node{

	char letter;
	int count;
	struct Node* children[NUMOFLETTERS];
	int endWord;
}Node;



char downCase(char c);

Node* newNode();

void insert(Node *root, char* str);

int haveChildren(Node* curr);

int search(Node *root,char *str);

void frequency(Node* root, char* str, int level);

void frequencyR(Node* root, char* str, int level);

void trieFree(Node* root);

#endif