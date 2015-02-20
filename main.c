#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define LINE_MAX 256

typedef struct Node {
  char ch;
  struct Node* firstChild;
  struct Node* nextSibling;
}Node;

bool Init(Node * root, char * filename){
  FILE * f;
  char buf[LINE_MAX];
  
  f = fopen(filename, "r");
  if(f == NULL){
    printf("Error, no dict.txt found\n");
    return false;
  }
  
  while(fgets(buf, sizeof(buf), f)){
    printf("+Dict line: %s", buf);
    char * ch = buf;
    Node * currNode = root;
    do{
      if(currNode->firstChild == NULL){
	currNode->firstChild = malloc(sizeof(Node));
	currNode = currNode->firstChild;
	currNode->ch = *ch;
      }else{
	currNode = currNode->firstChild;

	while(true){
	  if(currNode->ch == *ch){
	    break;
	  }

	  if(currNode->nextSibling != NULL){
	    currNode = currNode->nextSibling;
	  }else{
	    break;
	  }
	}

	if(currNode->ch != *ch){
	  currNode->nextSibling = malloc(sizeof(Node));
	  currNode = currNode->nextSibling;
	  currNode-> ch = *ch;
	}
      }
      ch++;
    }while(*ch);
  }

  fclose(f);
  return true;
}

bool Search(Node * root, char * str){
  int pos = 0;
  Node * currNode = root->firstChild;
  do{
      while(true){
        
      if(currNode->ch == *str){
	break;
      }
      if(currNode->nextSibling != NULL){
	currNode = currNode->nextSibling;
      }else{
	break;
      }
    }

    if(currNode->ch != *str){
        return false;
    }

    if(currNode->firstChild != NULL){
       currNode=currNode->firstChild;
    }
    str++;
  }while(*str != '\0');
  return true;  
}

int main(int argc, char * argv[]){
  char buf[LINE_MAX];
  Node * root = malloc(sizeof(Node));

  if(argc != 2){
    printf("Please, provide dictoinary filename\n");
    return -1;
  }
  
  if(!Init(root, argv[1])){
    return -2;
  }

  while(fgets(buf, sizeof(buf), stdin)){
    if(strcmp("exit\n",buf) == 0){
      return 0;
    }
    if(Search(root,buf)){
      printf("YES\n");
    }else{
      printf("NO\n");
    }    
  }
}
