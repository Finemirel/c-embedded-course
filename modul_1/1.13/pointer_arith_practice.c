#include <stdio.h>

#define EL 6

void print_via_pointer(const int *arr, size_t n);
int sum_via_pointer(const int *arr, size_t n);

int main(void) {
  int nums[EL] = {5, 10, 15, 20, 25, 30};
  int *p = nums;
  print_via_pointer(p, EL);
  int summa = sum_via_pointer(p, EL);
  printf("Summa whole numbers of array is %d.\n", summa);
  printf("Size whole array 6 el type int (4 bytes) is %zu bytes.\n", sizeof(nums));
  printf("Size pointer is %zu bytes.\n", sizeof(p));
  printf("%p\n", nums + 5);
  printf("%p\n", &nums[5]);
  if(nums + 5 == &nums[5]) {
    printf("Pointers is equals\n");
  } else {
    printf("Pointers is not equals\n");
  }
  return 0;
}

void print_via_pointer(const int *arr, size_t n) {
  printf("Elements of array: ");
  for(int i = 0; i < n; i++) {
    printf("%d ", *(arr + i));
  }
  printf("\n");
  printf("Elements of array: ");
  for(int j = 0; j < n; j++) {
    printf("%d ", arr[j]);
  }
  printf("\n");
}

int sum_via_pointer(const int *arr, size_t n) {
  int sum = 0;
  while(n--) {
    sum = sum + *(arr++);
  }
  return sum;
}

