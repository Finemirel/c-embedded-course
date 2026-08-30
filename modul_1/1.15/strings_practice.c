#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

size_t my_strlen(const char * s);

/**
 *  Create copy string in heap.
 * @return  pointer on new string, or NULL if memory is not enough.
 * @note    OWNERSHIP is transferred to the caller: 
 *          the result must be freed with free_and_null().
 */
char * my_str_dup(const char * src);

/**
 *  Create one string from two strings.
 * @return  pointer on new string, or NULL if memory is not enough.
 * @note    OWNERSHIP is transferred to the caller: 
 *          the result must be freed with free_and_null().
 */
char * str_concat_new(const char *a, const char *b);
void free_and_null(char **p);
void to_upper_inplace(char *s);

int main(void) {
  const char * ps = "Embedded";
  size_t len = my_strlen(ps);
  printf("%zu\n", len);
  printf("String ps: %s\n", ps);
  char * copy = my_str_dup(ps);
  if (copy == NULL) {
    fprintf(stderr, "allocation failed\n");
    return 1;
  }
  printf("String copy: %s\n", copy);
  *copy = 'X';
  printf("String ps: %s\n", ps);
  printf("String copy: %s\n", copy);
  char * string_cont = str_concat_new("STM", "32");
  if (string_cont == NULL) {
    fprintf(stderr, "allocation failed\n");
    return 1;
  }
  printf("String string_cont: %s\n", string_cont);
  
  char * string_cont_empty = str_concat_new("STM", "");
  if (string_cont_empty == NULL) {
    fprintf(stderr, "allocation failed\n");
    return 1;
  } 
  printf("String string_cont_empty: %s\n", string_cont_empty);
  
  printf("String copy: %s\n", copy);
  
  char buf[] = "hello";
  to_upper_inplace(buf);
  printf("String buf: %s\n", buf);
  
  free_and_null(&copy);
  free_and_null(&string_cont);
  free_and_null(&string_cont_empty);
  return 0;
}

size_t my_strlen(const char * s) {
  const char * p = s;
  while(*s != '\0') {
    s += 1;
  }
  return (s-p);
}

char * my_str_dup(const char * src) {
  size_t count = my_strlen(src);
  char * pointer = malloc(sizeof(char) * (count + 1) );
  if (pointer == NULL) {
    return NULL;
  }
  char * point = pointer;
  while(*src != '\0') {
    *point = *src;
    src += 1;
    point += 1;
  }
  *point = '\0';
  return pointer;
}

char * str_concat_new(const char *a, const char *b) {
  size_t count = my_strlen(a) + my_strlen(b);
  char * pointer = malloc(sizeof(char) * (count + 1));
  if (pointer == NULL) {
    return NULL;
  }
  char * point = pointer;
  while(*a != '\0') {
    *point = *a;
    a += 1;
    point += 1;
  }
  while(*b != '\0') {
    *point = *b;
    b += 1;
    point += 1;
  }
  *point = '\0';
  return pointer;
}

void free_and_null(char **p) {
  free(*p);
  *p = NULL;
}

void to_upper_inplace(char *s) {
   while(*s != '\0') {
    *s = toupper((unsigned char)*s);
    s += 1;
  }
}

