#include <stdio.h>
#include <stddef.h>   // for size_t
#include <string.h>

size_t my_strlen_before_size(const char *s, size_t size);


int main(void) {
  char str1[] = "Hello CLAUDE!";
  size_t count = my_strlen_before_size(str1, 1000);
  printf("Symbols is %zu\nLenth array chars is %zu\n", count, count + 1);


  return 0;
}


size_t my_strlen_before_size(const char *s, size_t size) {
  size_t size_len = 0;
  while(size_len < size && s[size_len] != '\0') {
    size_len++;
  }
  return size_len;
}
