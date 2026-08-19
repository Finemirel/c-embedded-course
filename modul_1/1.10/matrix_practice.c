#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MATRIX_ROW 3
#define MATRIX_COLUMN 4

void print_matrix(int m[][4], int rows);

int main(void) {
  srand((unsigned int)time(NULL));

  int matrix[MATRIX_ROW][MATRIX_COLUMN];
  for(int i = 0; i < MATRIX_ROW; i++) {
    for(int j = 0; j < MATRIX_COLUMN; j++) {
      matrix[i][j] = -50 + (int)((double)rand() / (RAND_MAX +1.0) * 100);
    }  
  }
  print_matrix(matrix, MATRIX_ROW);
  
  return 0;
}

void print_matrix(int m[][4], int rows) {
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < 4; j++) {
      printf("%d ", m[i][j]);
    } 
    printf("\n");
  }
}
