#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "avl_tree.h"

#define LINE_MAX 256
#define CH_MIN 32
#define CH_MAX 127

bool Init(Node ** root, char * filename){
  FILE * f;
  char buf[LINE_MAX];
  
  
  f = fopen(filename, "r");
  if(f == NULL){
    printf("Error, no dict.txt found\n");
    return false;
  }

  *root = avl_insert(*root, 0, NULL);
  
  while(fgets(buf, sizeof(buf), f)){
    //printf("+Dict line: %s", buf);
    char * ch = buf;
    Node * currNode = *root;

    do{
      if((*ch < CH_MIN || *ch > CH_MAX) && *ch != '\n'){
	break;
      }
    }while(*++ch);

    if(*ch){
      // printf("Not valid input\n");
      continue;
    }
    
    ch = buf;
    do{
      //   printf("Inserting 0x%02X\n", *ch);
      
      Node * oldNode = avl_find(currNode->data, *ch);
      if(oldNode != NULL){
	//	printf("Found old node\n");
	currNode = oldNode;
	continue;
      }
      
      currNode->data = avl_insert(currNode->data, *ch, NULL);
      //   printf("After 0x%02X insert\n", *ch);
      // avl_print(currNode->data);
      currNode = avl_find(currNode->data, *ch);

    }while(*++ch);
  }
  
  fclose(f);

  return true;
}

bool Search(Node * node, char * str){
  node = node->data;
  do{
    //  printf("Looking for %c [0x%02X]\n", *str, *str);
    //avl_print(node);
    node = avl_find(node, *str);

    if(node == NULL){
      return false;
    }

    node = node->data;

    str++;
    }while(*str);
  return true;  
}


int main(int argc, char * argv[]){
  char buf[LINE_MAX];
  Node * root = NULL;

  #ifdef DEBUG
  printf("DEBUG\n");
  #endif
  
  if(argc != 2){
    printf("Please, provide dictionary filename\n");
    return -1;
  }
  
  if(!Init(&root, argv[1])){
    return -2;
  }

  printf("Please, enter string to search\n");
  printf("To exit enter \"exit\"\n");
  while(fgets(buf, sizeof(buf), stdin)){
    if(strcmp("exit\n",buf) == 0){
      printf("Bye.\n");
      return 0;
    }
    if(Search(root,buf)){
      printf("YES\n");
    }else{
      printf("NO\n");
    }    
  }

  return 0;
}
