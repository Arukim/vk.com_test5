#include <stdint.h>
#include <stdlib.h>

#ifndef AVL_TREE_H
#define AVL_TREE_H

#pragma pack(push,1)
typedef struct avl_Node {
  char key;
  char * data;
  uint8_t height;
  struct avl_Node * next;
  struct avl_Node * left;
  struct avl_Node * right;
}avl_Node;
#pragma pack(pop)

avl_Node * avl_insert(avl_Node * node, char key);
avl_Node * avl_find(avl_Node * node, char key);
void avl_print(avl_Node * node);
int avl_nodes_count();

#endif // AVL_TREE_H
