#include <stdio.h>

int total_calls = 0;

void log_call(void);
void generate_id(void);

int main(void) {
  log_call();
  log_call();
  log_call();
  
  generate_id();
  generate_id();
  generate_id();
  
  return 0;
}

void log_call(void) {
  ++total_calls;
  printf("%d\n", total_calls);
}

void generate_id(void) {
  static int next_id = 1;
  printf("%d\n", next_id);
  ++next_id;
}
