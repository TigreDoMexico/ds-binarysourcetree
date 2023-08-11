#include<stdio.h>
#include<stdlib.h>
#include "treeNode.h"

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

/* HEADER METHODS */

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

	// Caso s� haja 1 filho
	if (curr->nEsq == NULL || curr->nDir == NULL)
	{
		if (curr->nEsq == NULL) child = curr->nDir;
		else child = curr->nEsq;
	}
	else // Caso s� haja 2 filho
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
	
	if (father == NULL) { // CASO SEJA A RAIZ PRIM�RIA
		free(curr);
		return child;
	} 
	
	if (value > father->valor) father->nDir = child;
	else father->nEsq = child;
	
	free(curr);
	return root;
}

PNODE deleteNode2(PNODE root, int value) {	
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

int countNodes(PNODE root) {
	if (root == NULL) return 0;
	return countNodes(root->nEsq) + 1 + countNodes(root->nDir);
}

// Function to print binary tree in 2D
// It does reverse inorder traversal
void print2DUtil(PNODE root, int space)
{
    // Base case
    if (root == NULL)
        return;
 
    // Increase distance between levels
    space += COUNT;
 
    // Process right child first
    print2DUtil(root->nDir, space);
 
    // Print current node after space
    // count
    int i;
    printf("\n");
    for (i = COUNT; i < space; i++)
        printf(" ");
    printf("%d\n", root->valor);
 
    // Process left child
    print2DUtil(root->nEsq, space);
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

