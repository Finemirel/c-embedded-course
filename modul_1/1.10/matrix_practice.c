#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MATRIX_ROW 3
#define MATRIX_COLUMN 4

void print_matrix(int rows, int columns, int m[rows][columns]);
int sum_matrix(int rows, int columns, int m[rows][columns]);
void transpose(int rows, int columns, int m[rows][columns], int res[columns][rows]);

int main(void) {
  srand((unsigned int)time(NULL));

  int matrix[MATRIX_ROW][MATRIX_COLUMN];
  for(int i = 0; i < MATRIX_ROW; i++) {
    for(int j = 0; j < MATRIX_COLUMN; j++) {
      matrix[i][j] = -50 + (int)((double)rand() / (RAND_MAX +1.0) * 100);
    }  
  }
  
  print_matrix(MATRIX_ROW, MATRIX_COLUMN, matrix);
  
  int (*p)[MATRIX_COLUMN] = matrix;
  printf("%d\n", p[1][2]);
  
  int summ = sum_matrix(MATRIX_ROW, MATRIX_COLUMN, matrix);
  printf("%d\n", summ);
  int reverse_matrix[MATRIX_COLUMN][MATRIX_ROW];
  transpose(MATRIX_ROW, MATRIX_COLUMN, matrix, reverse_matrix);
  print_matrix(MATRIX_COLUMN, MATRIX_ROW, reverse_matrix);
  
  return 0;
}

void print_matrix(int rows, int columns, int m[rows][columns]) {
  printf("In print_matrix:\n");
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      printf("%d ", m[i][j]);
    } 
    printf("\n");
  }
}

int sum_matrix(int rows, int columns, int m[rows][columns]) {
  printf("In sum_matrix:\n");
  int summ = 0;
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      summ += m[i][j];
    } 
  }
  return summ;
}

void transpose(int rows, int columns, int src[rows][columns], int res[columns][rows]) {
  printf("In transpose:\n");
  for(int i = 0; i < rows; i++) {
    for(int j = 0; j < columns; j++) {
      res[j][i] = src[i][j];
    } 
  }
}
