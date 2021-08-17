#include <stdio.h>
#include "tree.h"

int main(int argc, char *argv[]) {
	TREE myTree = constructorTree();

	addValueInTree(&myTree, 15);
	addValueInTree(&myTree, 12);
	addValueInTree(&myTree, 50);
	addValueInTree(&myTree, 40);
	addValueInTree(&myTree, 2);
	addValueInTree(&myTree, 10);
	addValueInTree(&myTree, 100);
	addValueInTree(&myTree, 5);
	addValueInTree(&myTree, 1);

	printTree(&myTree);

	searchValueInTree(&myTree, 40);
	searchValueInTree(&myTree, 16);

	printf("A ARVORE POSSUI %d ELEMENTOS", numberOfNodesInTree(&myTree));
}
