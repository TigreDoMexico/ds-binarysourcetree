#include <stdio.h>
#include "tree.h"
#include "treeNode.h"

TREE constructorTree() {
	TREE tree;
	tree.root = NULL;

	return tree;
}

void addValueInTree(PTREE tree, int value) {
   	PNODE newNode = constructor(value);
   	tree->root = addNode(tree->root, newNode);
}

void removeValueInTree(PTREE tree, int value) {
   	tree->root = removeNode(tree->root, value);
}

int numberOfNodesInTree(PTREE tree) {
   	return countNodes(tree->root);
}

void searchValueInTree(PTREE tree, int value) {
	PNODE result = searchNode(tree->root, value);

	if (result == NULL) printf("VALOR %d NAO ENCONTRADO\n", value);
	else printf("VALOR %d ENCONTRADO\n", result->valor);
}

void printTree(PTREE tree) {
	printf("ARVORE: ");
	printNodes(tree->root);
	printf("\n");
}
