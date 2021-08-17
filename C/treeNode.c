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

PNODE searchNode(PNODE root, int value) {
	if (root == NULL) return NULL;
	if (root->valor == value) return root;

	if (value > root->valor) return searchNode(root->nDir, value);
	return searchNode(root->nEsq, value);
}

PNODE searchWithFather(PNODE root, int value, PNODE* father) {
	PNODE curr = root;
	*father = NULL;
	
	while (curr != NULL) {
		if (curr->valor == value) return curr;
		
		*father = curr;
		if (value > curr->valor) curr = curr->nDir;
		else curr = curr->nEsq;
	}
	
	return NULL;
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
	PNODE father, curr, child, aux;
	
	curr = searchWithFather(root, value, &father);
	
	if (curr == NULL) return root;

	// Caso só haja 1 filho
	if (curr->nEsq == NULL || curr->nDir == NULL)
	{
		if (curr->nEsq == NULL) child = curr->nDir;
		else child = curr->nEsq;
	}
	else // Caso só haja 2 filho
	{
		// Pegar o elemento mais a direita dos filhos a esquerda
		aux = curr;
		child = curr->nEsq;
		
		while (child->nDir) {
			aux = child;
			child = child->nDir;
		}
		
		if (aux != curr) {
			aux->nDir = child->nEsq;
			child->nEsq = curr->nEsq;
		}
		
		child->nDir = curr->nDir;		
	}
	
	if (father == NULL) { // CASO SEJA A RAIZ PRIMÁRIA
		free(curr);
		return child;
	} 
	
	if (value > father->valor) father->nDir = child;
	else father->nEsq = child;
	
	free(curr);
	return root;
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

