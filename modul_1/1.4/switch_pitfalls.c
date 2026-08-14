#include <stdio.h>

int main(void) {
  int param = 0;
  
  printf("Enter your parameter from 0 to 2: ");
  scanf("%d", &param);
  
  switch(param) {
    case 0:
      printf("OK\n");
      break;
    case 1:
      printf("WARNING\n");
      break;
    case 2:
      printf("ERROR\n");
      break;
    default:
      printf("UNKNOWN CODE\n");
  }
  
  
  return 0;
}
