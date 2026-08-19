#include <stdio.h>
#include <math.h>

int main(void) {
  int a = 6, b = 3;
  char f = '+';
  printf("6+3= %d\n", (a + b));
  printf("6-3= %d\n", (a - b));
  printf("6*3= %d\n", (a * b));
  printf("6/3= %f\n", (double)a / b);
  printf("6%%3= %d\n", (a % b));
  
  int x = 5, y = 9;
  printf("5&9 %d\n", (x & y));
  printf("5|9 %d\n", (x | y));
  
  printf("%d\n", (x > 3) && (y < 10));
  
  int i = 5;
  printf("%d\n", i++); // что выведет?
  printf("%d\n", i);   // а теперь?
  int j = 5;
  printf("%d\n", ++j); // что выведет?
  
  return 0;
}
