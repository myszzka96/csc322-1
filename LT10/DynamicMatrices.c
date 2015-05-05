#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <unistd.h>

typedef char String[20];

double * input_matrix(int* r, int* c, String name) {
	int rows = *r;
	int columns = *c;
	double *matrix = (double*)(malloc(rows*columns*sizeof(double)));	

	int row, column;
	for(row = 0; row < rows; row++) {
		for(column = 0; column < columns; column++) {
			printf("Enter value for (%d,%d) in %s: ", row, column, name);
			scanf("%lf", matrix+row+column);
		}
		printf("\n");
	}
	return matrix;
}

void output_matrix(double* m,int rows,int columns){
	int row, column;
	for(row = 0; row < rows; row++) {
		printf("Row %d [ ", row);
		for(column = 0; column < columns; column++) {
			printf("%.0lf ", *(m+row+column));
		}
		printf("]\n");
	}
}

int matrix_multiply(double* m1, int m1_rows, int m1_columns, double* m2, int m2_rows, int m2_columns, double* m3) {
	if(m1_rows == m2_rows && m1_columns == m2_columns) {
		int row, column;
		int rows = m1_rows;       
		int columns = m1_columns;

		for(row = 0; row < rows; row++) {
			for(column = 0; column < columns; column++){
				double x = *(m1+row+column);
				double y = *(m2+row+column);
				double z = x*y;
				*(m3+row+column) = z;
			}
		}
		return 1;
	} else {
		return 0;
	}
}

int main(void) {

	double *m1,*m2,*m3;
	int m1_rows,m1_columns,m2_rows,m2_columns;

	printf("Enter M1 Dimensions: ");
	scanf("%d %d", &m1_rows, &m1_columns);

	printf("Enter M2 Dimensions: ");
	scanf("%d %d", &m2_rows, &m2_columns);

	if (((m1 = input_matrix(&m1_rows,&m1_columns,"Matrix 1")) != NULL) &&
			((m2 = input_matrix(&m2_rows,&m2_columns,"Matrix 2")) != NULL) &&
			((m3 = malloc(m1_rows*m2_columns*sizeof(double))) != NULL)) {
		printf("Matrix 1\n");
		output_matrix(m1,m1_rows,m1_columns);
		printf("Matrix 2\n");
		output_matrix(m2,m2_rows,m2_columns);
		if (matrix_multiply(m1,m1_rows,m1_columns,m2,m2_rows,m2_columns,m3)) {
			printf("Product\n");
			output_matrix(m3,m1_rows,m2_columns);
			free(m1);
			free(m2);
			free(m3);
			return(0);
		} else {
			printf("Error in dimensions\n");
			free(m1);
			free(m2);
			free(m3);
			return(-1);
		}
	} else {
		free(m1);
		free(m2);
		free(m3);
		printf("Error allocating memory\n");
		return(-2);
	}
}

