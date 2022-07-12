//Maxheap
/*
	
*/
#include <stdio.h>
#include <stdlib.h>
#define SIZE 15

typedef int Info[SIZE];
typedef struct{
    int data[SIZE];
    int lastNdx;
}Heap;

void initializeHeap(Heap *H);
void insert(Heap *H, int num);

int deleteMax(Heap *H);
void maxHeapify(Heap *H);

void heapSort(Heap *H);
void display(Heap H);

int main(){
    Heap H;
    Info x = {20, 5, 9, 8, 6, 9, 10, 10, 18, 9};
    int i, len = 10, toFind;
    
    initializeHeap(&H);
    
    for(i = 0; i < len; i++) insert(&H, x[i]);
	
    printf("\nHeapsort:\n"); heapSort(&H); display(H);
	
    return 0;
}

void initializeHeap(Heap *H){
    H->lastNdx = -1;
}

void insert(Heap *H, int num){
    int childndx = 0, parentndx = 0;
	
    if (H->lastNdx < SIZE-1){
        H->lastNdx++;
        childndx = H->lastNdx;
        parentndx = (childndx-1)/2;

        while (childndx > 0 && H->data[parentndx] > num){
            H->data[childndx] = H->data[parentndx];
            childndx = parentndx;
            parentndx = (childndx-1)/2;
        }
        H->data[childndx] = num;
    }
}

int deleteMax(Heap *H){
	int min, parent, child, swap;
	
	//Get the root
    min = H->data[0];
    H->data[0] = H->data[H->lastNdx--];
    parent = 0;
    child = (parent*2)+1;

    while(child <= H->lastNdx){
		//Identify the greater ? right or left
        if(child+1 <= H->lastNdx && H->data[child+1] > H->data[child]){
			//child + 1 is right and child is left
            child++;
        }

		//Swapping time
        if(H->data[parent] < H->data[child]){
            swap = H->data[parent];
            H->data[parent] = H->data[child];
            H->data[child] = swap;
            
            //moving parent
            parent = child;
            //moving child to Info left of current parent
            child = (parent*2)+1;
        } else{
            child = H->lastNdx+1;
        }
    }
    return min;
}

void maxHeapify(Heap *H){
	int lowPar, down, child, swap;
	
	if(H->lastNdx != -1){
		lowPar = (H->lastNdx-1)/2;
		while(lowPar >= 0){
			down = lowPar;
			child = (down*2)+1;

			while(child <= H->lastNdx){
				if(child+1 <= H->lastNdx && H->data[child+1] > H->data[child]){
					child++;
				}
				if(H->data[down] < H->data[child]){
					swap = H->data[down];
					H->data[down] = H->data[child];
					H->data[child] = swap;
					down = child;
					child = (down*2)+1;
				} else{
					child = H->lastNdx+1;
				}
			}
			lowPar--;
		}
	}
}

void heapSort(Heap *H){
    int i, oldLast, max;

    /*
	    // call insert function to populate the heap//
	    for(i = 0; i < H->lastNdx; i++){
	    	insert(H, H->data[i]);
		}
	*/
	maxHeapify(H);	

    oldLast = H->lastNdx;
    while (H->lastNdx != -1){
        max = deleteMax(H);
        H->data[H->lastNdx+1] = max;
    }
    H->lastNdx = oldLast;
}

void display(Heap H){
    int x;
    for (x = 0; x < H.lastNdx+1; x++){
        printf("[%d]\t", H.data[x]);
    }
    printf("\n");
    for (x = 0; x < H.lastNdx+1; x++){
        printf(" %d\t", x);
    }
    printf("\nLast Index: %d\n", H.lastNdx);
}
