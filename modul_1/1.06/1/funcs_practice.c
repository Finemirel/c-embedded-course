#include <stdio.h>

int max_of_three(int a, int b, int c);
void try_to_double(int x);

int main(void) {
  int first_number;
  printf("Enter your first number: ");
  scanf("%d", &first_number);
  int second_number;
  printf("Enter your second number: ");
  scanf("%d", &second_number);
  int third_number;
  printf("Enter your third number: ");
  scanf("%d", &third_number);
  printf("Max digit is %d\n", max_of_three(first_number, second_number, third_number));
  
  printf("\nNext finction!\n\n");

  int your_number;
  printf("Enter your number: ");
  scanf("%d", &your_number);
  try_to_double(your_number);
  //function try_to_double don't change your_number
  printf("Your entered digit is %d\n", your_number);
}

int max_of_three(int a, int b, int c) {
  int max = a;
    if (b > max) max = b;
    if (c > max) max = c;
    return max;
}

void try_to_double(int x) {
  printf("Your digit is %d\n", (x*2));
}
