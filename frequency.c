#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include"frequency.h"

#define WORD 30
#define BUFFER 1024

char buff[BUFFER];

Node* newNode(){
	Node *node = (Node*)malloc(sizeof(Node));
	if(node){
		node->letter='\0';
		node->count=0;
		node->endWord = FALSE;

		for(int i = 0; i < NUMOFLETTERS; i++){
			node->children[i] = NULL;
		}	
	}
	return node;
}

char downCase(char c){
	if(c>='A' && c<='Z'){
		return c-'A'+'a';
	}

	return c;
}


void insert(Node *root, char* str){
	Node *curr = root;	
	while(*str){
		char c = downCase(*str);
		if(curr->children[c-'a']==NULL){
			curr->children[c-'a'] = newNode();
		}
		curr->letter=*str;
		curr = curr->children[c-'a'];
		str = str+1;
		curr->count++;
	}
	
	curr->endWord=TRUE;		
}




int haveChildren(Node* curr){
	for(int i = 0; i < NUMOFLETTERS; i++){
		if(curr->children[i]!=NULL){
			return TRUE;
		}
	}
	return FALSE;
}


int search(Node *root,char *str){
	if(root==NULL){
		return 0;
	}

	Node *curr = root;

	while(*str){
		curr = curr->children[*str-'a'];

		if(curr == NULL){
			return 0;
		}
		str++;
	}

	return curr->count;
}



void frequency(Node* head, char* str, int level){
	
	if(head == NULL){
		return;
	}

	if(head->endWord){
		str[level] = '\0';
		printf("%s\t",str);
		printf("%d\n", head->count);		
	}

	for(int i = 0; i < NUMOFLETTERS; i++){
		if(head->children[i]){
			*(str+level) = i + 'a';
			frequency(head->children[i],str,level+1);
		}
	}
	
}


void frequencyR(Node* head, char* str, int level){
	
	if(head == NULL){
		return;
	}

	if(head->endWord){
		str[level] = '\0';
		printf("%s\t",str);
		printf("%d\n", head->count);		
	}

	for(int i = NUMOFLETTERS-1; i >= 0 ; i--){
		if(head->children[i]){
			*(str+level) = i + 'a';
			frequencyR(head->children[i],str,level+1);
		}
	}
	
}


void trieFree(Node* root){

    if(root != NULL){

        int i;
        for(i = 0; i < NUMOFLETTERS; i++){

            if(root->children[i] != NULL){
                trieFree(root->children[i]);
            }
        }
        free(root);
    }
}


int main(int argc, char* argv[]){
	
	Node *head = newNode();
	char word[BUFFER];
	memset(buff,'\0',BUFFER);
	memset(word,'\0',BUFFER);
	while(fgets(buff, sizeof(buff), stdin)!=NULL){
		int length = strlen(buff);	
		for(int i = 0, j = 0 ; i <= length; i++){		
			
			if(buff[i]==' ' || buff[i]=='\n' || buff[i]=='\t'){
				insert(head, word);
				memset(word,'\0',BUFFER);
				j = 0;
			}
			

			else if((buff[i]>='a' && buff[i]<='z') || (buff[i]>='A' && buff[i]<='Z')){
				word[j] = buff[i];
				j++;
			}	
		}
	}
	char str[BUFFER]={'\0'};
	int level = 0;
	if(argc == 2){
		int check = strcmp(argv[1], "r");
		if(argc == 2 && check == 0){		
			frequencyR(head,str,level);
		}
		else{
			frequency(head,str,level);
		}
	}

	

	else{
		frequency(head,str,level);
	}
	trieFree(head);
	return 0 ;
}