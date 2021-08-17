#include<stdio.h>
#include<malloc.h>
#include "treeNode.h"

PNODE constructor(int value) {
	PNODE newNode = (PNODE) malloc(sizeof(TREE_NODE));
	
	newNode->valor = value;
	newNode->nDir = NULL;
	newNode->nEsq = NULL;
	
	return newNode;
}

PNODE addNode(PNODE root, PNODE node) {	
	if (root == NULL) return node;
	
	if (node->valor > root->valor)
		root->nDir = addNode(root->nDir, node);
	else
		root->nEsq = addNode(root->nEsq, node);
	
	return root;
}

PNODE removeNode(PNODE root, int value) {
	return root;
}

PNODE searchNode(PNODE root, int value) {
	if (root == NULL) return NULL;
	if (root->valor == value) return root;
	
	if (value > root->valor) return searchNode(root->nDir, value);
	return searchNode(root->nEsq, value);
}

int countNodes(PNODE root) {
	if (root == NULL) return 0;
	return countNodes(root->nEsq) + 1 + countNodes(root->nDir);
}

void printNodes(PNODE root) {
	if (root != NULL) {
		printf("%d", root->valor);
		printf("[");
		printNodes(root->nEsq);
		printNodes(root->nDir);
		printf("]");
	}
}

