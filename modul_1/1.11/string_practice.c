#include <stdio.h>
#include <stddef.h>   // for size_t
#include <string.h>
#include <stdbool.h>

size_t my_strlen_before_size(const char *s, size_t size);
bool can_copy_safely(const char *src, size_t max_len);
bool safe_copy(char *dst, size_t dst_size, const char *src);
void print_string_before_size(const char *s, size_t size);


int main(void) {
  char str1[] = "Hello CLAUDE!";
  size_t count = my_strlen_before_size(str1, 1000);
  printf("Symbols is %zu\nLenth array chars is %zu\n", count, count + 1);
  count = strlen(str1);
  printf("Symbols is %zu\nLenth array chars is %zu\n", count, count + 1);
  
  char name[20];
  fgets(name, 20, stdin);
  print_string_before_size(name, 20);
  
  
  if(strchr(name, '\n') != NULL) {
    char *p;
    p = strchr(name, '\n');
    *p = '\0';
  }
  print_string_before_size(name, 20);
  printf("\n");
  
  char greeting[30] = "Hello, ";
  if(strchr(greeting, '\0') != NULL) {
    char *p;
    p = strchr(greeting, '\0');
    if(!safe_copy(p, sizeof(greeting) - (p - greeting), name)) {
      printf("Don't safely");
    }
  }
  print_string_before_size(greeting, 30);
  printf("\n");
  
  char user_name[20];
  fgets(user_name, 20, stdin);
  print_string_before_size(user_name, 20);
  
  if(strchr(user_name, '\n') != NULL) {
    char *p;
    p = strchr(user_name, '\n');
    *p = '\0';
  }
  
  if(strcmp(name, user_name) == 0) {
    printf("Your name %s and your username %s is same!\n", name, user_name);
  } else {
    printf("Your name %s and your username %s is diffrent!\n", name, user_name);
  }
  
  char buf[5];
  strcpy(buf, "Hello World"); // строка длиннее 5 байт — переполнение буфера, UB
  printf("%s\n", buf);
  
  
  return 0;
}


size_t my_strlen_before_size(const char *s, size_t size) {
  size_t size_len = 0;
  while(size_len < size && s[size_len] != '\0') {
    size_len++;
  }
  return size_len;
}

bool can_copy_safely(const char *src, size_t max_len) {
  size_t size_len = 0;
  while(size_len < max_len) {
    if(src[size_len] == '\0') {
      return true;
    }
    size_len++;
  }
  return false;
}

bool safe_copy(char *dst, size_t dst_size, const char *src) {
  if(can_copy_safely(src, dst_size)) {
    strcpy(dst, src);
    return true;
  } else {
    return false;
  }
}

void print_string_before_size(const char *s, size_t size) {
  size_t size_len = 0;
  while(size_len < size && s[size_len] != '\0') {
    printf("%c", s[size_len]);
    size_len++;
  }
}
