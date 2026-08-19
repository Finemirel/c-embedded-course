#include <stdio.h>
#include <stddef.h>

int main() {
  signed char s_char;
  unsigned char u_char;
  short s_short;
  unsigned short u_short;
  long s_long;
  unsigned long u_long;
  
  printf(" s_char = %zu,\n u_char = %zu,\n short = %zu,\n u_short = %zu,\n s_long = %zu,\n u_long = %zu\n", sizeof(s_char), sizeof(u_char), sizeof(s_short), sizeof(u_short), sizeof(s_long), sizeof(u_long));

  u_char = -1;
  printf(" %d\n", u_char);
  
  s_char = 200;
  printf(" %d\n", s_char);

  return 0;
}
