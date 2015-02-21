// based on habrahabr.ru/post/150732/ - C++ implementation of avl-tree
#include "avl_tree.h"

Node * const_node(char key, void * data){
  Node * node = malloc(sizeof(Node));
  node->key = key;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  return node;
}

uint8_t get_height(Node * node){
  return node ? node->height : 0;
}

int get_bfactor(Node * node){
  return get_height(node->right) - get_height(node->left);
}

void fix_height(Node * node){
  uint8_t hl = get_height(node->left);
  uint8_t hr = get_height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

Node * rotate_right(Node * node){ //правый поворот вокруг p
  Node* tmp = node->left;
  node->left = node->right;
  node->right = tmp;

  fix_height(node);
  fix_height(tmp);
  return tmp;
}

Node * rotate_left(Node * node){ //левый поворот вокруг p
  Node* tmp = node->right;
  node->right = node->left;
  node->left = tmp;

  fix_height(node);
  fix_height(tmp);
  return tmp;
}

Node * balance(Node * node){ //балансировка узла
  fix_height(node);
  
  if(get_bfactor(node) == 2){
    if(get_bfactor(node->right) < 0){
      node->right = rotate_right(node->right);
    }
    return rotate_left(node);
  }

  if(get_bfactor(node) == -2){
    if(get_bfactor(node->left) > 0){
	node->left = rotate_left(node->left);
      }
      return rotate_right(node);
  }

  return node;
}

Node * avl_insert(Node * node, char key, void * data){
  if(!node){
    return const_node(key, data);
  }

  if(key < node->key){
    node->left = avl_insert(node->left, key, data);
  }else{
    node->right = avl_insert(node->right, key, data);
  }

  return balance(node);
}

Node * avl_find(Node * node, char key){
  if(node == NULL){
    return NULL;
  }
  
  if(node->key == key){
    return node;
  }

  if(key < node->key){
    return avl_find(node->left, key);
  }else{
    return avl_find(node->right, key);
  }
}

void avl_print(Node * node){
  if(node == NULL){
    printf(";\n");
    return;
  }
  printf("%c\n", node->key);
  printf("<");
  avl_print(node->left);
  printf(">");
  avl_print(node->right);
}
