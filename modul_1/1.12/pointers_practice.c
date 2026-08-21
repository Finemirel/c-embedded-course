#include <stdio.h>

void swap(int *a, int *b);

int main(void) {
  int a = 0;
  int *pz = &a;
  printf("%p\n", (void*)&a);
  printf("%d\n", *pz);
  
  *pz = 99;
  printf("%d\n", a);
  
  int one = 23;
  int two = 45;
  printf("One = %d, and two = %d\n", one, two);
  swap(&one, &two);
  printf("One = %d, and two = %d\n", one, two);
  
  printf("Pointer size = %zu, and size int = %zu\n", sizeof(pz), sizeof(a));
  
  return 0;
}

void swap(int *pa, int *pb) {
  int m = *pa;
  *pa = *pb;
  *pb = m;
}
