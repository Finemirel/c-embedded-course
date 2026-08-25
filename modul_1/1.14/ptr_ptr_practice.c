#include <stdio.h>

void bad_choose(int *a, int *b, int *result);
void good_choose(int *a, int *b, int **result);

int main(void) {
  
  //#1
  int x = 42;
  int *p = &x;
  int **pp = &p;
  
  printf("Value var x : %d, %d, %d\n", x, *p, **pp);
  printf("Adres var x : %p, %p, %p\n", (void*)&x, (void*)&(*p), (void*)&(**pp));
  printf("Adres pointer p : %p, %p\n", (void*)&p, (void*)&(*pp));
  
  //#2
  int m = 10, n = 77;
  int *winner = NULL;
  bad_choose(&m, &n, winner);
  if (winner != NULL) {
    printf("After bad choose winner is : %d\n", *winner);
  } else {
    printf("After bad choose winner is still NULL\n");
  }
  good_choose(&m, &n, &winner);
  if (winner != NULL) {
    printf("After good choose winner is : %d\n", *winner);
  }else {
    printf("After good choose winner is still NULL\n");
  }
  
  //#3
  const char *boards[] = {"ESP32-WROOM-32", "STM32F103C8T6", "Blue Pill"};
  const char **bp = boards;
  size_t size = sizeof(boards)/sizeof(boards[0]);
  printf("Size elements of array is : %zu\n", size);
  printf("First way:\n");
  for(size_t i = 0; i < size; i++) {
    printf("%s\n", bp[i]);
  }
  printf("Second way:\n");
  for(size_t i = 0; i < size; i++) {
    printf("%s\n", *(bp+i));
  }
  
  //#4
  printf("Size x = %zu;\n", sizeof(x));
  printf("Size p = %zu;\n", sizeof(p));
  printf("Size pp = %zu;\n", sizeof(pp));
  printf("Size bp = %zu;\n", sizeof(bp));
  /*First, 'x' is var integer who have size 4 bytes but other vars is pointers who has in my platform 8 bytes.*/
  
  return 0;
}

void bad_choose(int *a, int *b, int *result){
  if(*a > *b) {
    result = a;
    printf("In bad choose %d\n", *result);
  } else if(*a < *b) {
    result = b;
    printf("In bad choose %d\n", *result);
  } else {
    printf("In bad choose value is equals\n");
  }
}

void good_choose(int *a, int *b, int **result){
  if(*a > *b) {
    *result = a;
    printf("In good choose %d\n", **result);
  } else if(*a < *b) {
    *result = b;
    printf("In good choose %d\n", **result);
  } else {
    printf("In good choose value is equals\n");
  } 
}
