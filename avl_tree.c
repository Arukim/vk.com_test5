// based on habrahabr.ru/post/150732/ - C++ implementation of avl-tree
#include <stdio.h>
#include "avl_tree.h"

void print_impl(avl_Node * node, int depth);

int _nodes_count = 0;

avl_Node * const_node(char key, void * data){
  avl_Node * node = malloc(sizeof(avl_Node));
  node->key = key;
  node->data = data;
  node->left = NULL;
  node->right = NULL;
  node->height = 1;
  _nodes_count++;
  return node;
}

uint8_t get_height(avl_Node * node){
  return node ? node->height : 0;
}

int get_bfactor(avl_Node * node){
  return get_height(node->right) - get_height(node->left);
}

void fix_height(avl_Node * node){
  uint8_t hl = get_height(node->left);
  uint8_t hr = get_height(node->right);
  node->height = (hl > hr ? hl : hr) + 1;
}

avl_Node * rotate_right(avl_Node * node){ //правый поворот вокруг p
  avl_Node* tmp = node->left;
  node->left = tmp->right;
  tmp->right = node;

  fix_height(node);
  fix_height(tmp);
  return tmp;
}

avl_Node * rotate_left(avl_Node * node){ //левый поворот вокруг p
  avl_Node* tmp = node->right;
  node->right = tmp->left;
  tmp->left = node;

  fix_height(node);
  fix_height(tmp);
  return tmp;
}

avl_Node * balance(avl_Node * node){ //балансировка узла
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

avl_Node * avl_insert(avl_Node * node, char key, void * data){
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

avl_Node * avl_find(avl_Node * node, char key){
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

void avl_print(avl_Node *node){
  print_impl(node,0);
}

int avl_nodes_count(){
  return _nodes_count;
}

void print_impl(avl_Node * node, int depth){
  int i=0;
  
  if(node == NULL){
    printf(";\n");
    return;
  }

  depth++;
  printf("0x%02X\n", node->key);

  for(i=0; i<depth; i++){
    putchar('-');
  }
  printf("<");
  print_impl(node->left, depth);
  
  for(i=0; i<depth; i++){
    putchar('-');
  }
  printf(">");
  print_impl(node->right, depth);
}
