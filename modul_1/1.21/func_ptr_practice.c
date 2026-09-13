#include <stdio.h>
#include <stdlib.h>

int add(int, int);
int sub(int, int);
int mul(int, int);

//typedef int (*op)(int, int);
typedef int (*BinaryOp)(int, int);
static const BinaryOp ops[] = {add, sub, mul};
static const char * namesBop[] = {"+", "-", "*"};

int calc(int a, int b, BinaryOp op);
void for_each(const int *arr, size_t n, void (*action)(int)); //TODO
void print_number(int);
void print_sqrt(int);

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <part 1-5>\n", argv[0]);
    return 1;
  }
  char *end;
  long part = strtol(argv[1], &end, 10);
  if (*end != '\0') {
    fprintf(stderr, "First argument not a number: %s\n", argv[1]);
    return 1;
  }
  
  switch (part) {
    case 1: {
      //op opp = add;
      BinaryOp bop = add;
      int a = 17, b = 4;
      printf("Part %ld\n", part);
      printf("a + b = %d\n", bop(a, b));
      printf("a + b = %d\n", (*bop)(a, b));
      printf("(void *)add = %p\n", (void *)add);
      printf("(void *)&add = %p\n", (void *)&add);
      printf("Comparison result = %d\n", (void *)add == (void *)&add);
      /*
      int *f(int) это функция принимающая int и возвращющая int, 
      а int (*f)(int) это указатель на функцию которая принимает int и возвращает int;
      */
      break;
    }
    case 2: {
      printf("Part %ld\n", part);
      int paramOne = 0, paramTwo = 0;
      printf("Enter first number: ");
      scanf("%d", &paramOne);
      printf("\33[1A");
      printf("\33[2K");
      printf("First number is %d, enter second number: ", paramOne);
      scanf("%d", &paramTwo);
      printf("\33[1A");
      printf("\33[2K");
      for (size_t i = 0; i < sizeof(namesBop) / sizeof(namesBop[0]); i++) {
        printf("%d %s %d = %d\n", paramOne, namesBop[i], paramTwo, ops[i](paramOne, paramTwo));
      }
      BinaryOp biop = NULL;
      int myNumber = calc(paramOne, paramTwo, biop);
      printf("My number = %d\n", myNumber);
      break;
    }
    case 3: {
      printf("Part %ld\n", part);
      const int arr[] = {1, 2, 3, 4, 5, 6, 7, 8, 9};
      for_each(arr, sizeof(arr)/sizeof(arr[0]), print_number);
      for_each(arr, sizeof(arr)/sizeof(arr[0]), print_sqrt);
      break;
    }
    case 4: {
      printf("Part %ld\n", part);
      //TODO
      break;
    }
    case 5: {
      printf("Part %ld\n", part);
      //TODO
      break;
    }
    case 6: {
      printf("Part %ld\n", part);
      //TODO
      break;
    }
    default:
        fprintf(stderr, "Unknown part: %ld\n", part);
        return 1;
    }
  
  
  return 0;
}

int add(int a, int b) {
  return a + b;
}

int sub(int a, int b) {
  return a - b;
}

int mul(int a, int b) {
  return a * b;
}

int calc(int a, int b, BinaryOp op) {
  if(op == NULL) {
    fprintf(stderr, "op is NULL\n");
    return 0;
  }
  return op(a, b);
}

void for_each(const int *arr, size_t n, void (*action)(int)) {
  for(size_t i = 0; i < n; i++) {
    printf("Result with %d = ", arr[i]);
    action(arr[i]);
  }
}
void print_number(int a) {
  printf("number is %d\n", a);
}
void print_sqrt(int a) {
  printf("sqrt is %d\n", a * a);
}
