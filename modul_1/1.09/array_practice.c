#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define SIZE 7
#define SIZED 5

int find_max(int arr[], int size);

int main(void) {
  srand((unsigned int)time(NULL));

  int scores[SIZE];
  for(int i = 0; i < SIZE; i++) {
    scores[i] = (i + 1) * 10;
  }
  
  int summator = 0;
  for(int i = 0; i < SIZE; i++) {
    summator += scores[i];
    printf("%d\n", scores[i]);
  }
  printf("%d\n", summator);
  
  printf("%d\n", find_max(scores, SIZE));
  
  double temps[SIZED] = {0};
  for(int i = 0; i < SIZED; i++) {
    temps[i] = -10.0 + (rand() / (double)RAND_MAX) * 50.0;
  }
  
  double summ = 0;
  
  for(int i = 0; i < SIZED; i++) {
    //summ += temps[i];
    printf("%.2f\n", temps[i]);
  }
  
  for(int i = 0; i < SIZED; i++) {
    summ += temps[i];
  }
  printf("%.2f\n", summ/SIZED);
  
  // scores[SIZE] = 999;  // UB! Индекс 7 не существует (валидны только 0..6),
                         // запись пойдёт в чужую память — может испортить
                         // соседнюю переменную или служебные данные стека
  
  return 0;
}

int find_max(int arr[], int size) {
  int max = arr[0];
  for(int i = 0; i < size; i++) {
    if(arr[i] > max) {
      max = arr[i];
    }
  }
  return max;
}
