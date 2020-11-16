#include <stdio.h>
#include <stdlib.h>
#include <time.h>

struct m_matrix{
	int row;
	int col;
	int **array;
};

typedef struct m_matrix matrix;

void matrix_malloc(matrix* mat, int row, int col){
	(*mat).row = row;
	(*mat).col = col;
	(*mat).array = malloc(row*sizeof(int*));
	if ((*mat).array == NULL){
		printf("Memory allocation problem!\n");
		exit(1);
	}

	for(int i=0; i<row; i++){
		(*mat).array[i] = malloc(col*sizeof(int));
		if ((*mat).array[i] == NULL){
			printf("Memory allocation problem!\n");
			exit(1);
		}
	}
}


void free_malloc(matrix* mat, int row){
	(*mat).row = row;
	for(int i=0; i<row; i++){
		free((*mat).array[i]);
	}
	free((*mat).array);
}


void fill_matrix(matrix* mat, int row, int col){
	matrix_malloc(mat, row, col);
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			mat->array[i][j] = rand()%100;
		}
	}
}


void multiply_matrices(matrix* mat1, matrix* mat2, matrix* product){
	for(int i=0; i<mat1->row; i++){
		for(int j=0; j<mat2->col; j++){
			product->array[i][j] = 0;
		}
	}

	for(int i=0; i<mat1->row; i++){
		for(int j=0; j<mat2->col; j++){
			for(int k=0; k<mat2->row; k++){
				product->array[i][j] = product->array[i][j] + (mat1->array[i][k])*(mat2->array[k][j]);
			}
		}
	}
}


void print_matrix(matrix* mat, int row, int col){
	(*mat).row = row;
	(*mat).col = col;
	for(int i=0; i<row; i++){
		for(int j=0; j<col; j++){
			printf("%d ", mat->array[i][j]);
		}
		printf("\n");
	}
}


int main(int argc, char **argv){

	if(argc != 4 || atoi(argv[1])<0 || atoi(argv[2])<0){
		printf("ERROR: Invalid input\n");
		return -1;
	}

	srand(atoi(argv[3]));
	matrix mat1, mat2, product;

	matrix_malloc(&mat1, atoi(argv[1]), atoi(argv[2]));
	fill_matrix(&mat1, atoi(argv[1]), atoi(argv[2]));
	printf("MATRIX 1:\n");
	print_matrix(&mat1, atoi(argv[1]), atoi(argv[2]));

	printf("\n");

	matrix_malloc(&mat2, atoi(argv[2]), atoi(argv[1]));
	fill_matrix(&mat2, atoi(argv[2]), atoi(argv[1]));
	printf("MATRIX 2:\n");
	print_matrix(&mat2, atoi(argv[2]), atoi(argv[1]));

	printf("\n");

	matrix_malloc(&product, atoi(argv[1]), atoi(argv[1]));

	clock_t start = clock();
	multiply_matrices(&mat1, &mat2, &product);
	clock_t end = clock();

	printf("RESULT:\n");
	print_matrix(&product, atoi(argv[1]), atoi(argv[1]));
	printf("\n");
	printf("EXECUTION TIME: %f \n", (double)(end-start)/CLOCKS_PER_SEC);

	free_malloc(&mat1, atoi(argv[1]));
	free_malloc(&mat2, atoi(argv[2]));
	free_malloc(&product, atoi(argv[1]));

	return 0;
}
