#include <stdio.h>
#include <stddef.h>

int main() {
  char a_char;
  short b_short;
  int c_int;
  long d_long;
  long long e_long_long;
  float f_float;
  double g_double;
  size_t h_size;
  void* pointer;
  
  printf(" char = %zu,\n short = %zu,\n int = %zu,\n long = %zu,\n long long = %zu,\n float = %zu,\n double = %zu,\n size_t = %zu,\n void* = %zu\n", sizeof(a_char), sizeof(b_short), sizeof(c_int), sizeof(d_long), sizeof(e_long_long), sizeof(f_float), sizeof(g_double), sizeof(h_size), sizeof(pointer));

  return 0;
}
