#include <stdio.h>

void count_down(int n);
int fib(int n);
void infinite_recursion(int depth);

int main(void) {
  //count_down(5);
  //printf("%d\n", fib(10));
  infinite_recursion(0);
  return 0;
}

void count_down(int n) {
  if(n > 0) {
    printf("%d\n", n);
    count_down(n-1);
  }
  printf("return to %d\n", n);
}

int fib(int n) {
  printf("%d\n",n);
  if (n <= 1) {
        printf("%d\n",n);
        return n;
    }
    printf("%d\n",n);
    return fib(n - 1) + fib(n - 2);
}

void infinite_recursion(int depth) {
  printf("%d\n", depth);
  infinite_recursion(depth + 1);
}
