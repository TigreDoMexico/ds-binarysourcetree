#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

#define COUNT 10

typedef struct treeNode {
	int valor;
	struct treeNode* nDir;
	struct treeNode* nEsq;
} TREE_NODE;

typedef TREE_NODE* PNODE;

PNODE constructor(int value);
PNODE addNode(PNODE root, PNODE node);
PNODE removeNode(PNODE root, int value);
PNODE deleteNode2(PNODE root, int value);
PNODE searchWithFather(PNODE root, int value, PNODE* father);
PNODE searchNode(PNODE root, int value);
int countNodes(PNODE root);
void printNodes(PNODE root);
void print2DUtil(PNODE root, int space);

#endif
