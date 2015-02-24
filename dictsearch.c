#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdint.h>

#include "avl_tree.h"

#define LINE_MAX 256
#define CH_MIN 32
#define CH_MAX 127

void put_data(avl_Node * node, char * str){
  int len = strlen(str) + 1;
  if(len > 0){
    node->data = malloc(len);
    memcpy(node->data, str, len);
  }
}
  
int aux_cmp(char * base, char * conc, int * len){
  *len = 0;
  if(base == 0){
    return -2;
  }
  while(*base++ == *conc++){
    (*len)++;
    if(*base == 0 && *conc != 0){
      return -3;
    }
    if(*base == 0 && *conc == 0){
      return -1;
    }
  }

  if(*len == 0 && *base == 0){
    return 1;
  }
  
  if(*base == 0 && *conc != 0){
    return 2;
  }
  return 1;
}

void aux_trim(avl_Node * node, int len){
  int trimLen = strlen(node->data) + 1 - len;

  if(trimLen > 0){
    if(len == 0){
      free(node->data);
      node->data = NULL;
      return;
    }
    node->data[len] = 0;
    node->data = realloc(node->data, len);
  }
}

bool init(avl_Node ** root, char * filename){
  FILE * f;
  char buf[LINE_MAX];
  int linesAdded = 0, linesDiscarded = 0;
  
  
  f = fopen(filename, "r");
  if(f == NULL){
    printf("Error, no %s found\n", filename);
    return false;
  }

  //root->searchNode = avl_insert(root->searchNode, 0, NULL);
  
  while(fgets(buf, sizeof(buf), f)){
    // printf("+Dict line: %s", buf);
    char * ch = buf;
 

    do{
      if((*ch < CH_MIN || *ch > CH_MAX) && *ch != '\n'){
	break;
      }
    }while(*++ch);

    if(*ch){
      // printf("Not valid input\n");
      linesDiscarded++;
      continue;
    }
    linesAdded++;    

    avl_Node * currNode = *root;
    ch = buf;
    do{
      //printf("Inserting 0x%02X\n", *ch);

      avl_Node * pNode = avl_find(currNode->next, *ch);
      
      if(pNode == NULL){
	//	printf("No node found, adding new\n");
	currNode->next = avl_insert(currNode->next, *ch);
	pNode = avl_find(currNode->next, *ch);
	put_data(pNode, ch + 1);
	//	printf("Put data %s", ch + 1);
	break;
      }

      int len = 0;
      int cmpRes = aux_cmp(pNode->data, ch + 1, &len);
      // printf("aux_cmp %s %s = res %d len %d\n",pNode->data, ch + 1, cmpRes, len);

      if(cmpRes == -3 || cmpRes == 2){
	while(len-- > 0){
	  ch++;
	}
	currNode = pNode;
	continue;
      }      

      if(cmpRes == -2){
	currNode = pNode; //move to next level
	continue;
      }
      
      if(cmpRes == -1){
	break; //already in dict
      }

      // printf("Moving old node key %c data %s\n", pNode->key, pNode->data);
      
      // printf("Inserting next node key %c\n", *(pNode->data + len));
      avl_Node *oldNext = pNode->next;
      pNode->next = NULL;
      pNode->next = avl_insert(pNode->next, *(pNode->data + len));
      avl_Node * pNode2 = avl_find(pNode->next, *(pNode->data + len));
      //printf("Putting data %s\n", pNode->data + 1 + len);
      put_data(pNode2, pNode->data + 1 + len);
      pNode2->next = oldNext;
      aux_trim(pNode, len);

      //printf("Inserting next node key %c\n", *(ch + len + 1));
      pNode->next = avl_insert(pNode->next, *(ch + len + 1));
      pNode = avl_find(pNode->next, *(ch + len + 1));
      //printf("Putting data %s\n", ch + len  + 2);
      put_data(pNode, ch + len + 2);
      break;
      
    }while(*++ch);
  }
  
  fclose(f);

  printf("Lines: added %d discarded %d\n", linesAdded, linesDiscarded);
  printf("Nodes count: %d size: %dB\n", avl_nodes_count(), (int)sizeof(avl_Node));
  
  return true;
}

bool search(avl_Node * root, char * str){
  avl_Node * node = root->next;
  do{
    //  printf("Looking for %c [0x%02X]\n", *str, *str);
    //avl_print(node);
    node = avl_find(node, *str);

    if(node == NULL){
      return false;
    }

    char * pData = node->data;
    if(pData != NULL){
      do{
	str++;
	if(*str != *pData){
	  str--;
	  break;
	}	
      }while(*++pData);
      if(*(str + 1) == 0){
	return true;
      }
    }
         
    node = node->next;
   
    }while(*str++);
  return true;  
}


int main(int argc, char * argv[]){
  char buf[LINE_MAX];
  avl_Node * root = NULL;
  root = avl_insert(root, 0);

  #ifdef DEBUG
  printf("DEBUG\n");
  #endif
  
  if(argc != 2){
    printf("Please, provide dictionary filename\n");
    return -1;
  }
  
  if(!init(&root, argv[1])){
    return -2;
  }

  printf("Please, enter string to search\n");
  printf("To exit enter \"exit\"\n");
  while(fgets(buf, sizeof(buf), stdin)){
    if(strcmp("exit\n",buf) == 0){
      printf("Bye.\n");
      return 0;
    }
    if(search(root,buf)){
      printf("YES\n");
    }else{
      printf("NO\n");
    }    
  }

  return 0;
}
