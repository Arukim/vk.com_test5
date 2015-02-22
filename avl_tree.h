#include <stdint.h>
#include <stdlib.h>

#ifndef AVL_TREE_H
#define AVL_TREE_H

#pragma pack(push,1)
typedef struct Node {
  char key;
  void * data;
  uint8_t height;
  struct Node * left;
  struct Node * right;
}Node;
#pragma pack(pop)

Node * avl_insert(Node * node, char key, void * data);
Node * avl_find(Node * node, char key);
void avl_print(Node * node);
int avl_nodes_count();

#endif // AVL_TREE_H
