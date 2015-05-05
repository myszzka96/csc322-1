#include <stdio.h>
#include <stdlib.h>

int MatrixOne[3][3];
int MatrixTwo[3][3];
int MatrixThree[3][3];

void fillMatrixOne() {
	int x, y; 
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			printf("Pick an integer for (%i,%i) in matrix 1\n", (x+1), (y+1));
			scanf("%i", & *(*(MatrixOne + x) + y)); 
		}
	}
}

void fillMatrixTwo() {
	int x, y;
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			printf("Pick an integer for (%i,%i) in matrix 2\n", (x+1), (y+1));
			scanf("%i", & *(*(MatrixTwo + x)+ y));
		}
	}
}

void printMatrixOne() {
	int x, y;
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			printf("%i, ", *(*(MatrixOne + x) + y));
		}
		printf("\n");
	}
}

void printMatrixTwo() {
	int x, y;
	for (x = 0; x < 3; x++) {
		for (y = 0; y < 3; y++) {
			printf("%i, ", *(*(MatrixTwo + x) + y));
		}
		printf("\n");
	}
}

int mult(int x, int y) {
	return x * y;
}

int calcMatrixSlot(int x, int y) {  
	int product;
	product = mult((*(*(MatrixOne + x) + 0)), (*(*(MatrixTwo + 0) + y))) + mult((*(*(MatrixOne + x) + 1)), (*(*(MatrixTwo + 1) + y))) + mult((*(*(MatrixOne + x) + 2)), (*(*(MatrixTwo + 2) + y))); 
	return product;
}

void multMatrices() { 
	int x, y;
	for (x = 0; x < 2; x++) {
		for (y = 0; y < 2; y++) {
			*(*(MatrixThree + x) + y) = calcMatrixSlot(x, y);
		}
	}
}

void printMatrixThree() {
	int x, y;
	printf("Matrix 1 * Matrix 2 =\n");
	for (x = 0; x < 3; x++) {
		printf("[");
		for (y = 0; y < 3; y++) {
			printf("%i ", *(*(MatrixThree + x) + y));
		}
		printf("]");
		printf("\n");
	}
}

int main () {
	fillMatrixOne();
	fillMatrixTwo();
	multMatrices();
	printMatrixThree();
	return EXIT_SUCCESS;
}

