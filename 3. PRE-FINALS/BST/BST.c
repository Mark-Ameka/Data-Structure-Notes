#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#define MAX 15

typedef int SET[MAX];
typedef struct node{
	int data;
	struct node *left;
	struct node *right;
}BSTList, *BST;

void initTree(BST *T);

void insertTree_NR(BST *T, int newData); //Non-Recursive
void insertTree_R(BST *T, int newData); //Recursive

void deleteTree_NR(BST *T, int data); //Non-Recursive
void deleteTree_R(BST *T, int data); //Recursive

void displayAllOrder(BST T);
void displayInOrder(BST T);
void displayPreOrder(BST T);
void displayPostOrder(BST T);

BST* getMin(BST T);
BST* getMax(BST T);

int getMinElem(BST T);
int getMaxElem(BST T);

int deleteMin(BST *T);
int deleteMax(BST *T);

bool isMember(BST T, int val);
int maxHeight(BST T);
bool isBalance(BST T);

int main(){
	BST T;
	SET x = {29, 5, 12, 66, 20, 50, 40, 68, 99, 2, 1, 23, 63, 56, 71};
	int i, toFind;
		
	initTree(&T);
	for(i = 0; i < MAX; i++) insertTree_NR(&T, x[i]);
	
	displayAllOrder(T);
	
	BST* min = getMin(T);
	printf("\nSmallest element: %d\n", (*min)->data);
	BST* max = getMax(T);
	printf("Largest element: %d\n\n", (*max)->data);
	
	int minVal = getMinElem(T);
	printf("Smallest element(returning int): %d\n", minVal);	
	int maxVal = getMaxElem(T);
	printf("Largest element(returning int): %d\n", maxVal);
	
	toFind = 20;
	printf("\n%d is %s\n\n", toFind, isMember(T, toFind) == 1 ? "found" : "not found");
	
	printf("Deleted: 40\n");
	deleteTree_NR(&T, 40);
		
	displayAllOrder(T);
	
	printf("\nMax height is: %d", maxHeight(T));
	
	printf("\nCurrent tree is %s", isBalance(T) == true ? "balanced" : "not balanced");
	return 0;
}

void initTree(BST *T){
	*T = NULL;
}

void insertTree_NR(BST *T, int newData){
	BST *trav;
	
	for(trav = T; *trav != NULL && (*trav)->data != newData;){
		trav = ((*trav)->data) < newData ? &(*trav)->right : &(*trav)->left;
	}
 	
	if(*trav == NULL){
		*trav = calloc(1, sizeof(BSTList));
		if(*trav != NULL){
			(*trav)->data = newData;
		}
	}
}

void insertTree_R(BST *T, int newData){
	if(*T != NULL && (*T)->data != newData){
		T = ((*T)->data < newData) ? &(*T)->right : &(*T)->left;
		insertTree_R(T, newData);
	} else{
		*T = calloc(1, sizeof(BSTList));
		if(*T != NULL){
			(*T)->data = newData;
		}
	}
}

void deleteTree_NR(BST *T, int data){
	BST temp, *trav;
	
	for(trav = T; *trav != NULL && (*trav)->data != data;){
		trav = ((*trav)->data < data) ? &(*trav)->right : &(*trav)->left;
	}
	
	if(*trav != NULL){
		temp = *trav;
		if((*trav)->left == NULL){
			*trav = (*trav)->right;
		} else if((*trav)->right == NULL){
			*trav = (*trav)->left;
		} else{
			for(trav = &(*trav)->left; (*trav)->right != NULL; trav = &(*trav)->right){}
			temp->data = (*trav)->data;
			
			temp = *trav;
			*trav = temp->left;
		}
		free(temp);
	}
	
}

void deleteTree_R(BST *T, int data){
	BST temp, *trav;
	if(*T != NULL && (*T)->data != data){
		T = ((*T)->data < data) ? &(*T)->right : &(*T)->left;
		deleteTree_R(T, data);
	} else{
		temp = *T;
		if((*T)->left == NULL){
			*T = (*T)->right;
		} else if((*T)->right == NULL){
			*T = (*T)->left;
		} else{
			for(trav = &(*T)->left; (*trav)->right != NULL; trav = &(*trav)->right){}
			temp->data = (*trav)->data;
			
			temp = *trav;
			*trav = temp->left;
		}
		free(temp);
	}
}

void displayInOrder(BST T){
	if(T != NULL){
		displayInOrder(T->left);
		printf("%d ", T->data);
		displayInOrder(T->right);
	}
}

void displayPreOrder(BST T){
	if(T != NULL){
		printf("%d ", T->data);
		displayPreOrder(T->left);
		displayPreOrder(T->right);
	}
}

void displayPostOrder(BST T){
	if(T != NULL){
		displayPostOrder(T->left);
		displayPostOrder(T->right);
		printf("%d ", T->data);
	}
}

void displayAllOrder(BST T){
	printf("Pre-Order:\t");
	displayPreOrder(T); printf("\n");
	printf("In-Order:\t");
	displayInOrder(T); printf("\n");
	printf("Post-Order:\t");
	displayPostOrder(T); printf("\n");
}

BST* getMin(BST T){
	BST *retTree;
	for(retTree = &T; (*retTree)->left != NULL; retTree = &(*retTree)->left){}
	return retTree;
}

BST* getMax(BST T){
	BST *retTree;
	for(retTree = &T; (*retTree)->right != NULL; retTree = &(*retTree)->right){}
	return retTree;
}

int getMinElem(BST T){
	while(T->left != NULL){
		T = T->left;
	}
	return T->data;
}

int getMaxElem(BST T){
	while(T->right != NULL){
		T = T->right;
	}
	return T->data;
}

int deleteMin(BST *T){
	int retVal = 0;
	BST *trav, temp;
	
	for(trav = T; *T != NULL && (*trav)->left != NULL; trav = &(*trav)->left){}
	temp = *trav;
	retVal = temp->data;
	free(temp);
	
	return retVal;
}

int deleteMax(BST *T){
	int retVal = 0;
	BST *trav, temp;
	
	for(trav = T; *T != NULL && (*trav)->right != NULL; trav = &(*trav)->right){}
	temp = *trav;
	retVal = temp->data;
	free(temp);
	
	return retVal;
}

bool isMember(BST T, int val){
	for(; T != NULL && T->data != val;){
		T = (T->data < val) ? T->right : T->left;
	}
	return T != NULL && T->data == val ? true : false;
}

int maxHeight(BST T){
	int flag;
	if(T != NULL){
		int lc = maxHeight(T->left);
		int rc = maxHeight(T->right);
		flag = (lc > rc) ? lc+1 : rc+1;
	} else{
		flag = -1;
	}
	return flag;
}

bool isBalance(BST T){
	if(T != NULL){
		int lc = isBalance(T->left);
		int rc = isBalance(T->right);
		return (lc - rc) <= 1 ? true : false;
	}
}
