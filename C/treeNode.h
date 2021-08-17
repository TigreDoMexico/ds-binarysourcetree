#ifndef _TREE_NODE_H_
#define _TREE_NODE_H_

typedef struct treeNode {
	int valor;
	struct treeNode* nDir;
	struct treeNode* nEsq;	
} TREE_NODE;

typedef TREE_NODE* PNODE;

PNODE constructor(int value);
PNODE addNode(PNODE root, PNODE node);
PNODE removeNode(PNODE root, int value);
PNODE searchNode(PNODE root, int value);
int countNodes(PNODE root);
void printNodes(PNODE root);

#endif
