#include<stdio.h>
#include<stdlib.h>
#include "treeNode.h"

/* HEADER PRIVATE METHODS */

PNODE searchWithFather(PNODE root, int value, PNODE* father);
int isFilhoDireita(PNODE node, PNODE father);
int isFilhoEsquerda(PNODE node, PNODE father);
PNODE deleteNoChild(PNODE node, PNODE father, PNODE root);
PNODE deleteOneChildDir(PNODE node, PNODE father, PNODE root);
PNODE deleteOneChildEsq(PNODE node, PNODE father, PNODE root);
PNODE deleteTwoChild(PNODE node, PNODE father, PNODE root);

/* HEADER MAIN METHODS */

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

int countNodes(PNODE root) {
	if (root == NULL) return 0;
	return countNodes(root->nEsq) + 1 + countNodes(root->nDir);
}

void printPreOrder(PNODE root) {
	if (root != NULL) {
		printf("%d", root->valor);
		printf("[");
		printPreOrder(root->nEsq);
		printPreOrder(root->nDir);
		printf("]");
	}
}

void print2DTree(PNODE root, int space)
{
    if (root == NULL)
        return;
 
    space += COUNT;
 
    print2DTree(root->nDir, space);
 
    int i;
    printf("\n");
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->valor);
 
    print2DTree(root->nEsq, space);
}

PNODE addNode(PNODE root, PNODE node) {
	if (root == NULL) return node;

	if (node->valor > root->valor)
		root->nDir = addNode(root->nDir, node);
	else
		root->nEsq = addNode(root->nEsq, node);

	return root;
}

PNODE deleteNode(PNODE root, int value) {	
	PNODE curr, father;

	if (root == NULL) return NULL;	
	curr = searchWithFather(root, value, &father);
			
	// 0 FILHOS
	if (curr->nDir == NULL && curr->nEsq == NULL) {
		return deleteNoChild(curr, father, root);
	}
	
	// 1 FILHO
	if (curr->nDir != NULL && curr->nEsq == NULL) { // FILHO A DIREITA
		return deleteOneChildDir(curr, father, root);
	}
	
	if (curr->nEsq != NULL && curr->nDir == NULL) { // FILHO A ESQUERDA
		return deleteOneChildEsq(curr, father, root);
	}
	
	// 2 FILHOS
	return deleteTwoChild(curr, father, root);
}

/* PRIVATE METHODS */

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

int isFilhoDireita(PNODE node, PNODE father) {
	if (father != NULL)
		return node->valor > father->valor ? 1 : 0;
	
	return 0;
}

int isFilhoEsquerda(PNODE node, PNODE father) {
	if (father != NULL)
		return node->valor < father->valor ? 1 : 0;

	return 0;
}

PNODE deleteNoChild(PNODE node, PNODE father, PNODE root) {
	free(node);
		
	if (father != NULL) {
		if (isFilhoDireita(node, father) == 1) father->nDir = NULL;
		else if (isFilhoEsquerda(node, father) == 1) father->nEsq = NULL;
	 		
		return root;
	}
		
	return NULL;
}

PNODE deleteOneChildDir(PNODE node, PNODE father, PNODE root) {
	if (father != NULL) {
		if (isFilhoDireita(node, father) == 1) father->nDir = node->nDir;
	  	else if (isFilhoEsquerda(node, father) == 1) father->nEsq = node->nDir;
			
		free(node);
		return root;
	}
		
	PNODE returnValue = node->nDir;
	free(node);
		
	return returnValue;
}

PNODE deleteOneChildEsq(PNODE node, PNODE father, PNODE root) {
	if (father != NULL) {
		if (isFilhoDireita(node, father) == 1) father->nDir = node->nEsq;
	    else if (isFilhoEsquerda(node, father) == 1) father->nEsq = node->nEsq;
			
		free(node);
		return root;
	}

	PNODE returnValue = node->nEsq;
	free(node);
		
	return returnValue;
}

PNODE deleteTwoChild(PNODE node, PNODE father, PNODE root) {
	// Pegar o elemento mais a direita dos filhos a esquerda
	PNODE fatherPromoted = node;
	PNODE promoted = node->nEsq;
		
	while (promoted->nDir != NULL) {
		fatherPromoted = promoted;
		promoted = promoted->nDir;
	}
	
	if (fatherPromoted != node) {
		fatherPromoted->nDir = promoted->nEsq;
		promoted->nEsq = node->nEsq;
	}
		
	promoted->nDir = node->nDir;
	
	if (father != NULL) {
	  	if (isFilhoDireita(node, father) == 1) father->nDir = promoted;
	  	else if (isFilhoEsquerda(node, father) == 1) father->nEsq = promoted;
	  	
	  	free(node);
	  		
	  	return root;
	}
	
	free(node);
	return promoted;
}

