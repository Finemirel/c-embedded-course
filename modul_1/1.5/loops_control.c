#include <stdio.h>
#include <stdlib.h>

int main(void) {
  /* Функция, которая находит первое простое число больше заданного N 
  (перебор + continue для отсечения делителей, 
  break когда простое найдено). */
  
  int min = 0;
  int max = 100;
  int size_first_array;
  printf("Enter size array: ");
  scanf("%d", &size_first_array);
  int first_array[size_first_array];
  for(int i = 0; i < size_first_array; i++) {
    first_array[i] = min + arc4random_uniform(max - min + 1);
  }
  
  int find_number_minus_one;
  printf("Enter your number: ");
  scanf("%d", &find_number_minus_one);
  
  int number_array = 0;
  for(int i = 0; i < size_first_array; i++) {
    if(find_number_minus_one > first_array[i]) continue;
    if(find_number_minus_one < first_array[i]) {
      number_array = first_array[i];
      printf("Find number in array: %d \n", first_array[i]);
      break;
    }
  }
  
  if(number_array == 0) {
    printf("Number in array not found!\n");
  }
  
  /* Двойной цикл 5×5, эмулирующий сканирование матрицы датчиков 
  (int matrix[5][5] с случайными числами 0-100). 
  Найти первую ячейку со значением > 90 и 
  выйти из обоих циклов сразу — реализовать через goto 
  (правильный, «вперёд», паттерн). */
  int minM = 0;
  int maxM = 100;
  int lineM = 5;
  int columnM = 5;
  int first_matrix[lineM][columnM];
  
  not_find:
    for(int i = 0; i < lineM; i++) {
      for(int j = 0; j < columnM; j++) {
        first_matrix[i][j] = minM + arc4random_uniform(maxM - minM + 1);
      }
    }
  
  int find_number = 0;
  for(int i = 0; i < lineM; i++) {
    for(int j = 0; j < columnM; j++) {
      if(first_matrix[i][j] <= 90) continue;
      if(first_matrix[i][j] > 90) {
        find_number = first_matrix[i][j];
        goto ended;
      }
    }
  }
  
  printf("No values greater than 90 were found in the matrix.\n");
  printf("Shell we try again? 1 - yes 0 - no\n");
  int x;
  int result = scanf("%d", &x);
  if (result != 1) {
    goto ended;
  }
  if(find_number == 0) goto not_find;
  
  ended:
    if(find_number == 0) {
      printf("Bye");
    } else {
      printf("Find number in matrix: %d\n", find_number);
    }
  
  /* do-while меню в консоли: выводит пункты 
  1) сканировать 2) выход, 
  крутится пока пользователь не введёт 2. */
  
  
  return 0;
}
