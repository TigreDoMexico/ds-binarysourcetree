#ifndef _TREE_H_
#define _TREE_H_
#include "treeNode.h"

typedef struct {
	PNODE root;
} TREE;

typedef TREE* PTREE;

TREE constructorTree();

void addValueInTree(PTREE tree, int value);
void removeValueInTree(PTREE tree, int value);
int numberOfNodesInTree(PTREE tree);
void searchValueInTree(PTREE tree, int value);
void printTree(PTREE tree);

#endif
