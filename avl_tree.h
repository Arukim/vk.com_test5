#include <stdint.h>
#include <stdlib.h>

#ifndef AVL_TREE_H
#define AVL_TREE_H

typedef struct Node {
  char key;
  void * data;
  uint8_t height;
  struct Node * left;
  struct Node * right;
}Node;

Node * avl_insert(Node * node, char key, void * data);
Node * avl_find(Node * node, char key);
void avl_print(Node * node);

#endif // AVL_TREE_H
